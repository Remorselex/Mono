# CMake Guide для Node.js Addons

Руководство по настройке CMake для создания Node.js нативных модулей (C++ addons).

## 📚 Основы

### Что такое Node.js Addon?

Node.js addon - это динамически подключаемая библиотека (.node файл), написанная на C++, которая может быть загружена в Node.js через `require()` или `import()`.

### Зачем использовать CMake вместо node-gyp?

| node-gyp (GYP) | CMake |
|----------------|-------|
| ✅ Стандарт для Node.js | ✅ Мощная система сборки |
| ✅ Простая настройка | ✅ Переиспользование существующих CMakeLists.txt |
| ❌ Ограниченные возможности | ✅ Поддержка сложных проектов |
| ❌ Еще один build tool | ✅ Единая система для всего монорепо |
| ❌ Сложно интегрировать с существующим C++ | ✅ Легко подключить внешние библиотеки |

---

## 🚀 Быстрый старт

### 1. Установка зависимостей

```bash
# cmake-js - инструмент для сборки Node.js addons через CMake
pnpm add -D cmake-js

# node-addon-api - C++ обертки для Node-API
pnpm add node-addon-api
```

### 2. Минимальный CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.15)
project(native)

set(CMAKE_CXX_STANDARD 17)

# Получаем путь к node-addon-api
execute_process(
  COMMAND node -p "require('node-addon-api').include"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Include directories
include_directories(${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})

# Исходники
file(GLOB SOURCE_FILES "src/native/*.cpp")

# Создаем .node библиотеку
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
```

### 3. Сборка

```bash
# Сборка
pnpm build  # или: cmake-js compile

# Пересборка (очистка + сборка)
pnpm rebuild  # или: cmake-js rebuild

# Очистка
pnpm clean  # или: cmake-js clean
```

---

## 📖 Детальное объяснение CMakeLists.txt

### Базовая настройка

```cmake
cmake_minimum_required(VERSION 3.15)  # Минимальная версия CMake
project(native)                        # Имя проекта (будет native.node)

set(CMAKE_CXX_STANDARD 17)            # C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # Обязательно C++17
```

### Получение пути к node-addon-api

```cmake
execute_process(
  COMMAND node -p "require('node-addon-api').include"
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
```

**Что происходит:**
- Запускается Node.js
- Выполняется `require('node-addon-api').include`
- Результат сохраняется в переменную `NODE_ADDON_API_DIR`

### Include directories

```cmake
include_directories(${NODE_ADDON_API_DIR})  # node-addon-api headers
include_directories(${CMAKE_JS_INC})        # Node.js headers (от cmake-js)
include_directories(../../Cpp/include)      # Ваш C++ код
```

### Сбор исходников

```cmake
# Вариант 1: Все .cpp файлы в папке
file(GLOB SOURCE_FILES "src/native/*.cpp")

# Вариант 2: Явно перечислить
set(SOURCE_FILES
  src/native/addon.cpp
  src/native/math.cpp
  src/native/crypto.cpp
)
```

### Создание библиотеки

```cmake
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
```

- `SHARED` - динамическая библиотека
- `${CMAKE_JS_SRC}` - дополнительные файлы от cmake-js

### Настройка свойств

```cmake
set_target_properties(${PROJECT_NAME} PROPERTIES 
  PREFIX ""           # Убираем префикс "lib"
  SUFFIX ".node"      # Расширение .node вместо .so/.dylib/.dll
  CXX_STANDARD 17
)
```

### Линковка

```cmake
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
```

Линкуем с Node.js библиотеками.

---

## 🔧 Продвинутые настройки

### Подключение внешних библиотек

```cmake
# Пример: подключение вашего C++ кода из Mono/Cpp
include_directories(${CMAKE_SOURCE_DIR}/../../Cpp/include)

# Если у вас есть скомпилированная библиотека
target_link_libraries(${PROJECT_NAME} 
  ${CMAKE_JS_LIB}
  ${CMAKE_SOURCE_DIR}/../../Cpp/build/libmylib.a
)
```

### Условная компиляция для разных платформ

```cmake
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_RPATH ON
    BUILD_WITH_INSTALL_RPATH ON
  )
elseif(WIN32)
  # Windows специфичные настройки
  target_compile_definitions(${PROJECT_NAME} PRIVATE WIN32_LEAN_AND_MEAN)
elseif(UNIX)
  # Linux специфичные настройки
  target_link_libraries(${PROJECT_NAME} pthread)
endif()
```

### Оптимизация

```cmake
# Release build с оптимизацией
if(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_options(${PROJECT_NAME} PRIVATE
    -O3              # Максимальная оптимизация
    -march=native    # Оптимизация под текущий процессор
  )
endif()

# Debug build с отладочной информацией
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_options(${PROJECT_NAME} PRIVATE
    -g               # Отладочная информация
    -O0              # Без оптимизации
  )
endif()
```

### Использование внешних пакетов

```cmake
# Пример: OpenSSL
find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} 
  ${CMAKE_JS_LIB}
  ${OPENSSL_LIBRARIES}
)
```

---

## 🎯 Примеры использования

### Пример 1: Простой addon

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.15)
project(math_addon)

set(CMAKE_CXX_STANDARD 17)

execute_process(
  COMMAND node -p "require('node-addon-api').include"
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})

add_library(${PROJECT_NAME} SHARED src/addon.cpp ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
```

**src/addon.cpp:**
```cpp
#include <napi.h>

Napi::Number Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  double a = info[0].As<Napi::Number>().DoubleValue();
  double b = info[1].As<Napi::Number>().DoubleValue();
  return Napi::Number::New(env, a + b);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("add", Napi::Function::New(env, Add));
  return exports;
}

NODE_API_MODULE(math_addon, Init)
```

### Пример 2: Addon с несколькими файлами

**Структура:**
```
node-addons/
├── CMakeLists.txt
├── src/
│   ├── addon.cpp       # Главный файл
│   ├── math.cpp        # Математические функции
│   ├── math.h
│   ├── crypto.cpp      # Криптография
│   └── crypto.h
```

**CMakeLists.txt:**
```cmake
cmake_minimum_required(VERSION 3.15)
project(advanced_addon)

set(CMAKE_CXX_STANDARD 17)

execute_process(
  COMMAND node -p "require('node-addon-api').include"
  OUTPUT_VARIABLE NODE_ADDON_API_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

include_directories(${NODE_ADDON_API_DIR})
include_directories(${CMAKE_JS_INC})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE_FILES
  src/addon.cpp
  src/math.cpp
  src/crypto.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
```

---

## 🐛 Отладка

### Сборка в Debug режиме

```bash
# Установить режим Debug
cmake-js compile --debug

# Или через переменную окружения
CMAKE_BUILD_TYPE=Debug cmake-js compile
```

### Просмотр команд компиляции

```bash
cmake-js compile --verbose
```

### Проверка путей

```bash
# Проверить путь к node-addon-api
node -p "require('node-addon-api').include"

# Проверить версию Node.js
node --version

# Проверить версию CMake
cmake --version
```

---

## 📚 Полезные ссылки

### Официальная документация

- **Node-API (N-API)**: https://nodejs.org/api/n-api.html
  - Стабильный ABI для нативных модулей
  
- **node-addon-api**: https://github.com/nodejs/node-addon-api
  - C++ обертки для Node-API
  - Документация: https://github.com/nodejs/node-addon-api/blob/main/doc/
  
- **cmake-js**: https://github.com/cmake-js/cmake-js
  - CMake для Node.js addons
  
- **CMake Documentation**: https://cmake.org/documentation/
  - Официальная документация CMake

### Туториалы и примеры

- **Node.js C++ Addons Guide**: https://nodejs.org/api/addons.html
- **node-addon-api Examples**: https://github.com/nodejs/node-addon-api/tree/main/test
- **CMake Tutorial**: https://cmake.org/cmake/help/latest/guide/tutorial/index.html

### Производительность

- **V8 Optimization**: https://v8.dev/docs
- **Node.js Performance**: https://nodejs.org/en/docs/guides/simple-profiling/

### Сообщество

- **Node.js Addons Discord**: https://discord.gg/nodejs
- **Stack Overflow**: https://stackoverflow.com/questions/tagged/node-addon-api

---

## 💡 Best Practices

### 1. Обработка ошибок

```cpp
Napi::Value SafeFunction(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  
  try {
    // Ваш код
    if (info.Length() < 1) {
      throw Napi::Error::New(env, "Expected at least 1 argument");
    }
    
    // ...
    
  } catch (const std::exception& e) {
    Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();
    return env.Null();
  }
}
```

### 2. Проверка типов

```cpp
if (!info[0].IsNumber()) {
  Napi::TypeError::New(env, "Expected a number").ThrowAsJavaScriptException();
  return env.Null();
}
```

### 3. Асинхронные операции

```cpp
// Используйте AsyncWorker для длительных операций
class MyAsyncWorker : public Napi::AsyncWorker {
  // ...
};
```

### 4. Управление памятью

```cpp
// Используйте RAII
// Избегайте ручного new/delete
// Используйте std::unique_ptr, std::shared_ptr
```

---

## 🔥 Частые проблемы

### Проблема: "Cannot find module '../build/Release/native.node'"

**Решение:**
```bash
# Пересоберите addon
pnpm rebuild
```

### Проблема: "node-addon-api not found"

**Решение:**
```bash
# Установите зависимости
pnpm install
```

### Проблема: CMake не находит компилятор

**macOS:**
```bash
xcode-select --install
```

**Linux:**
```bash
sudo apt-get install build-essential cmake
```

---

**Happy coding with CMake! 🚀**

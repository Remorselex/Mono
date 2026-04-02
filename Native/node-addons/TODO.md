# TODO: Настройка node-addons с CMake

## ✅ Что уже сделано

- ✅ Структура папок создана
- ✅ C++ код addon.cpp готов
- ✅ TypeScript код index.ts готов

## 📝 Что нужно сделать вам

### 1. Обновите package.json

Замените содержимое на:

```json
{
  "name": "@mono/node-addons",
  "version": "1.0.0",
  "private": true,
  "type": "module",
  "scripts": {
    "dev": "tsx watch src/index.ts",
    "build": "cmake-js compile",
    "rebuild": "cmake-js rebuild",
    "clean": "cmake-js clean"
  },
  "dependencies": {
    "node-addon-api": "^8.1.0"
  },
  "devDependencies": {
    "@types/node": "^20.14.15",
    "cmake-js": "^7.3.0",
    "tsx": "^4.17.0",
    "typescript": "^5.5.4"
  }
}
```

**Изменения:**
- Убрали `node-gyp` и `gypfile`
- Добавили `cmake-js`
- Изменили скрипты на CMake

---

### 2. Создайте CMakeLists.txt

Создайте файл `CMakeLists.txt` в корне `node-addons/`:

```cmake
cmake_minimum_required(VERSION 3.15)
project(native)

# C++ стандарт
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
include_directories(${CMAKE_SOURCE_DIR}/../../Cpp/include)

# Исходники
file(GLOB SOURCE_FILES "src/native/*.cpp")

# Создаем библиотеку
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})

# Настройки для Node.js addon
set_target_properties(${PROJECT_NAME} PROPERTIES 
  PREFIX "" 
  SUFFIX ".node"
  CXX_STANDARD 17
)

# Линковка
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Определяем NAPI_VERSION
target_compile_definitions(${PROJECT_NAME} PRIVATE NAPI_VERSION=8)

# Для macOS
if(APPLE)
  set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_RPATH ON
    BUILD_WITH_INSTALL_RPATH ON
  )
endif()
```

---

### 3. Создайте tsconfig.json

```json
{
  "compilerOptions": {
    "target": "ES2022",
    "module": "NodeNext",
    "moduleResolution": "NodeNext",
    "lib": ["ES2022"],
    "outDir": "./dist",
    "rootDir": "./src",
    "strict": true,
    "esModuleInterop": true,
    "skipLibCheck": true,
    "types": ["node"]
  },
  "include": ["src/**/*.ts"],
  "exclude": ["node_modules", "build", "src/native"]
}
```

---

### 4. Удалите binding.gyp

```bash
rm binding.gyp
```

Он больше не нужен, так как используем CMake.

---

### 5. Установите зависимости

```bash
cd /Users/helgostrovskiy/CLionProjects/Mono/Native/node-addons
pnpm install
```

---

### 6. Соберите addon

```bash
pnpm build
```

Если все настроено правильно, вы увидите:
```
[cmake-js] Compiling...
[cmake-js] Build succeeded!
```

---

### 7. Запустите

```bash
pnpm dev
```

Должно вывести:
```
🔬 Testing Node.js C++ Addon (CMake build)

✅ C++ Addon loaded successfully!
   2 + 3 = 5
   10 + 25 = 35
```

---

## 🐛 Если что-то пошло не так

### CMake не найден

```bash
brew install cmake
```

### Компилятор не найден (macOS)

```bash
xcode-select --install
```

### node-addon-api не найден

```bash
pnpm install
```

### Подробный вывод ошибок

```bash
pnpm build -- --verbose
```

---

## 📚 Дополнительно

Прочитайте `../CMAKE_GUIDE.md` для:
- Детального объяснения каждой строки CMakeLists.txt
- Продвинутых настроек
- Примеров использования
- Полезных ссылок

---

**Удачи! 🚀**

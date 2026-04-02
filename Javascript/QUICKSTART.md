# 🚀 Quick Start Guide

Быстрый старт для работы с JavaScript/TypeScript монорепозиторием.

## 📦 Установка

### 1. Установите pnpm (если еще не установлен)

```bash
# Через npm
npm install -g pnpm

# Или через Homebrew
brew install pnpm

# Проверка
pnpm --version
```

### 2. Установите зависимости

```bash
cd Javascript
pnpm install
```

### 3. Создайте React приложение (первый раз)

```bash
cd frontend/frameworks
pnpm create vite . --template react-ts
# Следуйте инструкциям Vite
```

---

## 🎯 Команды для запуска

### Запуск всех сервисов параллельно

```bash
pnpm dev
```

Запустит:
- Frontend Playground (http://localhost:5174)
- Backend (http://localhost:3001)
- Node Addons (консоль)

### Запуск отдельных сервисов

```bash
# Vanilla JS/TS Playground
pnpm dev:playground
# → http://localhost:5174

# Backend API
pnpm dev:backend
# → http://localhost:3001

# Node.js C++ Addons
pnpm dev:addons
# → Консольный вывод
```

### Или напрямую в папке

```bash
# Frontend Playground
cd frontend/playground
pnpm dev

# Frontend Frameworks (React)
cd frontend/frameworks
pnpm dev

# Backend
cd backend
pnpm dev

# Node Addons
cd ../Native/node-addons
pnpm dev
```

---

## 🔨 Сборка проектов

### Сборка всех проектов

```bash
pnpm build
```

### Сборка C++ Addons

```bash
# Первая сборка
pnpm build:addons

# Пересборка (clean + build)
pnpm rebuild:addons
```

### Сборка отдельного проекта

```bash
cd backend
pnpm build
```

---

## 🧪 Работа с C++ Addons

### Требования

- **CMake** (версия 3.15+)
- **C++ компилятор** (Xcode на macOS, GCC/Clang на Linux)
- **Node.js** (версия 20+)

### Установка инструментов (macOS)

```bash
# Xcode Command Line Tools
xcode-select --install

# CMake (если нет)
brew install cmake

# Проверка
cmake --version
```

### Сборка addon

```bash
cd ../Native/node-addons

# Установка зависимостей
pnpm install

# Сборка
pnpm build

# Запуск
pnpm dev
```

### Отладка addon

```bash
# Сборка в Debug режиме
pnpm build -- --debug

# Verbose вывод
pnpm build -- --verbose
```

---

## 📁 Структура проекта

```
Mono/
├── Javascript/
│   ├── frontend/
│   │   ├── frameworks/      # React приложение
│   │   └── playground/      # Vanilla JS/TS
│   ├── backend/             # Node.js API
│   ├── package.json         # Корневой package.json
│   └── pnpm-workspace.yaml
├── Native/
│   ├── node-addons/         # C++ addons для Node.js
│   ├── wasm/                # WebAssembly модули (TODO)
│   └── CMAKE_GUIDE.md       # Гайд по CMake
└── Cpp/                     # Основной C++ код
```

---

## 🔗 API Endpoints (Backend)

После запуска `pnpm dev:backend`:

- **GET** `http://localhost:3001/` - Hello message
- **GET** `http://localhost:3001/api/health` - Health check

---

## 🧹 Очистка

```bash
# Очистить все build артефакты
pnpm clean

# Удалить node_modules
rm -rf node_modules frontend/*/node_modules backend/node_modules ../Native/node-addons/node_modules

# Переустановить зависимости
pnpm install
```

---

## 📚 Полезные ссылки

- **CMake Guide**: `../Native/CMAKE_GUIDE.md`
- **Node-API Docs**: https://nodejs.org/api/n-api.html
- **pnpm Workspaces**: https://pnpm.io/workspaces
- **Vite Docs**: https://vitejs.dev/

---

## 💡 Советы

1. **Используйте `pnpm` вместо `npm`** - быстрее и экономит место
2. **Запускайте `pnpm dev` из корня** - все сервисы стартуют параллельно
3. **C++ addons собирайте через CMake** - единая система сборки
4. **Читайте CMAKE_GUIDE.md** - там подробные примеры

---

## 🐛 Частые проблемы

### "command not found: pnpm"

```bash
npm install -g pnpm
```

### "Cannot find module '../build/Release/native.node'"

```bash
pnpm build:addons
```

### "CMake not found"

```bash
brew install cmake
```

### Порт уже занят

```bash
# Найти процесс на порту 3001
lsof -ti:3001

# Убить процесс
kill -9 $(lsof -ti:3001)
```

---

**Happy coding! 🚀**

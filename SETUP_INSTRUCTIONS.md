# 🎯 Инструкции по настройке монорепозитория

## ✅ Что уже готово

### Структура проекта
```
Mono/
├── Cpp/                    # Ваш C++ код
├── Javascript/             # JavaScript/TypeScript workspace
│   ├── frontend/
│   │   ├── playground/     # ✅ Vanilla TS готов
│   │   └── frameworks/     # ⚠️  Нужно создать React
│   ├── backend/            # ✅ Fastify готов
│   ├── package.json        # ✅ Скрипты настроены
│   ├── pnpm-workspace.yaml # ✅ Workspace настроен
│   ├── tsconfig.json       # ✅ TypeScript конфиг
│   ├── .eslintrc.js        # ✅ ESLint конфиг
│   ├── QUICKSTART.md       # ✅ Команды для запуска
│   └── README.md           # ✅ Документация
├── Native/                 # Нативные модули
│   ├── node-addons/        # ⚠️  Нужно настроить CMake
│   ├── wasm/               # 📝 TODO
│   ├── CMAKE_GUIDE.md      # ✅ Подробный гайд
│   └── README.md           # ✅ Документация
└── .gitignore              # ✅ Обновлен
```

---

## 📝 Что нужно сделать ВАМ

### Шаг 1: Установите pnpm

```bash
# Выберите один способ:
npm install -g pnpm
# или
brew install pnpm

# Проверка
pnpm --version
```

---

### Шаг 2: Настройте Native/node-addons

**Следуйте инструкциям в:**
```
Native/node-addons/TODO.md
```

**Кратко:**
1. Обновите `package.json` (замените node-gyp на cmake-js)
2. Создайте `CMakeLists.txt`
3. Создайте `tsconfig.json`
4. Удалите `binding.gyp`
5. Установите зависимости: `pnpm install`
6. Соберите: `pnpm build`
7. Запустите: `pnpm dev`

**Подробный гайд по CMake:**
```
Native/CMAKE_GUIDE.md
```

---

### Шаг 3: Создайте React приложение

```bash
cd /Users/helgostrovskiy/CLionProjects/Mono/Javascript/frontend/frameworks
pnpm create vite . --template react-ts
```

Vite создаст готовую структуру React проекта.

---

### Шаг 4: Установите зависимости для всего workspace

```bash
cd /Users/helgostrovskiy/CLionProjects/Mono/Javascript
pnpm install
```

Это установит зависимости для всех пакетов.

---

### Шаг 5: Запустите проекты

```bash
# Из корня Javascript/
pnpm dev
```

Или отдельно:
```bash
pnpm dev:playground   # http://localhost:5174
pnpm dev:backend      # http://localhost:3001
pnpm dev:addons       # Консоль
```

---

## 📚 Документация

### Для быстрого старта:
- **Javascript/QUICKSTART.md** - все команды для запуска

### Для изучения CMake:
- **Native/CMAKE_GUIDE.md** - подробный гайд с примерами

### Для понимания структуры:
- **Javascript/README.md** - про JavaScript workspace
- **Native/README.md** - про нативные модули

---

## 🎓 Рекомендуемый порядок изучения

### 1. Начните с простого
```bash
cd Javascript/frontend/playground
pnpm dev
```
Откройте `src/main.ts` и экспериментируйте с TypeScript.

### 2. Изучите Backend
```bash
cd Javascript/backend
pnpm dev
```
Откройте `src/index.ts` и добавьте новые endpoints.

### 3. Попробуйте React
```bash
cd Javascript/frontend/frameworks
pnpm dev
```
Создавайте компоненты, изучайте React.

### 4. Погрузитесь в C++ addons
```bash
cd Native/node-addons
pnpm build
pnpm dev
```
Читайте `CMAKE_GUIDE.md` и экспериментируйте с C++.

---

## 🔧 Полезные команды

### Из корня Javascript/

```bash
# Запуск
pnpm dev                  # Все сервисы параллельно
pnpm dev:playground       # Только playground
pnpm dev:backend          # Только backend
pnpm dev:addons           # Только C++ addons

# Сборка
pnpm build                # Все проекты
pnpm build:addons         # C++ addons
pnpm rebuild:addons       # Пересборка addons

# Очистка
pnpm clean                # Очистить build артефакты
```

---

## 🐛 Частые проблемы

### "command not found: pnpm"
```bash
npm install -g pnpm
```

### "CMake not found"
```bash
brew install cmake
```

### "Cannot find module '../build/Release/native.node'"
```bash
cd Native/node-addons
pnpm build
```

### Порт уже занят
```bash
# Найти и убить процесс на порту 3001
lsof -ti:3001 | xargs kill -9
```

---

## 💡 Советы

1. **Читайте QUICKSTART.md** - там все команды
2. **Читайте CMAKE_GUIDE.md** - там примеры и объяснения
3. **Используйте TypeScript** - меньше ошибок
4. **Экспериментируйте** - это учебный проект!
5. **Задавайте вопросы** - если что-то непонятно

---

## 🎯 Следующие шаги

После того как все заработает:

1. **Добавьте тесты** - Vitest для JS, Google Test для C++
2. **Создайте shared пакет** - для общего кода
3. **Попробуйте WebAssembly** - компиляция C++ в WASM
4. **Изучите GraphQL** - создайте `frontend/graphql`
5. **Оптимизируйте** - профилируйте и улучшайте производительность

---

## 📖 Что вы изучите

- ✅ **Монорепозиторий** с pnpm workspaces
- ✅ **TypeScript** для фронтенда и бэкенда
- ✅ **React** с Vite
- ✅ **Node.js API** с Fastify
- ✅ **C++ addons** с Node-API
- ✅ **CMake** для сборки нативных модулей
- 📝 **WebAssembly** (планируется)
- 📝 **Assembly** (планируется)

---

**Начните с шага 1 и следуйте инструкциям! Удачи! 🚀**

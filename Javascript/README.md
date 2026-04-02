# JavaScript/TypeScript Workspace

Монорепозиторий для изучения JavaScript/TypeScript технологий.

## 📁 Структура

```
Javascript/
├── frontend/
│   ├── frameworks/      # React приложение (Vite + TypeScript)
│   └── playground/      # Vanilla JS/TS для экспериментов
├── backend/             # Node.js API (Fastify + TypeScript)
├── package.json         # Корневой package.json с скриптами
├── pnpm-workspace.yaml  # Workspace конфигурация
├── tsconfig.json        # Базовый TypeScript конфиг
├── .eslintrc.js         # ESLint конфигурация
├── QUICKSTART.md        # 🚀 Быстрый старт (начните отсюда!)
└── README.md            # Этот файл
```

## 🎯 Цели проекта

1. **Frontend** - изучение React и других фреймворков
2. **Backend** - Node.js API разработка
3. **Native** - интеграция с C++ через addons (см. `../Native/`)
4. **WebAssembly** - низкоуровневые оптимизации (планируется)

## 🚀 Быстрый старт

**Читайте QUICKSTART.md** - там все команды и инструкции!

```bash
# Установка
pnpm install

# Запуск всех сервисов
pnpm dev

# Запуск отдельного сервиса
pnpm dev:playground
pnpm dev:backend
```

## 📦 Пакеты

### @mono/scripts (frontend/playground)
- **Технологии:** Vanilla TypeScript + Vite
- **Порт:** 5174
- **Назначение:** Playground для экспериментов с JS/TS

### @mono/frameworks (frontend/frameworks)
- **Технологии:** React + TypeScript + Vite
- **Порт:** 5173
- **Назначение:** Изучение React и других фреймворков

### @mono/backend
- **Технологии:** Fastify + TypeScript
- **Порт:** 3001
- **Назначение:** REST API сервер

### @mono/node-addons (../Native/node-addons)
- **Технологии:** C++ + Node-API + CMake
- **Назначение:** Нативные модули для оптимизации

## 🔧 Технологии

- **pnpm workspaces** - управление монорепозиторием
- **TypeScript 5.5+** - типизация
- **Vite** - быстрый dev сервер и сборка
- **Fastify** - быстрый веб-фреймворк
- **ESLint** - линтинг кода

## 📚 Документация

- **QUICKSTART.md** - команды для запуска
- **../Native/CMAKE_GUIDE.md** - гайд по CMake для addons
- **../Native/README.md** - про нативные модули

## 🎓 Обучение

### Рекомендуемый порядок изучения:

1. **frontend/playground** - начните с простого Vanilla TS
2. **backend** - изучите Node.js API
3. **frontend/frameworks** - перейдите к React
4. **../Native/node-addons** - низкоуровневые оптимизации

## 🔗 Связь с другими частями монорепо

### C++ код (../Cpp/)
Ваш основной C++ код можно использовать в Node.js через addons:

```cmake
# В Native/node-addons/CMakeLists.txt
include_directories(${CMAKE_SOURCE_DIR}/../../Cpp/include)
```

### WebAssembly (планируется)
Компиляция C++ в WASM для использования в браузере.

### Assembly (планируется)
Низкоуровневые оптимизации на ассемблере.

## 💡 Best Practices

1. **Используйте TypeScript везде** - меньше ошибок
2. **Следуйте ESLint правилам** - единый стиль кода
3. **Тестируйте перед оптимизацией** - не все нужно писать на C++
4. **Читайте документацию** - QUICKSTART.md и CMAKE_GUIDE.md

## 🛠️ Команды

```bash
# Разработка
pnpm dev                  # Все сервисы
pnpm dev:playground       # Только playground
pnpm dev:backend          # Только backend
pnpm dev:addons           # Только addons

# Сборка
pnpm build                # Все проекты
pnpm build:addons         # C++ addons

# Утилиты
pnpm clean                # Очистка
pnpm rebuild:addons       # Пересборка addons
```

## 📈 Планы развития

- [ ] Добавить GraphQL (`frontend/graphql`)
- [ ] Создать `shared` пакет для общего кода
- [ ] Добавить тесты (Vitest)
- [ ] WebAssembly модули
- [ ] Assembly оптимизации
- [ ] CI/CD pipeline

## 🤝 Структура монорепозитория

```
Mono/
├── Cpp/           # C++ проекты
├── Javascript/    # 👈 Вы здесь
├── Native/        # Нативные модули (C++ addons, WASM)
└── ...            # Другие языки (Go, Rust, Python...)
```

---

**Начните с QUICKSTART.md! 🚀**

# Native Modules

Нативные модули для различных языков и платформ.

## 📁 Структура

```
Native/
├── node-addons/        # Node.js C++ addons (CMake)
├── wasm/               # WebAssembly модули (TODO)
└── CMAKE_GUIDE.md      # Подробный гайд по CMake
```

---

## 🎯 node-addons

Node.js нативные модули, написанные на C++ и собираемые через CMake.

### Быстрый старт

```bash
cd node-addons
pnpm install
pnpm build
pnpm dev
```

### Что внутри

- **C++ код** в `src/native/`
- **TypeScript** в `src/`
- **CMakeLists.txt** для сборки
- **package.json** с скриптами

### Связь с Mono/Cpp

В `CMakeLists.txt` настроен путь к `../../Cpp/include` - вы можете использовать свой C++ код из основного репозитория!

```cmake
include_directories(${CMAKE_SOURCE_DIR}/../../Cpp/include)
```

---

## 🌐 wasm (TODO)

WebAssembly модули для использования в браузере и Node.js.

### Планы

- Компиляция C/C++ в WASM через Emscripten
- Rust → WASM через wasm-pack
- AssemblyScript модули

---

## 📚 Документация

- **CMAKE_GUIDE.md** - Подробный гайд по настройке CMake для Node.js addons
- Примеры использования
- Best practices
- Полезные ссылки

---

## 🔗 Интеграция с Javascript/

Нативные модули подключены в `Javascript/pnpm-workspace.yaml`:

```yaml
packages:
  - '../Native/node-addons'
```

Это позволяет управлять ими через pnpm из корня Javascript/.

---

## 💡 Зачем выносить Native/ отдельно?

1. **Чистое разделение языков** - C++ код отдельно от JavaScript
2. **Переиспользование** - один C++ код для Node.js, Python, WASM
3. **Логичная структура** - нативные модули не смешиваются с JS
4. **Масштабируемость** - легко добавить другие биндинги

---

**См. также:**
- `CMAKE_GUIDE.md` - детальный гайд по CMake
- `../Javascript/QUICKSTART.md` - команды для запуска

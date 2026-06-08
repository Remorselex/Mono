# Mono — Educational Monorepo

## Project Overview

Full-stack educational monorepo covering C++ data structures, JavaScript/TypeScript web development, and Node.js native addons. Author: Remorselex (aleh.astrouski@softnetix.io).

## Repository Layout

```
Mono/
├── Cpp/               # C++17 data structures & projects (CMake)
├── Javascript/        # pnpm workspace: frontend + backend + libraries
│   ├── frontend/
│   │   ├── playground/          # Vanilla TypeScript (Vite)
│   │   └── frameworks/
│   │       ├── react/           # React 19 + Rspack
│   │       └── vue/             # Vue
│   ├── backend/                 # Fastify 4 on port 3001
│   └── libraries/
│       └── rx/                  # Custom RxJS-like library (WIP)
└── Native/
    ├── node-addons/             # C++ Node-API addon (cmake-js)
    └── wasm/                    # WebAssembly (TODO)
```

## Key Commands

### C++ (from Cpp/)
```bash
cmake -B cmake-build-debug -S .
cmake --build cmake-build-debug
./cmake-build-debug/Mono
```

### JavaScript (from Javascript/)
```bash
pnpm install          # install all workspace deps
pnpm dev              # run all packages in parallel
pnpm dev:backend      # Fastify server (port 3001)
pnpm dev:playground   # Vite playground
pnpm build            # build all packages
pnpm clean            # clean all build artifacts
```

### Native Addons (from Javascript/ or Native/node-addons/)
```bash
pnpm build:addons     # build C++ addon via cmake-js
pnpm rebuild:addons   # rebuild addon
```

## Technology Stack

| Layer | Technology |
|-------|-----------|
| Systems | C++17, CMake 3.15+, clang-tidy |
| Frontend | TypeScript, React 19.2, Vue, Vite, Rspack |
| Backend | Node.js 24+, Fastify 4.28, TypeScript |
| Native | Node-API v8, cmake-js |
| Package mgmt | pnpm 9+ (workspaces) |
| Linting | ESLint, @typescript-eslint, Prettier, Biome, clang-tidy |

## Important Files

- `Javascript/pnpm-workspace.yaml` — defines workspace packages (includes `../Native/node-addons`)
- `Javascript/tsconfig.json` — shared TypeScript root config
- `Cpp/CMakeLists.txt` — C++ build entry point
- `Native/node-addons/CMakeLists.txt` — native addon build
- `Native/CMAKE_GUIDE.md` — comprehensive CMake reference
- `SETUP_INSTRUCTIONS.md` — full setup guide (Russian)

## Architecture Notes

- The Native/node-addons package is **included in the pnpm workspace** and can call C++ code from `Cpp/src/`
- React app uses **Rspack** (Rust-based bundler), not Webpack — config is `rspack.config.ts`
- Backend runs on port **3001**; frontend dev servers use their default ports (Vite: 5173, Rspack: 8080)
- The `rx` library in `Javascript/libraries/rx/` is a WIP custom reactive library — `Observer.ts` is currently staged

## Assistant Instructions

When working in this repo:

1. **C++ changes**: always check `Cpp/CMakeLists.txt` for build targets before adding files; prefer header-only implementations in `Cpp/src/Containers/` following existing patterns.
2. **JS/TS changes**: respect pnpm workspaces — run commands from `Javascript/` root using `--filter` flags to target specific packages.
3. **New packages**: add them to `Javascript/pnpm-workspace.yaml`.
4. **Native addon**: `Native/node-addons/src/native/` contains C++ sources; `src/index.ts` is the TypeScript wrapper — keep them in sync.
5. **Code style**: TypeScript uses strict mode; C++ targets C++17; no comments unless the WHY is non-obvious.
6. **Language**: user communicates in Russian — respond in Russian unless code/technical terms require English.

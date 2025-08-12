# Tractor Telemetry (C++/CMake, GoogleTest, CAN sim, FSM)

Pequeno projeto em **C++17** que simula telemetria de um trator: leitura de sensores,
processamento por **máquina de estados** e comandos via **CAN** (simulados).

## Build rápido (VS Code + CMake)

1. Instale **CMake** e um compilador (MSVC ou MinGW).
2. Abra a pasta no **VS Code**.
3. Use o comando **CMake: Configure** e depois **CMake: Build**.
4. Rode `tractor_telemetry`.

### CLI manual

```bash
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build -j
./build/tractor_telemetry
```

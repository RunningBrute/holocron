# Holocron

A small network simulator written in C.

The project consists of independent processes representing nodes, a supervisor responsible for managing them, and a router.

Current work focuses on process management and the project infrastructure. Qt/QML GUI is being developed separately.

## Build and tests

Build:

```bash
cmake -S . -B build
cmake --build build
```

Run tests:

```bash
ctest --test-dir build
```

## Components

* `node` — network node process
* `supervisor` — creates and manages nodes
* `router` — router process
* `gui` — Qt/QML interface

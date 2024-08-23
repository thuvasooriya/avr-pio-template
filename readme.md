# avr development with platformio

this repository contains an avr microcontroller project set up with platformio and nix for a deterministic development environment.

## project structure

- `lib/`: project-specific libraries
- `src/`: source code files
  - `main.c`: main entry point of the program
- `test/`: test files for the project
- `.clangd`: configuration for clangd language server
- `.gitignore`: specifies intentionally untracked files to ignore
- `.justfile`: task runner configuration file
- `compile_commands.json`: compilation database for tooling
- `flake.lock`: nix flake lock file
- `flake.nix`: nix flake configuration for reproducible development environment
- `platformio.ini`: platformio project configuration

## getting started

1. ensure you have nix installed on your system.
2. clone this repository.
3. run `nix develop` to enter the development environment.

## build and run

we use `just` as a command runner. here are the available commands:

- `just build`: compile the project
- `just upload`: upload the compiled code to the device
- `just monitor`: monitor serial output from the device
- `just clean`: clean the project build files
- `just all`: run build, upload, and monitor in sequence

to see all available commands, simply run `just` without arguments.

## development environment

this project uses a nix flake to provide a reproducible development environment. the environment includes:

- platformio core
- avr gcc toolchain
- avrdude for uploading code to devices
- git for version control

## configuration

- `platformio.ini`: configure your specific avr board and build options here.
- `flake.nix`: modify if you need to change the development environment.
- `.justfile`: add or modify build and utility commands here.

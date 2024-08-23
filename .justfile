@default:
    just --list --list-heading ''

# build the project
build:
    pio run
    pio run --target compiledb

# upload the code to the device
upload:
    pio run --target upload

# monitor serial output
monitor:
    pio device monitor

# clean the project
clean:
    pio run --target clean

# run all steps: build, upload, and monitor
all: build upload monitor

# pio project init --ide vim

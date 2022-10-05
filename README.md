# Space Station Zebra

## Build Instructions

Run the following commands:
```
cmake -S . -B .
cmake --build . --parallel 4
```

A different build directory may be used if desired, but must be empty.
There will be two binaries: `run_tests` and `space-station-zebra`.
`run_tests` will run the tests. `space-station-zebra` will begin a simulation.

## Building Doxygen Documentation

Run the following command:
```
doxygen
```

## Configuration

The file `constants.h` contains values that may be modified if desired.
See that file's page for details (or click the filename).

## Usage

Run `./space-station-zebra --help` for info.

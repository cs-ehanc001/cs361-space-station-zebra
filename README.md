# Space Station Zebra

## Build Instructions

Run the following commands:
```
cmake -S . -B .
cmake --build . --parallel 4
```

There will be two binaries: `run_tests` and `space-station-zebra`.
`run_tests` will run the tests. `space-station-zebra` will begin a simulation.

## Building Doxygen Documentation

Run the following command:

```
doxygen
```

## Configuration

The file `constants.h` contains values that may be modified if desired for compiled-in configuration.
See that file's page for details (or click the filename if you are reading this in Doxygen).

## Usage

Run `./space-station-zebra --help` for info.

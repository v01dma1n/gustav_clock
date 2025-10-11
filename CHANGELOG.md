# Changelog

All notable changes to this project will be documented in this file.

## [3.0.0] - 2025-10-02

### Added
- New `ESP32NTPClock_Drivers` library to segregate hardware drivers.
- Reusable `i2c_util` added to the core library.

### Changed
- Refactored `i_generic_clock` into a minimal `i_base_clock` to better support non-weather clocks.

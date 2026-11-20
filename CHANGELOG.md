# Change Log
All notable changes to this project will be documented in this file.

## [1.2.1] - 2026/11/20

### Fixed
- Increased buffer size to prevent overflows on large integers
- Fixed stack memory restoration

## [1.2.0] - 2026/11/5

### Changed
- `update_system_copy` now uses optimization flags

### Fixed
- Fixed a buffer overflow in `parse_hex` detected by the optimization flags

## [1.1.0] - 2026/11/3

### Changed
- Replaced file extension check with automatic detection and classification of binary/hex files

## [1.0.0] - 2026/10/16

### Added
- Machine code parser, interpreter, and generator
- Assembly disassembler
# Ping in C

A C implementation of ICMP ping functionality with custom data structures and utilities for network communication.

## Overview

This project implements a basic ICMP (Internet Control Message Protocol) ping utility in C. It provides functionality to create, send, and process ICMP echo requests and echo replies, which are the fundamental building blocks of the ping command.

## Features

- **ICMP Packet Creation**: Build ICMP echo requests and echo replies
- **Checksum Calculation**: Proper ICMP checksum computation
- **Packet Serialization**: Convert ICMP structures to raw network packets
- **Hex Dumping**: Debug utilities for packet inspection
- **Cross-platform**: Designed to work on Unix-like systems

## Project Structure

```
Ping_in_C/
├── ping.c      # Main implementation file
├── ping.h      # Header file with data structures and function declarations
└── Makefile    # Build configuration
```

## Prerequisites

- GCC compiler with C2x standard support
- Unix-like operating system (Linux, macOS, BSD)
- Standard C libraries (stdio, stdlib, string, etc.)

## Building the Project

### Using Make (Recommended)

```bash
cd Ping_in_C
make
```

This will compile the project with optimization flags (`-O2`) and create an executable named `ping`.

### Manual Compilation

```bash
cd Ping_in_C
gcc -O2 -Wall -std=c2x -c ping.c -o ping.o
gcc -O2 -Wall -std=c2x ping.o -o ping
```

## Usage

Currently, the main function demonstrates the creation and serialization of an ICMP echo packet:

```bash
./ping
```

The program will:

1. Create an ICMP echo packet with "Hello" as payload
2. Display the packet contents
3. Serialize the packet to raw format
4. Print the hex representation of the raw packet

## Technical Details

### Data Structures

#### ICMP Packet Structure

```c
struct s_icmp {
    type kind;      // echo or echoreply
    int16 size;     // payload size
    int8 *data;     // payload data
} packed;
```

#### Raw ICMP Structure

```c
struct s_rawicmp {
    int8 type;      // ICMP type (8 for echo, 0 for reply)
    int8 code;      // ICMP code (0 for echo/reply)
    int16 checksum; // ICMP checksum
    int8 data[];    // variable-length payload
} packed;
```

### Key Functions

- `mkicmp()`: Create an ICMP packet structure
- `evalicmp()`: Serialize ICMP packet to raw format
- `checksum()`: Calculate ICMP checksum
- `showicmp()`: Display ICMP packet contents
- `printhex()`: Print hex dump of data

### ICMP Types Supported

- **Echo Request** (Type 8): Sent to test connectivity
- **Echo Reply** (Type 0): Response to echo requests

## Development Notes

### Compiler Flags

- `-O2`: Optimization level 2
- `-Wall`: Enable all warnings
- `-std=c2x`: Use C2x standard
- `packed` attribute: Ensure structure packing for network compatibility

### Custom Type Definitions

The project uses custom integer type definitions for clarity:

- `int8`: 8-bit unsigned integer
- `int16`: 16-bit unsigned integer
- `int32`: 32-bit unsigned integer
- `int64`: 64-bit unsigned integer

## Future Enhancements

This appears to be a foundation for a complete ping implementation. Potential additions could include:

- Network socket operations for actual packet transmission
- Command-line argument parsing
- Statistics collection (RTT, packet loss)
- Support for different payload sizes
- IPv6 support
- Timestamp functionality

## License

This project is provided as-is for educational and development purposes.

## Contributing

Feel free to submit issues, feature requests, or pull requests to improve this implementation.

## Related Resources

- [RFC 792 - Internet Control Message Protocol](https://tools.ietf.org/html/rfc792)
- [ICMP Wikipedia](https://en.wikipedia.org/wiki/Internet_Control_Message_Protocol)
- [Ping Wikipedia](<https://en.wikipedia.org/wiki/Ping_(networking_utility)>)

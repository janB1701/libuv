# Project Source Files

This directory contains the source code for key components of our project. Each file serves a specific purpose, detailed below.

## Files Overview

1. **network_dissector.c**
   - **Description**: This file contains code for a basic network packet dissector. It interprets the contents of a raw network packet, extracting and displaying information such as the Ethernet source and destination MAC addresses, as well as the IP source and destination addresses.
   - **Key Functions**: Parsing Ethernet and IP headers from raw packet data.

2. **tcp_calculator.c**
   - **Description**: Implements a TCP server that receives a number from a client, calculates its square, and sends the result back. This file showcases basic network communication using the `libuv` library.
   - **Key Functions**: Handling TCP connections, reading data, and sending responses.

3. **timer.c**
   - **Description**: Demonstrates the use of timers and idle handles in `libuv`. This file includes a timer that counts up to a user-specified number, and an idle handle that updates the display during the counting process.
   - **Key Functions**: Timer initialization and callback management, idle loop handling.

## Running the Programs

To compile and run these programs, follow these steps:

1. Install `libuv` if not already installed.
2. Compile each file using a C compiler, e.g., `gcc -o network_dissector network_dissector.c`.
3. Run the compiled executable, e.g., `./network_dissector`.

## Dependencies

- `libuv` library for `tcp_calculator.c` and `timer.c`.
- Standard C libraries for `network_dissector.c`.

## Additional Notes

- `network_dissector.c` does not handle all possible network protocols and is meant for educational purposes.
- `tcp_calculator.c` requires a TCP client to interact with the server.
- `timer.c` uses the terminal for output, and the display updates depend on the idle handle.

## Contributing

Contributions to improve or extend the functionality of these programs are welcome. Please follow standard GitHub pull request procedures.

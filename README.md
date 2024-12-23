# PBX Server Assignment

## Overview

This repository contains the implementation for a multithreaded network server that simulates a Private Branch Exchange (PBX) telephone system. The server handles communication between Telephone Units (TUs) registered in the system, supporting typical PBX features such as dialing extensions, handling calls, and enabling chat functionality.

## Features

The PBX server supports:
- **TU Registration and Unregistration**: Manage clients as extensions.
- **Call Handling**: Dial, connect, and manage calls between extensions.
- **State Transitions**: Support various states like on-hook, ringing, busy, and connected.
- **Multithreading**: Use POSIX threads to handle multiple simultaneous clients.
- **Concurrency**: Ensure safe concurrent access using mutexes and semaphores.

---

## Repository Structure

- **src/**: Contains the source code files.
  - `main.c`: Initializes the server, sets up signal handling, and accepts client connections.
  - `server.c`: Implements `pbx_client_service()` for handling client interactions.
  - `pbx.c`: Manages PBX functionality, including maintaining extension mappings and handling TU state transitions.
  - `tu.c`: Simulates a telephone unit (TU) with state management and network communication.

---

### Building the Project

To compile the project:
```bash
make clean debug
```

### Running the Server
To run the server, specify the port number using the -p option:

```bash
./pbx -p <port>
```

### Commands and Responses
**Client to Server Commands**:
- `pickup`
- `hangup`
- `dial <extension>`
- `chat <message>`

**Server to Client Responses**:
- `ON HOOK <extension>`
- `RINGING`
- `DIAL TONE`
- `RING BACK`
- `CONNECTED <extension>`
- `ERROR`
- `CHAT <message>`

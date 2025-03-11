# IoT Relay Control System with ESP8266

This project implements a system to remotely control a relay module using the ESP8266 microcontroller. The system leverages WiFi, MQTT, and JSON for efficient communication and integration, making it ideal for smart home and IoT applications.

---

## Table of Contents
1. [Introduction](#introduction)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Tools and Technologies](#software-tools-and-technologies)
4. [How It Works](#how-it-works)
5. [Code Structure](#code-structure)
    - [WiFi and MQTT Relay Controller](#wifi-and-mqtt-relay-controller)
    - [Sending Relay State with JSON Payload](#sending-relay-state-with-json-payload)
    - [MQTT Command-Based Relay Control](#mqtt-command-based-relay-control)
      
6. [Expected Terminal Output](#expected-terminal-output)
7. [Applications](#applications)

---

## Introduction
This project demonstrates a relay control system using the ESP8266 microcontroller. By connecting to WiFi and utilizing MQTT communication, the system can remotely toggle a relay's state. JSON is used for structured data exchange, ensuring clear communication with the server.

---

## Hardware Requirements
- **ESP8266 Microcontroller**
- **Relay Module** (connected to GPIO pin D1)

---

## Software Tools and Technologies
- **WiFi**: Connects the ESP8266 to the internet.
- **MQTT**: Facilitates message-based communication with a broker.
- **JSON**: Formats and exchanges data for organized communication.
- **NTP (Network Time Protocol)**: Ensures accurate timestamps.

---

## How It Works
1. **WiFi Setup**:
   - The ESP8266 connects to a WiFi network using an SSID and password.
2. **MQTT Communication**:
   - Connects to an MQTT broker at `192.168.174.29:1883`.
   - Listens to the `relay_control` topic for commands and publishes status updates to the `hasan_quentin` topic.
3. **Relay Control**:
   - Commands:
     - `1`: Turns the relay **ON**.
     - `-1`: Turns the relay **OFF**.
   - Logs invalid commands for troubleshooting.
4. **JSON Data Exchange**:
   - Relay state updates are sent in JSON format, including details like timestamp and node name.
5. **Error Handling**:
   - Logs errors and ensures uninterrupted operation.

---

## Code Structure

### WiFi and MQTT Relay Controller
This component establishes a WiFi connection and initializes MQTT communication. It also synchronizes the time using an NTP client and configures the relay to its default state (OFF).

### Sending Relay State with JSON Payload
A function formats and sends the relay state as a JSON payload to the MQTT broker. The message includes:
- Node name
- Sensor type
- Relay state
- Timestamp (retrieved via NTP)

### MQTT Command-Based Relay Control
Handles relay control based on MQTT commands:
- `1`: Turns the relay ON.
- `-1`: Turns the relay OFF.
- Invalid commands are logged and ignored.
State updates are sent using the `sendRelayState` function.

---

## Expected Terminal Output
Below is an example of the expected terminal output during operation:
```plaintext
WiFi connected: IP 192.168.1.10
MQTT connected to broker: 192.168.174.29
Received command: 1
Relay state: ON
Published state: {"node":"ESP8266","type":"relay","state":"ON","timestamp":"2025-03-06T10:00:00Z"}
Received command: -1
Relay state: OFF
Published state: {"node":"ESP8266","type":"relay","state":"OFF","timestamp":"2025-03-06T10:00:10Z"}
```

---
## Applications
This system is ideal for:

- Smart Home Automation: Remote control of devices like lights and appliances.
- IoT Systems: Interfacing with other devices using MQTT and JSON for seamless integration.




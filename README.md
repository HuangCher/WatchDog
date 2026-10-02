# Study Companion Robot

A cardboard desk companion powered by an ESP32 that monitors study activity using motion detection. During study mode, the robot detects inactivity and responds with LED eyes, servo head movement, and a buzzer to help maintain focus and manage Pomodoro study cycles.

The project is designed as a small real-time embedded system, with a focus on **finite state machine design, sensor/actuator control, and deterministic behavior**. Future development will explore **FreeRTOS-based task scheduling, inter-task communication, timing analysis, and fault handling**.

## Features

* Motion detection using a PIR sensor
* Finite state machine for robot behavior
* Pomodoro study/break timer
* Servo-controlled head movement
* RGB LED eyes for visual feedback
* Buzzer alerts
* Button input for user control
* Modular C++ code structure
* ESP32-based embedded system

## System Architecture

The robot uses a finite state machine to manage its behavior based on sensor inputs, timer events, and user interaction.

![Finite State Machine](images/fsm.png)

Current system components include:

* **Motion:** Reads and processes PIR motion sensor input
* **FSM:** Controls the robot's current operating state
* **Timer:** Manages Pomodoro study/break cycles
* **Servo:** Controls head movement
* **Alerts:** Controls LED and buzzer feedback
* **Button:** Handles user input
* **Pins:** Centralizes ESP32 GPIO assignments

## Hardware

* ESP32
* PIR motion sensor
* SG90 servo motor
* RGB LED
* Buzzer
* Push button
* Cardboard enclosure

## Datasheets, Schematics, and Documentation

* [ESP32 Pinout Reference](https://lastminuteengineers.com/esp32-pinout-reference/)
* [PIR Motion Sensor (HC-SR501) Datasheet](https://www.handsontec.com/dataspecs/SR501%20Motion%20Sensor.pdf)
* [SG90 Servo Motor Datasheet](https://handsontec.com/dataspecs/motor_fan/SG90-Servo.pdf)
* [Buzzer Datasheet](https://components101.com/misc/buzzer-pinout-working-datasheet)
* [RGB LED Reference](https://www.build-electronic-circuits.com/rgb-led/)

## Development

This project is developed using:

* **C++**
* **ESP32**
* **PlatformIO**
* **Arduino framework**

Future development will focus on:

* FreeRTOS task-based architecture
* Sensor, behavior, actuator, and telemetry tasks
* Inter-task communication using queues and notifications
* Non-blocking real-time scheduling
* Task timing and jitter measurements
* Fault detection and recovery
* Hardware/software watchdog functionality
* Telemetry and system monitoring

## File Structure

```text
Study-Companion-Robot/
│
├── README.md
├── platformio.ini
│
├── include/
│   ├── config.h
│   ├── pins.h
│   │
│   ├── hw/
│   │   ├── motion.h
│   │   ├── servo.h
│   │   ├── alerts.h
│   │   └── button.h
│   │
│   ├── sys/
│   │   ├── fsm.h
│   │   └── timer.h
│   │
│   └── rtos/
│       ├── tasks.h
│       ├── queues.h
│       └── events.h
│
├── src/
│   ├── main.cpp
│   │
│   ├── hw/
│   │   ├── motion.cpp
│   │   ├── servo.cpp
│   │   ├── alerts.cpp
│   │   └── button.cpp
│   │
│   ├── sys/
│   │   ├── fsm.cpp
│   │   └── timer.cpp
│   │
│   └── rtos/
│       ├── tasks.cpp
│       ├── queues.cpp
│       └── events.cpp
│
├── dashboard/
│   ├── README.md
│   ├── requirements.txt
│   ├── app.py
│   │
│   ├── static/
│   │   ├── style.css
│   │   └── script.js
│   │
│   └── templates/
│       └── index.html
│
├── tests/
│   ├── unit/
│   │   ├── test_fsm.cpp
│   │   ├── test_timer.cpp
│   │   └── test_sensor_logic.cpp
│   │
│   ├── integration/
│   │   ├── test_sensor_fsm.cpp
│   │   └── test_fsm_actuator.cpp
│   │
│   └── fault_injection/
│       ├── sensor_timeout.cpp
│       ├── invalid_state.cpp
│       └── communication_failure.cpp
│
└── data/
    ├── timing/
    │   ├── task_timing.csv
    │   └── timing_results.md
    │
    └── logs/
        └── README.md
```

## Project Goals

The goal of this project is to develop a small embedded system that combines **hardware, firmware, and real-time software design**. As the project develops, the system will be expanded from a basic ESP32 control loop into a more structured real-time architecture with measurable timing behavior, concurrent tasks, and fault handling.

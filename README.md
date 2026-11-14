# 🤖 Autonomous Obstacle-Avoiding Robot Car (Differential Drive)

An autonomous obstacle-avoiding robot car powered by an **Arduino Uno**, driven by an **H-bridge motor driver**, and navigated using an **HC-SR04 ultrasonic sensor** mounted on a **9g micro servo** panning mechanism. 

---

## 🛠️ Kit Components

* **Microcontroller:** Arduino Uno R3[cite: 2]
* **Motor Driver:** H-Bridge Motor Driver (e.g., L293D / L298N)[cite: 2]
* **Distance Sensor:** HC-SR04 Ultrasonic Distance Sensor (4-pin)[cite: 2]
* **Steering & Scanning:** Positional Micro Servo (9g)[cite: 2]
* **Drive System:** 2 x Hobby Gearmotors (`M1` Right, `M2` Left)[cite: 2]
* **Power Source:** 9V Battery Pack / External DC Power[cite: 2]

---

## 🔌 Pin Connections & Wiring

| Component | Pin / Terminal | Arduino Uno Connection |
| :--- | :--- | :--- |
| **Servo Motor (`SERVO1`)** | Signal (`SIG`) | Pin **`D2`** |
| **Motor Driver (`U2`)** | Left Enable (`1-2EN`) | Pin **`D3`** (PWM) |
| | Left Direction 1 (`1A`) | Pin **`D4`** |
| | Left Direction 2 (`2A`) | Pin **`D5`** |
| | Right Direction 1 (`3A`) | Pin **`D6`** |
| | Right Direction 2 (`4A`) | Pin **`D7`** |
| | Right Enable (`3-4EN`) | Pin **`D8`** (PWM) |
| **Ultrasonic Sensor (`DIST1`)** | Trigger (`TRIG`) | Pin **`D13`** |
| | Echo (`ECHO`) | Pin **`D12`** |

---

## 🧠 How It Works

1. **Forward Cruise:** The robot moves straight ahead using Pulse Width Modulation (PWM) on both drive motors.
2. **Obstacle Detection:** The ultrasonic sensor continuously pings the environment ahead. If an object is detected within the threshold (e.g., `< 25 cm`), the robot halts and reverses briefly.
3. **Surrounding Scan:** The micro servo pans the ultrasonic sensor to the left and right to check clearance distances.
4. **Autonomous Steering:** The robot compares left and right path distances and turns toward the clearer side before resuming forward movement.

---
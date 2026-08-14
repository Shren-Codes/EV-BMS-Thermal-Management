# 🚗⚡ EV BMS — Intelligent Battery Thermal Monitoring & Alert System

<p align="center">
  <img src="https://img.shields.io/badge/Embedded-ESP32-blue?style=for-the-badge&logo=espressif" />
  <img src="https://img.shields.io/badge/Language-Embedded%20C%2B%2B-00599C?style=for-the-badge&logo=cplusplus" />
  <img src="https://img.shields.io/badge/Simulation-Wokwi-orange?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Build-PlatformIO-red?style=for-the-badge" />
  <img src="https://img.shields.io/badge/IoT-Telegram-26A5E4?style=for-the-badge&logo=telegram" />
  <img src="https://img.shields.io/badge/IDE-VS%20Code-007ACC?style=for-the-badge&logo=visual-studio-code" />
</p>

<p align="center">

## 🔋 Real-Time EV Battery Thermal Monitoring & Protection

**ESP32 • Embedded C++ • BMS • EV Thermal Management • IoT • Wokwi • Telegram**

</p>

---

## 🚨 Project Overview

**EV BMS — Intelligent Battery Thermal Monitoring & Alert System** is an ESP32-based embedded system developed to simulate the **thermal monitoring, protection, and alerting layer of an Electric Vehicle Battery Management System (BMS)**.

The system continuously monitors battery temperature using a **DHT22 temperature sensor**, processes the telemetry on the **ESP32**, evaluates thermal operating conditions, calculates the **rate of temperature rise (dT/dt)**, activates a simulated cooling system, and sends event-driven notifications through **Telegram**.

The complete embedded system is developed using **Embedded C++**, built with **PlatformIO**, and validated through **Wokwi hardware simulation**.

> ⚠️ **Simulation Note:** The DHT22 represents a battery temperature sensor, while the LED represents the cooling-system activation state. The project is a simulation and does not directly control a physical EV battery pack, cooling pump, or thermal-management hardware.

---

## 🎯 Project Objectives

The main objective is to implement a compact and practical **EV battery thermal monitoring and protection subsystem**.

### Core Objectives

- 🔋 Implement **real-time battery thermal monitoring**
- 🌡️ Acquire temperature telemetry using a **DHT22**
- 🧠 Implement embedded **BMS thermal decision logic**
- 📈 Calculate the **rate of temperature rise (dT/dt)**
- ⚠️ Detect elevated battery temperature
- 🔴 Detect critical thermal conditions
- ⚡ Detect rapid temperature-rise events
- ❄️ Activate a simulated cooling system
- 📡 Establish wireless connectivity through ESP32 Wi-Fi
- 📱 Deliver remote Telegram safety notifications
- 🧪 Validate embedded behavior using Wokwi simulation
- 🖥️ Provide real-time diagnostics through Serial Monitor

---

## ✨ Key Features

| Feature | Implementation |
|---|---|
| 🌡️ Temperature Monitoring | DHT22 real-time temperature acquisition |
| 🧠 BMS Decision Logic | Threshold-based thermal state evaluation |
| 🟢 Normal State | Temperature < 35°C |
| 🟡 Warning State | Temperature ≥ 35°C and < 45°C |
| 🔴 Critical State | Temperature ≥ 45°C |
| ⚡ Rapid Rise Detection | dT/dt > 0.5°C/s |
| ❄️ Cooling Control | ESP32 GPIO-driven LED simulation |
| 📡 Wireless Communication | ESP32 Wi-Fi |
| 📱 Remote Alerting | Telegram Bot API |
| 🖥️ Diagnostics | Serial Monitor |
| 🧪 Hardware Simulation | Wokwi |
| ⚙️ Firmware Build | PlatformIO |
| 🔐 Credential Protection | Local `secrets.h` configuration |

---

## 🏗️ System Architecture

```text
                         🔋 EV BATTERY
                              │
                              ▼
                    ┌───────────────────┐
                    │       DHT22       │
                    │ Temperature       │
                    │ Sensor            │
                    └─────────┬─────────┘
                              │
                              │ GPIO 15
                              ▼
                    ┌───────────────────┐
                    │       ESP32       │
                    │                   │
                    │ Sensor Acquisition│
                    │ Thermal Analysis  │
                    │ dT/dt Calculation │
                    │ BMS Decision Logic│
                    │ Cooling Control   │
                    └───────┬─────┬─────┘
                            │     │
                       GPIO 2     │ Wi-Fi
                            │     │
                            ▼     ▼
                     ┌─────────┐ ┌──────────────┐
                     │ Cooling │ │   Telegram   │
                     │   LED   │ │ Bot / Alerts │
                     └─────────┘ └──────────────┘
```

---

## 🔄 Complete System Workflow

The system follows a continuous embedded monitoring and decision-making loop.

```text
                         ┌───────────────┐
                         │     START     │
                         └───────┬───────┘
                                 │
                                 ▼
                    ┌────────────────────────┐
                    │ Initialize ESP32       │
                    │ • GPIO                 │
                    │ • Serial               │
                    │ • DHT22                │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │ Connect to Wi-Fi        │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │ Send Telegram           │
                    │ System Online Alert     │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │ Read Battery            │
                    │ Temperature             │
                    └───────────┬────────────┘
                                │
                                ▼
                    ┌────────────────────────┐
                    │ Calculate dT/dt         │
                    │ Rate of Temperature     │
                    │ Rise                    │
                    └───────────┬────────────┘
                                │
                     ┌──────────┴──────────┐
                     ▼                     ▼
              dT/dt > 0.5°C/s        Normal Rate
                     │                     │
                     ▼                     ▼
             ⚡ Rapid Rise Alert     Evaluate Temperature
                                           │
                              ┌────────────┼────────────┐
                              ▼            ▼            ▼
                           < 35°C      35–44.9°C       ≥45°C
                              │            │            │
                              ▼            ▼            ▼
                           🟢 NORMAL    🟡 WARNING    🔴 CRITICAL
                              │            │            │
                              ▼            ▼            ▼
                         Cooling OFF   Cooling ON   Emergency Cooling
                              │            │            │
                              │            ▼            ▼
                              │       Telegram Alert  Telegram Alert
                              │            │            │
                              └────────────┴────────────┘
                                           │
                                           ▼
                                    Repeat Monitoring
```

---

## 🧠 BMS Thermal Decision Logic

The firmware uses a state-based thermal classification approach.

### 🟢 NORMAL — Temperature < 35°C

```text
Temperature < 35°C
        ↓
Battery Status = NORMAL
        ↓
Cooling System = OFF
        ↓
Continue Monitoring
```

**System behavior**
- Cooling LED → OFF
- Warning flag → reset
- Critical flag → reset
- Continuous temperature monitoring → ACTIVE

### 🟡 WARNING — 35°C ≤ Temperature < 45°C

```text
35°C ≤ Temperature < 45°C
        ↓
Battery Status = WARNING
        ↓
Cooling System = ON
        ↓
Telegram Warning Alert
        ↓
Continue Monitoring
```

**System behavior**
- Cooling LED → ON
- Warning notification → sent once per event
- BMS thermal monitoring → ACTIVE

### 🔴 CRITICAL — Temperature ≥ 45°C

```text
Temperature ≥ 45°C
        ↓
Battery Status = CRITICAL
        ↓
Emergency Cooling = ON
        ↓
Telegram Critical Alert
        ↓
Immediate Inspection Recommended
```

**System behavior**
- Cooling LED → ON
- Critical notification → sent once per event
- Emergency cooling state → ACTIVE

---

## ⚡ Rapid Temperature Rise Detection

The system uses an additional thermal indicator based on the rate of temperature change.

The firmware calculates:

```text
             ΔT
dT/dt =  ─────────
             Δt
```

where:
- `ΔT` = change in temperature
- `Δt` = elapsed time
- `dT/dt` = temperature rise rate

**Rapid-rise threshold:** `dT/dt > 0.5 °C/s`

When the threshold is exceeded:

```text
Temperature Change
        ↓
Calculate dT/dt
        ↓
dT/dt > 0.5°C/s
        ↓
⚡ Rapid Temperature Rise
        ↓
Telegram Alert
```

The rapid-rise condition is reset when `dT/dt ≤ 0.2 °C/s`.

> ⚠️ The rapid-rise event is treated as a thermal-risk indicator and not as definitive proof of thermal runaway.

---

## 📊 Thermal State Matrix

| Condition | Temperature | dT/dt | State | Cooling | Alert |
|---|---|---|---|---|---|
| Normal | < 35°C | Any normal rate | 🟢 NORMAL | OFF | — |
| Warning | 35–44.9°C | Normal rate | 🟡 WARNING | ON | ⚠️ |
| Critical | ≥ 45°C | Normal rate | 🔴 CRITICAL | ON | 🔴 |
| Rapid Rise | Any temperature | > 0.5°C/s | ⚡ RAPID RISE | Monitoring | ⚡ |

---

## 📱 Telegram Alert System

The ESP32 communicates with Telegram through Wi-Fi using the `UniversalTelegramBot` library. Notifications are event-driven so the system does not continuously spam the user with identical messages.

**🚀 System Online**
```text
✅ EV BMS System Online
Thermal Monitoring Started
Thresholds: Warning>35°C | Critical>45°C
```
This notification confirms ESP32 initialization, Wi-Fi connectivity, Telegram communication, and thermal monitoring activation.

**⚡ Rapid Temperature Rise**
```text
⚡ RAPID TEMPERATURE RISE!
Current Temp: 31.6 °C
Rate: 3.13 °C/s
Thermal Runaway Risk — Check Immediately!
```
This notification is generated when the measured temperature rises rapidly.

**🟡 Warning**
```text
⚠️ WARNING!
EV Battery Temperature High
Current Temp: 40.0 °C
Cooling System Activated
```

**🔴 Critical**
```text
🔴 CRITICAL ALERT!
Thermal Runaway Risk Detected
Current Temp: 51.1 °C
Rate of Rise: 0.00 °C/s
Emergency Cooling Activated
```

---

## 📸 Project Screenshots

| Screenshot | Path |
|---|---|
| 🔌 Wokwi Circuit Diagram | `images/Diagram.png` |
| 🧪 Wokwi Simulation | `images/wokwi-simulation.png` |
| 📱 Telegram Alert | `images/telegramalert.png` |

<!--
Embed once the files exist, e.g.:
![Wokwi Circuit Diagram](docs/images/wokwi-diagram.png)
-->

---

## 🔌 Hardware / Simulation Components

| Component | Purpose |
|---|---|
| ESP32 DevKit | Main embedded controller |
| DHT22 | Battery temperature sensing |
| Blue LED | Simulated cooling activation |
| 1 kΩ Resistor | LED current limiting |
| Wi-Fi | IoT connectivity |
| Telegram Bot | Remote safety notification |
| Wokwi | Embedded hardware simulation |

### 🔗 Pin Configuration

| Component | ESP32 Pin | Function |
|---|---|---|
| DHT22 DATA | GPIO 15 | Temperature data |
| DHT22 VCC | 3V3 | Sensor power |
| DHT22 GND | GND | Ground |
| Cooling LED | GPIO 2 | Cooling activation |
| LED Resistor | GND | Current limiting |

---

## 🛠️ Technology Stack

**💻 Programming**
- Embedded C++
- Arduino Framework

**🔧 Microcontroller**
- ESP32

**🌡️ Sensors**
- DHT22 — Digital temperature sensing

**📡 Communication**
- Wi-Fi
- HTTPS
- Telegram Bot API
- WiFiClientSecure

**🧠 Control & Processing**
- Temperature thresholding
- State-based thermal classification
- dT/dt calculation
- Rapid temperature-rise detection
- Event-driven alerting
- Cooling-state control

**🧪 Simulation & Development**
- Wokwi
- PlatformIO
- Visual Studio Code

**🔄 Version Control**
- Git
- GitHub

### 📚 Software Libraries
- `WiFi`
- `WiFiClientSecure`
- `UniversalTelegramBot`
- `DHTesp`

---

## 🧩 Embedded Software Architecture

```text
┌────────────────────────────────────────────┐
│              EV BMS FIRMWARE                │
├────────────────────────────────────────────┤
│                                              │
│  Sensor Acquisition Layer                   │
│          │                                  │
│          ▼                                  │
│  DHT22 Temperature Reading                  │
│          │                                  │
│          ▼                                  │
│  Thermal Processing Layer                   │
│          │                                  │
│          ├── Temperature Evaluation         │
│          │                                  │
│          └── dT/dt Calculation              │
│                    │                        │
│                    ▼                        │
│          Thermal Decision Engine            │
│                    │                        │
│       ┌────────────┼────────────┐           │
│       ▼            ▼            ▼           │
│    NORMAL       WARNING      CRITICAL        │
│       │            │            │            │
│       ▼            ▼            ▼            │
│  Cooling OFF   Cooling ON   Emergency ON     │
│                    │            │            │
│                    └─────┬──────┘            │
│                          ▼                   │
│                  Alert Management            │
│                          │                   │
│                          ▼                   │
│                  Telegram Notification       │
│                                              │
└────────────────────────────────────────────┘
```

---

## 🔄 Event-Driven Alert Architecture

The system uses event flags to avoid repeatedly sending the same alert.

```text
Temperature Event
       │
       ▼
Evaluate Condition
       │
       ▼
Is Alert Already Sent?
       │
   ┌───┴───┐
  YES      NO
   │       │
   ▼       ▼
Ignore   Send Telegram
           │
           ▼
      Set Alert Flag
```

The firmware maintains independent alert states for:
- `warningSent`
- `criticalSent`
- `rapidRiseSent`

This prevents repeated Telegram notifications while a condition remains active.

---

## 🧪 Wokwi Simulation

The complete embedded system is simulated using Wokwi. This enables controlled testing of different thermal conditions without requiring physical EV hardware.

**Simulation Flow**

```text
Change DHT22 Temperature
          │
          ▼
      ESP32 Reads
          │
          ▼
   Thermal Processing
          │
          ▼
   Decision / State Logic
          │
     ┌────┼────┐
     ▼    ▼    ▼
  NORMAL WARNING CRITICAL
     │    │    │
     ▼    ▼    ▼
   OFF    ON    ON
          │    │
          └─┬──┘
            ▼
      Telegram Alert
```

---

## 🧪 Test & Validation

The system was validated through controlled temperature scenarios using Wokwi.

| Test Case | Input | Expected Battery Status | Expected Cooling | Expected Telegram |
|---|---|---|---|---|
| 1 — Normal Operation | Temperature = 30°C | NORMAL | OFF | No Alert |
| 2 — Warning | Temperature = 40°C | WARNING | ON | WARNING ALERT |
| 3 — Critical | Temperature = 51.1°C | CRITICAL | ON | CRITICAL ALERT |
| 4 — Rapid Temperature Rise | dT/dt > 0.5°C/s | Rapid Rise Detection → ACTIVE | — | RAPID TEMPERATURE RISE ALERT |

---

## 🖥️ Serial Monitoring

The firmware provides real-time diagnostic information through the ESP32 Serial interface.

**Example:**
```text
================================
EV BMS THERMAL MONITORING SYSTEM
================================

Connecting to WiFi....
WiFi Connected!

IP Address: 192.168.x.x

Telegram: Startup alert sent

Battery Temperature: 51.1 °C
Rate of Rise: 0.00 °C/s
CRITICAL: Thermal Runaway Risk!
Emergency Cooling Activated
---------------------------
```

This allows system behavior to be verified during simulation and debugging.

---

## 📊 Example Operating Scenarios

```text
                  TEMPERATURE
                       │
                45°C ──┼────────────── 🔴 CRITICAL
                       │
                35°C ──┼────────────── 🟡 WARNING
                       │
                 0°C ──┼────────────── 🟢 NORMAL
                       │
                       └─────────────────────► TIME
```

The system combines:
- Absolute Temperature
- Temperature Rate of Rise
- Thermal State Classification
- Cooling Control
- Remote Alerting

---

## 🔐 Security

Telegram credentials are intentionally separated from the main firmware. Credentials are stored locally in `include/secrets.h`, and the file is excluded from version control via `.gitignore`.

---

## 📁 Project Structure

```text
EV-BMS-Thermal-Management/
│
├── include/
│   ├── secrets.h
│   └── README
│
├── lib/
│
├── src/
│   └── main.cpp
│
├── test/
│
├──images/
│       ├── wokwi-diagram.png
│       ├── wokwi-simulation.png
│       └── telegram-alert.png
│
├── diagram.json
├── platformio.ini
├── wokwi.toml
├── .gitignore
├── .gitattributes
└── README.md
```

---

## 🚀 Getting Started

### 1️⃣ Clone the Repository

```bash
git clone https://github.com/Shren-Codes/EV-BMS-Thermal-Management.git
```

Open the project in **Visual Studio Code + PlatformIO**.

### 2️⃣ Configure Telegram

Create `include/secrets.h`:

```cpp
#ifndef SECRETS_H
#define SECRETS_H

#define BOT_TOKEN "YOUR_TELEGRAM_BOT_TOKEN"
#define CHAT_ID "YOUR_TELEGRAM_CHAT_ID"

#endif
```

⚠️ Never upload this file to GitHub.

### 3️⃣ Build the Firmware

Using PlatformIO:
```bash
pio run
```
Or via the VS Code command palette: **PlatformIO → Build**

Expected result: `SUCCESS`

### 4️⃣ Start Wokwi

Launch **Wokwi: Start Simulator** from Visual Studio Code.

### 5️⃣ Test Temperature Conditions

Recommended sequence:

| Step | Temperature | Expected Result |
|---|---|---|
| 1 | 30°C | 🟢 NORMAL |
| 2 | 40°C | 🟡 WARNING |
| 3 | 51°C | 🔴 CRITICAL |
| 4 | Rapid increase | ⚡ RAPID TEMPERATURE RISE |

---

## 🧠 Engineering Concepts Demonstrated

**🔋 EV / Battery Systems**
- Battery Management Systems (BMS)
- Battery thermal monitoring
- Thermal management & protection
- Thermal runaway risk detection
- Cooling control
- Battery operating thresholds

**⚙️ Embedded Systems**
- ESP32 firmware development
- Embedded C++ / Arduino framework
- GPIO programming
- Digital sensor interfacing
- Real-time monitoring
- State-based control
- Event-driven firmware

**📊 Data Processing**
- Real-time telemetry acquisition
- Temperature threshold evaluation
- dT/dt calculation
- Thermal event detection
- Rate-of-rise analysis
- State classification

**📡 IoT**
- Wi-Fi connectivity
- HTTPS communication
- Telegram Bot API
- Remote monitoring
- Event-driven notifications

**🧪 Validation**
- Wokwi hardware simulation
- Controlled test scenarios
- Serial diagnostics
- Threshold-based validation
- Fault-condition testing

---

## 🏭 Real-World EV Relevance

The project demonstrates the fundamental workflow of an EV battery thermal monitoring subsystem:

```text
Battery Temperature Sensor
          │
          ▼
   Data Acquisition
          │
          ▼
     BMS Processing
          │
          ▼
 Thermal State Evaluation
          │
          ▼
 Protection Decision
          │
      ┌───┴────┐
      ▼        ▼
  Cooling     Alert
  Control     System
```

In a production EV BMS, this concept can be expanded with:
- Cell-level voltage monitoring
- Pack voltage measurement
- Current sensing
- SOC estimation
- SOH estimation
- Multiple temperature sensors
- CAN communication
- Contactor control
- Thermal-management hardware
- Diagnostic communication
- Battery fault handling

This project specifically demonstrates the **thermal monitoring, thermal-risk detection, cooling-state control, and remote alerting** layer.

---

## 📈 Future Enhancements

**🔋 Battery Monitoring**
- [ ] Cell voltage monitoring
- [ ] Pack voltage monitoring
- [ ] Current sensing
- [ ] SOC estimation
- [ ] SOH estimation
- [ ] Cell imbalance detection

**🚗 Automotive Communication**
- [ ] CAN bus integration
- [ ] CAN-based BMS telemetry
- [ ] Diagnostic communication
- [ ] ECU integration

**🌡️ Thermal Management**
- [ ] Multiple temperature sensors
- [ ] Fan control
- [ ] Pump control
- [ ] Liquid-cooling simulation
- [ ] Thermal-zone monitoring

**📊 Monitoring**
- [ ] OLED dashboard
- [ ] Web dashboard
- [ ] Historical telemetry
- [ ] Telegram command interface

# PhotonIQ
# 💡 IoT-based smart lighting system with automatic brightness control and real-time cloud monitoring using Thingsboard

---

> **Smart Automation | Real-Time Cloud Monitoring | Energy Efficient Lighting Control**

This project demonstrates an **IoT-based Smart Lighting System** that intelligently manages room or environmental lighting based on ambient light intensity. It utilizes an **ESP32 microcontroller**, an **LDR sensor**, and a **relay-controlled LED bulb** to automatically switch lighting ON/OFF, while transmitting real-time telemetry data to the **ThingsBoard Cloud IoT platform** via **MQTT protocol**.

---

## 🚀 Project Overview

The system continuously monitors environmental light intensity using an **LDR (Light Dependent Resistor)** sensor.

* When **darkness** is detected → the **relay module** activates the LED bulb.
* When **sufficient brightness** is detected → the **relay module** turns the bulb OFF.

Meanwhile, the ESP32 continuously uploads data such as **LDR sensor readings, light status, and relay state** to **ThingsBoard Cloud**. This enables real-time visualization, analytics, and remote monitoring through an IoT dashboard.

---

## 🧠 Key Features

* ⚡ **Automated Lighting Control** — Lights adjust intelligently based on ambient brightness.
* 🌐 **IoT Cloud Integration** — Real-time telemetry sent to **ThingsBoard Cloud** via **MQTT**.
* 📶 **Wi-Fi-Enabled ESP32** — Acts as the system’s brain and gateway to the cloud.
* 💾 **Low Power Consumption** — Efficient, scalable, and designed for smart home integration.
* 🧰 **Modular Hardware Design** — Simple and safe circuit wiring using 5V and 3.3V logic.
* 📊 **Data Visualization** — Live data dashboard on ThingsBoard for LDR and relay states.

---

## 🪛 Hardware Components

| Component               | Quantity | Description                                        |
| ----------------------- | -------- | -------------------------------------------------- |
| ESP32 Dev Board         | 1        | Microcontroller with built-in Wi-Fi & MQTT support |
| LDR Sensor              | 1        | Detects surrounding light intensity                |
| Relay Module (5V)       | 1        | Controls LED bulb switching                        |
| LED Bulb                | 1        | Represents room lighting                           |
| Resistor (220Ω)         | 1        | Current limiting for LED                           |
| Jumper Wires (M-M, M-F) | —        | For making connections                             |
| Breadboard              | 1        | For circuit prototyping                            |

---

## ⚙️ Circuit Connections

| Module              | Pin         | Connected To                 |
| ------------------- | ----------- | ---------------------------- |
| **LDR Sensor**      | VCC         | ESP32 **Vin (5V)**           |
|                     | GND         | ESP32 **GND**                |
|                     | DO          | ESP32 **D34**                |
| **Relay Module**    | VCC         | ESP32 **3.3V**               |
|                     | GND         | ESP32 **GND**                |
|                     | IN          | ESP32 **D23**                |
|                     | COM         | ESP32 **3.3V**               |
|                     | NO          | One end of **220Ω resistor** |
| **Resistor (220Ω)** | Other end   | LED **Anode (+)**            |
| **LED Bulb**        | Cathode (−) | ESP32 **GND**                |

---

## 🧩 Working Principle

1. The **LDR** continuously measures surrounding light intensity.
2. Based on the threshold, the **ESP32** decides whether it’s bright or dark.
3. When darkness is detected, the **relay** activates the LED bulb.
4. When light is detected, the **relay** deactivates the bulb.
5. The system publishes **JSON telemetry** (LDR value, brightness status, relay state) to **ThingsBoard Cloud** every 3 seconds via MQTT.

Example Telemetry Payload:

```json
{
  "ldr_value": 1567,
  "light_status": 0,
  "relay_state": 1
}
```

---

## ☁️ Cloud Integration (ThingsBoard)

* Platform: **ThingsBoard Cloud** (MQTT-based IoT platform)
* Protocol: **MQTT (Port 1883)**
* Device Token: `L3aElpLH1oHyZQEKGvMa`
* Data Stream: `v1/devices/me/telemetry`

The ESP32 connects to Wi-Fi and authenticates with ThingsBoard using the **Access Token**.
All sensor and device states are then visualized on a customizable **ThingsBoard Dashboard**.

---

## 🧠 Code Logic Highlights

The logic is written in **C++ using Arduino IDE**.

Key snippets:

```cpp
#define LDR_PIN 34
#define RELAY_PIN 23

int ldrValue = analogRead(LDR_PIN);
bool bright = (ldrValue < 2000);  // Threshold check
```

Relay control logic:

```cpp
if (bright) {
  digitalWrite(RELAY_PIN, HIGH);  // LED OFF
} else {
  digitalWrite(RELAY_PIN, LOW);   // LED ON
}
```

MQTT publishing:

```cpp
String payload = "{\"ldr_value\":" + String(ldrValue) +
                 ",\"light_status\":" + String(bright ? 1 : 0) +
                 ",\"relay_state\":" + String(relayState) + "}";
client.publish("v1/devices/me/telemetry", payload.c_str());
```

---

## 📈 Real-Time Monitoring Dashboard

You can visualize data in **ThingsBoard** using widgets like:

* 🌞 **Light Intensity Graph** (LDR Value vs Time)
* 💡 **LED Status Indicator**
* ⚙️ **Relay ON/OFF Toggle**
* 📊 **Live Telemetry Feed**

This provides an interactive, real-time insight into environmental lighting and device behavior.

---

## 🧠 Future Enhancements

* 🔋 Integration with **Solar Panels** or **Power Monitoring Sensors**
* 📱 Mobile Dashboard for remote control and alerts
* 🧠 Adaptive thresholding using **Machine Learning**
* 🌍 Integration with **Google Home / Alexa** for voice-based control
* 🕓 Scheduling and energy usage analytics

---

## 🧾 Summary

This **IoT Smart Lighting System** is a **complete automation solution** for intelligent light management.
It merges **hardware sensing**, **cloud connectivity**, and **real-time analytics** to demonstrate how modern IoT systems can improve energy efficiency, comfort, and automation at minimal cost.

---

## 📸 (Optional: Add These Sections Later)

* 🔌 **Circuit Diagram** (upload schematic image)
* 🧠 **ThingsBoard Dashboard Screenshot**
* 🎥 **Demo Video / GIF of Live Working**

---

## 👨‍💻 Author

**Aditya Raj**

B.Tech in Information Technology
IoT | Embedded Systems | AI | Cloud Integrations


### ⭐ If you like this project, don’t forget to star this repository!

---

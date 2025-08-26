# ArduinoUNO_SerialClock
arduino uno based serial updated clock with bluetooth hc 05 /06 support


## 🕒 Arduino Daily Alarm with EEPROM Persistence

A simple yet powerful Arduino sketch that lets you set a daily alarm using serial commands. The alarm persists across power cycles using EEPROM, and triggers a relay at the specified time.

### 🚀 Features

- ⏰ **Daily Alarm**: Set an alarm that triggers every day at the same time  
- 💾 **EEPROM Storage**: Alarm settings are saved even after power loss  
- 🔌 **Relay Control**: Activates a relay when the alarm goes off  
- 🧠 **Serial Commands**: Easily set time, alarm, and view status via Serial Monitor  
- 🧹 **Clear Alarm**: Remove saved alarm with a single command

---

### 🧰 Hardware Requirements

- Arduino Uno (or compatible board)  
- Relay module connected to pin `13`  
- USB connection for Serial Monitor

---

### 📦 Installation

1. Clone this repository  
   ```bash
   git clone https://github.com/yourusername/arduino-daily-alarm.git
   ```
2. Open the `.ino` file in the Arduino IDE  
3. Upload to your board  
4. Open Serial Monitor at `9600 baud`

---

### 🧪 Serial Commands

| Command         | Description                        | Example         |
|----------------|------------------------------------|-----------------|
| `TIME hh:mmAM/PM`   | Set current time                   | `TIME 3:45PM`   |
| `ALARM hh:mmAM/PM`  | Set and save alarm                 | `ALARM 7:30AM`  |
| `READ`          | Show current time and next alarm   | `READ`          |
| `CLEARALARM`    | Remove alarm from EEPROM           | `CLEARALARM`    |

---

### 🔔 Alarm Behavior

- Triggers once per day at the set time  
- Pulses the relay 5 times (500ms ON/OFF)  
- Resets daily so it can trigger again tomorrow

---

### 📁 EEPROM Usage

| Address | Purpose       | Value Range |
|---------|---------------|-------------|
| `0`     | Alarm Hour    | `1–12` or `255` (cleared) |
| `1`     | Alarm Minute  | `0–59` or `255` (cleared) |
| `2`     | AM/PM Flag    | `0 = AM`, `1 = PM`, `255 = cleared` |

---

### 🧠 Future Ideas

- Multiple alarms  
- Weekday scheduling  
- Snooze functionality  
- RTC module integration for real-time accuracy

---

### 📸 Preview

> _Imagine a simple relay clicking on at 7:30AM every day, even after a power outage. That’s the magic of EEPROM._

---

### 🛠 License

This project is open-source under the MIT License. Feel free to modify and share!

---

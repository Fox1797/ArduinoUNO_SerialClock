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
- Relay module or whaterver you want to control connected to pin `13`   (can be customized)
- USB connection for Serial Monitor or use hc-05 /hc-06 connected to tx and rx of arduino to remotly updated and read the time

---

### 📦 Installation

1. Open the `.ino` file in the Arduino IDE  
2. Upload to your board  
3. Open Serial Monitor at `9600 baud`

---

### 🧪 Serial Commands

| Command         | Description                        | Example         |
|----------------|------------------------------------|-----------------|
| `TIME=hh:mmAM/PM`   | Set current time                   | `TIME=3:45PM`   |
| `ALARM=hh:mmAM/PM`  | Set and save alarm                 | `ALARM=7:30AM`  |
| `READ`          | Show current time and next alarm   | `READ`          |
| `CLEARALARM`    | Remove alarm from EEPROM           | `CLEARALARM`    |

---

### ⏰ Alarm Behavior

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

###  Future Ideas

- Multiple alarms  
- Weekday scheduling  
- Snooze functionality  
- RTC module integration for real-time accuracy. I built this as the rtc module never arrived so had to improvise...

---

### 🛠 License

This project is open-source under the MIT License. Feel free to modify and share!

---

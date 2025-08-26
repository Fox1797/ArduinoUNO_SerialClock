#include <EEPROM.h>

const int relayPin = 13;

int currentHour = 12;
int currentMinute = 0;
bool isPM = false;

int alarmHour = -1;
int alarmMinute = -1;
bool alarmIsPM = false;
bool alarmTriggered = false;

unsigned long lastMillis = 0;

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Relay OFF
  Serial.begin(9600);
  lastMillis = millis();
  loadAlarmFromEEPROM();
}

void loop() {
  updateTime();
  checkSerial();
  checkAlarm();
}

void updateTime() {
  unsigned long currentMillis = millis();
  if (currentMillis - lastMillis >= 60000) {
    lastMillis = currentMillis;
    currentMinute++;
    if (currentMinute >= 60) {
      currentMinute = 0;
      currentHour++;
      if (currentHour > 12) {
        currentHour = 1;
      } else if (currentHour == 12) {
        isPM = !isPM;
      }
    }
  }
}

void checkSerial() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    if (input.startsWith("TIME")) {
      setTime(input);
    } else if (input.startsWith("ALARM")) {
      setAlarm(input);
    } else if (input == "READ") {
      readTime();
    } else if (input == "CLEARALARM") {
      clearAlarm();
    }
  }
}

void setTime(String cmd) {
  int h, m;
  bool pm;
  if (parseTime(cmd.substring(5), h, m, pm)) {
    currentHour = h;
    currentMinute = m;
    isPM = pm;
    Serial.println("Time set.");
  } else {
    Serial.println("Invalid TIME format.");
  }
}

void setAlarm(String cmd) {
  int h, m;
  bool pm;
  if (parseTime(cmd.substring(6), h, m, pm)) {
    alarmHour = h;
    alarmMinute = m;
    alarmIsPM = pm;
    alarmTriggered = false;
    saveAlarmToEEPROM();
    Serial.println("Alarm set and saved.");
  } else {
    Serial.println("Invalid ALARM format.");
  }
}

void clearAlarm() {
  alarmHour = -1;
  alarmMinute = -1;
  alarmIsPM = false;
  alarmTriggered = false;

  EEPROM.update(0, 255);
  EEPROM.update(1, 255);
  EEPROM.update(2, 255);

  Serial.println("Alarm cleared.");
}

void readTime() {
  Serial.print("Current Time: ");
  Serial.print(currentHour);
  Serial.print(":");
  if (currentMinute < 10) Serial.print("0");
  Serial.print(currentMinute);
  Serial.println(isPM ? " PM" : " AM");

  if (alarmHour != -1) {
    Serial.print("Next Alarm: ");
    Serial.print(alarmHour);
    Serial.print(":");
    if (alarmMinute < 10) Serial.print("0");
    Serial.print(alarmMinute);
    Serial.println(alarmIsPM ? " PM" : " AM");
  } else {
    Serial.println("No alarm set.");
  }
}

bool parseTime(String timeStr, int &h, int &m, bool &pm) {
  timeStr.trim();
  int colonIndex = timeStr.indexOf(':');
  if (colonIndex == -1) return false;

  String hourStr = timeStr.substring(0, colonIndex);
  String minStr = timeStr.substring(colonIndex + 1);
  minStr.trim();

  if (minStr.endsWith("AM")) {
    pm = false;
    minStr = minStr.substring(0, minStr.length() - 2);
  } else if (minStr.endsWith("PM")) {
    pm = true;
    minStr = minStr.substring(0, minStr.length() - 2);
  } else {
    return false;
  }

  h = hourStr.toInt();
  m = minStr.toInt();

  return (h >= 1 && h <= 12 && m >= 0 && m < 60);
}

void checkAlarm() {
  if (alarmHour == -1) return;

  if (!alarmTriggered &&
      currentHour == alarmHour &&
      currentMinute == alarmMinute &&
      isPM == alarmIsPM) {
    Serial.println("🔔 Alarm Triggered!");
    pulseRelay(5);
    alarmTriggered = true;
  }
}

void pulseRelay(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(relayPin, LOW);  // Relay ON
    delay(500);
    digitalWrite(relayPin, HIGH); // Relay OFF
    delay(500);
  }
}

void saveAlarmToEEPROM() {
  EEPROM.update(0, alarmHour);
  EEPROM.update(1, alarmMinute);
  EEPROM.update(2, alarmIsPM ? 1 : 0);
}

void loadAlarmFromEEPROM() {
  int h = EEPROM.read(0);
  int m = EEPROM.read(1);
  int pmFlag = EEPROM.read(2);

  if (h == 255 || m == 255 || pmFlag == 255) {
    alarmHour = -1;
    alarmMinute = -1;
    alarmIsPM = false;
  } else {
    alarmHour = h;
    alarmMinute = m;
    alarmIsPM = (pmFlag == 1);
  }

  alarmTriggered = false;
}

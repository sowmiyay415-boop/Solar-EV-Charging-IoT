/*
  Solar Power Wireless Charging Station for EV with IoT
  ESP32 demo firmware: monitors solar/battery voltage and charging current,
  then publishes readings to Serial Monitor.

  IMPORTANT:
  - This is a monitoring/demo sketch, not an EV battery charger controller.
  - Use only a low-voltage, protected prototype and compatible sensors.
  - Do not connect this directly to a full-size EV battery or mains voltage.
  - Calibrate voltage/current sensor scale factors before use.
*/

#include <Arduino.h>

// Example analog input pins on ESP32. Adjust for your board and wiring.
const int SOLAR_VOLTAGE_PIN = 34;
const int BATTERY_VOLTAGE_PIN = 35;
const int CURRENT_SENSOR_PIN = 32;

// Set these calibration values for your actual sensor modules.
// Voltage divider/module scale factor: volts at input = ADC volts * factor.
const float SOLAR_VOLTAGE_FACTOR = 5.0;
const float BATTERY_VOLTAGE_FACTOR = 5.0;

// Example ACS712-style current sensor settings; calibrate for your module.
// These defaults are illustrative and must be adjusted before use.
const float ADC_REFERENCE_V = 3.3;
const float ADC_MAX_VALUE = 4095.0;
const float CURRENT_ZERO_V = 1.65;
const float CURRENT_SENSITIVITY_V_PER_A = 0.100; // e.g. 20A module; verify yours

unsigned long lastSample = 0;
const unsigned long SAMPLE_INTERVAL_MS = 2000;

float readAdcVoltage(int pin) {
  int raw = analogRead(pin);
  return (raw / ADC_MAX_VALUE) * ADC_REFERENCE_V;
}

float readSolarVoltage() {
  return readAdcVoltage(SOLAR_VOLTAGE_PIN) * SOLAR_VOLTAGE_FACTOR;
}

float readBatteryVoltage() {
  return readAdcVoltage(BATTERY_VOLTAGE_PIN) * BATTERY_VOLTAGE_FACTOR;
}

float readCurrentAmps() {
  float sensorVoltage = readAdcVoltage(CURRENT_SENSOR_PIN);
  return (sensorVoltage - CURRENT_ZERO_V) / CURRENT_SENSITIVITY_V_PER_A;
}

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  delay(500);
  Serial.println();
  Serial.println("Solar EV Wireless Charging IoT Demo");
  Serial.println("Monitoring only - calibrate sensors before use.");
}

void loop() {
  if (millis() - lastSample >= SAMPLE_INTERVAL_MS) {
    lastSample = millis();

    float solarV = readSolarVoltage();
    float batteryV = readBatteryVoltage();
    float currentA = readCurrentAmps();

    Serial.println("---- Live System Data ----");
    Serial.printf("Solar voltage: %.2f V\n", solarV);
    Serial.printf("Battery voltage: %.2f V\n", batteryV);
    Serial.printf("Charging current: %.2f A\n", currentA);

    if (solarV < 1.0) {
      Serial.println("Solar status: Low / no solar input");
    } else {
      Serial.println("Solar status: Input detected");
    }

    if (currentA > 0.10) {
      Serial.println("Charging status: Current detected (verify sensor direction)");
    } else {
      Serial.println("Charging status: No significant current detected");
    }

    Serial.println("--------------------------");
  }
}

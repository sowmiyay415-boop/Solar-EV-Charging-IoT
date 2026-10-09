# Solar Power Wireless Charging Station for Electric Vehicle with IoT

## Project overview
This repository contains starter ESP32 firmware for monitoring a small, low-voltage solar-powered wireless-power-transfer demonstration. It reads solar voltage, battery voltage, and current-sensor data and prints a live status report to the Serial Monitor.

**This is not a complete EV charger and does not control battery charging.** Use a separate, correctly rated wireless power transfer module and a compatible protected low-voltage battery charging circuit.

## Hardware (prototype)
- ESP32 development board
- Low-voltage solar panel
- Solar charge controller suitable for the selected battery chemistry
- Protected low-voltage battery and compatible charger/BMS
- Wireless power transfer transmitter/receiver module rated for the demonstration
- Two voltage sensor/divider modules compatible with the ESP32 input range
- Current sensor module compatible with the ESP32 ADC
- Common ground for sensor outputs and ESP32, where required by the sensor design

## Example pin mapping
| Signal | ESP32 pin |
|---|---:|
| Solar voltage sensor analog output | GPIO 34 |
| Battery voltage sensor analog output | GPIO 35 |
| Current sensor analog output | GPIO 32 |

Check your specific modules' datasheets and wiring before connecting. ESP32 ADC pins must never receive a voltage above the board's allowed input range.

## Software setup
1. Install Arduino IDE.
2. Add ESP32 board support in Arduino IDE's Boards Manager.
3. Open `Solar_EV_Charging_IoT.ino`.
4. Select the correct ESP32 board and serial port.
5. Verify the pin mapping and sensor calibration constants.
6. Upload the sketch and open Serial Monitor at **115200 baud**.

## Sensor calibration
The voltage scaling constants and current sensor zero/sensitivity values in the sketch are examples only. Calibrate them against a suitable multimeter and the exact sensor module. Current sensor output may be noisy; average samples if needed.

## IoT dashboard extension
To send readings to Blynk or ThingSpeak, add the relevant library and credentials locally, then publish the measured values over Wi-Fi. Do not commit Wi-Fi passwords, API keys, or tokens to a public repository. This starter version prints readings locally and does not upload data to a cloud service yet.

## Safety
- Prototype with low voltage only.
- Do not connect this project to a full-size EV battery or mains supply.
- Use a battery-specific charge controller/BMS and appropriate fusing.
- Keep metal objects away from inductive charging coils while powered.
- Follow the wireless power module manufacturer's current, spacing, and thermal limits.

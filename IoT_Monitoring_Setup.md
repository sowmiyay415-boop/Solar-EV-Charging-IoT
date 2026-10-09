# IoT monitoring setup (next step)

The supplied sketch currently outputs readings to the Arduino Serial Monitor. For remote IoT monitoring:

1. Choose Blynk IoT or ThingSpeak.
2. Create a private device/channel and define fields for solar voltage, battery voltage, and charging current.
3. Add the platform's ESP32 library and Wi-Fi connection code.
4. Publish readings at a reasonable interval (for example, every 5–10 seconds).
5. Keep credentials in a separate local header file that is excluded from Git, or enter them only in a private development environment.

Never upload Wi-Fi passwords, authentication tokens, or API keys to a public GitHub repository.

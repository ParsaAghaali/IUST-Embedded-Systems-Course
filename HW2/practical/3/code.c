#include <Arduino.h>

#define BUTTON_PIN 4  // GPIO pin connected to the button
#define LED_PIN 2     // GPIO pin connected to the LED

volatile bool ledState = false;  // LED state (on/off)
volatile bool buttonPressed = false;  // Debounced button state

void IRAM_ATTR handleButtonInterrupt() {
  static unsigned long lastInterruptTime = 0;  // Timestamp of the last interrupt
  unsigned long currentTime = millis();

  // Debouncing: Only trigger if > 50ms since the last interrupt
  if (currentTime - lastInterruptTime > 50) {
    buttonPressed = true;  // Flag the button press
    lastInterruptTime = currentTime;
  }
}

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);  // Turn LED off initially

  // Initialize the button pin as an input with an internal pull-up resistor
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Attach interrupt to the button pin (falling edge triggers interrupt)
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleButtonInterrupt, FALLING);

  Serial.begin(115200);  // Initialize serial for debugging
}

void loop() {
  if (buttonPressed) {
    // Toggle LED state
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState ? HIGH : LOW);

    Serial.println(ledState ? "LED ON" : "LED OFF");

    buttonPressed = false;  // Reset button press flag
  }
}

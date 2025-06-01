#include <Arduino.h>

// Simulating a memory-mapped sensor address
volatile uint32_t* sensorRegister = (uint32_t*)0x3FF44000; // Dummy memory address

void setup() {
  Serial.begin(115200); // Start serial communication

  // Initialize the simulated sensor value
  *sensorRegister = 100; // Initial value for simulation
}

void loop() {
  const int numCycles = 10; // Number of cycles to read the sensor
  uint32_t values[numCycles]; // Array to store the 10 values
  uint32_t sum = 0; // To calculate the total sum

  // Loop to read sensor values
  for (int i = 0; i < numCycles; i++) {
    uint32_t value = *sensorRegister; // Read the sensor value
    values[i] = value; // Store the value in the array
    sum += value; // Add to the sum

    Serial.println("Cycle " + String(i + 1) + ": Sensor Value = " + String(value));

    delay(10); // Wait for 10ms between readings

    // Simulate a fluctuating sensor value for the next reading
    *sensorRegister = random(90, 110);
  }

  // Calculate the average with two decimal points
  float average = sum / (float)numCycles;

  // Print all values
  Serial.println("\nAll Sensor Values:");
  for (int i = 0; i < numCycles; i++) {
    Serial.println("Value " + String(i + 1) + ": " + String(values[i]));
  }

  // Print the average value with two decimal places
  Serial.print("\nAverage Sensor Value: ");
  Serial.println(average, 2); // Print with 2 decimal points
  boolean x = true;
  // Stop execution
  while (x) {
    delay(6000);
    x=false;
  }
}

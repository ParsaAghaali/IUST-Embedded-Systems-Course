#include <Arduino.h>

// Custom delay function using microseconds
void custom_delay_ms(uint32_t delay_ms) {
    uint32_t start_time = micros();
    uint32_t delay_micros = delay_ms * 1000;
    
    while (micros() - start_time < delay_micros) {
        // Wait until desired delay is reached
    }
}

void setup() {
    Serial.begin(115200);
    
}
int x = 0;
void loop() {
    Serial.println("Starting delay...");
    Serial.println(x);
    x = x+1;
    custom_delay_ms(500);  // 500ms delay
    Serial.println("500ms passed!");
}
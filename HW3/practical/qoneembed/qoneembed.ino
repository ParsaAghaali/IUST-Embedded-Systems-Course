#include <WiFi.h>
#include <WiFi.h>
#include <WiFiClient.h>
const char* ssid = "ParsaTCL";
const char* password = "255252343334";
const char* serverHost = "192.168.1.100";  
const int serverPort = 80;               
WiFiClient client;
void setup() {
  Serial.begin(115200);  
  connectToWiFi();
  sendHeartbeat();
}

void loop() {
  Serial.println("Going to deep sleep for 10 minutes...");
  ESP.deepSleep(600000000); 
}

void connectToWiFi() {
  Serial.println("ESP32 Waking Up...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  Serial.println("Wi-Fi connected!");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());
}

void sendHeartbeat() {
  Serial.println("Connecting to server...");

  if (client.connect(serverHost, serverPort)) {
    Serial.println("Connected to server. Sending Heartbeat...");

    client.println("GET /heartbeat HTTP/1.1");
    client.println("Host: " + String(serverHost));
    client.println("Connection: close");
    client.println(); 

    client.stop();
    Serial.println("Heartbeat sent. Server connection closed.");
  } else {
    Serial.println("Failed to connect to server.");
  }
}

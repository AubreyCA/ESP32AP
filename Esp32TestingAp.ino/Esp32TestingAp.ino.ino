#include <WiFi.h>

const char* apSSID = "ESP32_AP"; // SSID for ESP32 Access Point
const char* apPassword = "123"; // Password for ESP32 Access Point

// Static IP configuration
IPAddress local_IP(192, 168, 1, 1); // Static IP address for the ESP32
IPAddress gateway(192, 168, 1, 1); // Gateway address
IPAddress subnet(255, 255, 255, 0); // Subnet mask

WiFiServer server(12345); // Port number for the server

void setup() {
  Serial.begin(115200);

  // Set up the ESP32 as an Access Point with a static IP
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(apSSID, apPassword);
  Serial.println("Access Point started");

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Start the server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("New Client Connected");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r');
        Serial.println("Request: " + request);
        client.flush();
        String message = "Hello from ESP32! This is some data.";
        client.println(message);
        Serial.println("Data sent to client: " + message);

        // Send a response
        client.print("Message received from ESP32!");
        
        // Close the connection
        client.stop();
        Serial.println("Client Disconnected");
      }
    }
  }
}

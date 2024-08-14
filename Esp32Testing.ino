#include <WiFi.h>

const char* ssid = "IMO Q2 Plus"; // Replace with your WiFi SSID
const char* password = "32ecaae6"; // Replace with your WiFi password

WiFiServer server(80); // Port 80 for HTTP
IPAddress local_IP(192, 168, 1, 43);
IPAddress gateway(192, 168, 130, 173); //needs to be checked on the router
IPAddress dns(192, 168, 130, 173); //needs to be checked on the router
IPAddress dns2(0, 0, 0, 0);
IPAddress subnet(255, 255, 255, 0);


void setup() {
  Serial.begin(115200);
  // if (!WiFi.config(local_IP, gateway, subnet, dns, dns2)) {
  //   Serial.println("STA Failed to configure");
  // }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.gatewayIP());
  Serial.println(WiFi.dnsIP(0));
  Serial.println(WiFi.dnsIP(1));
  Serial.println(WiFi.subnetMask());



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
        
        // Send a response
        client.print("HTTP/1.1 200 OK\r\n");
        client.print("Content-Type: text/plain\r\n");
        client.print("Connection: close\r\n");
        client.print("\r\n");
        client.print("Hello from ESP32!");
        
        // Close the connection
        client.stop();
        Serial.println("Client Disconnected");
      }
    }
  }
}

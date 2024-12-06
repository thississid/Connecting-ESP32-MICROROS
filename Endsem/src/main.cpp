#include <WiFi.h>

// Replace with your WiFi credentials
const char* ssid = "2";       // Your WiFi SSID
const char* password = ""; // Your WiFi password

WiFiServer server(80); // Create a web server on port 80

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConnected to WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Start the server
  server.begin();
  Serial.println("Server started.");

  // Initialize onboard LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); // Ensure LED is off initially
}

void loop() {
  // Check if a client is connected
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client connected.");
    String request = "";
    
    // Read the client request
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request += c;

        // Break out of loop once the request ends
        if (request.endsWith("\r\n\r\n")) break;
      }
    }

    // Debug: Print the request to the Serial Monitor
    Serial.println(request);

    // Parse the request for LED control
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(LED_BUILTIN, HIGH); // Turn ON the LED
      Serial.println("LED turned ON");
    } else if (request.indexOf("/LED=OFF") != -1) {
      digitalWrite(LED_BUILTIN, LOW);  // Turn OFF the LED
      Serial.println("LED turned OFF");
    }

    // Send an HTTP response to the client
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("Connection: close");
    client.println();
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
    client.println("<h1>ESP32 LED Control</h1>");
    client.println("<p><a href=\"/LED=ON\">Turn LED ON</a></p>");
    client.println("<p><a href=\"/LED=OFF\">Turn LED OFF</a></p>");
    client.println("</html>");

    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
  }
}
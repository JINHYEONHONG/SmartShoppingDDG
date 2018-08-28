#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;
uint8_t pin_led = 16;
char* ssid = "iptime";
char* password = "";

void setup() {
  pinMode(pin_led, OUTPUT);
  WiFi.begin(ssid, password);
  Serial.begin(115200);
  while(WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.print("IP Address: ");
  Serial.print(WiFi.localIP());

  server.on("/",[](){server.send(200, "text/html", "<h1>Hello World</h1>");});
  server.on("/toggle", toggleLED);
  server.begin();
}

void loop() {
  server.handleClient();
}

void toggleLED() {
  digitalWrite(pin_led, !digitalRead(pin_led));
  server.send(204, "");
}

-------------------------------------------------------------

#include <ESP8266WiFi.h>
const char* ssid  = "mqtt";
const char* password = "coap12345678";
const char* host = "google.com";
const char* passcode = "gksdldma";
//IPAddress server(74,125,115,105);

// Wake from sleep, in seconds.
#define wakeuptime 30

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);

  // Connect to host
  Serial.print("Connecting to ");
  Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connection failed!");
    return;
  }

/*
  // Create a URL for the request. Modify YOUR_HOST_DIRECTORY so that you're pointing to the PHP file.
  String url = "/YOUR_HOST_DIRECTORY/index.php?s1=";
  url += switch1;
  url += "&s2=";
  url += switch2;
  url += "&pass=";
  url += passcode;

  // This will send the request to the server
  Serial.print("Requesting URL: ");
  Serial.println(url);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
/*
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  */

  Serial.println();
  Serial.println("Closing connection");
  
  // Sleep
  Serial.println("Going to sleep");
  delay(5000);
  ESP.deepSleep(wakeuptime * 1000000, WAKE_RF_DEFAULT);
  delay(5000);
}

void loop() {
}

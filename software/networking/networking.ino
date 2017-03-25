#include <Adafruit_NeoPixel.h>

//#include <JsonListener.h>
//#include <JsonStreamingParser.h>

#include <ArduinoJson.h>

/*
   Simple HTTP get webclient test
*/

#include <ESP8266WiFi.h>

const char* ssid     = "MHacks";
const char* password = "mhacks9design";

const char* host = "mhacks.github.io";

char basic[] = "{\"basic\":\"1234\"}";

Adafruit_NeoPixel leds = Adafruit_NeoPixel(2, 15, NEO_GRB + NEO_KHZ800);


void setup() {
  Serial.begin(9600);
  delay(100);

  // We start by connecting to a WiFi network

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

 leds.begin();
 leds.show();
}

int value = 0;

void loop() {
  delay(5000);
  ++value;

  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request
  String url = "/ws2812-test.html";
  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);
  //JsonObject& root = jsonBuffer.parseObject(basic);

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    const String data = client.readStringUntil('\r');
    StaticJsonBuffer<2000> jsonBuffer;
    Serial.println(data);
    JsonObject& root = jsonBuffer.parseObject((data.c_str()));
    Serial.print("See what's next to me?");
    Serial.println(root.containsKey("test"));
    if(root.containsKey("test"))
    {
      const char * what_we_wanted = root["test"];
      int red_one = root["red-1"];
      int green_one = root["green-1"];
      int blue_one = root["blue-1"];
      int red_two = root["red-2"];
      int green_two = root["green-2"];
      int blue_two = root["blue-2"];
      leds.setPixelColor(0, red_one, green_one, blue_one);
      leds.setPixelColor(1, red_two, green_two, blue_two);
      leds.setBrightness(50);
      leds.show();
      Serial.println(what_we_wanted);
      Serial.println(red_one);
      Serial.println(green_one);
      Serial.println(blue_one);
      Serial.println(red_two);
      Serial.println(green_two);
      Serial.println(blue_two);
    }
  }

  Serial.println();
  Serial.println("closing connection");
}


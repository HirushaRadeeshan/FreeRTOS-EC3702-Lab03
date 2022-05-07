#include <WiFi.h> //wifi.h header

const char* ssid     = "EN20404482";  //defining name of the HOTSPOT
const char* password = "12hirusha";   //defining the password of HOTSPOT


WiFiServer server(80);
static SemaphoreHandle_t mutex;

String header;

String output22State = "off";
String output23State = "off";

const int output22 = 22;
const int output23 = 23;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

void C1Task(void *parameters) {     //creating task function
  WiFi.begin(ssid, password);       //calling wifi.begin
  Serial.print("Connecting to ");
  Serial.print(ssid);

  while (WiFi.status() != WL_CONNECTED) {   //checking weather connected to hotspot
    delay(500);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.println("Connection established!");
  Serial.print("IP address:\t");      //printing local IP address
  Serial.println(WiFi.localIP());     //calling WiFi.localIP to return local IP


  Serial.print("Connected to hotspot on CORE ");
  Serial.println(xPortGetCoreID());   //findout the core ID

  vTaskDelete(NULL);                  //delete task
}

void C2Task(void *parameters) {     //creating task function
  while (1) {
    if (xSemaphoreTake(mutex, 0) == pdTRUE) {

      WiFiClient client = server.available();   // Listen for incoming clients

      if (client) {                             // If a new client connects,
        delay(100);
        Serial.println(">>>>>>>>>>>>");
        currentTime = millis();
        previousTime = currentTime;
        Serial.println("New Client.");          // print a message out in the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
          currentTime = millis();
          if (client.available()) {             // if there's bytes to read from the client,
            char c = client.read();              // read a byte, then
            Serial.write(c);                    // print it out the serial monitor
            header += c;
            if (c == '\n') {                    // if the byte is a newline character
              // if the current line is blank, you got two newline characters in a row.
              // that's the end of the client HTTP request, so send a response:
              if (currentLine.length() == 0) {
                // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                // and a content-type so the client knows what's coming, then a blank line:
                client.println("HTTP/1.1 200 OK");
                client.println("Content-type:text/html");
                client.println("Connection: close");
                client.println();

                // turns the GPIOs on and off
                if (header.indexOf("GET /22/on") >= 0) {
                  Serial.println("GPIO 22 on");
                  output22State = "on";
                  digitalWrite(output22, HIGH);
                } else if (header.indexOf("GET /22/off") >= 0) {
                  Serial.println("GPIO 22 off");
                  output22State = "off";
                  digitalWrite(output22, LOW);
                } else if (header.indexOf("GET /23/on") >= 0) {
                  Serial.println("GPIO 23 on");
                  output23State = "on";
                  digitalWrite(output23, HIGH);
                } else if (header.indexOf("GET /23/off") >= 0) {
                  Serial.println("GPIO 23 off");
                  output23State = "off";
                  digitalWrite(output23, LOW);
                }

                // Display the HTML web page
                client.println("<!DOCTYPE html><html>");
                client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=2\">");
                client.println("<link rel=\"icon\" href=\"data:,\">");
                // CSS to style the on/off buttons
                // Feel free to change the background-color and font-size attributes to fit your preferences
                client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                client.println(".button { background-color: yellow; border: none; color: blue; padding: 16px 40px;");
                client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                client.println(".button2 {background-color: #555555;}</style></head>");

                // Web Page Heading
                client.println("<body><h1>EN20404482 Lab03 part07 TaskII</h1>");

                // Display current state, and ON/OFF buttons for GPIO 26
                client.println("<p>GPIO 22 - State " + output22State + "</p>");
                // If the output26State is off, it displays the ON button
                if (output22State == "off") {
                  client.println("<p><a href=\"/22/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/22/off\"><button class=\"button button2\">OFF</button></a></p>");
                }

                // Display current state, and ON/OFF buttons for GPIO 27
                client.println("<p>GPIO 23 - State " + output23State + "</p>");
                // If the output27State is off, it displays the ON button
                if (output23State == "off") {
                  client.println("<p><a href=\"/23/on\"><button class=\"button\">ON</button></a></p>");
                } else {
                  client.println("<p><a href=\"/23/off\"><button class=\"button button2\">OFF</button></a></p>");
                }
                client.println("</body></html>");

                // The HTTP response ends with another blank line
                client.println();
                // Break out of the while loop
                break;
              } else { // if you got a newline, then clear currentLine
                currentLine = "";
              }
            } else if (c != '\r') {  // if you got anything else but a carriage return character,
              currentLine += c;      // add it to the end of the currentLine
            }
          }
        }
        // Clear the header variable
        header = "";
        // Close the connection
        client.stop();
        Serial.println("Client disconnected.");
        Serial.println("");
      }
      xSemaphoreGive(mutex);
    } else {

    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(output22, OUTPUT);
  pinMode(output23, OUTPUT);

  digitalWrite(output22, LOW);
  digitalWrite(output23, LOW);

  delay(10);
  Serial.println('\n');

  mutex = xSemaphoreCreateMutex();


  xTaskCreatePinnedToCore(C1Task,
                          "Task A Core0",
                          5000,
                          NULL,
                          1,
                          NULL,
                          0);

  xTaskCreatePinnedToCore(C2Task,
                          "Task B Core1",
                          1024,
                          NULL,
                          1,
                          NULL,
                          1);

  vTaskDelete(NULL);

}

void loop() {

}

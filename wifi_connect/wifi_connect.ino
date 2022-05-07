#include <WiFi.h> //wifi.h header

const char* ssid     = "EN20404482";  //defining name of the HOTSPOT 
const char* password = "12hirusha";   //defining the password of HOTSPOT


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

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  
  
  xTaskCreatePinnedToCore(C1Task,
                          "Task A Core0",
                          4096,
                          NULL,
                          1,
                          NULL,
                          0);
}

void loop() { 
  
}

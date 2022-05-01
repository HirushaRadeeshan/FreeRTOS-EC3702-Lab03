static const int led = LED_BUILTIN;

int value=0;
char val;
String pass;

void toggleLED(void *parameter) {
  
  while(1) {
    digitalWrite(led, HIGH);
    vTaskDelay(pdMS_TO_TICKS( value ));
    digitalWrite(led, LOW);
    vTaskDelay(pdMS_TO_TICKS( value ));
    Serial.print("present LED delay - ");
    Serial.println(value);
  }
}

void input(void *parameter){
 while(1)
 {
  if(Serial.available()>0){   
     val=Serial.read();
     pass=pass+val; 
     value=pass.toInt();     
  }  
  if(Serial.available()==0){
     vTaskDelay(100/portTICK_PERIOD_MS);
     pass="";
  }
 }   
}
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  xTaskCreate(input,"Input",1024,NULL,1,NULL);  
  xTaskCreate(toggleLED,"Toggle",1024,NULL,1,NULL);   
}
void loop() {

}

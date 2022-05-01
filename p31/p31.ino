TaskHandle_t Task_Handle1;

static const int led = LED_BUILTIN;

void Toggle_LED(void *parameter){
  
  while(1){
    digitalWrite(led,HIGH);
    vTaskDelay(pdMS_TO_TICKS( 500 ));
    digitalWrite(led,LOW);
    vTaskDelay(pdMS_TO_TICKS( 500 ));
    Serial.println("Toggle LED with 500ms delay");
  } 
}


void setup() {
  // put your setup code here, to run once:
  pinMode(led,OUTPUT);
  xTaskCreate(Toggle_LED,"Toggle LED with 500ms",1024,NULL,1,&Task_Handle1);

}

void loop() {
  // put your main code here, to run repeatedly:

}

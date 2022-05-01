TaskHandle_t Task_Handle1;

static const int led1 = 23;
static const int led2 = 22;

void Toggle_LED1(void *parameter1){
  
  while(1){
    digitalWrite(led1,HIGH);
    vTaskDelay(pdMS_TO_TICKS( 500 ));
    digitalWrite(led1,LOW);
    vTaskDelay(pdMS_TO_TICKS( 500 ));
    Serial.println("Toggle LED1 with 500ms delay");
  } 
}

void Toggle_LED2(void *parameter2){
  
  while(1){
    digitalWrite(led2,HIGH);
    vTaskDelay(pdMS_TO_TICKS( 300 ));
    digitalWrite(led2,LOW);
    vTaskDelay(pdMS_TO_TICKS( 300 ));
    Serial.println("Toggle LED2 with 300ms delay");
  } 
}


void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  xTaskCreate(Toggle_LED1,"Toggle LED with 500ms",1024,NULL,1,&Task_Handle1);
  xTaskCreate(Toggle_LED2,"Toggle LED with 300ms",1024,NULL,1,&Task_Handle1);

}

void loop() {
  // put your main code here, to run repeatedly:

}

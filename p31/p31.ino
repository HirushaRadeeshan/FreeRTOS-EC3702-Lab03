TaskHandle_t Task_Handle1;

static const int led = LED_BUILTIN; //selecting inbuilt LED pin

void Toggle_LED(void *parameter){   //Function of the Task 
  
  while(1){                         //starting an infinity while loop
    digitalWrite(led,HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    digitalWrite(led,LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    Serial.println("Toggle LED with 500ms delay");
  } 
}

void setup() {

  pinMode(led,OUTPUT);          //setting LED pin as output

  //setting the Task 
  xTaskCreate(Toggle_LED,"Toggle LED with 500ms",1024,NULL,1,&Task_Handle1);

}

void loop() {

}

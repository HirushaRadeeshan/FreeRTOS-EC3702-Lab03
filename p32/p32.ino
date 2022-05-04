TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

static const int led = LED_BUILTIN; //selecting inbuilt LED pin

void Toggle_LED1(void *parameter1){   //Function of the Task1
  
  while(1){                         //starting an infinity while loop
    digitalWrite(led,HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    digitalWrite(led,LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    Serial.println("Toggle LED with 500ms delay");
  } 
}

void Toggle_LED2(void *parameter2){   //Function of the Task2
  
  while(1){                         //starting an infinity while loop
    digitalWrite(led,HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( 300 ));               //300ms delay
    digitalWrite(led,LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( 300 ));               //300ms delay
    Serial.println("Toggle LED with 300ms delay");
  } 
}


void setup() {

  pinMode(led,OUTPUT);          //setting LED pin as output
  //setting the Task1
  xTaskCreate(Toggle_LED1,"Toggle LED with 500ms",1024,NULL,1,&Task_Handle1);
  //setting the Task2
  xTaskCreate(Toggle_LED2,"Toggle LED with 300ms",1024,NULL,1,&Task_Handle2);

}

void loop() {

}

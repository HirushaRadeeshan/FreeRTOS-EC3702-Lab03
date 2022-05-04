TaskHandle_t Task_Handle1;
TaskHandle_t Task_Handle2;

static const int led1 = 23; //selecting 23 GPIO pin as LED1 pin
static const int led2 = 22; //selecting 22 GPIO pin as LED2 pin

void Toggle_LED1(void *parameter1){   //Function of the Task1
  
  while(1){                         //starting an infinity while loop
    digitalWrite(led1,HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    digitalWrite(led1,LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( 500 ));               //500ms delay
    Serial.println("Toggle LED1 with 500ms delay");
  } 
}

void Toggle_LED2(void *parameter2){   //Function of the Task2
  
  while(1){                         //starting an infinity while loop
    digitalWrite(led2,HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( 300 ));               //300ms delay
    digitalWrite(led2,LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( 300 ));               //300ms delay
    Serial.println("Toggle LED2 with 300ms delay");
  } 
}


void setup() {

  Serial.begin(115200);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  xTaskCreate(Toggle_LED1,"Toggle LED with 500ms",1024,NULL,1,&Task_Handle1);
  xTaskCreate(Toggle_LED2,"Toggle LED with 300ms",1024,NULL,1,&Task_Handle2);

}

void loop() {
  // put your main code here, to run repeatedly:

}

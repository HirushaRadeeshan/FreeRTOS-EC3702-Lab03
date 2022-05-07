// Task handles
static TaskHandle_t task_A = NULL;
static TaskHandle_t task_B = NULL;

// TaskA
void TaskA(void *parameters) {

  while(1){             //starting an infinity loop
    Serial.print("I am Task A I am Running on CORE ");    //printing in serial monitor
    Serial.println(xPortGetCoreID());         //printing Core ID on serial monitor
    
    vTaskDelay(pdMS_TO_TICKS( 1000 ));    //giving a delay
  }  
}

// TaskB
void TaskB(void *parameters) {

  while(1){             //starting an infinity loop
    Serial.print("I am Task B I am Running on CORE ");    //printing in serial monitor
    Serial.println(xPortGetCoreID());         //printing Core ID on serial monitor
    
    vTaskDelay(pdMS_TO_TICKS( 1000 ));    //giving a delay
  }  
}


void setup() {

  Serial.begin(115200);

  // Start task A
  xTaskCreatePinnedToCore(TaskA,    //function
                          "Task A Core0", //name of the task
                          1024,         //stack size(bytes)
                          NULL,         //parameter to pass to function
                          1,            //giving lower priority
                          &task_A,       //task handle
                          0);           //Core ID
  
  // Start task 2
  xTaskCreatePinnedToCore(TaskB,    //function
                          "Task B Core1", //name of the task
                          1024,         //stack size(bytes)
                          NULL,         //parameter to pass to function
                          1,            //giving lower priority
                          &task_B,       //task handle
                          1);           //Core ID
  
  // Delete "setup and loop" task
  vTaskDelete(NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}

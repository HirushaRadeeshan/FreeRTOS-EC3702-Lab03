static const int led = LED_BUILTIN; //selecting inbuilt LED as LED

int Delay=100;        //creating a variable to led delay and setting it as 100ms
char val;             //creating a variable to input value
String pass;          //creating a variable to store new delay

void LEDblink(void *parameter) {  //creating task function to blink LED 
  
  while(1) {                         //starting an infinity while loop
    digitalWrite(led, HIGH);                         //light up LED
    vTaskDelay(pdMS_TO_TICKS( Delay ));               //500ms delay
    digitalWrite(led, LOW);                          //turn off LED
    vTaskDelay(pdMS_TO_TICKS( Delay ));               //500ms delay
    Serial.print("present LED delay - ");
    Serial.println(Delay);          //printing LED delay
  }
}

void input(void *parameter){  //creating task function to get input delay

 while(1) {                         //starting an infinity while loop
  if(Serial.available()>0){         //checking availability of input
     val=Serial.read();             //storing input value in val
     pass=pass+val;                 //putting that value to pass string
     Delay=pass.toInt();            //converting to int and storing that value to delay
  }  
  if(Serial.available()==0){        //checking input was not there
     vTaskDelay(100/portTICK_PERIOD_MS);  //giving a delay
     pass="";                       //resetting pass variable
  }
 }   
}
void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);          //setting LED pin as output
  //setting the Task1
  xTaskCreate(input,"Input",1024,NULL,1,NULL);
  //setting the Task2
  xTaskCreate(LEDblink,"Toggle",1024,NULL,1,NULL);   
}
void loop() {

}

#include <Bridge.h>
#include <HttpClient.h>

#define LED1 2
#define LED2 3
#define LED3 4
#define LED4 5
#define LED5 6
#define LED6 7

void controlLed(int signal);

void ioInit(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}

void controlLed(int signal){
  int flag = 0;
  
  Serial.println(char(signal));
  if(signal > 0 && signal < 50){
      flag = signal / 30 + 1;     
  }
  Serial.println(char(flag));
  if(signal >= 50){
    flag = 5;
  }
  
  switch(flag){
    case 1: 
            lightOff(LED2);
            lightOff(LED3);
            lightOff(LED4);
            lightOff(LED5);
            lightOff(LED6);
            twinklLED(LED1);
            Serial.println("a");
            break;
    case 2: 
            lightOff(LED3);
            lightOff(LED4);
            lightOff(LED5);
            lightOff(LED6);
            lightOn(LED1);
            twinklLED(LED2);
            Serial.println("b");
            break;        
    case 3: 
            lightOff(LED4);
            lightOff(LED5);
            lightOff(LED6);
            lightOn(LED1);
            lightOn(LED2);
            twinklLED(LED3);           
            Serial.println("c");
            break;
    case 4: 
            lightOff(LED5);
            lightOff(LED6);
            lightOn(LED1);
            lightOn(LED2);
            lightOn(LED3);
            twinklLED(LED4);
            Serial.println("d");
            break;        
    case 5: lightOn(LED1);
            lightOn(LED2);
            lightOn(LED3);
            lightOn(LED4);
            lightOn(LED5);
            lightOn(LED6);
            Serial.println("e");
            break;
    default: lightOffall();
             Serial.println("0");
             break;
  }
}

void lightOn(int LED){
  digitalWrite(LED, HIGH);
}

void twinklLED(int LED){
  for(int i = 0; i < 50;i++){
    digitalWrite(LED, LOW);
    delay(50);
    digitalWrite(LED, HIGH);
    delay(50);
  }
}

void fireFlush(int LED){
  for(int i = 0; i < 10; i++){
    digitalWrite(LED, LOW);
    delay(30);
    digitalWrite(LED, HIGH);
    delay(30);
  }
}

void lightOffall(){
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
}

void lightOff(int LED){
  digitalWrite(LED, LOW);
}

void setup() {
  // Bridge takes about two seconds to start up
  // it can be helpful to use the on-board LED
  // as an indicator for when it has initialized
  pinMode(13, OUTPUT);
//  digitalWrite(13, LOW);
  Bridge.begin();
//  digitalWrite(13, HIGH);
  ioInit();

  Serial.begin(9600);

//  while (!Serial); // wait for a serial connection
}

int index = 0;
char strValue[6];
int signal;

void loop() {
  // Initialize the client library
  HttpClient client;
  int index = 0;

  // Make a HTTP request:
  client.get("http://localhost/num.txt");

  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();
//    Serial.println(c);
    if (index<2 && isDigit(c)){
      strValue[index++]=c;
    }
    else{
      strValue[index] = 0;
    }
    signal = atoi(strValue);    
  }
//  signal = 20;
//  Serial.flush();
  Serial.println("starting .......");
  Serial.print(signal);
  controlLed(signal);
  Serial.println("ending .......");  
}

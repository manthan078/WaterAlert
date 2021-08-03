 
#include<SoftwareSerial.h>        

SoftwareSerial mySerial(9,10);    

int i = 0;
byte statusLed    = 13;

byte sensorInterrupt = 0;         
byte sensorPin       = 2;

float calibrationFactor = 4.5;

volatile byte pulseCount;  

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

void setup()
{
  
  Serial.begin(9600);

  mySerial.begin(9600);
     
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  
  
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop()
{
   
   if((millis() - oldTime) > 1000)    
   { 
    detachInterrupt(sensorInterrupt);
        
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
    
    oldTime = millis();
    
    
    flowMilliLitres = (flowRate / 60) * 1000;
    
    
    totalMilliLitres += flowMilliLitres;
      
    unsigned int frac;
    
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  
    Serial.print("L/min");
    Serial.print("\t"); 		  

    
    Serial.print("Output Liquid Quantity: ");        
    Serial.print(totalMilliLitres);
    Serial.println("mL"); 
    Serial.print("\t"); 		  
	  Serial.print(totalMilliLitres/1000);
	  Serial.print("L");
    

    pulseCount = 0;
    
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
    int rate = (totalMilliLitres/1000);
    int VALUE = 0,result=0;
   
    if((int)flowRate > VALUE){
   
        for(i=0;i<=1;i++){
          SendMessage();
        }
      }
  }
}
void SendMessage()
{
   mySerial.println("AT+CMGF=1");

  delay(1000);  
  mySerial.println("AT+CMGS=\"+917378709622\"\r");

  delay(100);

  mySerial.println("Paani aala aahe");

  delay(100);

  mySerial.println((char)26);

  delay(100);

}
void pulseCounter()
{
  
  pulseCount++;
} 

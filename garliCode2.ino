

int hotPadPin = 11;
int servoPin = 7;
char val;
int ledPin = 5;
int smallLedPin = 13;
int smallLedOn = 0;


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
int lastPos = pos;
 
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 9 to the servo object 
  pinMode(ledPin, OUTPUT);
  pinMode(hotPadPin, OUTPUT);
  pinMode(smallLedPin, OUTPUT);
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  if (Serial.available()) {
    val = Serial.read();
  }
  
  if (val == '1') {
  
    digitalWrite(hotPadPin, HIGH);
    digitalWrite(smallLedPin, LOW);
  
  } else if (val == '2') {
  
    digitalWrite(hotPadPin, LOW);
    
  } else if (val == '3' && lastPos > 170) {
  
    for(pos = lastPos; pos < 180; pos += 1)  // goes from 180- degrees to 180 degrees 
     {                                  // in steps of 1 degree 
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
     }
     lastPos = pos; 
  
  } else if (val == '4' && lastPos < 10) {
  
     for(pos = lastPos; pos>=1; pos-=1)     // goes from 0+ degrees to 0 degrees 
     {                                
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
     }
     lastPos = pos; 
     
  } else if (val == '5' && lastPos > 80 && lastPos < 100) {
  
    if (lastPos > 90) {
      for(pos = lastPos; pos>=90; pos-=1)     // goes from 90+ degrees to 90 degrees 
      {                                
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
      }
      lastPos = pos;
      
    } else if (lastPos < 90) {
      for(pos = lastPos; pos>90; pos+=1)     // goes from 90- degrees to 90 degrees 
      {                                
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
      }
      lastPos = pos;
    }
  } else if (val == '6') {

    digitalWrite(ledPin, HIGH);
  
  } else if (val == '7') {
  
    digitalWrite(hotPadPin, LOW);
    digitalWrite(ledPin, LOW);
    digitalWrite(smallLedPin, LOW);
    smallLedOn = 0;
   
    if (lastPos > 90) {
      for(pos = lastPos; pos>=90; pos-=1)     // goes from 90+ degrees to 90 degrees 
      {                                
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
      }
      lastPos = 90;
    } else if (lastPos < 90) {
      for(pos = lastPos; pos>90; pos+=1)     // goes from 90- degrees to 90 degrees 
      {                                
       myservo.write(pos);              // tell servo to go to position in variable 'pos' 
       delay(15);                       // waits 15ms for the servo to reach the position 
      }
      lastPos = 90;
    }
 
 // when there's not signal from processing
 } else {
 
   if (smallLedOn == 0) {
   
     digitalWrite(smallLedPin, HIGH);
     smallLedOn = 1;
   
   }
 
 }
 delay(10);
  
} 

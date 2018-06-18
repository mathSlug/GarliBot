/*Controls Garlic Bread robot based on serial input
 * Char '1': Turns on the hot plate 
 * 2: Turns off hot plate
 * 3: Turns the servo to its limit in one direction
 * 4: Turns the servo to the limit in the opposite direction
 * 5: Centers the servo
 * 6: Turns on the LED - ideally an indicator when the bread is finished and must be replace
 * 7: Resets - servo to center, LED and hot plate off - send before replacing bread
 * all else: nothing occurs
 * 
 * Apologies for the hacky code
 */



int hotPadPin = 11;
int servoPin = 7;
char val; // holds character received from serial
int ledPin = 5;
int smallLedPin = 13;
int smallLedOn = 0;


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                
 
int pos = 0;    // variable to store the servo position 
int lastPos = pos;
 
void setup() 
{ 
  myservo.attach(servoPin);  // attaches the servo on pin 7 to the servo object 
  pinMode(ledPin, OUTPUT);
  pinMode(hotPadPin, OUTPUT);
  pinMode(smallLedPin, OUTPUT);
  Serial.begin(9600);
} 
 
 
void loop() 
{ 
  if (Serial.available()) {
    val = Serial.read(); // continually read Serial. If no new serial data is sent, the previous byte's command is executed
                         // This is fine. Servo will stay at commanded position, LED and hot plate state will remain
  }
  
  if (val == '1') {
  
    digitalWrite(hotPadPin, HIGH);
    digitalWrite(smallLedPin, LOW);
  
  } else if (val == '2') {
  
    digitalWrite(hotPadPin, LOW);
    
  } else if (val == '3' && lastPos > 170) {
  
    for(pos = lastPos; pos < 180; pos += 1)   // smoothly move servo, easier on robot structure
     {                                  
       myservo.write(pos);              
       delay(15);                // waits 15ms for the servo to reach the position. reduces jitter        
     }
     lastPos = pos; 
  
  } else if (val == '4' && lastPos < 10) {
  
     for(pos = lastPos; pos>=1; pos-=1)     
     {                                
       myservo.write(pos);              
       delay(15);                       
     }
     lastPos = pos; 
     
  } else if (val == '5' && lastPos > 80 && lastPos < 100) {
  
    if (lastPos > 90) {
      for(pos = lastPos; pos>=90; pos-=1)    
      {                                
       myservo.write(pos);               
       delay(15);                     
      }
      lastPos = pos;
      
    } else if (lastPos < 90) {
      for(pos = lastPos; pos>90; pos+=1)    
      {                                
       myservo.write(pos);              
       delay(15);                       
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
      for(pos = lastPos; pos>=90; pos-=1)     
      {                                
       myservo.write(pos);              
       delay(15);                       
      }
      lastPos = 90;
    } else if (lastPos < 90) {
      for(pos = lastPos; pos>90; pos+=1)    
      {                                
       myservo.write(pos);              
       delay(15);                       
      }
      lastPos = 90;
    }
 
 // when there's not a serial signal
 } else {
 
   if (smallLedOn == 0) {
   
     digitalWrite(smallLedPin, HIGH);
     smallLedOn = 1;
   
   }
 
 }
 delay(10);
  
} 

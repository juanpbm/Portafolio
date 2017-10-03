
#include <IRremote.h>
#include <Servo.h>  // servo library
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

Servo servo1;  // servo control object
Servo servo2;
Servo servo3;
Servo servo4;

const int frontsensor = 1;
const int tempsensor = 0;

float distance, voltage, temp;
void danger();

int s1=100,s2=40,s3=100;

void setup()
{
  servo1.attach(11);
  servo2.attach(12);
  servo3.attach(9);
  servo4.attach(10);
  irrecv.enableIRIn(); 
  Serial.begin(9600);
  servo1.write(100);
  servo2.write(40);
  servo3.write(100);
  pinMode(13,OUTPUT);
}

float getVoltage(int pin)     //input from front sensor
{
  return (analogRead(pin) * 0.004882814);
}

void volt ()    //convert voltage to distance
{
  voltage = getVoltage(frontsensor); //get voltage reading from front sensor
  distance = 2.439 * voltage * voltage - 14.341 * voltage + 21.997; //inches, Volts
}

void danger()
{  
  volt();
  voltage = getVoltage(tempsensor);
  temp = (voltage - 0.5) * 100.0;
  Serial.println(distance);
  if (distance<=1|| temp>120){
  Serial.println("high");
  digitalWrite(13,HIGH);
  }else{ 
  Serial.println("low");
  digitalWrite(13,LOW);
  }  
}


void loop()
{
  danger();
  int position;
 if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    delay(20);
    switch (results.value) {
      //360
      case 1168:
      if (s1<=180)
      s1+=5;
      servo1.write(s1);
      break;
      case 3216:
      if (s1>=0)
      s1-=5;
      servo1.write(s1);
      //delay(1);
      break;
      //2
       case 2192:
      if (s2<=130)
      s2+=5;
      servo2.write(s2);
      //delay(1);
      break;
      case 144:
      if (s2>=0)
      s2-=5;
      servo2.write(s2);
      //delay(1);
      break;
      //3
      case 16:
      if (s3<=180)
      s3+=5;
      servo3.write(s3);
      //delay(1);
      break;
      case 1040:
      if (s3>=50)
      s3-=5;
      servo3.write(s3);
      //delay(1);
      break;
      //claw
      case 3344:
      servo4.write(180);
      break;
      case 2640:
      servo4.write(0);
      break;
    }
    irrecv.resume();

    danger();
 }
 danger();
} 

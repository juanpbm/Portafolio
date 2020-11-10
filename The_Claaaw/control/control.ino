#include <IRremote.h>

int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

int left1=10;
int left2=12;
int right1=11;
int right2=13;

const int frontsensor = 1;
const int tempsensor = 0;
float distance, voltage, temp;
int x, y = 0, l = 0;



void danger ();
float getVoltage(int pin);
void volt ();

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);

  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
  
  while (y == 0) {
    
   Serial.println("OFF");
    if (irrecv.decode(&results)) {
      if (results.value == 2704) {
        y = 1;
      }
      irrecv.resume();
    }
  }
 Serial.println("Safety Check...");
  delay(1000);
 danger();
  delay(400);
  Serial.println("Robot Safe Press");
  Serial.println("Any Key To Go");
  digitalWrite(7,HIGH);
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

void danger ()
{
  voltage = getVoltage(tempsensor);
  temp = (voltage - 0.5) * 100.0;
//  Serial.println(temp);
 // volt();
 //Serial.print(distance);
  x = 0;
  while (digitalRead(6)==HIGH ) {
    x = 1;
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
    Serial.println("Danger Alert!!!!");
    if (temp >= 120) {
      Serial.println("Temp Too High");
      Serial.println(temp);
    } else {
      Serial.println("Object Ahead");
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
      delay(500);
    }
  //  volt();
    voltage = getVoltage(tempsensor);
    temp = (voltage - 0.5) * 100.0;
  }
  if (x == 1) {
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
   Serial.println("Robot Safe Press");
   Serial.println("Any Key To Go");
    l=1;
  }
}

void loop()
{
 danger();
 
  if (irrecv.decode(&results)) {
    Serial.println(results.value, DEC);
    delay(100);
    danger();
    switch (results.value) {
      //forward
      case 2064:
  digitalWrite(left1,HIGH);
  digitalWrite(left2,LOW);
  digitalWrite(right1,HIGH);
  digitalWrite(right2,LOW);
       Serial.println("Forward!!!!");
        break;
      //back
      case 3600:
  digitalWrite(left1,LOW);
  digitalWrite(left2,HIGH);
  digitalWrite(right1,LOW);
  digitalWrite(right2,HIGH);
       Serial.println("Backward!!!!");
        break;
      //left
      case 2576:
  digitalWrite(left1,HIGH);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,HIGH);
        Serial.println("Left!!!!");
        break;
      //right
      case 3088:
  digitalWrite(left1,LOW);
  digitalWrite(left2,HIGH);
  digitalWrite(right1,HIGH);
  digitalWrite(right2,LOW);
      Serial.println("Right!!!!");
        break;
      //SOTP
      case 528:
  digitalWrite(left1,LOW);
  digitalWrite(left2,LOW);
  digitalWrite(right1,LOW);
  digitalWrite(right2,LOW);
        Serial.println("Stop!!!!");
        break;
    }
    irrecv.resume(); // Receive the next value
  }
}


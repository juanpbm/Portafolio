#include <Servo.h> // servo library

Servo servo_R; //declare servo objects -servo_R for right; servo_L for left
Servo servo_L;


Servo servo_R; //declare servo objects -servo_R for right; servo_L for left
Servo servo_L;


const int leftSensor = 10; // Assign sensor pins for two down sensors
const int rightSensor = 9;
int lsensorState = 0; // Initialize sensor variable
int rsensorState = 0;
const int front_sensor = 0; //declare global variables
float distance, voltage;
int p = 0;
int b = 0;


void setup()
{ 
 servo_R.attach(12); //connect Right motor single wire to Digital Port 12
 servo_L.attach(11); //connect Left motor single wire to Digital Port 11
 pinMode(leftSensor, INPUT); // Declare assigned sensor pins as input
 pinMode(rightSensor, INPUT);
 Serial.begin(9600); //front sensor 
}


//l and r sensors say when to stop if it reaches an edge 
void stops()
{
 rsensorState = digitalRead(rightSensor); //read right sensor
 lsensorState = digitalRead(leftSensor);
 
while (rsensorState == HIGH ||lsensorState == HIGH)
{
    servo_R.write(180);
    servo_L.write(0);
    delay(500);
  if (lsensorState == HIGH && rsensorState == HIGH)
    {
    servo_R.write(180);
    servo_L.write(0);
    delay(500);
    servo_R.write(180);
    servo_L.write(180);
    delay(1000);
    }
  else if(rsensorState == HIGH)//right sensor table edge
    {
    servo_R.write(0);
    servo_L.write(0);
    delay(900);
    }
  else if(lsensorState == HIGH) //left sensor table edge 
    {
    servo_R.write(180);
    servo_L.write(180);
    delay(900);
    }
 }  //end while
 rsensorState = digitalRead(rightSensor); //read downward sensors
 lsensorState = digitalRead(leftSensor);
} //end stops

float getVoltage(int pin)     //input from front sensor
{
 return (analogRead(pin) * 0.004882814);
}

void volt ()    //convert voltage to distance
{
 voltage = getVoltage(front_sensor); //get voltage reading from front sensor
 //distance = 6.6344*voltage*voltage - 27.942*voltage + 31.952; //inches, Volts
 distance = 2.439*voltage*voltage - 14.341*voltage + 21.997;
}

void loop()
{
 rsensorState = digitalRead(rightSensor); //input from side sensors
 lsensorState = digitalRead(leftSensor);

//get distance from the front sensor
  volt();
/*Serial.print(distance);
Serial.println(" ");
delay (1000);
Serial.print(p);
Serial.println(" ");
delay (1000); ,*/
 while (p==0)     //initially keep turning until opponent is sensed
 {  
  servo_R.write (180);      
  servo_L.write (180);
  stops();
  volt();
    if (distance <= 9.0)   //when bot senses opponent
    {
    p=1;
    }
  } //close while
  
 while (p==1)        //if opponent sensed, go straight -- charge
  {
  servo_R.write (0);
  servo_L.write (180);
  stops();
  volt();
    if (distance >= 9.0)   //if bot no longer senses opponent
    {
    p=0;
    }
  }//close while
}//close loop


#include <Adafruit_MotorShield.h>


#include <IRremote.hpp>

#include <AFMotor.h>
//#include <IRremote.h>

AF_DCMotor motor1 (1);
AF_DCMotor motor2 (2);
AF_DCMotor motor3 (3);
AF_DCMotor motor4 (4);

IRrecv irrecv(2);   //create instance of 'IRrecv'
decode_results results;    //create instance of 'decode_results'

long previous;
unsigned long LastReceive = 0;
 
//unsigned long   TimerUp;   //UP arrow on the remote
//boolean         TimerUpFlag = false;
 
//unsigned long   TimerDown; //DOWN arrow on the remote
//boolean         TimerDownFlag = false;
 
//unsigned long TimerIntensity;
//unsigned long TimerIncDec;
//boolean intesityUpFlag   = false;
//boolean intesityDownFlag = false;
int brightness;
int speed=150;
long ircode; 
//unsigned long   dummy;
//unsigned long * TimerPtr = &dummy; //pointer to the current timer

// Imposta i pin di controllo del L298N Dual H-Bridge Motor Controller


 
 
//______________________________________________________________________________________________
void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); //start receive

motor1.setSpeed(150);
motor2.setSpeed(150);
motor3.setSpeed(150);
motor4.setSpeed(150);

 
  //motor1.run(FORWARD);
  //motor2.run(FORWARD);
  //motor3.run(FORWARD);
  //motor4.run(FORWARD);


}
//______________________________________________________________________________________________



 
 
//______________________________________________________________________________________________
void loop()
{

  
  if (irrecv.decode()) //is there IR remote button code
  {
    Serial.println(irrecv.decodedIRData.decodedRawData, HEX);
    ircode=irrecv.decodedIRData.decodedRawData;
    Serial.println(ircode);
    processButton(); //process button press
    delay(500);
    irrecv.resume(); //restart for next button press
  }
 
  //**********************                                //Turn off upLED
  //if timing is enabled, is it time to stop
  //if (TimerUpFlag && millis() - TimerUp >= 250ul)
  //{
    //TimerUpFlag = false; //disable timing
    //TimerPtr = &dummy;   //pointer to dummy timer
    //fermo();
  //}
 
  //**********************                                //Turn off downLED
  //if timing is enabled, is it time to stop
  //if (TimerDownFlag && millis() - TimerDown >= 250ul)
  //{
    //TimerDownFlag = false; //disable timing
    //TimerPtr = &dummy;     //pointer to dummy timer
    //fermo();
  //}
 
}
//______________________________________________________________________________________________

 
 
 
//______________________________________________________________________________________________

void zpositivo()  {
motor1.setSpeed(speed);
motor2.setSpeed(speed);
motor3.setSpeed(speed);
motor4.setSpeed(speed);
motor1.run(FORWARD);
motor2.run(FORWARD);
motor3.run(FORWARD);
motor4.run(FORWARD);


}

void znegativo()  {
motor1.setSpeed(speed);
motor2.setSpeed(speed);
motor3.setSpeed(speed);
motor4.setSpeed(speed);
motor1.run(BACKWARD);
motor2.run(BACKWARD);
motor3.run(BACKWARD);
motor4.run(BACKWARD);

}

void xpositivo()  {
motor1.setSpeed(speed);
motor2.setSpeed(speed);
motor3.setSpeed(speed);
motor4.setSpeed(speed);
motor1.run(FORWARD);
motor2.run(BACKWARD);
motor3.run(BACKWARD);
motor4.run(FORWARD);
}

void xnegativo()  {
motor1.setSpeed(speed);
motor2.setSpeed(speed);
motor3.setSpeed(speed);
motor4.setSpeed(speed);
motor1.run(BACKWARD);
motor2.run(FORWARD);
motor3.run(FORWARD);
motor4.run(BACKWARD);
}

void ypositivo()  {
motor1.setSpeed(255);
motor2.setSpeed(255);
motor3.setSpeed(255);
motor4.setSpeed(255);
motor1.run(FORWARD);
motor2.run(FORWARD);
motor3.run(FORWARD);
motor4.run(FORWARD);
}

void ynegativo()  {
motor1.setSpeed(255);
motor2.setSpeed(255);
motor3.setSpeed(255);
motor4.setSpeed(255);
motor1.run(BACKWARD);
motor2.run(BACKWARD);
motor3.run(BACKWARD);
motor4.run(BACKWARD);
}

void fermo()  {

motor1.run(RELEASE);
motor2.run(RELEASE);
motor3.run(RELEASE);
motor4.run(RELEASE);
}

//______________________________________________________________________________________________

 
//______________________________________________________________________________________________

void processButton()
{
  switch (ircode)
  {
    //**********************
    case -1169817856:                                           //Speed 150
      {
        Serial.println("Speed 150");
       speed=150;
      }
      break;
      case -1186529536:                                           //Speed 200
      {
         Serial.println("Speed 200");
       speed=200;
      }
      break;
      case -1203241216:                                           //Speed 255
      {
         Serial.println("Speed 255");
       speed=255;
      }
      break;
      case -417792256:                                           //UP Arrow
      {
        Serial.println("Z+");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        zpositivo();
        //TimerUp = millis();
      }
      break;

    //**********************
    case -1387069696:                                           //UP Arrow
      {
        Serial.println("Z-");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        znegativo();
        //TimerUp = millis();
      }
      break;

    case -1520763136:                                           //UP Arrow
      {
        Serial.println("X+");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        xpositivo();
        //TimerUp = millis();
      }
      break;

     case -150405376:                                           //UP Arrow
      {
        Serial.println("X-");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        xnegativo();
        //TimerUp = millis();
      }
      break;

     case -233963776:                                           //UP Arrow
      {
        Serial.println("Y+");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        ypositivo();
        //TimerUp = millis();
      }
      break;

     case -384368896:                                           //UP Arrow
      {
        Serial.println("Y-");
        //TimerPtr = &TimerUp;  //point to this timer
        //TimerUpFlag = true;   //enable timing
        ynegativo();
        //TimerUp = millis();
      }
      break;
 

    case -484638976: //Repeat code
      {
        Serial.println("REPEAT");
       motor1.run(RELEASE);
motor2.run(RELEASE);
motor3.run(RELEASE);
motor4.run(RELEASE);
        //*TimerPtr = millis();       //reset the current timer
      }
      break;

      default:
      {
        Serial.println("REPEAT");
        //*TimerPtr = millis();       //reset the current timer
      }
  break;
  }
  }
  

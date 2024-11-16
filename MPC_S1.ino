#include <AFMotor.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h> //On A4 and A5 pin //BMP
#define seaLevelPressure_hPa 1013.25
#define DHTPIN A3 //Temp
#define DHTTYPE DHT11 
#define IR_BUTTON_UP 24
#define IR_BUTTON_RIGHT 90
#define IR_BUTTON_LEFT 8
DHT dht (DHTPIN,DHTTYPE);
const int tiltpin = 7;
int PR = A2;
int sensorPin = A1;  //Soil moisture
int sensorValue = 0;  
int percent = 0;
int TopLeft = 6;
int TopRight = 5;
int BottomLeft = 3;
int BottomRight = 2;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_BMP085 bmp;

void setup()
{
  pinMode(7,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0,0);
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
} 
int convertToPercent(int value)
{
  int percentValue = 0;
  percentValue = map(value, 1023, 465, 0, 100);
  return percentValue;
} 

void loop()
{
  while (1==1){
    lcd.scrollDisplayLeft();
    delay(500);
        //Tilt
    int tilt = digitalRead(tiltpin);

    //Pressure
    float Pressure= bmp.readPressure();

    //Soil Moisture
    sensorValue = analogRead(sensorPin);
    percent = convertToPercent(sensorValue);
   
    //Temperature and humidity part
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    
    //Photoresistor part
    int Sunlight;
    Sunlight= analogRead(PR);
    Sunlight=((Sunlight/169)*100);

    
    lcd.setCursor(0,0);
    lcd.print("Temp=");
    lcd.print(t);
    lcd.print("|");
    lcd.print("Humidity=");
    lcd.print(h);
    lcd.print("|");
    lcd.print("SunLight=");
    lcd.print(Sunlight);
    lcd.print("|");
    lcd.setCursor(0,2);
    lcd.print("Land=");
    if(tilt==HIGH)
    {
      lcd.print("Tilted");
    }
    else 
    {
      lcd.print("Normal");
    }
    lcd.print("|");
    lcd.print("Press=");
    lcd.print(Pressure);
    lcd.print("|");
    lcd.print("SoilMois=");
    lcd.print(percent);
    lcd.print(" |");
  }
}

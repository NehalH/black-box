#include <Wire.h> // imports the wire library for talking over I2C 

#include <SD.h> //Load SD card library
#include<SPI.h> //Load SPI Library

const int MPU_addr=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265;
int maxVal=402;

int x;

float sec= 00.0;
int mins= 00;

int chipSelect = 4; //chipSelect pin for the SD card Reader
File mySensorData; //Data object you will write your sesnor data to

void setup() {
  
  Serial.begin(9600);

  pinMode(10, OUTPUT); //Must declare 10 an output and reserve it
  SD.begin(4); //Initialize the SD card reader
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  
  mySensorData = SD.open("PTData.txt", FILE_WRITE);
  mySensorData.println("______________________R E S E T______________________");
  mySensorData.close();
  
}

/////////////////////////////////////////////////////////////////

void loop() { 
  
  mySensorData = SD.open("PTData.txt", FILE_WRITE);
  
  // Read angle
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);

  sec=sec+0.1;
  if(sec>=60.0){
    sec= 0.0;
    mins++;
  }

  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();

  int xAng = map(AcX,minVal,maxVal,-90,90);
  int yAng = map(AcY,minVal,maxVal,-90,90);
  int zAng = map(AcZ,minVal,maxVal,-90,90);
  
  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);                 // Convert rad to deg
  //y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  //z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  
  if(x>90) x=90-(x-90);                                          // Convert angles (x>180) to Negative angles (0 to -180)

  /*
  if(x<-180){
    x= 90+(270+x);
  }	
  */

  /*
  if(x<-180){
    x= x+180
  }
  */


  if(x>29){
    if (mySensorData) {
      Serial.println("-----------------------------------------");
      Serial.print(mins);
      Serial.print(":");
      Serial.print(sec);
      Serial.print("\t\tPitch= ");
      Serial.println(x);
  
      mySensorData.print(mins);
      mySensorData.print(":");
      mySensorData.print(sec);
      mySensorData.print("\t\t");
      mySensorData.println(x);
      
    }
  }
<<<<<<< HEAD
  mySensorData.close();
  delay(1000);
=======
  delay(100);
>>>>>>> dev

}

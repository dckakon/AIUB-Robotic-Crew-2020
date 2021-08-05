#include <Wire.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#include <SPI.h>
#include "MPU9250.h"
#include "EEPROM.h"

SoftwareSerial mySerial(A8, 18);
Adafruit_GPS GPS(&mySerial);

//char st=0;

float latitude_1;
float longitude_1;

float latitude_2 = 23.821813;  //  destination latitude
float longitude_2 = 90.427230;// destination longitude
float bearing_angle;
int heading_angle;

uint8_t R_EN[] = {49 ,51,53};
uint8_t L_EN[] = {23,25,27};


int R_rPWM0 = 13;
int R_rPWM1 = 11;
int R_rPWM2 = 9; // Motor Group: Right

int R_lPWM0 = 12;
int R_lPWM1 = 10;
int R_lPWM2 = 8; // Motor Group: Right

int L_rPWM0 = 6;
int L_rPWM1 = 4;
int L_rPWM2 = 2; // Motor Group: Left

int L_lPWM0 = 7;
int L_lPWM1 = 5;
int L_lPWM2 = 3; // Motor Group: Left

                                                                  // Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console | ------|Set to 'true' if you want to debug and listen to the raw GPS sentences
#define GPSECHO  true

//compass 
float h, hx, hy, hz;

float hxb, hxs, hyb, hys, hzb, hzs;

float yaw_rad, heading_rad;

float filtered_heading_rad;
float window_size = 20;

const float R2D = 180.0f / PI;

MPU9250 imu(Wire, 0x68);

const uint8_t kMpu9250DrdyPin = 2;

volatile bool imu_data_ready = false;




void setup()
{

  //  Serial.begin(115200);
    Serial.begin(9600);
    Wire.begin();  
    delay(1000);
    Serial.println(" ** GPS test  **  ");
    GPS.begin(9600);

 
    GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
    GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);  
    GPS.sendCommand(PGCMD_ANTENNA);

   
 for(int i=0; i<3; i++)
  {
    pinMode(R_EN[i], OUTPUT);
    pinMode(L_EN[i], OUTPUT);
  }

  pinMode(R_rPWM0, OUTPUT);
  pinMode(R_rPWM1, OUTPUT);
  pinMode(R_rPWM2, OUTPUT);
  pinMode(R_lPWM0, OUTPUT);
  pinMode(R_lPWM1, OUTPUT);
  pinMode(R_lPWM2, OUTPUT);

  pinMode(L_rPWM0, OUTPUT);
  pinMode(L_rPWM1, OUTPUT);
  pinMode(L_rPWM2, OUTPUT);
  pinMode(L_lPWM0, OUTPUT);
  pinMode(L_lPWM1, OUTPUT);
  pinMode(L_lPWM2, OUTPUT);
  
    for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i], HIGH);
    digitalWrite(L_EN[i], HIGH);
  }


//------------------------------------------compass---------------------------------------------------------------------------------------------------------------


 while(!Serial) {}
  /* 
  * Start the sensor, set the bandwidth the 10 Hz, the output data rate to
  * 50 Hz, and enable the data ready interrupt. 
  */
  imu.begin();
  imu.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_10HZ);
  imu.setSrd(19);
  imu.enableDataReadyInterrupt();
  /*
  * Load the magnetometer calibration
  */
  uint8_t eeprom_buffer[24];
  for (unsigned int i = 0; i < sizeof(eeprom_buffer); i++ ) {
    eeprom_buffer[i] = EEPROM.read(i);
  }
  memcpy(&hxb, eeprom_buffer, sizeof(hxb));
  memcpy(&hyb, eeprom_buffer + 4, sizeof(hyb));
  memcpy(&hzb, eeprom_buffer + 8, sizeof(hzb));
  memcpy(&hxs, eeprom_buffer + 12, sizeof(hxs));
  memcpy(&hys, eeprom_buffer + 16, sizeof(hys));
  memcpy(&hzs, eeprom_buffer + 20, sizeof(hzs));
  imu.setMagCalX(hxb, hxs);
  imu.setMagCalY(hyb, hys);
  imu.setMagCalZ(hzb, hzs);
  /* Attach the data ready interrupt to the data ready ISR */
  pinMode(kMpu9250DrdyPin, INPUT);
  attachInterrupt(kMpu9250DrdyPin, data_ready, RISING);
  
}

  uint32_t timer = millis();  
  int flag= 1;



void loop()                     // run over and over again
{
  if(flag==1)
    {
      distance();
    }
}


int counter=0;

void distance()
{
   
     
   char c = GPS.read();
  
    if ((c) && (GPSECHO))
 
    if (GPS.newNMEAreceived()) {
   
    if (!GPS.parse(GPS.lastNMEA()))   // this also sets the newNMEAreceived() flag to false
      return;                         // we can fail to parse a sentence in which case we should just wait for another
  }

  
  if (timer > millis())  timer = millis();
  
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer

   
    if (GPS.fix) {
    
      latitude_1=GPS.latitudeDegrees;
      longitude_1=GPS.longitudeDegrees;
      
     Serial.println("Location : ");
     Serial.println(latitude_1,6);
     Serial.println(longitude_1,6);
      
     float latitude_1_radian = latitude_1*(PI/180);
     float latitude_2_radian = latitude_2*(PI/180);
 
     float  difference_between_latitude  =latitude_2_radian - latitude_1_radian;
     float  difference_between_longitude =(longitude_2 - longitude_1)*(PI/180);

     float a= (sq(sin(difference_between_latitude/2)) + cos(latitude_1_radian)*cos(latitude_2_radian)* sq(sin(difference_between_longitude/2)));
     float c= 2* atan2(sqrt(a), sqrt(1-a));

     float distance = 6371*c*1000;  // output distance in   meter
   
     float Xb=sin(difference_between_longitude)*cos(latitude_2_radian);
     float Yb=cos(latitude_1_radian)*sin(latitude_2_radian)-sin(latitude_1_radian)*cos(latitude_2_radian)*cos(difference_between_longitude);
     
     
     Serial.print("Distance remaining: ");
     Serial.println(distance);
     
     
     bearing_angle=atan2(Xb,Yb)*(180/PI); 
     if (bearing_angle < 0){bearing_angle += 360;}    
     
     Serial.println(" Bearing_Angle - "); 
     Serial.println(bearing_angle);
     
      //gps fix && mille
     //compass
    
      
    
 
     counter=1;
     if(counter==1)
     {
         if((distance >= 0)&&(distance <=3))
      {
         Serial.flush();    
         roverstop(); 
         flag = 0;                                                                                
      }
       else if(abs(bearing_angle - compass()) <=15)
      {   
          Serial.flush();
          enable();
          roverforward();
      }
      else 
      {
            int xx = (bearing_angle - 360);                           // xx = the GPS desired heading - 360
            int yy = ( compass() - (xx));                      // yy = the Compass heading - x
            int zz = (yy - 360);                                    // zz = yy - 360
            
            if ((zz <= 180) && (zz >= 0))                           // if z is less than 180 and not a negative value then turn left otherwise turn right
                  {
                    
                     right();
                  }
             else { 
                 
                    left();
                  } 
      }
     } 
   }
  }
}  
    
  
  



void roverforward()
{
   Serial.println("Forward ");
  analogWrite(R_rPWM0, 0);
  analogWrite(R_rPWM1, 0);
  analogWrite(R_rPWM2, 0);
  analogWrite(L_rPWM0, 0);
  analogWrite(L_rPWM1, 0);
  analogWrite(L_rPWM2, 0);

  analogWrite(R_lPWM0, 120);
  analogWrite(R_lPWM1, 120);
  analogWrite(R_lPWM2, 120);
  analogWrite(L_lPWM0, 120);
  analogWrite(L_lPWM1, 120);
  analogWrite(L_lPWM2, 120);
}

void roverstop()
{     Serial.println(" Stop");
       for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i],LOW);
    digitalWrite(L_EN[i],LOW);
  }
  
  analogWrite(R_rPWM0, 0);
  analogWrite(R_rPWM1, 0);
  analogWrite(R_rPWM2, 0);
  analogWrite(L_rPWM0, 0);
  analogWrite(L_rPWM1, 0);
  analogWrite(L_rPWM2, 0);

  analogWrite(R_lPWM0, 0);
  analogWrite(R_lPWM1, 0);
  analogWrite(R_lPWM2, 0);
  analogWrite(L_lPWM0, 0);
  analogWrite(L_lPWM1, 0);
  analogWrite(L_lPWM2, 0);

}

void enable()
{
  for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i],HIGH);
    digitalWrite(L_EN[i],HIGH);
  }
}

void right()
  {
    analogWrite(R_rPWM0, 100);
    analogWrite(R_lPWM1, 100);
    analogWrite(R_rPWM2, 100);
    analogWrite(L_rPWM0, 100);
    analogWrite(L_lPWM1, 100);
    analogWrite(L_lPWM2, 100);

    
    analogWrite(R_lPWM0, 0);
    analogWrite(R_rPWM1, 0);
    analogWrite(R_lPWM2, 0);
    analogWrite(L_lPWM0, 0);
    analogWrite(L_rPWM1, 0);
    analogWrite(L_rPWM2, 0);
}

  void left(){
   analogWrite(L_lPWM0, 100);
   analogWrite(L_rPWM1, 100);
   analogWrite(L_rPWM2, 100);
   analogWrite(R_lPWM0, 100);
   analogWrite(R_rPWM1, 100);
   analogWrite(R_lPWM2, 100);

   analogWrite(L_rPWM0, 0);
   analogWrite(L_lPWM1, 0);
   analogWrite(L_lPWM2, 0);
   analogWrite(R_rPWM0, 0);
   analogWrite(R_lPWM1, 0);
   analogWrite(R_rPWM2, 0);
}



float constrainAngle360(float dta) {
  dta = fmod(dta, 2.0 * PI);
  if (dta < 0.0)
    dta += 2.0 * PI;
  return dta;
}
void data_ready()
{
  imu_data_ready = true;
}
float compass()
{      if (imu_data_ready) {
    imu_data_ready = false;
    /* Read the MPU 9250 data */
    imu.readSensor();
    hx = imu.getMagX_uT();
    hy = imu.getMagY_uT();
    hz = imu.getMagZ_uT();
    /* Normalize magnetometer data */
    h = sqrtf(hx * hx + hy * hy + hz * hz);
    hx /= h;
    hy /= h;
    hz /= h;
    /* Compute euler angles */
    yaw_rad = atan2f(-hy, hx);
    heading_rad = constrainAngle360(yaw_rad);
    /* Filtering heading */
    filtered_heading_rad = (filtered_heading_rad * (window_size - 1.0f) + heading_rad) / window_size;
    /* Display the results */
   // Serial.print(yaw_rad * R2D);
    //Serial.print("\t");
    //Serial.print(heading_rad * R2D);
    Serial.print("\t");
    heading_angle=filtered_heading_rad * R2D;
    Serial.println("Heading Angle :");
    Serial.println(heading_angle);
    return heading_angle;
  }
}

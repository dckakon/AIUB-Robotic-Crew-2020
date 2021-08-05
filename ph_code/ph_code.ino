float calibration = 23.38; //change this value to calibrate
const int analogInPin = A0; 
int sensorValue = 0; 
int smokeA0 = A5;
unsigned long int avgValue; 
float b;
int buf[10],temp;
void setup() {
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
}
 
void loop() {

  int analogSensor = analogRead(smokeA0);

 // Serial.print("Gas Value: ");
  Serial.print(analogSensor);
 for(int i=0;i<10;i++) 
 { 
 buf[i]=analogRead(analogInPin);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buf[i]>buf[j])
 {
 temp=buf[i];
 buf[i]=buf[j];
 buf[j]=temp;
 }
 }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + calibration;
 Serial.print("\t");
 Serial.print("PH Value = ");
 Serial.print(phValue);
 Serial.println();
 
 delay(500);
}

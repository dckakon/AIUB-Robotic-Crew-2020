//@Created by @Boshir vai  X Updated by DCKAKON
/* EN pins are to turn driver ON or OFF 
   All the motors driver R_EN and L_EN are common
*/
uint8_t R_EN[] = {49 ,51,53};
uint8_t L_EN[] = {23,25,27};

char st = 0;
int speed00=180;


/* R_PWM controls Right Turn, L_PWM Left Turn */
int R6_rPWM0 = 13;
int R5_rPWM1 = 11;
int R4_rPWM2 = 9; // Motor Group: Right

int R6_lPWM0 = 12;
int R5_lPWM1 = 10;
int R4_lPWM2 = 8; // Motor Group: Right

int L3_rPWM0 = 6;
int L2_rPWM1 = 4;
int L1_rPWM2 = 2; // Motor Group: Left

int L3_lPWM0 = 7;
int L2_lPWM1 = 5;
int L1_lPWM2 = 3; // Motor Group: Left

int h1[] = {29,31}; //Claw
int h2[] = {33,35}; //3 Actuator
int h3[] = {37,39}; //2 Actuator 
int h4[] = {41,43};// base motor
int h5[] = {45,47}; // 1 Actuator
int h6[] = {50,52};// Claw motor

int claw_r=24;
int claw_l=26;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  for(int i=0; i<3; i++)
  {
    pinMode(R_EN[i], OUTPUT);
    pinMode(L_EN[i], OUTPUT);
  }

  pinMode(R6_rPWM0, OUTPUT);
  pinMode(R5_rPWM1, OUTPUT);
  pinMode(R4_rPWM2, OUTPUT);
  pinMode(R6_lPWM0, OUTPUT);
  pinMode(R5_lPWM1, OUTPUT);
  pinMode(R4_lPWM2, OUTPUT);

  pinMode(L3_rPWM0, OUTPUT);
  pinMode(L2_rPWM1, OUTPUT);
  pinMode(L1_rPWM2, OUTPUT);
  pinMode(L3_lPWM0, OUTPUT);
  pinMode(L2_lPWM1, OUTPUT);
  pinMode(L1_lPWM2, OUTPUT);
  
  pinMode(claw_r ,OUTPUT);
  pinMode(claw_l ,OUTPUT);

  for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i], HIGH);
    digitalWrite(L_EN[i], HIGH);
  }

  /*Hand*/

  pinMode(h1[0], OUTPUT);
  pinMode(h1[1], OUTPUT);    // CLAW Grab & catch 

  pinMode(h2[0], OUTPUT);    // 3rd Acu
  pinMode(h2[1], OUTPUT);

  pinMode(h3[0], OUTPUT);    // 2nd Acu
  pinMode(h3[1], OUTPUT);

  pinMode(h4[0], OUTPUT);    // base motor 
  pinMode(h4[1], OUTPUT);

  pinMode(h5[0], OUTPUT); 
  pinMode(h5[1], OUTPUT);    //1st Acu

  pinMode(h6[0], OUTPUT);
  pinMode(h6[1], OUTPUT);    // claw motor
}

void loop() {
 

  if(Serial.available())
  {
    st = Serial.read();

    if(st == '8')
    {
      Serial.flush();
      Serial.println("Forward");
      enable();
      forward();
    }
    else if(st=='6')
    {
      Serial.flush();
      Serial.println("Right");
      enable();
      right();
    }
     else if(st=='4')
    {
      Serial.flush();
      Serial.println("Left");
      enable();
      left();
    }
    else if(st == '5')
    {
      Serial.flush();
      Serial.println("back");
      enable();
      back();
    }
    else if(st == 'k')
    {
      Serial.flush();
      Serial.println("kill");
      halt();
    }
    
    else if(st == '7')
    {
    digitalWrite(claw_r ,HIGH);
    digitalWrite(claw_l ,LOW);
    Serial.println("CLAW l");
   }
     else if(st == '8')
    {
    digitalWrite(claw_r ,LOW);
    digitalWrite(claw_l ,HIGH);
    Serial.println("CLAW r" );
     } 
    else if(st == 'r')
    {
      digitalWrite(h1[0], HIGH);   //grab 
      digitalWrite(h1[1], LOW);
    }
    else if(st == 'f')          // grab 
    {
      digitalWrite(h1[0], LOW);
      digitalWrite(h1[1], HIGH);
    }
    else if(st == 'e')                
    {                             // 3 actuator
      digitalWrite(h2[0], HIGH);
      digitalWrite(h2[1], LOW);
    }
    else if(st == 'd')            //3 actuator
    {
      digitalWrite(h2[0], LOW);
      digitalWrite(h2[1], HIGH);
    }
    else if(st == 'w')           //2 actuator
    {
      digitalWrite(h3[0], HIGH);
      digitalWrite(h3[1], LOW);
    }
    else if(st == 's')           //2  actuator
    {
      digitalWrite(h3[0], LOW);
      digitalWrite(h3[1], HIGH);
    }
    else if(st == 'q')             //1 actuator
    {
      digitalWrite(h4[0], HIGH);
      digitalWrite(h4[1], LOW);
    }
    else if(st == 'a')           //1 actuator
    {
      digitalWrite(h4[0], LOW);
      digitalWrite(h4[1], HIGH);
    }
    else if(st == 'y')    // base left 
    {
      digitalWrite(h5[0], HIGH);
      digitalWrite(h5[1], LOW);
    }
    else if(st == 'h')    // base right 
    {
      digitalWrite(h5[0], LOW);
      digitalWrite(h5[1], HIGH);
    }
    else if(st == 'g')         //claw motor right
    {
      digitalWrite(h6[0], HIGH);
      digitalWrite(h6[1], LOW);
    }
    
     else if(st == 't')    //  claw motor left 
    {
      digitalWrite(h6[0], LOW);
      digitalWrite(h6[1], HIGH);
    }
     else if(st == '1')
    {
      speed00=60;
    }
     else if(st == '3')
    {
      speed00=255;
    }
       else if(st == '2')
    {
      speed00=180;
    }
 
    else if(st == 'v')   // stop
    {
      digitalWrite(h1[0], LOW);
      digitalWrite(h1[1], LOW);

      digitalWrite(h2[0], LOW);
      digitalWrite(h2[1], LOW);

      digitalWrite(h3[0], LOW);
      digitalWrite(h3[1], LOW);

      digitalWrite(h4[0], LOW);
      digitalWrite(h4[1], LOW);

      digitalWrite(h5[0], LOW);
      digitalWrite(h5[1], LOW);

      digitalWrite(h6[0], LOW);
      digitalWrite(h6[1], LOW);
    }
  }
}

void enable()
{
  for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i],HIGH);
    digitalWrite(L_EN[i],HIGH);
  }
}

void forward()
{
  /* Both groups of motors drive forward as their R_PWM is HIGH */
 
   
  analogWrite(R6_rPWM0, 0);
  analogWrite(R5_rPWM1, 0);
  analogWrite(R4_rPWM2, 0);
  analogWrite(L3_rPWM0, 0);
  analogWrite(L2_rPWM1, 0);
  analogWrite(L1_rPWM2, 0);

  analogWrite(R6_lPWM0,speed00);
  analogWrite(R5_lPWM1, speed00);
  analogWrite(R4_lPWM2, speed00);
  analogWrite(L3_lPWM0, speed00);
  analogWrite(L2_lPWM1, speed00);
  analogWrite(L1_lPWM2, speed00);
 


}
void right()
  {
    analogWrite(R6_rPWM0, speed00);
    analogWrite(R5_rPWM1, speed00);
    analogWrite(R4_rPWM2, speed00);
    analogWrite(L3_lPWM0, speed00);
    analogWrite(L2_lPWM1, speed00);
    analogWrite(L1_lPWM2, speed00);

    
    analogWrite(R6_lPWM0, 0);
    analogWrite(R5_lPWM1, 0);
    analogWrite(R4_lPWM2, 0);
    analogWrite(L3_rPWM0, 0);
    analogWrite(L2_rPWM1, 0);
    analogWrite(L1_rPWM2, 0);
}

  void left(){
   analogWrite(L3_rPWM0, speed00);
   analogWrite(L2_rPWM1, speed00);
   analogWrite(L1_rPWM2, speed00);
   analogWrite(R6_lPWM0, speed00);
   analogWrite(R5_lPWM1, speed00);
   analogWrite(R4_lPWM2, speed00);

   analogWrite(L3_lPWM0, 0);
   analogWrite(L2_lPWM1, 0);
   analogWrite(L1_lPWM2, 0);
   analogWrite(R6_rPWM0, 0);
   analogWrite(R5_rPWM1, 0);
   analogWrite(R4_rPWM2, 0);
}

void back()
{
  /* Both groups of motors drive backward as their L_PWM is HIGH */
   analogWrite(R6_rPWM0, speed00);
  analogWrite(R5_rPWM1, speed00);
  analogWrite(R4_rPWM2, speed00);
  analogWrite(L3_rPWM0, speed00);
  analogWrite(L2_rPWM1, speed00);
  analogWrite(L1_rPWM2, speed00);

  analogWrite(R6_lPWM0, 0);
  analogWrite(R5_lPWM1, 0);
  analogWrite(R4_lPWM2, 0);
  analogWrite(L3_lPWM0, 0);
  analogWrite(L2_lPWM1, 0);
  analogWrite(L1_lPWM2, 0);


}

void halt()
{
  for(int i=0; i<3; i++)
  {
    digitalWrite(R_EN[i],LOW);
    digitalWrite(L_EN[i],LOW);
  }
  
  analogWrite(R6_rPWM0, 0);
  analogWrite(R5_rPWM1, 0);
  analogWrite(R4_rPWM2, 0);
  analogWrite(L3_rPWM0, 0);
  analogWrite(L2_rPWM1, 0);
  analogWrite(L1_rPWM2, 0);

  analogWrite(R6_rPWM0, 0);
  analogWrite(R5_lPWM1, 0);
  analogWrite(R4_lPWM2, 0);
  analogWrite(L3_lPWM0, 0);
  analogWrite(L2_lPWM1, 0);
  analogWrite(L1_lPWM2, 0);
}

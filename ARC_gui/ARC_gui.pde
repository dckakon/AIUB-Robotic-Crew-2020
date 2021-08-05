import controlP5.*;
import processing.serial.*;

Serial port;

PImage arc;
PImage aiub;

ControlP5 cp5;
PFont font,font1;

void setup()
{
 size (800,450); 
 
 //printArray(Serial.list());
 
 //port = new Serial(this, "COM11",9600);
 arc = loadImage("ARC.jpg");
 aiub = loadImage("aiub.png");
 cp5 = new ControlP5(this);
 
 font  = createFont("Bold",20);
 font1 = createFont("calibri light",13);
 cp5.addButton("Forward")
    .setPosition(600,300)
    .setSize(70,40)
    .setFont(font1) 
 ;
 
 cp5.addButton("Backward")
    .setPosition(600,350)
    .setSize(70,40)
     .setFont(font1)
 ;
 
 cp5.addButton("Left")
    .setPosition(520,350)
    .setSize(70,40)
     .setFont(font1)
 ;
 
  cp5.addButton("Right")
    .setPosition(680,350)
    .setSize(70,40)
     .setFont(font1)
 ;
  cp5.addButton("LOW")
    .setPosition(620,80)
    .setSize(50,20)
     .setFont(font1)
 ;
  cp5.addButton("Medium")
    .setPosition(620,110)
    .setSize(50,20)
     .setFont(font1)
 ;
   cp5.addButton("HIGH")
    .setPosition(620,140)
    .setSize(50,20)
     .setFont(font1)
 ;
    cp5.addButton("Q")
    .setPosition(40,80)
    .setSize(30,30)
     .setFont(font1)
 ;
   cp5.addButton("A")
    .setPosition(40,120)
    .setSize(30,30)
     .setFont(font1)
 ;
   cp5.addButton("W")
    .setPosition(80,80)
    .setSize(30,30)
     .setFont(font1)
 ;
   cp5.addButton("S")
    .setPosition(80,120)
    .setSize(30,30)
     .setFont(font1)
 ;
   cp5.addButton("E")
    .setPosition(120,80)
    .setSize(30,30)
     .setFont(font1)
 ;
  cp5.addButton("D")
    .setPosition(120,120)
    .setSize(30,30)
     .setFont(font1)
 ;
  cp5.addButton("R")
    .setPosition(160,80)
    .setSize(30,30)
     .setFont(font1)
 ; 
  cp5.addButton("F")
    .setPosition(160,120)
    .setSize(30,30)
    .setFont(font1)
 ;  
  cp5.addButton("T")
    .setPosition(200,80)
    .setSize(30,30)
    .setFont(font1)
 ;  
   cp5.addButton("G")
    .setPosition(200,120)
    .setSize(30,30)
    .setFont(font1)
 ;
   cp5.addButton("Y")
    .setPosition(240,80)
    .setSize(30,30)
    .setFont(font1)
 ;
  cp5.addButton("H")
    .setPosition(240,120)
    .setSize(30,30)
    .setFont(font1)
 ;
  cp5.addButton("U")
    .setPosition(280,80)
    .setSize(30,30)
    .setFont(font1)
 ;
   cp5.addButton("J")
    .setPosition(280,120)
    .setSize(30,30)
    .setFont(font1)
 ;
   cp5.addButton("Kill-K")
    .setPosition(100,200)
    .setSize(80,80)
    .setColorBackground(color(250,0,0))
    .setFont(font1)
 ;
   cp5.addButton("Hand Kill-V")
    .setPosition(100,290)
    .setSize(80,80)
    .setColorBackground(color(250,0,0))
    .setFont(font1)
 ;
}
void draw()
{

  background(255,255,255);
  image(arc,200,85);
  image(aiub,720,10);
  fill(0,0,0);
  textFont(font);
  text(" ARC 2020 ",350,30);
  
  
  text("Speed", 615,70);
  
  text("Hand", 110,70);
  
}
/*void forward()
{
port.write(key.up);
}*/

// TCS230 Arduino Stuff, Dakota Rowehl

#include <Servo.h>

// This is where we declare our pins

#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
const int PhotoResistor = A1;
const int IRreceiver = A0;
int servoPin2 = 10;
int servoPin1 = 11;
int servoPin3 = 9;

// These are global variables for 
// the frequencies that our RGB sensor can record.

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;
int clearFrequency = 0;
int PhotoVal;
int IRval;
String Result1;
String Result2;
String Result3;
String Result;
int n = 0;

Servo Servo2;
Servo Servo3;
Servo Servo1;

int Metal = 0; int Wood = 0; int Plastic = 0;


void setup() {

  // Here we set up what pins are inputs and waht pins are outputs.
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(PhotoResistor, INPUT);
  pinMode(IRreceiver, INPUT);
  pinMode(sensorOut, INPUT);

  Servo2.attach(servoPin2);
  Servo1.attach(servoPin1);
  Servo3.attach(servoPin3);
  
  // Setting frequency scaling to 20%
  // This effects the accuracy of our data coming from the RGB sensor
  // There are four settings.
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  // Starts the serial data recording.
  Serial.begin(9600);

  // This chambers the first ball
  Servo2.write(60);
  delay(1000);
  Servo1.write(100);
  delay(1000);
  Servo1.write(85);

}





void loop() {

// First block is the RGBCIR Data intake
  
  // Setting RED (R) filtered photodiodes.
  // Then storing the red value inputs.
  // Then printing the red values.
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  
  redFrequency = pulseIn(sensorOut, LOW);
  //redFrequency = redFrequency*10;
  
  Serial.print("    ");
  Serial.print(redFrequency);
  delay(100);



  // Setting Green (G) filtered photodiodes.
  // Then storing the green value inputs.
  // Then printing the green values.

  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  greenFrequency = pulseIn(sensorOut, LOW);
  //greenFrequency = greenFrequency*10;
  
  Serial.print("    ");
  Serial.print(greenFrequency);
  delay(100);


   // Setting Blue (B) filtered photodiodes.
  // Then storing the blue value inputs.
  // Then printing the blue values.
  
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  
  blueFrequency = pulseIn(sensorOut, LOW);
  //blueFrequency = blueFrequency*10;
  
  Serial.print("    ");
  Serial.print(blueFrequency);
  delay(100);



  // Setting Clear (C) filtered photodiodes.
  // Then storing the clear value inputs.
  // Then printing the clear values.
  
  digitalWrite(S2,HIGH);
  digitalWrite(S3,LOW);
  
  clearFrequency = pulseIn(sensorOut, LOW);
  //clearFrequency = clearFrequency*10;
  
  Serial.print("    ");
  Serial.print(clearFrequency);
  delay(100);



  // Here we accept and print the input data from the IR receiver.
  
  IRval= analogRead(IRreceiver);

  Serial.print("    ");
  Serial.print(IRval);


  
  // Here we accept and print the input data from the photoresistor.

  PhotoVal = analogRead(PhotoResistor);

  Serial.print("    ");
  Serial.print(PhotoVal);
  






  // Here we call the sorting function and print the determined material.
  // Also prints the scores for each material.
  RGBCIRSort();

  Serial.print("    ");
  Serial.print(Metal);
  Serial.print("    ");
  Serial.print(Wood);
  Serial.print("    ");
  Serial.print(Plastic);
  Serial.print("    ");
  Serial.println(Result);

  Wood = 0;
  Metal = 0;
  Plastic = 0;
  Result = "";
  Servo3.write(90);

  IRSort();
  
  // This code is delaying the whole process by half a second

}












// In the function below we decide the material of the ball using a point system. 
// We check the input for red, green, blue, and clear, against the expected values for each material. 
// If the values agree within a tolerance of 5%, a point is given towards the material. 
// Whatver material has the most points is output as the decided material.

void RGBCIRSort(){

         //These are values calibrated based on ambient light.
  //int MExpR = -.029*PhotoVal + 290; int PlExpR = -.023*PhotoVal + 260; int WExpR = -.02*PhotoVal + 260;
  //int MExpG = -.015*PhotoVal + 330; int PlExpG = -.013*PhotoVal + 290; int WExpG = -.01*PhotoVal + 300;
  //int MExpB = -.0095*PhotoVal + 260; int PlExpB = -.0064*PhotoVal + 230; int WExpB = -.0072*PhotoVal + 250;
  //int MExpC = -.0042*PhotoVal + 92; int PlExpC = -.0034*PhotoVal + 82; int WExpC = -.004*PhotoVal + 86;

         // These are emergency values taken in the test room should the calibration fail.
  int MExpR = 317; int PlExpR = 246; int WExpR = 289;
  int MExpG = 388; int PlExpG = 288; int WExpG = 350;
  int MExpB = 373; int PlExpB = 278; int WExpB = 337;
  int MExpC = 192; int PlExpC = 160; int WExpC = 180;

  


  if (redFrequency >= MExpR - (MExpR*.05)   &&  redFrequency <= MExpR + (MExpR*.05)){
    Metal++;
  }
  if (redFrequency >= WExpR - (WExpR*.05)   &&  redFrequency <= WExpR + (WExpR*.05)){
    Wood++;
  }
  if (redFrequency >= PlExpR - (PlExpR*.05)   &&  redFrequency <= PlExpR + (PlExpR*.05)){
    Plastic++;
  }

  if (greenFrequency >= MExpG - (MExpG*.05)   &&  greenFrequency <= MExpG + (MExpG*.05)){
    Metal++;
  }
  if (greenFrequency >= WExpG - (WExpG*.05)   &&  greenFrequency <= WExpG + (WExpG*.05)){
    Wood++;
  }
  if (greenFrequency >= PlExpG - (PlExpG*.05)   &&  greenFrequency <= PlExpG + (PlExpG*.05)){
    Plastic++;
  }

  if (blueFrequency >= MExpB - (MExpB*.05)   &&  blueFrequency <= MExpB + (MExpB*.05)){
    Metal++;
  }
  if (blueFrequency >= WExpB - (WExpB*.05)   &&  blueFrequency <= WExpB + (WExpB*.05)){
    Wood++;
  }
  if (blueFrequency >= PlExpB - (PlExpB*.05)   &&  blueFrequency <= PlExpB + (PlExpB*.05)){
    Plastic++;
  }

  if (clearFrequency >= MExpC - (MExpC*.05)   &&  clearFrequency <= MExpC + (MExpC*.05)){
    Metal++;
  }
  if (clearFrequency >= WExpC - (WExpC*.05)   &&  clearFrequency <= WExpC + (WExpC*.05)){
    Wood++;
  }
  if (clearFrequency >= PlExpC - (PlExpC*.05)   &&  clearFrequency <= PlExpC + (PlExpC*.05)){
    Plastic++;
  }




 if(Metal > Wood && Metal > Plastic){
  Result = "Metal";
  Servo3.write(45);

  // This sets the center servo to its 'open' position allowing balls to roll down.
  Servo2.write(20);
  delay(1500);

  // This sets the center servo back to its 'closed' position, then opening and closing the rear servo
  Servo2.write(60);
  delay(1000);
  Servo1.write(95);
  delay(1000);
  Servo1.write(85);



 }

 
 else if(Wood > Metal && Wood > Plastic){
  Result = "Wood";
  Servo3.write(90);

  // This sets the center servo to its 'open' position allowing balls to roll down.
  Servo2.write(20);
  delay(1500);

  // This sets the center servo back to its 'closed' position, then opening and closing the rear servo
  Servo2.write(60);
  delay(1000);
  Servo1.write(95);
  delay(1000);
  Servo1.write(85);


 }

 
 else if(Plastic > Wood && Plastic > Metal){
  Result = "Plastic";
  Servo3.write(140);
  
  // This sets the center servo to its 'open' position allowing balls to roll down.
  Servo2.write(20);
  delay(1500);

  // This sets the center servo back to its 'closed' position, then opening and closing the rear servo
  Servo2.write(60);
  delay(1000);
  Servo1.write(95);
  delay(1000);
  Servo1.write(85);



 }

}













// This code determines what the material may be based on IR reciever data. Currently it does nothing other than that.
void IRSort(){
  int MetalExpectedIR = .00097*PhotoVal + 10;
  int PlasticExpectedIR = .00069*PhotoVal + 7.4;
  int WoodExpectedIR = .00092*PhotoVal + 4.7;

  if (IRval <= MetalExpectedIR + 3 || IRval >= MetalExpectedIR - 2){
    Result1 = "Could be Metal";
  }
  else{
    Result1 = "Not Metal";
  }

  if (IRval <= WoodExpectedIR + 2 || IRval >= WoodExpectedIR - 1){
    Result2 = "Could be Wood";
  }
  else{
    Result2 = "Not Wood";
  }
  
    if (IRval <= PlasticExpectedIR + 3 || IRval >= PlasticExpectedIR - 2){
    Result3 = "Could be Plastic";
  }
  else{
    Result3 = "Not Plastic";
  }
  
}

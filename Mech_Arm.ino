#include<Servo.h> //Header file to make the Servo motor work by including the necessary functions
#include<IRremote.h> //Header file to make the IR sensor receive the signals from IR remote
int r = 12; //Pin to which the IR sensor is connected i.e. 12
IRrecv irrecv(r); //Object that receives the IR signal
decode_results results; // Results returned from the decoder
Servo S1,S2,S3,S4; //Objects of servo motor representing each motor
int p1,p2,p3,p4; //Integer variables for setting the angles of the servo motor
void setup()
{
  //Attaching the servo motors to their respective pins
  S1.attach(11);
  S2.attach(10);
  S3.attach(9);
  S4.attach(8);
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps

  irrecv.enableIRIn(); // Begin the receiving process. This will enable the timer interrupt which consumes a small amount of CPU every 50 µs
}

void loop()
{
 //setting value of the integers for servo motors
  p1=0; //Reference angle for S1 motor (Base motor)
  p2=90; // Reference angle for S2 motor (Elbow motor)
  p3=0; // Reference angle for S3 motor (Claw motor)
  p4=180; // Reference angle for S4 motor (Claw motor)
  if(irrecv.decode(&results)) //if IR sensor receives signal from the remote 
  {
  switch(results.value) //Switch case depending on result value of the code received
  {
    case 0xFD609F://Forward button
    {
   S1.write(p2+45); //Add 45 degrees to the base servo motor
    break;
    }
    case 0xFD20DF: //Backward button
    {
      S1.write(p2); //Maintain the base motor at 90 degrees
      break;
    }
    case 0xFDA05F: //Pick
    {
      S3.write(p3+45);  //Add 45 degrees to the S3 motor
  S4.write(p4-45); //Remove 45 degrees from S3 motor
      break;
    }
    case 0xFD40BF: //Leave
    {
//Set S3 and S4 motor to their original position
      S3.write(p3);  //0 degrees
      S4.write(p4);  //180 degrees
      break;
    }
    case 0xFD50AF: //Elbow movement up
    {
      S2.write(p2+30); //Add 30 degrees to S2 motor
      break;
    }
    case 0xFD10EF:
    {
      S2.write(p2-30); //Elbow down
      break;
    }
    case 0xFDB04F: //Elbow equalized
    {
      S2.write(p2); 
      break;
    }
    default: //Wrong input given
    Serial.println("Wrong Input!");
  }
  irrecv.resume(); //Wait for next IR signal
}
}

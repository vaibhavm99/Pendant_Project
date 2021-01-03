#include <SoftwareSerial.h>
#include <TinyGPS.h>


float gpslat, gpslon;

TinyGPS gps;
SoftwareSerial sgps(4, 5);  //  RX | TX
SoftwareSerial sgsm(2, 3);   // RX | TX

int button = 6;
int flag = 0;
void setup()
{
  sgsm.begin(9600);
  sgps.begin(9600);
  pinMode(button, INPUT);
}

 float s = millis();
void loop()
{
  

  // Increase button counter
 
  if(digitalRead(button) == HIGH)
  {
    flag++;
    float e = millis();
    if((e-s)>5000)
    {
      flag = 0;
      s = millis();
    }
  }
  
  
  if(flag == 3)     //If button pressed 3 times
  {
    flag = 0;
    // Get GPS Location 
  sgps.listen();
  while (sgps.available())
  {
    int c = sgps.read();
    if (gps.encode(c))
    {
      gps.f_get_position(&gpslat, &gpslon);
    }
  }
    SendMessage1();  // Can be edited for personal emergency contact
    SendMessage2();  // NOT TO BE EDITED! SENDS SMS TO POLICE!
  }
 delay(500);    
}


 void SendMessage1()
{
      sgsm.listen();
      sgsm.print("\r");
      delay(500);
      sgsm.print("AT+CMGF=1\r");
      delay(500);
      sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r");            // Change the xx with phone number
      delay(500);
      sgsm.println("I need HELP! My location is ");
      sgsm.print("https://www.google.com/maps/?q=");
      sgsm.print(gpslat, 6);
      sgsm.print(",");
      sgsm.print(gpslon, 6);   
      delay(500);
      sgsm.write(0x1A);
      delay(500); 
   
   
      
}


void SendMessage2()
{
      sgsm.listen();
      sgsm.print("\r");
      delay(500);
      sgsm.print("AT+CMGF=1\r");
      delay(500);
      sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(500);
      sgsm.println("I need HELP! My location is ");
      sgsm.print("https://www.google.com/maps/?q=");
      sgsm.print(gpslat, 6);
      sgsm.print(",");
      sgsm.print(gpslon, 6);   
      delay(500);
      sgsm.write(0x1A);
      delay(500); 
   
   
      
}


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
    SendMessage();          
  }
 delay(500);    
}


 void SendMessage()
{
      sgsm.listen();
      sgsm.print("\r");
      delay(500);
      sgsm.print("AT+CMGF=1\r");
      delay(500);
      sgsm.print("AT+CMGS=\"+91XXXXXXXXXX\"\r");
      delay(500);
      //The text of the message to be sent.
   
      sgsm.println("I need HELP! My location is ");
      sgsm.print("https://www.google.com/maps/?q=");
      sgsm.print(gpslat, 6);
      sgsm.print(",");
      sgsm.print(gpslon, 6);   
      delay(500);
      sgsm.write(0x1A);
      delay(500);
      
}


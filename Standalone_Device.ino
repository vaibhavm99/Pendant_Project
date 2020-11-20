#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);    // RX | TX
int button = 2;
int flag = 0;
void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  pinMode(button, INPUT);
}


void loop()
{
  if(digitalRead(button) == HIGH)
    flag++;
  if(flag == 3)     //If button pressed 3 times
  {
    flag = 0;
    SendMessage();          
  }
     
delay(100);


 if (mySerial.available()>0)             //Read any data coming from GSM Module
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+91xxxxxxxxxx\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("I need Help! My location is");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


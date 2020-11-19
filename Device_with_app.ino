#include <SoftwareSerial.h>

SoftwareSerial BTserial(10, 11); // RX | TX  
int button = 2;
int flag = 0;
void setup() {
  pinMode(button, INPUT);
  BTserial.begin(9600); 
}

void loop() {
  if(digitalRead(button) == HIGH)
    flag++;
  if(flag == 3)     //If button pressed 3 times
  {
    flag = 0;
    BTserial.print("1");             //EMERGENCY = 1
  }
  BTserial.print("0");              //NORMAL PING = 0   
delay(100);

}

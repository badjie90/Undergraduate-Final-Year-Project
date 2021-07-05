#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // gsm module connected here
String textForSMS;

int pirsensor = 2; // pir sensor is connected with pin2 of the arduino
int relay = 13; // Alarm/light can be connected with this relay

void setup() {


  randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM900.begin(9600); // original 19200. while enter 9600 for sim900A
  Serial.println(" logging time completed!");
  pinMode(pirsensor, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, LOW);

  delay(1000); // wait for 5 seconds


}

void loop() {


  if ( digitalRead(pirsensor) == HIGH) //
  {
    textForSMS =  "\nBAKARY INTRUDER DETECTED IN YOUR AREA OF CONCERNED";
    digitalWrite(relay, HIGH);
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("message sent.");
    delay(1500);
  }
  if ( digitalRead(pirsensor) == LOW) //
  {
    digitalWrite(relay, LOW);
    delay(500);
  }

}


void sendSMS(String message)
{
  SIM900.print("AT+CMGF=1\r");                     // AT command to send SMS message
  delay(500);
  SIM900.println("AT + CMGS = \"+2203221840\"");  // recipient's mobile number, in international format

  delay(50);
  SIM900.println(message);                         // message to send
  delay(50);
  SIM900.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(50);
  SIM900.println();
  delay(50);                                     // give module time to send SMS

}

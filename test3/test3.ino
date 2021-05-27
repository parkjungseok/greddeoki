#include <SoftwareSerial.h>

#include <TinyGPS.h>

int blueTx = 2; //Tx (보내는핀 설정)
int blueRx = 3; //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString = ""; //받는 문자열


TinyGPS gps;
SoftwareSerial ss(4, 5);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);
  
  Serial.print("Simple TinyGPS library v. "); Serial.println(TinyGPS::library_version());
  Serial.println("by Mikal Hart");
  Serial.println();


  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
}

void loop()
{

  /*while(ss.available())
  {
    Serial.println("GPS On");
    char gpsData = (char)ss.read();
    gpsData += gpsData;
    if(mySerial.available())
    {
      mySerial.write(gpsData);
    }
    delay(5);
  }*/
  
  /*while (Serial.available()) //mySerial 값이 있으면*/
  {
    /*Serial.println("asd");*/
    mySerial.write(1);
    /* char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString += myChar;*/ //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  
  /*if(myString.length() > 0)
  {
    mySerial.write(1);
  }
*/
 /* 
  if (myString.length() > 0) {
    Serial.println(myString);
    if (myString.equals("def"))
    {
      digitalWrite(13, HIGH); //LED ON
     }
    else{
      digitalWrite(13, LOW);  //LED OFF
      myString = "";
    }
   } 
   else {
    digitalWrite(13, LOW);  //LED OFF
    myString = "";
    
  }*/
}

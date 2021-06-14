#include <SoftwareSerial.h>
#include <TinyGPS.h>

//int blueTx = 2; //Tx (보내는핀 설정)
//int blueRx = 3; //Rx (받는핀 설정)
//SoftwareSerial Serial1(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString = ""; //받는 문자열


TinyGPS gps;


void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial.println();


  //Serial.begin(9600);   //시리얼모니터
  //Serial1.begin(9600); //블루투스 시리얼 개방
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
  Serial1.println("Project Start");
}

void loop()
{
  while (Serial1.available()) //Serial1 값이 있으면
  {
    char myChar = (char)Serial1.read();  //Serial1 int형식의 값을 char형식으로 변환
    myString += myChar; //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
    if (myString.length() > 0) {
    Serial.println(myString);
    if (myString.equals("on"))
    {
      digitalWrite(13, HIGH); //LED ON
      Serial.print("LED ON ");
    }
    else
    {
      digitalWrite(13, LOW);  //LED OFF
      Serial.print("LED OFF ");  
    }
    myString = "";
   } 
   else {
    myString = "";
  }
 




  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;


  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial2.available())
    {
      char c = Serial2.read();

      if (gps.encode(c)) 
        newData = true;
    }
  }

  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial1.print("LAT=");
    Serial1.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial1.print(" LON=");
    Serial1.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial1.print(" SAT=");
    Serial1.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial1.print(" PREC=");
    Serial1.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  Serial1.print(" CHARS=");
  Serial1.print(chars);
  Serial1.print(" SENTENCES=");
  Serial1.print(sentences);
  Serial1.print(" CSUM ERR=");
  Serial1.println(failed);
  if (chars == 0)
    Serial1.println("** No characters received from GPS: check wiring **");
}

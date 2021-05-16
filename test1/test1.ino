#include <SoftwareSerial.h> //시리얼 통신 라이브러리 호출
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(5, 6);
int blueTx = 2; //Tx (보내는핀 설정)
int blueRx = 3; //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString = ""; //받는 문자열
int bufferPosition;
byte buffer[1024];
void setup() {
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼 개방
  ss.begin(9600);
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
  bufferPosition = 0;  // 버퍼 위치 초기화 
  Serial.println(TinyGPS::library_version());
}

void loop() {

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  float flat, flon;
  unsigned long age;
  unsigned short data;
  gps.f_get_position(&flat, &flon, &age);
  
   for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (ss.available())
    {
      char c = ss.read();
           if (gps.encode(c))
        newData = true;
    }
  }

   if (newData)
  {
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  Serial.print(" CHARS=");
  Serial.print(chars);
  Serial.print(" SENTENCES=");
  Serial.print(sentences);
  Serial.print(" CSUM ERR=");
  Serial.println(failed);
  if (chars == 0)
    Serial.println("** No characters received from GPS: check wiring **");
  if (mySerial.available()) //mySerial 값이 있으면
  {
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString += myChar; //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
  Serial.println(myString);
  if (myString.length() > 0) {
    if (myString.equals("def"))
    {
      digitalWrite(13, HIGH); //LED ON
     }
    else{
      digitalWrite(13, LOW);  //LED OFF
      myString = "";
    }
  
  } 
  if(data == '\n') { 
      buffer[bufferPosition] = '\0';
      
      // 스마트폰으로 문자열 전송
      ss.write(buffer, bufferPosition);
      bufferPosition = 0;
    } 

}

#include <SoftwareSerial.h>
#include <TinyGPS.h>

int blueTx = 2; //Tx (보내는핀 설정)
int blueRx = 3; //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
String myString = ""; //받는 문자열


TinyGPS gps;
SoftwareSerial ss(11, 12);

void setup()
{
  Serial.begin(9600);
  ss.begin(9600);

  
  Serial.println();


 
  mySerial.begin(9600); //블루투스 시리얼 개방
  pinMode(13, OUTPUT);  //Pin 13을 OUTPUT으로 설정 (LED ON/OFF)
  Serial.println("Project Start");
}
int mode = 0 ;

void loop()
{
#if false
  if (mySerial.available()) {       
    Serial.write(mySerial.read());  //블루투스측 내용을 시리얼모니터에 출력
  }
  if (Serial.available()) {         
    mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  //  Serial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
 /* switch(mode){
  case 0 :mySerial.write("AT");mode++;break;    
  case 1 :mySerial.write("AT\r\n");mode++;break;
  case 2 :mySerial.write("AT\n");mode++;break;
  case 3 :mySerial.write("AT\r");mode++;break;
  case 4 :mySerial.write("AT\n\r");mode = 0;break;
  }
  */
  
  
  delay(500);



#else
  while (mySerial.available()) //mySerial 값이 있으면
  {
    //Serial.println("asd");
    char myChar = (char)mySerial.read();  //mySerial int형식의 값을 char형식으로 변환
    myString += myChar; //수신되는 문자열을 myString에 모두 붙임 (1바이트씩 전송되는 것을 모두 붙임)
    delay(5);           //수신 문자열 끊김 방지
  }
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
  }
 




  
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;


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
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    mySerial.print("LAT=");
    mySerial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    mySerial.print(" LON=");
    mySerial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    mySerial.print(" SAT=");
    mySerial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    mySerial.print(" PREC=");
    mySerial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
  }
  
  gps.stats(&chars, &sentences, &failed);
  mySerial.print(" CHARS=");
  mySerial.print(chars);
  mySerial.print(" SENTENCES=");
  mySerial.print(sentences);
  mySerial.print(" CSUM ERR=");
  mySerial.println(failed);
  if (chars == 0)
    mySerial.println("** No characters received from GPS: check wiring **");
#endif    
}

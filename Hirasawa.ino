#include <Wire.h>
#include <SPI.h>
#include <SD.h>

int Relay = 8;
int Sen1 = 7;
int Sen2 = 9;


File myFile;
const int chipSelect = 10;
double Time;
double Watt = 0;
void ReadText(){
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
//    Serial.println("error opening test.txt");
  }
}


void WriteText(long Time){
  myFile = SD.open("test.txt", FILE_WRITE);
  
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.println(Time);x
    myFile.println(Time);
  // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening watt.json");
  }
}
void Close(){
  digitalWrite(Relay , 1);
}
void setup() {
  pinMode(Relay , OUTPUT);
  pinMode(Sen1 , INPUT);
  pinMode(Sen2 , INPUT);
  Close();
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("SD Card Check...");
  pinMode(SS, OUTPUT);

  // if (!SD.begin(chipSelect)) { 
  if (!SD.begin(10, 11, 12, 13)) {
    Serial.println("SD Card initialization failed!");
    return;  
  }
  Serial.println("SD Card OK.");
  ReadText();
}
int count = 0;
bool w = false;
bool t = true;

void Open(){
  digitalWrite(Relay , 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(Sen1) == 0){
    Serial.println("Sen1 Detected");
//    count++;
//    Serial.println(count);
//    delay(1500);
    for(int i=0; i<500 ; i+1){
      if(digitalRead(Sen2) == 0){
        
        Serial.println("Open");
        count++;
        Serial.println(count);
        delay(500);
        Serial.println("Exit Loop 1");
        break;
      }
      if(i == 499){
        break;
      }
      delay(10);
    }
  }
  else if(digitalRead(Sen2) == 0){
     Serial.println("Sen2 Detected");
//    count--;
//    Serial.println(count);
//    delay(1500);
    for(int i=0; i<500 ; i+1){
      if(digitalRead(Sen1) == 0){
        
        Serial.println("Close");
        count--;
        Serial.println(count);
        delay(500);
        Serial.println("Exit Loop 2");
        break;
      }
      if(i == 499){
        break;
      }
      delay(10);
    }
  }
  if(count < 0){
    count = 0;
  }
  if(count >= 1){
    w = true;
    Open();
    if(t == true){
      Time = millis();
      t = false;
    }
  }
  else if(count == 0){

    if(w == true){
      Time = (millis() - Time) / 1000;
      Watt = Watt+(Time*0.0014);
      WriteText(Time);
      w=false;
      t = true;
    }else{
      
    }
    Close();
    
  }
  
  
}
//unsigned long ShowTime; // ประกาศตัวแปรชื่อ ShowTime เก็บค่าการนับเวลา เป็นตัวแปร unsigned long
//
//void setup(){
//Serial.begin(9600);
//} 
//void loop(){
//Serial.print("Time: ");
//ShowTime = millis(); // ให้ ShowTime = เวลาที่ Arduio นับได้
//delay(2000);
//ShowTime = millis()-ShowTime;
//Serial.println(ShowTime); // แสดงค่า ShowTime และขึ้นบรรทัดใหม่ด้วยคำสั่ง println
//}

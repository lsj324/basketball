// 디스플레이 소스코드
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>#define SCREEN_WIDTH 128     // OLED display 너비 픽셀
#define SCREEN_HEIGHT 64     // OLED display 높이 픽셀
#define OLED_RESET -1        // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C  // display 주소
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// 서브모터
#include <Servo.h>
Servo myservo;// 레이더로 검은색인지 아닌지 판별
const int IRPin = 12;
int count = 0;
int point = 0;// 부
int IR = 5;
int buzzerPin = 8;
int notes[] = { 2093, 2349, 2637, 2093, 2093, 2349, 2637, 2093, 2637, 2793, 3135, 2637, 2793, 3135, 3135, 3520, 3135, 2793, 2637, 2093, 3135, 3520, 3135, 2793, 2637, 2093, 2093, 1567, 2093, 2093, 1567, 2093 };
int durations[] = { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 };void setup() {
  pinMode(IRPin, INPUT);
  Serial.begin(115200);  oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  delay(2000);  oled.clearDisplay();
  oled.setTextColor(WHITE);  myservo.attach(4);  pinMode(IR, INPUT);
  pinMode(buzzerPin, OUTPUT);
}void loop() {
  int IRsensor = digitalRead(IR);  int IRInput = digitalRead(IRPin);
  Serial.println(IRInput);
  //Serial.println(point);
  oled.setTextSize(2);  if (IRInput  0) {
    if (count  0) {
      oled.clearDisplay();
      oled.setCursor(30, 28);
      oled.println("GOAL!!");      oled.display();
      count++;
      point++;
    }
  } else {
    oled.clearDisplay();
    oled.setCursor(4, 28);
    oled.print("Score: ");
    oled.println(10 * point);
    oled.display();
    count = 0;
  }
  // noTone(buzzerPin);
  if (IRsensor == 0) {
    for (int i = 0; i < 31; i++) {
      tone(buzzerPin, notes[i]);
      delay(200 / durations[i]);
      // delay(50);
    }  } else {
    noTone(buzzerPin);
  }
}

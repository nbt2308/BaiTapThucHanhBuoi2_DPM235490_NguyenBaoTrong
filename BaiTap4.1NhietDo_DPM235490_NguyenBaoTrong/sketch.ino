#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Gán chân analog A1 làm biến 'sensor'
const int sensor = A0;

float tempc;  // Biến lưu giá trị nhiệt độ theo độ C
float tempf;  // Biến lưu giá trị nhiệt độ theo độ F
float vout;   // Biến tạm thời chứa kết quả phép đọc

void setup() {
  pinMode(sensor, INPUT);  // Cấu hình chân A1 làm ngõ vào
  Serial.begin(9600);
  lcd.begin(16, 2);
  delay(500);
}

void loop() {
  vout = analogRead(sensor);
  vout = (vout * 500) / 1023;

  tempc = vout;             // Lưu kết quả dưới dạng độ C
  tempf = (vout * 1.8) + 32; // Chuyển đổi từ độ C sang độ F

  lcd.setCursor(0, 0);
  lcd.print("in DegreeC= ");
  lcd.print(tempc);

  lcd.setCursor(0, 1);
  lcd.print("in Fahrenheit=");
  lcd.print(tempf);

  // Trì hoãn 1 giây để đọc kết quả
  delay(1000);
}
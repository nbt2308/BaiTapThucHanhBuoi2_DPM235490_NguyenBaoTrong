#include <LiquidCrystal.h>

int mq2 = A0;   // Chân đọc tín hiệu analog từ cảm biến MQ-2
int rel = 13;   // Chân điều khiển rơ-le
int buz = 10;   // Chân điều khiển còi báo
int d;          // Biến lưu giá trị đọc từ bộ ADC
float p;        // Biến lưu nồng độ phần trăm khí/khói

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  pinMode(rel, OUTPUT);
  pinMode(buz, OUTPUT);
  digitalWrite(rel, LOW);
  digitalWrite(buz, LOW);
  lcd.begin(16, 2);
}

void loop() {
  d = analogRead(mq2);        // Đọc giá trị từ cảm biến MQ-2
  p = d / 9.48;               // Quy đổi ra nồng độ %

  lcd.setCursor(0, 0);
  lcd.print("LPG/SMOKE SENSOR");
  lcd.setCursor(0, 1);
  lcd.print("Conc: ");
  lcd.print(p);
  lcd.print("%");

  // Kiểm tra ngưỡng cảnh báo (ví dụ 30%)
  if (p > 30) {
    digitalWrite(rel, HIGH);  // Đóng rơ-le kích hoạt quạt/thiết bị
    digitalWrite(buz, HIGH); // Bật còi báo động
  } else {
    digitalWrite(rel, LOW);
    digitalWrite(buz, LOW);
  }
  
  delay(500);
}
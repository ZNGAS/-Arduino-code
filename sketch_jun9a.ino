#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_AHTX0 aht;

#define COMFORTABLE_PIN 8  // 舒適
#define UNCOMFORTABLE_PIN 9 // 不舒適

unsigned long startTime;

void setup() {
  Wire.begin();
  delay(500);

  // 初始化 OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while(1);
  }
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(F("Sensor Ready!"));
  display.display();
  delay(2000);

  // 初始化 AHT 感測器
  if (!aht.begin()) {
    while(1);
  }

  // 設定腳位
  pinMode(COMFORTABLE_PIN, OUTPUT);
  pinMode(UNCOMFORTABLE_PIN, OUTPUT);

  startTime = millis();
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float temperature = temp.temperature;
  float humidity_val = humidity.relative_humidity;

  // 計算經過秒數
  unsigned long elapsedSeconds = (millis() - startTime) / 1000;

  // 顯示溫濕度
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(temperature, 1);
  display.print(F(" C"));

  display.setCursor(0, 30);
  display.print(humidity_val, 1);
  display.print(F("%"));

  // 右下角顯示秒數，字體改小
  display.setTextSize(1);
  // 設定游標到右下角（大約在( SCREEN_WIDTH - 30, SCREEN_HEIGHT - 10)）
  display.setCursor(SCREEN_WIDTH - 40, SCREEN_HEIGHT - 10);
  display.print(elapsedSeconds);
  display.print(F("s"));

  display.display();

  // 判斷舒適狀態
  if (temperature >= 20 && temperature <= 26 && humidity_val >= 40 && humidity_val <= 60) {
    digitalWrite(COMFORTABLE_PIN, HIGH);
    digitalWrite(UNCOMFORTABLE_PIN, LOW);
  } else {
    digitalWrite(COMFORTABLE_PIN, LOW);
    digitalWrite(UNCOMFORTABLE_PIN, HIGH);
  }

  delay(1000);
}

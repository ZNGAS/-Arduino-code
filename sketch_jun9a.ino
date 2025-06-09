#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_AHTX0.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

Adafruit_AHTX0 aht;

void setup() {
  Wire.begin();
  delay(500);

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

  if (!aht.begin()) {
    while(1);
  }
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  float temperature = temp.temperature;
  float humidity_val = humidity.relative_humidity;

  display.clearDisplay();
  display.setTextSize(2);

  display.setCursor(0, 0);
  display.print(temperature, 1);
  display.print(F(" C"));

  display.setCursor(0, 30);
  display.print(humidity_val, 1);
  display.print(F("%"));

  display.display();

  delay(2000);
}

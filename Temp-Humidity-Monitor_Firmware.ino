#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

const int nums_LEDS[] = {2,3,4,5,6,7,8,9,10,11};

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define DHTPIN 12
#define DHTTYPE DHT22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  dht.begin();

  for (int i=2; i < 11; i++) {
    pinMode(nums_LEDS[i], OUTPUT);
  }
}

void loop() {

  float temp = (dht.readTemperature()) * 1.8 + 32; //Converted to Fahrenheit because default to Celcius

  float humidity = dht.readHumidity();

  float scoreTemp = map(temp, 52,93, 0,5);
  float scoreHumidity = map(humidity, 10, 80, 0,5);

  int slotsFilled = scoreTemp + scoreHumidity;

  slotsFilled = constrain(slotsFilled, 0,10);

  for (int i = 2; i < 11; i++){
    if (i < slotsFilled){
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }

  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(50,10);

  display.print(temp, 1);
  display.write(247);
  display.println(F("F"));

  
  display.setCursor(60,40);
  display.print(humidity, 1);
  display.print(F("%"));
  display.display();

  Serial.print(temp, 1);
  Serial.print(F("°F   "));
  Serial.print(humidity, 1);
  Serial.println((F("%")));

  delay(2000);
  
}


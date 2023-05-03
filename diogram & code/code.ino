#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define Button 2
#define Led 3
#define buzzer 4

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

Adafruit_SSD1306 oled(128, 64, &Wire, -1);

float voltComp;
float readAmb, readObj;
float ambTempComp, objTempComp;

void setup() {
  pinMode(Button, INPUT_PULLUP);
  pinMode(Led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  tone(buzzer, 600);
  delay(230);
  noTone(buzzer);
  Serial.begin(9600);
  mlx.begin();

  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  delay(500);
  oled.clearDisplay();
  oled.setTextColor(WHITE);
}

void loop() {
  voltComp = analogRead(A0) * (3.3 / 775);
  readAmb = mlx.readAmbientTempC();
  readObj = mlx.readObjectTempC();
  ambTempComp = readAmb - (voltComp - 3) * 0.6;
  objTempComp = readObj - (voltComp - 3) * 0.6;

    oled_display(digitalRead(Button));
    
 
  delay(250);
}
void oled_display(int Border)
{
  if (Border == LOW)
  {
    digitalWrite(Led, HIGH);
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(1);
    oled.print("Ambient Temp: ");
    oled.setCursor(0, 10);
    oled.setTextSize(2);
    oled.print(ambTempComp);
    oled.setTextSize(1);
    oled.print(" ");
    oled.cp437(true);
    oled.write(111);
    oled.setTextSize(2);
    oled.print("C");

    oled.setCursor(0, 30);
    oled.setTextSize(1);
    oled.print("Object Temp: ");
    oled.setCursor(0, 40);
    oled.setTextSize(2);
    oled.print(objTempComp);
    oled.setTextSize(1);
    oled.print(" ");
    oled.cp437(true);
    oled.write(111);
    oled.setTextSize(2);
    oled.print("C");

    oled.display();
  }if(Border == HIGH)
  {
    
  digitalWrite(Led, LOW);
  oled.clearDisplay();
  oled.setCursor(22, 20);
  oled.setTextSize(2);
  oled.print("press !");
  oled.display();
  }

}

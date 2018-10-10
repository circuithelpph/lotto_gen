/*
 * Lotto number generator
 * written by: gHiL
 * www.circuit-help.com.ph
 * 10/10/2018
 *  
 *  TODO: Trappings for numbers not to be repeated.
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define PIN_FOR_RANDOM A0
#define PIN_BTN_A 9

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup() {
  delay(3000);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Lotto Number");
  display.println("Generator (6/58)");
  display.println("Circuit-Help");
  display.println("circuit-help.com.ph");
  display.display();  
  randomSeed(analogRead(A0));
  delay(5000);

  pinMode(PIN_BTN_A, INPUT_PULLUP);
}

void loop() {
  // for number generated
  static boolean num_gen = false;
  
  // check if num gen is not yet generated
  if(!num_gen){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("6/58");
    for (uint8_t a=0; a<6; a++){
      display.print(random(59));
      if(a!=5){
        display.print("-");  
      }
      display.display();
    }
    num_gen = true;
  }

  if(!digitalRead(PIN_BTN_A)){
    num_gen = false;
    delay(500);
  }
}


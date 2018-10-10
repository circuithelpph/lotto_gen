/*
 *  Lotto number generator
 *  written by: gHiL
 *  www.circuit-help.com.ph
 *  10/10/2018
 *  
 *  Parts used:
 *  Feather Basic Proto
 *  Featherwing OLED
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET      (4)
Adafruit_SSD1306 display(OLED_RESET);

// required numbers for 6/58 = 6
#define NUM_REQ         (6)

// floating pin for random
#define PIN_FOR_RANDOM  (A0)

// button for generating new combinations
#define PIN_BTN_A       (9)

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

// storage for generated numbers
int8_t numbers[NUM_REQ] = {
  0,0,0,0,0,0
};

void setup() {
  // required delay for the OLED on 32u4
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

  // set button as input
  pinMode(PIN_BTN_A, INPUT_PULLUP);
}

void loop() {
  // for number generated
  static boolean num_gen = false;
  
  // check if num gen is not yet generated
  if(!num_gen){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Ultralotto 6/58");
    display.println("");
    int8_t gen_num = 0;
    
    for (uint8_t a=0; a<NUM_REQ; a++){      
      gen_num = random(1,59);

      // check if number is already present on list
      while(check_repetitive(gen_num, a)){        
        gen_num = random(1,59);
      }

      // store on list
      numbers[a] = gen_num;
      display.print(gen_num);

      // if last digit, do not display hyphen
      if(a!=5){
        display.print("-");  
      }
      
      display.display();
    }

    // number generated, toggle indicator
    num_gen = true;
  }

  if(!digitalRead(PIN_BTN_A)){
    // toggle again to enable the generation and display function
    num_gen = false;

    // clear current stored numbers
    clear_numbers();
    delay(500);
  }
}

// function to check if number is already present on list
boolean check_repetitive(int8_t num, int8_t counter){
  for(int8_t a=counter; a>-1; a--){
    if(numbers[a] != num){
    }
    else{
      // number on list, repeated
      return 1;
    }
  }
  // number not on list, not repeated
  return 0;
}

// function to clear number lists
void clear_numbers(){
  for(uint8_t a=0; a<NUM_REQ; a++){
    numbers[a] = 0;
  }
}


#include "FastLED.h"

#define NUM_LEDS 115
#define DATA_PIN 0 //Green wire when using the JST SM connectors
#define MAX_BRIGHTNESS 255

CRGB leds[NUM_LEDS];

void setup()
{
   //FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop()
{
  rainbow(20);
  //cylon(CRGB::Red,25, 5);
  //color_chase(CRGB::Green, 15);
  //color_chase(CRGB::BlueViolet, 15);
  //  color_chase(CRGB::Red, 15);
  //color_chase(CRGB::Yellow, 15);
  //color_chase(CRGB::Green, 15);
  //color_chase(CRGB::Cyan, 15);
  //color_chase(CRGB::White, 15);
  //color_chase(CRGB::Blue, 15);
  //missing_dot_chase(CRGB::White, 20);
  //missing_dot_chase(CRGB::Red, 20);
  //missing_dot_chase(CRGB::Yellow, 20);
  //missing_dot_chase(CRGB::Green, 20);
  //missing_dot_chase(CRGB::Cyan, 20);
  //missing_dot_chase(CRGB::Blue, 20);
  //missing_dot_chase(0x3000cc, 20) ;
}


/// Move a single led
void color_chase(uint32_t color, uint8_t wait)
{
  FastLED.clear();
  FastLED.setBrightness(MAX_BRIGHTNESS);

  for(int led_number = 0; led_number < NUM_LEDS; led_number++)
  {
    leds[led_number] = color;
    FastLED.show();
    delay(wait);
    leds[led_number] = CRGB::Black; //Will clear the current pixel on the next show()
  }
  return;
}


/// Move an "empty" dot down the strip
void missing_dot_chase(uint32_t color, uint8_t wait)
{
  for (int led_brightness = MAX_BRIGHTNESS; led_brightness > 10; led_brightness/=2)
  {
    FastLED.setBrightness(led_brightness);
    fill_solid(leds, NUM_LEDS, color);

    for(int led_number = 0; led_number < NUM_LEDS; led_number++)
    {
      leds[led_number] =  CRGB::Black; // Set new pixel 'off'
      if( led_number > 0 && led_number < NUM_LEDS)
      {
        leds[led_number-1] = color; // Set previous pixel 'on'
      }
      FastLED.show();
      delay(wait);
    }
  }
  return;
}

/// Cylon - LED sweeps back and forth
void cylon(CRGB color, uint16_t wait, uint8_t number_of_cycles)
{
  FastLED.setBrightness(MAX_BRIGHTNESS);
  
  for (uint8_t times = 0; times<=number_of_cycles; times++)
  {
    // Forward
    for(int led_number = 0; led_number < NUM_LEDS; led_number++)
    {
      leds[led_number] = color;
      FastLED.show();
      leds[led_number] = CRGB::Black; //Will clear the current pixel on the next show()
      delay(wait);
    }

    // Back
    for(int led_number = NUM_LEDS-1; led_number >= 0; led_number--)
    {
      leds[led_number] = color;
      FastLED.show();
      leds[led_number] = CRGB::Black;  //Will clear the current pixel on the next show()
      delay(wait);
    }
  }
  return;
}

void rainbow(uint8_t wait) 
{
  FastLED.clear();
  FastLED.setBrightness(MAX_BRIGHTNESS);

  for(uint16_t  hue=10; hue<255*3; hue++) 
  {
    fill_rainbow( &(leds[0]), NUM_LEDS /*led count*/, hue /*starting hue*/);    
    FastLED.show();
    delay(wait);
  }
  return;
}



#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    16

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 6

// Delay time in MS
#define SCRLDELAY 1000


char *letters[] = {
  // The letters A-Z in Morse code  
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."         
};
 
char *numbers[] = {
  // The numbers 0-9 in Morse code  
  "-----", ".----", "..---", "...--", "....-", ".....", "-....", 
  "--...", "---..", "----."
};


//internal shifting reg
bool Leds[LED_COUNT];


//ONLY LOWER CASE
char Text[] = "hello world";


// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);



// setup() function -- runs once at startup --------------------------------

void setup() 
{
  Serial.begin(115200);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255)

  //Init our led array
  for(int i=LED_COUNT-1; i>0; i--)
  {
    Leds[i]=false;
  }
}


void loop() 
{
  for(int i = 0; i <strlen(Text); i++)
  {
    if (Text[i] >= 'a' && Text[i] <= 'z') 
    {
        Morse(letters[Text[i] - 'a']);
    }
    else if (Text[i] >= '0' && Text[i] <= '9') 
    {
        Morse(numbers[Text[i] - '0']);
    }
    else if (Text[i] == ' ') 
    {
        // Put space between two words in a message...equal to seven dots
        EmptySpace(7);     
     }
    
  }
  //Clear board after each line
  EmptySpace(LED_COUNT); 
}


//print the char
void Morse(char *morse_code)
{
  // Read the dots and dashes and flash accordingly
  for(int i = 0; i <strlen(morse_code) ; i++)
  {
    flash_dot_or_dash(morse_code[i]);
  }
  //between letters add 3 empty spots
  EmptySpace(3);
}

//print the "Morse char"
void flash_dot_or_dash(char dot_or_dash) 
{
  if (dot_or_dash == '.') 
  { // If it is a dot
     ScrollLeds(true);
     delay(SCRLDELAY);          
  }
  else
  { // Has to be a dash...equal to three dots
    ScrollLeds(true);
    delay(SCRLDELAY); 
    ScrollLeds(true);
    delay(SCRLDELAY); 
    ScrollLeds(true);
    delay(SCRLDELAY);            
  }

  //beteen parts of letter One empty space
  EmptySpace(1);
}


//add X amount of empty spots
void EmptySpace(int Times)
{
  for(int i=1;i<=Times;i++)
  {
    ScrollLeds(false);
    delay(SCRLDELAY);
  }
}

//shift our internal reg with new state
void ScrollLeds(bool State)
{
  
  for(int i=strip.numPixels()-1; i>0; i--)
  {
    Leds[i]=Leds[i-1];
  }
  Leds[0]=State;
  SetLeds();
}


//set leds to reg
void SetLeds()
{
  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, strip.Color(Leds[i]? 255 : 0,   0,   0));
    delay(1);
  }
  strip.show();
}

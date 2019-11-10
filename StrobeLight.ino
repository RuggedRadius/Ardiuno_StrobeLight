// Code by Ben Royans
// 7/11/2019
// Strobe Light

#define pinRed 9
#define pinBlue 11
#define pinGreen 10
#define rotation 0
#define sync 3
#define mode 2
#define buzzer 5

// TEMPO MODE SETUP *****************
int tempo = 128;
bool setTempoModeOn = false;
// **********************************


bool currentMode = 0;

void setup() {
  // Set pins
  pinMode(pinRed, INPUT);
  pinMode(pinGreen, INPUT);
  pinMode(pinBlue, INPUT);
  pinMode(rotation, OUTPUT);
  pinMode(sync, INPUT);
  pinMode(mode, INPUT);
  pinMode(buzzer, OUTPUT);

  // Begin Serial output
  Serial.begin(9600);

  // Header
  Serial.println("\t\t\t****************************************************************");
  Serial.println("\t\t\t\t\tArduino Strobe Light\n");
  Serial.println("\t\t\t\t\t\tCode by Ben Royans © 2019");
  Serial.println("\t\t\t****************************************************************\n\n");

  // Startup Tone
  Arpeggio(5, 500, 100, 2000, 100);    
}

void loop() 
{ 
  // Get switch state if pressed 
  UpdateSwitch();
  
  switch (setTempoModeOn)
  {
    case 1:
      if (digitalRead(3) == 1)
      {  
        StrobeTempo();
      }
      break;
    case 0:
      if (digitalRead(3) == 1)
      {  
        StrobeRotator();
      }    
      break;    
  }
}

void UpdateSwitch() 
{
      // Get switch mode
  if (digitalRead(2) == 0)
  {
        
    // Change mode
    if (setTempoModeOn == 1)
    {
      setTempoModeOn = 0;
      PlayTone2();
      Serial.println("*** VARIABLE MODE ***");
      delay(500);
    }
    else
    {
      setTempoModeOn = 1;
      PlayTone3();
      Serial.println("*** TEMPO MODE ***");
      delay(500);
    }
  }
}

void PlayTone3 ()
{
    tone(5, 6000, 100);
    delay(150);
    tone(5, 8000, 100); 
}

void PlayTone2 ()
{
    tone(5, 6000, 100);
    delay(150);
    tone(5, 4000, 100); 
}

void PlayTone1 () 
{
    tone(5, 2000, 100);
    delay(100);
    tone(5, 4000, 100);     
}

void StrobeTempo() 
{
    RBG(255, 255, 255);
    delay(TempoCalc(tempo));
    RBG(0, 0, 0); 
    delay(TempoCalc(tempo));
}

void StrobeRotator() 
{
    RBG(255, 255, 255);
    delay(DelayTime());
    RBG(0, 0, 0);
    delay(DelayTime()); 
}

double TempoCalc (double t)
{
  double bps = t / 60;
  return (1000/ bps);
}


int DelayTime()
{
  return analogRead(0) / 4;
}

void RBG(int red, int blue, int green)
{   
   analogWrite(9, red);
   analogWrite(10, blue);
   analogWrite(11, green);
}

void Arpeggio(int notes, int interval, int timing, int initial, int del)
{
  for (int i = 0; i < notes; i++)
  {
    tone(buzzer, (initial + (interval * i)), timing);
    delay(del);
  }
}

#include <LedControl.h>
LedControl lc = LedControl(12, 11, 10, 1);

const int pinSW = 9;
const int pinX = A1;
const int pinY = A2;
int startgame = 0;
int ok = 0;
int oky = 0;
int okx = 0;
int lives;

int var = 0;

unsigned long lastmillis = 0;

unsigned long hit = 0;
const int nr = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lc.shutdown(0, false);
  lc.setIntensity(0, 2);
  pinMode(pinSW, INPUT_PULLUP);
}

unsigned long lastGen = 0;
unsigned long timer = 500;
unsigned long lastUpdateScreen = 0;
int intervalUpdateScreen = 3000;

unsigned long lasttime = 0;

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(pinSW) == 0 && startgame == 0)
  {
    startgame = 1;
  }
  
  if(startgame == 1 && var ==0)
  { 
  var = 1;
  lives = 3;
  lc.clearDisplay(0);
  for(int i = 0; i < nr; i++)
    lc.setLed(0, i, 3, true);
  lc.setLed(0, 6, 0, true);
  }

  if(var == 1)
  {
  if(digitalRead(pinSW) == 0)
  {
  oky = 1;
  lastmillis = millis();
  lc.setLed(0, 6, 0, false);
  lc.setLed(0, 6, 2, true);
  }

  if(oky == 1 && millis() - lastmillis >= 150)
  {
    lc.setLed(0, 6, 2, false);
    lc.setLed(0, 6, 1, true);
    lastmillis = millis();
    oky = 2;
  }

  if(oky == 2 && millis() - lastmillis >= 150)
  {
    lc.setLed(0, 6, 1, false);
    lc.setLed(0, 6, 2, true);
    lastmillis = millis();
    oky = 3;
  }

  if(oky == 3 && millis() - lastmillis >= 150)
  {
    lc.setLed(0, 6, 2, false);
    lc.setLed(0, 6, 0, true);
    lastmillis = millis();
    oky = 4;
  }

  
  if(millis() - lastGen >= 1700)
  {
  lasttime = millis();
  lc.setLed(0, 0, 0, true);
  ok = 0;
  lastGen = millis();
  }
  
  if(millis() - lasttime >= 200 && ok == 0)
  {
    lc.setLed(0, 0, 0, false);
    lc.setLed(0, 1, 0, true);
    lasttime = millis();
    ok = 1;
  }

  if(millis() - lasttime >= 200 && ok == 1)
  {
    lc.setLed(0, 1, 0, false);
    lc.setLed(0, 2, 0, true);
    lasttime = millis();
    ok = 2;
  }
    
    if(millis() - lasttime >= 200 && ok == 2)
  {
    lc.setLed(0, 2, 0, false);
    lc.setLed(0, 3, 0, true);
    lasttime = millis();
    ok = 3;
  }

  if(millis() - lasttime >= 200 && ok==3)
  {
    lc.setLed(0, 3, 0, false);
    lc.setLed(0,4,0,true);
    lasttime = millis();
    ok=4;
  }

  if(millis() - lasttime >= 200 && ok == 4)
  {
    lc.setLed(0, 4, 0, false);
    lc.setLed(0, 5, 0, true);
    lasttime = millis();
    ok = 5;
  }
  
    if(millis() - lasttime >= 200 && ok == 5)
  {
    lc.setLed(0, 5, 0, false);
    lc.setLed(0, 6, 0, true);
    lasttime = millis();
    ok = 6;
  }

      if(millis() - lasttime >= 200 && ok == 6)
  {
    lc.setLed(0, 6, 0, false);
    lc.setLed(0, 7, 0, true);
    lasttime = millis();
    ok = 7;
  }
    if(millis() - lasttime >= 200 && ok == 7)
    lc.setLed(0, 7, 0, false);
  
  if(ok == 6 && (oky == 4 || oky == 0))
  {
    hit = millis();  
    okx = 1;
  }

  if(millis() - hit >= 250 && okx == 1)
  {
  lives--;
  lc.setLed(0, 6, 0, true);
  okx = 0;}

  if(lives == 0) 
  {
  startgame = 0;
  for(int i = 0; i < nr; i++)
  for(int j = 0; j < nr; j++)
  lc.setLed(0, i, j, true);
  var = 0;
  }
    }
  
}

#include <LiquidCrystal.h>
const int RS = 12;
const int enable = 11;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int pinSW = 10;
const int pinX = A2;
const int pinY = A1;

int switchValue;
int xValue = 0;
int yValue = 0;

const int maxThreshold = 600;
const int minThreshold = 400;

int cursorValue = 0;

int okx = 0;
int oky = 0;
int ok = 0;

int hs = 0;
int score = 0;
int highscore = 0;

int congrats = 0;

int set = 0;
int startingLevelValue = 0;
int level = 0;
int count = 0;
unsigned long startTime = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  
  pinMode(pinSW, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  lcd.setCursor(0, 0);
  lcd.print(" Start");

  lcd.setCursor(0, 1);
  lcd.print("HighScore");
  
  lcd.setCursor(8, 0);
  lcd.print("Settings");
}

void loop() {
    switchValue = digitalRead(pinSW);
    if(switchValue == LOW)
    {
      delay(200);
      count++;
      lcd.clear();
      startTime = millis();
      level = startingLevelValue;
      congrats = 0;
      hs = 0;
      set = 0;
    }
  
    if(count % 2 == 0)
    {
      xValue = analogRead(pinX);
      
      if (xValue > maxThreshold && okx == 0)
    {
        cursorValue++;
        if (cursorValue > 2) 
          cursorValue = 0;
        okx = 1;
    }
       if (xValue < minThreshold && okx == 0)
    {
        cursorValue--;
        if (cursorValue < 0) 
          cursorValue = 2;
        okx = 1;
    }
      if (xValue < maxThreshold && xValue > minThreshold)
    {
        okx = 0;
    }

    lcd.setCursor(0, 0);
    if (cursorValue == 0) 
      lcd.print(">Start");
    else 
      lcd.print(" Start");
    
    lcd.setCursor(7, 0);
    if (cursorValue == 1) 
      lcd.print(">Settings");
    else 
      lcd.print(" Settings");
      
    lcd.setCursor(0, 1);
    if (cursorValue == 2)
      lcd.print(">HighScore");
    else 
      lcd.print(" HighScore");
  }

  else if(count %2 ==1)
  {
      if(cursorValue == 0)
      {
        if(millis() - startTime >= 5000 && millis() - startTime <= 5007)
          level++;
        if(millis() - startTime >= 10000 && millis() - startTime <= 10005)
        {
          lcd.clear();
          congrats = 1;
        }
        if(congrats)
        {
          lcd.setCursor(0, 0);
          lcd.print("Congrats");
        }
        else
        {
        lcd.setCursor(0, 0);
        lcd.print("Lives:3");

        lcd.setCursor(0, 1);
        lcd.print("Score:");
        lcd.setCursor(6, 1);
        lcd.print(level * 3);

        lcd.setCursor(8, 0);
        lcd.print("Level:");
        lcd.setCursor(14, 0);
        lcd.print(level);
        }
        score = level * 3;
      }
   else if (cursorValue == 2)
  {

    if(hs == 0)
    {
      if(score > highscore)
      highscore = score;
      lcd.clear();
      hs = 1;
    }
    lcd.setCursor(0, 0);
    lcd.print("HighScore:");
    lcd.setCursor(10, 0);
    lcd.print(highscore);
  }

  else if (cursorValue == 1)
  {
    if(set == 0)
    {
      lcd.clear();
      set = 1;
    }
    xValue = analogRead(pinX);
    if (xValue > maxThreshold && ok == 0)
    {
        startingLevelValue ++;
        ok = 1;
    }
       if (xValue < minThreshold && ok == 0)
    {
        if(startingLevelValue > 0)
        startingLevelValue --;
        ok = 1;
    }
      if (xValue < maxThreshold && xValue > minThreshold)
    {
        ok = 0;
    }

    lcd.setCursor(0, 0);
    lcd.print("Level:");
    lcd.setCursor(0, 1);
    lcd.print(startingLevelValue);
  }
  }
  Serial.println(count);
    
}

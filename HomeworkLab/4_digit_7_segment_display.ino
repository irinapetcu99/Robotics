const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 4;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 9;
const int pinD1 = 7;
const int pinD2 = 2;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

int segments[segSize] = {pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP};

int digits[noOfDisplays] = {pinD1, pinD2, pinD3, pinD4};

byte digitMatrix[noOfDigits][segSize - 1]={ 
                                 {1, 1, 1, 1, 1, 1, 0},
                                 {0, 1, 1, 0, 0, 0, 0},
                                 {1, 1, 0, 1, 1, 0, 1},
                                 {1, 1, 1, 1, 0, 0, 1},
                                 {0, 1, 1, 0, 0, 1, 1},
                                 {1, 0, 1, 1, 0, 1, 1},
                                 {1, 0, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 0, 0, 0, 0},
                                 {1, 1, 1, 1, 1, 1, 1},
                                 {1, 1, 1, 1, 0, 1, 1}};

int values[noOfDisplays] = {0, 0, 0, 0};

const int pinX = A0;
const int pinY = A1;
const int pinSW = A2;

int SWValue = 0;
int XValue = 0;
int YValue = 0;

const int minTreshold = 300;
const int maxTreshold = 700;

bool okx = 0;
bool oky = 0;

int count = 0;

int currentDisplay = noOfDisplays - 1;

void displayNumber(byte digit, bool dpValue)
{
  int i;
  
  for(i = 0; i < segSize - 1; i++)
  digitalWrite(segments[i], digitMatrix[digit][i]);
  
  digitalWrite(segments[segSize - 1], dpValue);

}

void showDigit(int num)
{
  for(int i = 0; i < noOfDisplays; i++)
  digitalWrite(digits[i], HIGH);
  
  digitalWrite(digits[num], LOW);
  
}

void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < segSize - 1; i++)
  pinMode(segments[i], OUTPUT);
  
  for(int i = 0; i < noOfDisplays; i++)
  pinMode(digits[i], OUTPUT);
  
  pinMode(pinSW,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int display = currentDisplay;
  
  YValue = analogRead(pinY);
  SWValue = digitalRead(pinSW);
  
  if(SWValue == LOW)
  {
    delay(200);
    count++;
  }
  
  if(YValue < minTreshold && oky == 0 && count % 2 == 0 )
  {
    if(currentDisplay == noOfDisplays - 1)
    display = 0;
    else 
    display = currentDisplay + 1;
    oky = 1;
  }

    if(YValue > maxTreshold && oky == 0 && count % 2==0 )
  {
    if(currentDisplay == 0)
    display = noOfDisplays - 1;
    else 
    display = currentDisplay - 1;
    oky = 1;
    count = 0;
  }
  
  if(YValue <= maxTreshold && YValue >= minTreshold)
  oky = 0;
  
  currentDisplay = display;
  
  XValue = analogRead(pinX);

  if( XValue < minTreshold && okx == 0 && count % 2 == 1)
  {  
    if(values[display] > 0) values[display]--;
    else  values[display] = 9;
    okx = 1;
  }

  if(XValue > maxTreshold && okx == 0 && count % 2 == 1)
  {
    if(values[display] < 9) values[display]++;
    else values[display] = 0;
    okx = 1;
  }
  if(XValue <= maxTreshold && XValue >= minTreshold)
  okx = 0;

  
   for(int i = 0; i < noOfDisplays; i++) 
   {
    if(i == display)
    {
      showDigit(i);
      displayNumber(values[i], 1);
      delay(1);
    }
    else
    {
      showDigit(i);
      displayNumber(values[i], 0);
      delay(1);
    }
   } 
}

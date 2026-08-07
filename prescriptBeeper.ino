#include <LiquidCrystal.h>


//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd(7,8,12,11,10,9,6,5,4,3);

int buzzerPin = 13;

int buttonPin = 2;

volatile bool switchStatus = false;
volatile bool isScrolling = false;
int lastState = LOW;
//int scrollCount = 38;

int numberOfShifts = 0;
int charactersDisplayed = 0;

unsigned long previousMillis = 0;
unsigned long previousBuzz = 0;

long messageShiftDelay = 200;
const long scrollDelay = 100;
const long symbolChangeDelay = 80;
const long symbolAnimationLength = 2000;
long buzzDelay = random(50,80);


bool showSymbolAnimation = false;
bool showMessageWritingAnimation = false;
unsigned long previousSymbolMillis = 0;

String prescriptList [10] = {
"_In 30 minutes, find a groom or bride. Bonus if brunette_",

"_Sleep for a total of 800 hours per day_",

"_Drink a liter of milk_",

"_Only eat, or write, or brush your teeth with your left hand_",

"_In four hundred thousand meters, turn right_",

"_Do not go home until you finish reading the value of E_",

"_Paint your room picturesque_",

"_Meow several times throughout the day_",

"_Speak to 753 people_",

"_Purchase a new set of silverware_"

};

String message = prescriptList[random(0,9)];
//String message = "!@#$%^&*()-_+=][{}]|;'\\.>,</?`~";
char symbolList [29] = {'~', '`','!','@','#','$','%','^','&','*','(',')','-','_','=','+','[','{','}',']',';','|',':','"', ',','>','<','/','?'};
int scrollCount = message.length();
//volatile bool testPressed = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzerPin, OUTPUT);
  lcd.noCursor();
  lcd.autoscroll();
  lcd.begin(16, 1);
  pinMode(buttonPin,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonISR, FALLING);
  //lcd.print("OFF");
}



void loop() {
  // put your main code here, to run repeatedly:
  // if(testPressed == true){
  //   testPressed = false;
  //   lcd.setCursor(0, 1);
  //   lcd.print("pressed");
  // }
  unsigned long currentMillis = millis();
  lcd.setCursor(0, 0);
  
  if(switchStatus == false){
    //lcd.print("OFF");
    lcd.clear();
    
  }else{
    //lcd.print("ON ");
    //delay(150);
    if(currentMillis - previousBuzz >= buzzDelay){
      //tone(buzzerPin, 1841+random(0,20),30+random(0,20));
      //tone(buzzerPin, 1741+random(0,20),30+random(0,20));
      switch(random(2)){
        case 0:
          tone(buzzerPin, 1841+random(0,20),30+random(0,20));
          break;
        case 1:
          tone(buzzerPin, 1801+random(0,20),30+random(0,20));
          break;
      }
      /*
      switch(random(3)){
        case 0:
          tone(buzzerPin, 841+random(0,20),30+random(0,20));
          break;
        case 1:
          tone(buzzerPin, 1241+random(0,20),30+random(0,20));
          break;
        case 2:
          tone(buzzerPin, 739+random(0,20),30+random(0,20));
          break;
      }
      */
      previousBuzz = currentMillis;
      buzzDelay = random(50,80);
    }
    

    if(currentMillis - previousMillis >= messageShiftDelay){
      previousMillis = currentMillis;
      
      if(numberOfShifts >= scrollCount){
        isScrolling = false;
        switchStatus = false;
        numberOfShifts = 0;
        showSymbolAnimation = false;
        charactersDisplayed = 0;
      }else{  //animation
        if(charactersDisplayed <= 16){
          messageShiftDelay = symbolChangeDelay;
          for(int i = 0; i < 16; i++){
            lcd.setCursor(i,0);
            lcd.print(symbolList[random(0,28)]);
        }
        if(currentMillis-previousSymbolMillis >= symbolAnimationLength){
          for(int i = 0; i < charactersDisplayed; i++){
              lcd.setCursor(i,0);
              lcd.print(message.substring(i,i+1));
            }
            charactersDisplayed = charactersDisplayed+1;
          }
        
        if(charactersDisplayed > 16){
          lcd.clear();
          lcd.print(message);
          messageShiftDelay = scrollDelay;
         
        }
        }else{
          
          lcd.scrollDisplayLeft();
          numberOfShifts = numberOfShifts+1;
        }
        
        
        
        // if(currentMillis - previousSymbolMillis >= symbolAnimationLength){
        //   }else{
        //     showSymbolAnimation = false;
        //     showMessageWriteAnimation = true;
        //     lcd.clear();
        //     lcd.setCursor(0,0);
        //     lcd.print(message);
        //   }
      }
    }
  }

//  if(currentMillis - previousMillis < symbolAnimationLength){
//       previousMillis = currentMillis;
//       if(currentMillis - previousMillis >= messageShiftDelay){
//         previousMillis = currentMillis;
//         lcd.clear();
//       for(int i = 0; i < 16; i++){
//         lcd.setCursor(i,0);
//         lcd.print(symbolList[random(0,28)]);
//       }
//      }
//     }

  // if(!isScrolling){ //ignore logic if message is in the process of being displayed
  //   if(digitalRead(buttonPin) == HIGH && digitalRead(buttonPin) != lastState){
  //   switchStatus = !switchStatus;
  //   lastState = HIGH;
  //   isScrolling = true;
  //   lcd.clear();
    
  //   lcd.print(message);
  //   delay(150);
  //   }else if(digitalRead(buttonPin) == LOW){
  //     lastState = LOW;
  //   }
  // }
  

  //delay(500);
}

void buttonISR(){
  //testPressed = true;
   if(!isScrolling){ //ignore logic if message is in the process of being displayed
    switchStatus = !switchStatus;
    //lastState = HIGH;
    isScrolling = true;
    lcd.clear();
    lcd.print(message);
    showSymbolAnimation = true;
    previousSymbolMillis = millis();
    message = prescriptList[random(0,9)];
    scrollCount = message.length();
  }
}


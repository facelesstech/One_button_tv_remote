#include <IRnew.h>

const int buttonPin = 4;
const int ledPin =  0;

int buttonPushCounter1 = 0;    // counts the button pushes
int buttonState1 = 0;    // tracks the button state
int lastButtonState1 = 0;    // last state of the button

int buttonState = 0;
int lastButtonState = LOW;

long a = 0;
long b = 0;
long c = 0;

IRsend irsend;

// Debounce

long lastDebounceTime = 0;
long debounceDelay = 50;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

int remoteone() {
  a += 1;
  if (c == 1) {
    c -= 1;
  }
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  irsend.sendRC6(0xC05C06, 24);
  delay(500);
  irsend.sendRC6(0xC05C00, 24);
  delay(500);
  irsend.sendRC6(0xC05C04, 24);
  delay(500);
  irsend.sendRC6(0xC00C5C, 24);
  delay(1000);
  irsend.sendRC6(0xC00C83, 24);
}

int remotetwo() {
  b += 1;
  a -= 1;
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  irsend.sendRC6(0xC05C06, 24);
  delay(500);
  irsend.sendRC6(0xC05C00, 24);
  delay(500);
  irsend.sendRC6(0xC05C05, 24);
  delay(500);
  irsend.sendRC6(0xC00C5C, 24);
  delay(1000);
  irsend.sendRC6(0xC00C83, 24);
}

int remotethree() {
  c += 1;
  b -= 1;
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  irsend.sendRC6(0xC05C06, 24);
  delay(500);
  irsend.sendRC6(0xC05C00, 24);
  delay(500);
  irsend.sendRC6(0xC05C06, 24);
  delay(500);
  irsend.sendRC6(0xC00C5C, 24);
  delay(1000);
  irsend.sendRC6(0xC00C83, 24);
}


  
void loop() {
    
  int reading = digitalRead(buttonPin);
  buttonState1 = digitalRead(buttonPin);
  
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  } 
  
  if ((millis() - lastDebounceTime) > debounceDelay) {

    if (reading != buttonState) {
      buttonState = reading;
      
        if (buttonState1 != lastButtonState1) {
          
          if (buttonState1 == HIGH) {
            buttonPushCounter1++;
            
            if (buttonPushCounter1 == 4) {
              buttonPushCounter1 = 1;}
          }
          else {
          }
        }
          lastButtonState1 = buttonState1;
    }
  }
  lastButtonState = reading;
  
  if (buttonPushCounter1 == 1) {
    if (a < 1) {
      remoteone();
    }
    else {
    }
  }
  
  if (buttonPushCounter1 == 2) {
    if (b < 1) {
      remotetwo();
    }
    else {
  }
  }
  if (buttonPushCounter1 == 3) {
    if (c < 1) {
      remotethree();
    }
    else {
  }
}
}

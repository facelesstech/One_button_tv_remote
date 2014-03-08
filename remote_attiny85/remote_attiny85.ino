#include <attiny85_RC6_IR.h>  // The modify IR libray

const int buttonPin = 4; // Button is on arduion pin 4 attiny pin 3
const int ledPin =  0;  // Status LED on arduino pin 0 attiny85 pin 5
                        // IR LED on arduino pin 1 attiny85 pin 6 this is defined in the IR libray

int buttonPushCounter1 = 0;    // counts the button pushes
int buttonState1 = 0;    // tracks the button state
int lastButtonState1 = 0;    // last state of the button

int buttonState = 0;  // Button status
int lastButtonState = LOW;  //Button set to LOW

long a = 0;  // Keep track of how many time the channel code has been run
long b = 0;  // Keep track of how many time the channel code has been run
long c = 0;  // Keep track of how many time the channel code has been run

IRsend irsend;  // Starts the IR code off

long lastDebounceTime = 0;  // Debounce status
long debounceDelay = 50;  // Debounce timer

void setup() {
  pinMode(ledPin, OUTPUT);  // Sets LED as output
  pinMode(buttonPin, INPUT);  // Sets button as input
}

// Pre set channel 604 nickelodeon
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

// Pre set channel 604 nickelodeon
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

// Pre set channel 606 nickelodeon+1
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
  // All the debound button press stuff
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
  
  if (buttonPushCounter1 == 1) {  // Enumerate throught the button presses and only allowys the channel code to be run once
    if (a < 1) {
      remoteone();
    }
    else {
    }
  }
  
  if (buttonPushCounter1 == 2) {  // Enumerate throught the button presses and only allowys the channel code to be run once
    if (b < 1) {
      remotetwo();
    }
    else {
  }
  }
  if (buttonPushCounter1 == 3) {  // Enumerate throught the button presses and only allowys the channel code to be run once
    if (c < 1) {
      remotethree();
    }
    else {
  }
}
}

// Define the pin connected to the LEDs and the button
#define RED_PIN 13
#define BLUE_PIN 12
#define PIEZO_PIN 10
#define BUTTON_PIN 7
#define POTENTIOMETER_PIN A1

// Define the debounce duration for the button in milliseconds
const unsigned long debounceDuration = 30; // Debounce duration for button input

// Variables to track button state and siren state
byte lastButtonState;
byte sirenState = LOW;

// Variable to track the last time the button state changed
unsigned long lastTimeButtonStateChanged;
// Variable to store the blink interval
unsigned long blinkInterval;

void setup() {
  // Set the LED pins as outputs and the button pin as input
  pinMode(RED_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT); 
  pinMode(BUTTON_PIN, INPUT);
  
  // Initialize lastButtonState with the current state of the button
  lastButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  // Check if it's time to debounce the button state
  if (millis() - lastTimeButtonStateChanged >= debounceDuration) {
    // Read the current state of the button
    byte buttonState = digitalRead(BUTTON_PIN);
    
    // Check if the button state has changed
    if (buttonState != lastButtonState) {
      // Update the last time the button state changed
      lastTimeButtonStateChanged = millis();
      // Update lastButtonState with the current button state
      lastButtonState = buttonState;
      
      // Toggle siren state when the button is pressed
      if (buttonState == HIGH) {
        sirenState = !sirenState;
        // If siren state is turned off, turn off both LEDs
        if (sirenState == LOW) {
          digitalWrite(RED_PIN, LOW);
          digitalWrite(BLUE_PIN, LOW);
          noTone(10);
        }
      }
    }
  }
  
  // If siren state is active, alternate blinking both LEDs
  if (sirenState == HIGH) {
    // Read the potentiometer value and update the blink interval
    int potValue = analogRead(POTENTIOMETER_PIN);
    blinkInterval = map(potValue, 0, 1023, 1, 1000);
    
    // Toggle between red and blue LEDs
    digitalWrite(RED_PIN, !digitalRead(BLUE_PIN));
    tone(10, 1300, 200);
    delay(200);
    
    delay(blinkInterval);
    digitalWrite(BLUE_PIN, digitalRead(RED_PIN));
    tone(10, 1800 , 200);
    delay(200);
    noTone(10);
  }
}
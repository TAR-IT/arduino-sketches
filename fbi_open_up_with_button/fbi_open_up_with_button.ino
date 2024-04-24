// Define the pin connected to the LEDs and the button
const int RED_PIN = 12;
const int BLUE_PIN = 13;
const int BUTTON_PIN = 8;


unsigned long blinkInterval = 400; // Define the time interval for blinking in milliseconds
unsigned long debounceDuration = 30; // Define the debounce duration for the button in milliseconds

// Variables to track button state and siren state
byte lastButtonState;
byte sirenState = LOW;

// Variable to track the last time the button state changed
unsigned long lastTimeButtonStateChanged = millis();

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
        }
      }
    }
  }
  
  // If siren state is active, alternate blinking both LEDs
  if (sirenState == HIGH) {
      // Turn off the red LED
      digitalWrite(RED_PIN, LOW);
      // Turn on the blue LED
      digitalWrite(BLUE_PIN, HIGH);
      // Delay for blinkInterval
      delay(blinkInterval);
      
      // Turn off the blue LED
      digitalWrite(BLUE_PIN, LOW);
      // Turn on the red LED
      digitalWrite(RED_PIN, HIGH);
      // Delay for blinkInterval
      delay(blinkInterval);
  }
}

#include <SoftwareSerial.h>

#define RELAY_PIN_1 7  // Relay for the initial functionality
#define RELAY_PIN_2 4  // Relay for lights

void setup() {
  // Set relay pins as output
  pinMode(RELAY_PIN_1, OUTPUT);
  pinMode(RELAY_PIN_2, OUTPUT);

  // Ensure relays are initially OFF
  digitalWrite(RELAY_PIN_1, LOW);
  digitalWrite(RELAY_PIN_2, LOW);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if a command is received via serial
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command == "engage") {
      // Activate the first relay
      digitalWrite(RELAY_PIN_1, HIGH);
      Serial.println("Relay engaged");  // Send feedback
      delay(1700);                      // Keep relay on for 1.7 seconds
      digitalWrite(RELAY_PIN_1, LOW);   // Turn off relay
      Serial.println("Relay disengaged");
    } 
    else if (command == "lights") {
      // Turn on lights relay
      digitalWrite(RELAY_PIN_2, HIGH);
      Serial.println("Lights turned on");
    } 
    else if (command == "lightoff") {
      // Turn off lights relay
      digitalWrite(RELAY_PIN_2, LOW);
      Serial.println("Lights turned off");
    } 
    else {
      Serial.println("Unknown command");
    }
  }
}

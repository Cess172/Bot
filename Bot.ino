#include <SoftwareSerial.h>

#define RELAY_PIN_1 7

void setup() {
  // Set relay pin as output
  pinMode(RELAY_PIN_1, OUTPUT);

  // Ensure relay is initially OFF
  digitalWrite(RELAY_PIN_1, LOW);

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Check if a command is received via serial
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');

    if (command == "engage") {
      // Activate the relay
      digitalWrite(RELAY_PIN_1, HIGH);
      Serial.println("Relay engaged");  // Send feedback
      delay(1700);                      // Keep relay on for 2.5 seconds
      digitalWrite(RELAY_PIN_1, LOW);   // Turn off relay
      Serial.println("Relay disengaged");
    } else {
      Serial.println("Unknown command");
    }
  }
}

#include <Stepper.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
// THANK YOU: https://create.arduino.cc/projecthub/muhammad-aqib/nrf24l01-interfacing-with-arduino-wireless-communication-0c13d4
int timesPressed = 0;
unsigned long previousMillis = 0;
const int BUTTON_PIN = 15;
// Number of steps per internal motor revolution
const float STEPS_PER_REV = 64;
const float GEAR_RED = 64;
// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
const int STEPPER_PIN_1 = 2;
const int STEPPER_PIN_2 = 4;
const int STEPPER_PIN_3 = 5;
const int STEPPER_PIN_4 = 3;

Stepper steppermotor(STEPS_PER_REV, STEPPER_PIN_1, STEPPER_PIN_2, STEPPER_PIN_3, STEPPER_PIN_4);
int STEPPER_SPEED = 300;
int STEPPER_ROTATIONS = 1;

void openThem();
void shutThem();
void enableSteppers();
void disableSteppers();
void radioSetup();
void radioCheck();

void setup() {
  Serial.begin(9600);  // start serial communication at 9600 baud
  radioSetup();

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long timeSince = currentMillis - previousMillis;

  if (timesPressed >= 1 && timeSince > 500) {
    timesPressed = 0;
    openThem();
  }

  if (digitalRead(BUTTON_PIN) == HIGH) {         // check if the input is HIGH (button released)
    Serial.println("Button pressed");
    delay(100);
    timesPressed++;
    Serial.print("Times pressed: ");
    Serial.println(timesPressed);
    if (timeSince <= 500 && timesPressed >= 2) { // quick double-press
      timesPressed = 0;
      shutThem();
    }
    previousMillis = currentMillis;
  }

  radioCheck();
}

void openThem() {
  Serial.println("Opening");
  enableSteppers();
  // Rotate CCW turn quickly
  StepsRequired  =  - STEPS_PER_OUT_REV / 2;
  steppermotor.setSpeed(STEPPER_SPEED);
  steppermotor.step(StepsRequired * STEPPER_ROTATIONS);
  disableSteppers();
}
void shutThem() {
  Serial.println("Shutting");
  enableSteppers();
  // Rotate CW turn quickly
  StepsRequired  =  STEPS_PER_OUT_REV / 2;
  steppermotor.setSpeed(STEPPER_SPEED);
  steppermotor.step(StepsRequired * STEPPER_ROTATIONS);
  disableSteppers();
}

void enableSteppers() {
  digitalWrite (STEPPER_PIN_1, HIGH);
  digitalWrite (STEPPER_PIN_2, HIGH);
  digitalWrite (STEPPER_PIN_3, HIGH);
  digitalWrite (STEPPER_PIN_4, HIGH);
}
void disableSteppers() {
  digitalWrite (STEPPER_PIN_1, LOW);
  digitalWrite (STEPPER_PIN_2, LOW);
  digitalWrite (STEPPER_PIN_3, LOW);
  digitalWrite (STEPPER_PIN_4, LOW);
}

void radioSetup() {
  radio.begin();
  radio.openReadingPipe(0, address);   // Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       // You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              // This sets the module as receiver
  Serial.println("RF set up");
}
void radioCheck() {
  if (radio.available()) {
    char text[11] = "";                 //Saving the incoming data
    radio.read(&text, sizeof(text));    //Reading the data
    if (strcmp(text, "") != 0) {
      Serial.print("Received RF message: ");
      Serial.println(text);
      if (strncmp(text, "blinds_shut", 11) == 0) {
        shutThem();
      } else if (strncmp(text, "blinds_open", 11) == 0) {
        openThem();
      }
    }
  }
  delay(5);
}

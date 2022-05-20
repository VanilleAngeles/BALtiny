// For nano led on 2 & ackno on 3, for Attiny led 0 & ackno 1
const int ledPin    = 0;
const int acknoledgePin = 1;
const int sensorPin = A2;
const int threshold = 500;

bool ledOn    = false;
int lightSens = 0;
int acknoledgePinValue;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin, INPUT);
  pinMode(acknoledgePin, INPUT);
  
/*   Usage of Serial output can't be used on ATtiny.
  Serial.begin(9600);
  Serial.println("Program started"); */

}


void loop() {
  while (ledOn) {
    acknoledgePinValue = digitalRead(acknoledgePin);
    while (acknoledgePinValue == 0) {
      delay(100);
      acknoledgePinValue = digitalRead(acknoledgePin);
    }
    digitalWrite(ledPin,LOW);
    ledOn = false;
  }

  while(!ledOn) {
    lightSens=analogRead(sensorPin);
    while (lightSens < threshold) {
      delay(100);
      lightSens=analogRead(sensorPin);
/*      Serial.println(lightSens); */
    }
    digitalWrite(ledPin,HIGH);
    ledOn = true;
  }
} 

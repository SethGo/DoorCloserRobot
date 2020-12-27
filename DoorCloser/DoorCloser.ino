#define dirPin 2
#define stepPin 3
#define delayLength 280

#define irPin 7
int irVal;
unsigned long time1;
unsigned long time2;

void setup() {
  // For console logging
  Serial.begin(9600);
  
  //set the irPin as INPUT
  pinMode(irPin, INPUT);
  
  // Declare stepper pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  // Initialize all stepper pins off
  digitalWrite(stepPin, LOW);
  digitalWrite(dirPin, LOW);
}

void loop() {  
  // Read the value of IR Sensor (1 = no obstacle, 0 = obstacle)
  boolean irVal = digitalRead(irPin); 
  time1 = millis();
  while (irVal == 0) {
    irVal = digitalRead(irPin); 
    time2 = millis();
    // If there has been an obstacle detected for more than 3 seconds
    if (time2 > time1 + 3000 && irVal == 0) {
      closeDoor(irVal);
    }
  }
}

void closeDoor(int ir) {
  // Set the spinning direction CW
  digitalWrite(dirPin, LOW);
  unsigned int stepCount = 0;
  unsigned int push = 900;
  
  while (ir == 0) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayLength);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayLength);
    stepCount++;
    ir = digitalRead(irPin);
   }
   
   // Push a little more after the sensor reads 'no obstacle'
   for (int s=0; s<=push; s++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayLength);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayLength);
    }
   
  // Set the spinning direction CCW and return arm
  digitalWrite(dirPin, HIGH);
  for (int s=0; s<=stepCount + push; s++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(delayLength/3);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(delayLength/3);
    }
 }

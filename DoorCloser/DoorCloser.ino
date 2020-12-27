unsigned long time1;
unsigned long time2;
const int irPin = 7; //the ir obstacle sensor attach to pin 7
#define waiting_time 10
#define stepper PORTB

void setup()
{
  //set the irPin as INPUT
  pinMode(irPin, INPUT);


//  // Set pins 8,9,10,11 as output for driving the step motor
//  for (int z = 9; z < 13; z++) {  // Full step drive
//    pinMode(z, OUTPUT);
//  }

  // Set pins 8,9,10,11 as output for driving the step motor
  for (int z = 5; z < 9; z++) {  // Full step drive
    pinMode(z, OUTPUT);
  }

  // For console logging
  Serial.begin(9600);
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
      runMotor();
      return;
    }
  }
  runMotor();
}


void runMotor() {
  // Close the door
  for (int steps = 0; steps < 320; steps++) {
    stepper = 0B0011;
    delay(waiting_time);
    stepper = 0B0110;
    delay(waiting_time);
    stepper = 0B1100;
    delay(waiting_time);
    stepper = 0B1001;
    delay(waiting_time);
  }

  // Return the arm
  for (int steps = 0; steps < 320; steps++) {
    stepper = 0B1001;
    delay(waiting_time);
    stepper = 0B1100;
    delay(waiting_time);
    stepper = 0B0110;
    delay(waiting_time);
    stepper = 0B0011;
    delay(waiting_time);
  }
}

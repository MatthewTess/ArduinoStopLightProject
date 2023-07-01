#define echoPin 3 // echo pin location on breadboard
#define trigPin 2 // trigger pin location on breadboard 

int red = 10; // my int variables and pin location for each color
int yellow = 9;
int green = 8;
int button = 12; // switch is on pin 12
long duration;  // amount of time ping is out
long distance;  //what we are to determine based on pin

void setup() {  // setup
  pinMode(red, OUTPUT); //pinMode Output tells the LED lights to blink
  pinMode(yellow, OUTPUT);  //I set my led light inputs
  pinMode(green, OUTPUT);
  pinMode(button, INPUT); // I setup a button Input to detect press
  pinMode(echoPin, INPUT); 
  pinMode(trigPin, OUTPUT);
  digitalWrite(green, HIGH);  // defaults green at all times when no motion or button press
  Serial.begin(9600); // allowing serial monitor display and ping
}
void loop() { //my loop cycle that repeats each time == true
  if (buttonIsPressed() || motionIsDetected()) {  //if either commands is fufilled wait
    changeLights(); //calling change lights function
    delay(10000); // wait for 10 seconds (wait time)
  }
  delay(10);
}

bool motionIsDetected() { //truth statement for motion detection is set
  digitalWrite(trigPin, LOW); // make sure trig pin is LOW
  delayMicroseconds(2); // microscond delay of 2 so above process has time to operate
  digitalWrite(trigPin, HIGH);  // emits our ping
  delayMicroseconds(10);  // microsecond dealy of 10
  digitalWrite(trigPin, LOW); // close trigger pin and stops

  duration = pulseIn(echoPin, HIGH);  // starts listening for ping and goes HIGH when it arrives
  distance = duration / 58.2; // takes time and / by 58.2 to give distance in cm
  Serial.println(distance); // print to Serial Port

  if (distance > 130) { // if ping detects value >115 activate  red lights
    return true;  //indictaes if function should be stopped or repeated
  }
  return false; // if false continue
}

bool buttonIsPressed() {  //truth statement for button press
  if (digitalRead(button) == HIGH) {
    delay(15); // software debounce
    if (digitalRead(button) == HIGH) {
      return true;  // same as truth statement above
    }
  }
  return false; //continue if false
}
void changeLights() { // light changing function
  // green off, yellow on for 3 seconds
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(3000);
  // turn off yellow, then turn red on for 5 seconds
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  delay(5000);

  // turn off red and yellow, then turn on green
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  delay(3000);
}

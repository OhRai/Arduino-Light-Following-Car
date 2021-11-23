/* Light Following Car - Written by Raiyan Samin 2021.11.10
   This code allows the car to follow a light source*/

// declare constants for all the pins and sets variables as either integers, floats, or booleans
const int LMotor_pin1 = 9;
const int LMotor_pin2 = 10;
const int RMotor_pin1 = 11;
const int RMotor_pin2 = 12;

const int photoresistor1Pin = A0;
int photovalue1;
const int photoresistor2Pin = A1;
int photovalue2;

const int button1Pin = 2;
int button1State;
const int button2Pin = 13;
int button2State;

const int buzzerPin = 7;

const int triggerPin = 8;
const int echoPin = 3;

float duration;
float distance;

boolean engine;

void setup()
{
  //set pins as OUTPUTS
  pinMode(LMotor_pin1, OUTPUT);
  pinMode(LMotor_pin2, OUTPUT);
  pinMode(RMotor_pin1, OUTPUT);
  pinMode(RMotor_pin2, OUTPUT);
  pinMode(triggerPin, OUTPUT);

  //sets pins as INPUTS
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  //reads the state of the buttons
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  //reads the value of that the photoresistors receive
  photovalue1 = analogRead(photoresistor1Pin);
  photovalue2 = analogRead(photoresistor2Pin);

  //if the green button is pressed, it lets the engine run
  if (button1State == LOW)
  {
    engine = true;
  }

  //if the red button is pressed, it turns the engine off
  if (button2State == LOW)
  {
    engine = false;
  }

  //if the engine is on
  if (engine == true)
  {
    /************ Start US Measurement Section ***********/
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    /************** End US Measurement Section ***********/

    //if the distance is less than 50cm
    if (distance < 50)
    {
      reverse();
      delay(10);
    }

    //if the distance is greater than 50cm
    else if (distance > 50)
    {
      //if both the photovalues are greater than 250
      if (photovalue1 > 250 && photovalue2 > 250)
      {
        forward();
      }

      //if the right photoresistor value is less than 250
      if (photovalue1 < 250 && photovalue2 > 250)
      {
        left();
        tone(buzzerPin, 200);
      }

      //if the left photoresistor value is less than 250
      if (photovalue1 > 250 && photovalue2 < 250)
      {
        right();
        tone(buzzerPin, 400);
      }
    }
  }

  //if the engine is off
  if (engine == false)
  {
    stopped();
    noTone(buzzerPin);
  }
}

//pin 1 controls forward pin 2 controls backwards
void forward()
{
  //Left motor forward
  digitalWrite(LMotor_pin1, HIGH);
  digitalWrite(LMotor_pin2, LOW);

  //Right motor forward
  digitalWrite(RMotor_pin1, HIGH);
  digitalWrite(RMotor_pin2, LOW);
}

void reverse()
{
  //Left motor reverse
  digitalWrite(LMotor_pin1, LOW);
  digitalWrite(LMotor_pin2, HIGH);

  //Right motor reverse
  digitalWrite(RMotor_pin1, LOW);
  digitalWrite(RMotor_pin2, HIGH);
}

void stopped()
{
  //Left motor does not move
  digitalWrite(LMotor_pin1, LOW);
  digitalWrite(LMotor_pin2, LOW);

  //Right motor does not move
  digitalWrite(RMotor_pin1, LOW);
  digitalWrite(RMotor_pin2, LOW);
}

void left()
{
  //turns right off
  digitalWrite(RMotor_pin1, LOW);
  digitalWrite(RMotor_pin2, LOW);

  //Left motor only moves forward
  digitalWrite(LMotor_pin1, HIGH);
  digitalWrite(LMotor_pin2, LOW);
}

void right()
{
  //turns left off
  digitalWrite(LMotor_pin1, LOW);
  digitalWrite(LMotor_pin2, LOW);

  //Right motor forward
  digitalWrite(RMotor_pin1, HIGH);
  digitalWrite(RMotor_pin2, LOW);
}

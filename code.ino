int ldrLeft = A0;
int ldrCenter = A1;
int ldrRight = A2;

int buttonPin = 2;
int statusLed = 13;

int in1 = 7;
int in2 = 8;
int in3 = 9;
int in4 = 10;

int enA = 6;
int enB = 11;

int lightThreshold = 400;
int stopThreshold = 900;

bool robotOn = false;

int lastButtonState = HIGH;

int tolerance = 50;

int forwardSpeed = 120;
int turnSpeed = 80;

void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(statusLed, OUTPUT);

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);

  if(buttonState == HIGH && lastButtonState == LOW)
  {
    robotOn = !robotOn;
  }

  lastButtonState = buttonState;

  if(robotOn)
  {
    digitalWrite(statusLed, HIGH);

    int leftValue = analogRead(ldrLeft);
    int centerValue = analogRead(ldrCenter);
    int rightValue = analogRead(ldrRight);

    Serial.print("L=");
    Serial.println(leftValue);

    Serial.print(" C=");
    Serial.println(centerValue);

    Serial.print(" R=");
    Serial.println(rightValue);

    if (leftValue > stopThreshold || centerValue > stopThreshold || rightValue > stopThreshold) {
      analogWrite(enA, 0);
      analogWrite(enB, 0);

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }

    if(leftValue < lightThreshold &&
       centerValue < lightThreshold &&
       rightValue < lightThreshold)
    {

      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);

      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
    }
    else if(leftValue > centerValue + tolerance && leftValue > rightValue + tolerance)
    {

      analogWrite(enA, turnSpeed);
      analogWrite(enB, turnSpeed);

      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);

      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }

    else if(rightValue > centerValue + tolerance && rightValue > leftValue + tolerance)
    {

      analogWrite(enA, turnSpeed);
      analogWrite(enB, turnSpeed);

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);

      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
    }

    else
    {

      analogWrite(enA, forwardSpeed);
      analogWrite(enB, forwardSpeed);

      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);

      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
    }
  }

  else
  {
    digitalWrite(statusLed, LOW);

    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    analogWrite(enA, 0);
    analogWrite(enB, 0);
  }
}

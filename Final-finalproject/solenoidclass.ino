class Solenoid
{
    int solenoidPin;
    long OnTime;
    long OffTime;

    int solenoidState;
    unsigned long previousMillis;

  public:

    Solenoid (int pin, long on, long off)
    {
      solenoidPin = pin;
      pinMode(solenoidPin, OUTPUT);

      OnTime = on;
      OffTime = off;

      solenoidState = LOW;
      previousMillis = 0;
    }

    void Update()
    {
      unsigned long currentMillis = millis();
      
      if ((solenoidState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
      solenoidState = LOW;
      previousMillis = currentMillis;
      digitalWrite(solenoidPin, solenoidState);
      }
      else if ((solenoidState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      solenoidState = HIGH;
      previousMillis = currentMillis;
      digitalWrite(solenoidPin, solenoidState);
      }
    }
}
;
Solenoid sole1(10, 200, 200);
Solenoid sole2 (3, 200, 200);
Solenoid sole3 (5, 600, 600);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  sole1.Update();
  sole2.Update();
  sole3.Update();
  int soleState = digitalRead(5);
  Serial.println(soleState);
  delay(1);
}

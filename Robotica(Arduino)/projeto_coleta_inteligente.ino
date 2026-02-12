C++ code
    //
    int distancia = 0;

int ldr = 0;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
    pinMode(triggerPin, OUTPUT); // Clear the trigger
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    // Sets the trigger pin to HIGH state for 10 microseconds
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    pinMode(echoPin, INPUT);
    // Reads the echo pin, and returns the sound wave travel time in microseconds
    return pulseIn(echoPin, HIGH);
}

void setup()
{
    pinMode(A0, INPUT);
    pinMode(10, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(8, OUTPUT);
}

void loop()
{
    ldr = analogRead(A0);
    distancia = 0.01723 * readUltrasonicDistance(11, 13);
    if (ldr <= 460)
    {
        digitalWrite(10, HIGH);
        digitalWrite(2, HIGH);
    }
    else
    {
        digitalWrite(2, LOW);
        digitalWrite(10, LOW);
    }
    if (distancia >= 50)
    {
        digitalWrite(4, HIGH);
        digitalWrite(6, LOW);
        digitalWrite(8, LOW);
    }
    if (distancia < 49 && distancia > 30)
    {
        digitalWrite(4, LOW);
        digitalWrite(6, HIGH);
        digitalWrite(8, LOW);
    }
    if (distancia < 29)
    {
        digitalWrite(4, LOW);
        digitalWrite(6, LOW);
        digitalWrite(8, HIGH);
    }
    delay(10); // Delay a little bit to improve simulation performance
}
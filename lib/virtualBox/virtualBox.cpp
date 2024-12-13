#include <virtualBox.h>

static int CurrentPos = 0;
static int WallPos = 1;
static float WallDist = 60;
static int targetSpace = 1;

static int lastErrorLocal;
static int errorSumLocal;

void doAllshitin1(int boxLoc)
{
    if (boxLoc == 1)
    {
        grabBox();
        encL = 0;
        encR = 0;
        attachInterrupts();
        movetoJunction(white);
        dropBox();
        lastErrorLocal = 0;
        errorSumLocal = 0;
        moveBacktillJunc(); // till junction
        turnRight();
        gotoFour(boxLoc);
        turnLeft();
        movetoJunction(white);
        turnRight();
    }
    else
    {
        turnRight();
        gotoFour(boxLoc);
        while (CurrentPos < targetSpace)
        {
            movetoJunction(white);
            CurrentPos--;
            if (CurrentPos == boxLoc)
                grabBox();
            if (CurrentPos == 1 || CurrentPos == 3)
                checkWall();
        }
        moveBacktillJunc();
    }
}

void grabBox()
{
    digitalWrite(Blue, HIGH);
}

void dropBox()
{
    digitalWrite(Blue, LOW);
}

void checkWall()
{
    float dist = getDistanceFromSensor(1);
    if (dist < WallDist && CurrentPos == 1)
    {
        targetSpace = 3;
        digitalWrite(Red, HIGH);
        delay(100);
        digitalWrite(Red, LOW);
    }
    if (dist < WallDist && CurrentPos == 3)
    {
        targetSpace = 1;
        digitalWrite(Red, HIGH);
        delay(100);
        digitalWrite(Red, LOW);
    }
}

void gotoFour(int boxLoc)
{
    while (CurrentPos < 4)
    {
        movetoJunction(white);
        CurrentPos++;
        if (CurrentPos == boxLoc)
            grabBox();
        if (CurrentPos == 1 || CurrentPos == 3)
            checkWall();
    }
}

static void moveBacktPID()
{
    int errorLocal = getError(white);
    errorSumLocal += errorLocal;
    int error_dif = errorLocal - lastErrorLocal;
    lastErrorLocal = errorLocal;
    int correction = Kp * errorLocal + Ki * errorSumLocal + Kd * error_dif;
    int leftSpeed = -(baseSpeed + correction);
    int rightSpeed = -(baseSpeed - correction);
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    controlMotors(leftSpeed, rightSpeed);
}

static void moveBacktillJunc()
{
    while (true)
    {
        moveBacktPID();
        if (areAllSame(white))
        {
            encL = 0;
            encR = 0;
            moveBackward();
            delay(500);
            stopMotors();
            break;
        }
    }
}
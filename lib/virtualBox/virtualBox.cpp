#include <virtualBox.h>

static int CurrentPos = 0;
static int WallPos = 1;
static float WallDist = 60;
static int targetSpace = 1;
int colorx;
static int lastErrorLocal;
static int errorSumLocal;

static void grabBox()
{
    digitalWrite(Blue, HIGH);
}

static void dropBox()
{
    digitalWrite(Blue, LOW);
}

static void checkWall()
{
    float dist = getDistanceFromSensor(1);
    if (dist < WallDist && CurrentPos == 1)
    {
        targetSpace = 3;
        digitalWrite(Red, HIGH);
        delay(500);
        digitalWrite(Red, LOW);
        colorx = 0;
    }
    if (dist < WallDist && CurrentPos == 3)
    {
        targetSpace = 1;
        digitalWrite(Red, HIGH);
        delay(500);
        digitalWrite(Red, LOW);
        colorx = 0;
    }
}

static void gotoFour(int boxLoc)
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

static void moveBacktillJunc()
{

    attachInterrupts();
    moveBackwardtillEncoders(30);
    encL = 0;
    encR = 0;
    while (true)
    {
        moveBackward();
        if (isHalfSame(white))
        {
            detachInterrupts();
            encL = 0;
            encR = 0;

            stopMotors();

            return;
        }
    }
}

static void placeBox()
{
    moveBacktillJunc();
    turnLeft();
    movetoJunction(white);
    turnRight();
    movetoJunction(white);
    turnRight();
    movetoJunction(white);
    grabBox();
}

void doAllshitin1(int boxLoc)
{
    if (boxLoc == 0)
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
        while (CurrentPos > boxLoc)
        {
            movetoJunction(white);
            CurrentPos--;
        }
        while (CurrentPos < targetSpace)
        {
            moveBacktillJunc();
            CurrentPos--;
        }
        placeBox();
        movetoJunction(white);
    }
    else
    {
        turnRight();
        moveForwardtillEncoders(30);
        gotoFour(boxLoc);
        while (CurrentPos > targetSpace)
        {
            moveBacktillJunc();
            CurrentPos--;
            digitalWrite(Green, HIGH);
            delay(500);
            digitalWrite(Green, LOW);
        }
        dropBox();
        stopMotors();
        digitalWrite(Red, HIGH);
        delay(500);
        placeBox();
        moveBacktillJunc();
        moveBacktillJunc();
        dropBox();
        turnBack(true);
    }
}
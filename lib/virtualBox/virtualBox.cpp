#include <virtualBox.h>

static int CurrentPos = 0;
static int WallPos = 1;
static float WallDist = 60;
static int targetSpace = 1;

static int lastErrorLocal;
static int errorSumLocal;

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
        gotoFour(boxLoc);
        while (CurrentPos > targetSpace)
        {
            moveBacktillJunc();
            CurrentPos--;
        }
        dropBox();
        placeBox();
        moveBacktillJunc();
        moveBacktillJunc();
        dropBox();
        turnBack(true);
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

static void moveBacktillJunc()
{
    encL = 0;
    encR = 0;
    attachInterrupts();
    while (true)
    {
        moveBackward();
        if (areAllSame(white))
        {
            detachInterrupts();
            encL = 0;
            encR = 0;
            moveBackward();
            delay(800);
            stopMotors();

            break;
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
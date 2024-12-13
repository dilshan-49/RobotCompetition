#include <virtualBox.h>

static int CurrentPos = 0;
static int WallPos = 1;
static float WallDist = 60;

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
        moveBackward();
    }
    else
    {
        turnRight();
        gotoFour(boxLoc);
        dropBox();
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
        WallPos = 1;
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
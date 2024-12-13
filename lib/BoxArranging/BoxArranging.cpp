#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <RoboArm.h>

int boxCount = 0;
int junctionCount = 0;
int error;

void boxOrdering(int colorNum)
{
    //***************** initially need to change the thresholds*********************
    // Blue = 1
    // Red = 0

    movetoJunction(black); // Initially go towards the first junction
    armInitializing();
    junctionCount = junctionCount + 1;
    switch (colorNum)
    {
    case 0: // Red decending

        // First box-----------------------------------------------
        gotoFirstBox();
        grabBox();
        redDecending();

        // Second box-----------------------------------------------
        gotoSecondBox();
        grabBox();
        redDecending();

        // third box-------------------------------------------------
        gotoThirdBox();
        grabBox();
        redDecending();
        return;
        break;

        //////////////////////////////////////////////////////////////////////////////

    case 1: // Blue assending

        // First box-----------------------------------------------
        gotoFirstBox();
        grabBox();
        blueAsending();

        // Second box-----------------------------------------------
        gotoSecondBox();
        grabBox();
        blueAsending();

        // third box-------------------------------------------------
        gotoThirdBox();
        grabBox();
        blueAsending();
        return;
        break;

    default:
        Serial.println("Error In color detection");
        break;
    }
    return;
}

void redDecending()
{
    int boxheight = measureHeight();

    //*********** Need to pick Up the Box*****************************
    blinkLED();

    switch (boxheight)
    {
    case 15:
        carryBoxTo(1);
        break;
    case 10:
        carryBoxTo(2);
        break;
    case 5:
        carryBoxTo(3);
        break;
    default:
        break;
    }
}

void blueAsending()
{
    int boxheight = measureHeight();
    //*********** Need to pick Up the Box*****************************
    blinkLED();

    switch (boxheight)
    {
    case 5:
        carryBoxTo(1);
        break;
    case 10:
        carryBoxTo(2);
        break;
    case 15:
        carryBoxTo(3);
        break;
    default:
        break;
    }
}

void gotoFirstBox()
{
    if (junctionCount == 1)
    {

        turnLeft();
        lineFollowTillWhite();
    }
}

void gotoSecondBox()
{
    if (junctionCount == 1)
    {
        turnRight();
        movetoJunction(black);
        junctionCount++;
        turnLeft();
        lineFollowTillWhite();
    }
    if (junctionCount == 2)
    {
        lineFollowTillWhite();
    }
    if (junctionCount == 3)
    {
        turnLeft();
        movetoJunction(black);
        junctionCount--;
        turnRight();
        lineFollowTillWhite();
    }
}
void gotoThirdBox()
{
    if (junctionCount == 1)
    {
        turnRight();
        movetoJunction(black);
        junctionCount++;

        moveForward();
        delay(1000);

        movetoJunction(black);
        junctionCount++;
        turnLeft();
        lineFollowTillWhite();
    }
    if (junctionCount == 2)
    {
        turnRight();
        movetoJunction(black);
        junctionCount++;
        turnLeft();
        lineFollowTillWhite();
    }
    if (junctionCount == 3)
    {
        lineFollowTillWhite();
    }
}
void carryBoxTo(int junctiontoTurn)
{
    turnBack(true);
    movetoJunction(black);
    if (junctionCount < junctiontoTurn)
    {
        turnLeft();
        movetoJunction(black);
        junctionCount++;
        nextMoveUp(junctiontoTurn); //
    }
    else if (junctionCount > junctiontoTurn)
    {
        turnRight();
        movetoJunction(black);
        junctionCount--;
        nextMoveDown(junctiontoTurn); //
    }
    else if (junctionCount == junctiontoTurn)
    {
        // move untill white meets
        nextMoveTillWhite();
    }
}
void nextMoveUp(int junctiontoTurn)
{
    if (junctionCount < junctiontoTurn)
    {

        moveForward();
        delay(1000);

        movetoJunction(black);
        junctionCount++;
    }
    turnRight();
    // move untill white meets
    nextMoveTillWhite();
}
void nextMoveDown(int junctiontoTurn)
{
    if (junctionCount > junctiontoTurn)
    {

        moveForward();
        delay(1000);

        movetoJunction(black);
        junctionCount--;
    }
    turnLeft();
    // move untill white meets
    nextMoveTillWhite();
}

int measureHeight()
{
    //----------------
    int height = 5;
    return height;
}

void blinkLED()
{
    digitalWrite(31, HIGH);
    delay(1000);
    digitalWrite(31, LOW);
    delay(1000);
}
void lineFollowTillWhite()
{
    while (true)
    {
        PIDfollow(black);
        if (areAllSame(white))
        {
            stopMotors();
            delay(1000);
            return;
        }
    }
}

void nextMoveTillWhite()
{
    while (true)
    {
        PIDfollow(black);
        if (areAllSame(white))
        {
            stopMotors();
            delay(1000);
            // place the box
            blinkLED();
            armInitializing();
            moveBackward();
            delay(800);
            turnBack(true);
            moveBackward();
            delay(800);
            movetoJunction(black);
            stopMotors();
            return;
        }
    }
}

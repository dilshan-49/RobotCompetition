#include <MazeSolving.h>
#include <LineSensor.h>
#include <motorControl.h>

#include <pinDefinitions.h>

int junction_count_Up = 0;
int junction_count_Down = 0;
int wall_Position = 0;

void mazeSolve(int VBoxPosition)
{
    // Starts after taking the first right turn
    movetoJunction();
    if (VBoxPosition == 0)
    {
        boxAtZero();
    }
    else
    {
        noBoxAtZero(VBoxPosition);
    }
}

void movetoJunction()
{
    while (true)
    {
        PIDfollow();
        if (areAllSame(white) or isHalfSame(white))
        {
            stopMotors();
            delay(1000);
            return;
        }
    }
}
void movetoJunctionBackward()
{
    moveBackward();
    delay(500);
    stopMotors();
    while (true)
    {
        PIDfollowBackward();
        if (areAllSame(white) or isHalfSame(white))
        {
            stopMotors();
            delay(1000);
            return;
        }
    }
}
void boxAtZero()
{
    digitalWrite(Green, HIGH);
    moveForward();
    delay(500);
    stopMotors();

    movetoJunction();

    digitalWrite(Green, LOW);
    delay(500);

    movetoJunctionBackward();
    stopMotors();
    delay(500);
    turnRight();
    delay(500);
    moveBackward();
    delay(200);
    stopMotors();

    // while(true){}
    while (junction_count_Up < 4)
    {
        movetoJunction();
        moveForward();
        delay(500);
        stopMotors();
        junction_count_Up++;
        if (junction_count_Up == 1 || junction_count_Up == 3)
        {
            if (CheckWall())
            {
                wall_Position = junction_count_Up;
            }
        }
    }
    turnLeft();
    movetoJunction();
    stopMotors();
    junction_count_Down = junction_count_Up;
    delay(500);
    turnLeft();

    stopMotors();

    while (junction_count_Down > 0)
    {
        movetoJunction();
        moveForward();
        delay(500);
        stopMotors();
        junction_count_Down--;
    }
    turnBack(false);
    delay(200);
    movetoJunctionBackward();
    moveBackward();
    delay(200);
    movetoJunctionBackward();
    delay(500);
    digitalWrite(Green, HIGH);
    while (true)
    {
    }

    turnBack(true);
    moveBackward();
    delay(500);

    while (junction_count_Down < wall_Position)
    {
        movetoJunction();
        junction_count_Down++;
    }
    digitalWrite(Green, LOW);
    bringTheBoxToSqure(2);
}
void noBoxAtZero(int n)
{
    if (n == 4)
    {
        turnRight();
        while (junction_count_Up < 4)
        {
            movetoJunction();
        }
        turnBack(true);
        digitalWrite(Green, HIGH);
        movetoJunction();
        digitalWrite(Green, LOW);
        junction_count_Up--;
        while (junction_count_Up > 0)
        {
            movetoJunction();
            junction_count_Up--;
        }
        turnRight();
        n = 3;
    }
    movetoJunction();
    turnRight();
    while (junction_count_Down < 4)
    {
        movetoJunction();
        junction_count_Down++;
        if (junction_count_Down == 1 || junction_count_Down == 3)
        {
            if (CheckWall())
            {
                wall_Position = junction_count_Down;
            }
        }
    }
    turnRight();
    movetoJunction();
    turnRight();
    junction_count_Up = junction_count_Down;
    while (junction_count_Up > n)
    {
        movetoJunction();
        junction_count_Up--;
    }
    digitalWrite(Green, HIGH);
    if (junction_count_Up > wall_Position)
    {
        while (junction_count_Up > wall_Position)
        {
            movetoJunction();
            junction_count_Up--;
        }
        digitalWrite(Green, LOW);
        turnBack(true);
        bringTheBoxToSqure(1);
    }
    if (junction_count_Up < wall_Position)
    {
    }
    if (junction_count_Up == wall_Position)
    {
    }
}
bool CheckWall()
{
    // ultrasonic sensor codei
    if (junction_count_Down == 3 or junction_count_Up == 3)
    {
        return true;
    }
    return false;
}
void bringTheBoxToSqure(int rowInMaze)
{
    if (rowInMaze == 2)
    {
        for (int i = 0; i < 3; i++)
        {
            movetoJunction();
            turnRight();
        }
        movetoJunction();
        digitalWrite(Green, HIGH);
        stopAtSqure();
    }
    if (rowInMaze == 1)
    {
        for (int i = 0; i < 3; i++)
        {
            movetoJunction();
            turnLeft();
        }
        movetoJunction();
        turnBack(true);
        digitalWrite(Green, HIGH);
        stopAtSqure();
    }
}
void stopAtSqure()
{
    // write  the code to stop the robo when it get into the squre
}

void PIDfollow()
{
    int error = getError();
    error_sum += error;
    error_dif = error - lastError;
    int correction = Kp * error + Ki * error_sum + Kd * error_dif;
    int leftSpeed = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    controlMotors(leftSpeed, rightSpeed);
}
void PIDfollowBackward()
{
    int error = getError();
    error_sum += error;
    error_dif = error - lastError;
    int correction = Kp * error + Ki * error_sum + Kd * error_dif;
    int leftSpeed = -(baseSpeed + correction);
    int rightSpeed = -(baseSpeed - correction);
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    controlMotors(leftSpeed, rightSpeed);
}

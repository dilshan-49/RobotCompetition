#include <MazeSolving.h>
#include <LineSensor.h>
#include <motorControl.h>

#define Indicate_LED 26
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

void movetoJunction(){
    //This function is to move the robo forward until it meets a junction
    // either T or F type junction
    //condition in the while loop should be edited
    while(true){
        moveForward(baseSpeed);
    }
    stopMotors();
}
void boxAtZero(){
    digitalWrite(Indicate_LED,HIGH);
    movetoJunction();
    digitalWrite(Indicate_LED,LOW);
    turnBack(baseSpeed);
    movetoJunction();
    turnLeft(85,60);
    while(junction_count_Up<4){
        movetoJunction();
        junction_count_Up++;
        if(junction_count_Up==1 || junction_count_Up==3){
            if(CheckWall()){
                wall_Position = junction_count_Up;
            }
        }
    }
    turnLeft(85,60);
    movetoJunction;
    junction_count_Down = junction_count_Up;
    turnLeft(85,60);
    while(junction_count_Down>0){
        movetoJunction();
        junction_count_Down--;
    }
    turnBack(baseSpeed);
    digitalWrite(Indicate_LED, HIGH);
    while(junction_count_Down<wall_Position){
        movetoJunction();
        junction_count_Down++;
    }
    digitalWrite(Indicate_LED,LOW);
    bringTheBoxToSqure(2);
}
void noBoxAtZero(int n){
    if(n==4){
        turnRight(85, 60);
        while(junction_count_Up<4){
            movetoJunction();
        }
        turnBack(baseSpeed);
        digitalWrite(Indicate_LED, HIGH);
        movetoJunction();
        digitalWrite(Indicate_LED, LOW);
        junction_count_Up-- ;
        while(junction_count_Up>0){
            movetoJunction();
            junction_count_Up--;
        }
        turnRight(85,60);
        n = 3;
    }
    movetoJunction();
    turnRight(85,60);
    while (junction_count_Down < 4)
    {
        movetoJunction();
        junction_count_Down++;
        if(junction_count_Down==1 || junction_count_Down==3){
            if(CheckWall()){
                wall_Position = junction_count_Down;
            }
        }
    }
    turnRight(85,60);
    movetoJunction();
    turnRight(85,60);
    junction_count_Up = junction_count_Down;
    while(junction_count_Up>n){
        movetoJunction();
        junction_count_Up--;
    }
    digitalWrite(Indicate_LED,HIGH);
    if(junction_count_Up>wall_Position){
        while(junction_count_Up>wall_Position){
            movetoJunction();
            junction_count_Up--;
        }
        digitalWrite(Indicate_LED,LOW);
        turnBack(baseSpeed);
        bringTheBoxToSqure(1);
    }
    if(junction_count_Up<wall_Position){

        }
    if(junction_count_Up==wall_Position){

    }

}
bool CheckWall(){
    // ultrasonic sensor code

}
void bringTheBoxToSqure(int rowInMaze){
    if(rowInMaze==2){
        for (int i = 0; i < 3 ; i++)
        {
            movetoJunction();
            turnRight(85,60);
        }
        movetoJunction();
        digitalWrite(Indicate_LED, HIGH);
        stopAtSqure();
    }
    if(rowInMaze==1){
        for (int i = 0; i < 3 ; i++)
        {
            movetoJunction();
            turnLeft(85,60);
        }
        movetoJunction();
        turnBack(baseSpeed);
        digitalWrite(Indicate_LED, HIGH);
        stopAtSqure();
    }
}
void stopAtSqure(){
    //write  the code to stop the robo when it get into the squre
    }
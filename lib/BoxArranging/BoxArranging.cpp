#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>

#define led 35

int boxCount = 0;
int junctionCount = 0;
int error;

void boxOrdering(int colorNum)
{
    //***************** initially need to change the thresholds*********************
    //Blue = 1
    //Red = 0
    
    movetoJunction(); //Initially go towards the first junction
    junctionCount = junctionCount + 1;
    switch (colorNum)
    {
    case 0://Red decending

        //First box-----------------------------------------------
        gotoFirstBox();
        redDecending();

        //Second box-----------------------------------------------
        gotoSecondBox();
        redDecending();

        //third box-------------------------------------------------
        gotoThirdBox();
        redDecending();
        break;

//////////////////////////////////////////////////////////////////////////////

    case 1://Blue assending

        //First box-----------------------------------------------
        gotoFirstBox();
        blueAsending();

        //Second box-----------------------------------------------
        gotoSecondBox();
        blueAsending();

        //third box-------------------------------------------------
        gotoThirdBox();
        blueAsending();
        break;

    default:
        Serial.println("Error In color detection");
        break;
    }
}

void redDecending(){
    int boxheight = measureHeight();
    //*********** Need to pick Up the Box*****************************
    digitalWrite(31,HIGH);
    delay(1000);
    digitalWrite(31,LOW);
    delay(1000);
    boxheight = 10;

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

void blueAsending(){
    int boxheight = measureHeight();
    //*********** Need to pick Up the Box*****************************
    boxheight = 10;
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

void gotoFirstBox(){
    if (junctionCount == 1){
        
        turnLeft(70);
        while(true){
            error_sum += error;
            error_dif = error - lastError;
            int correction = Kp * error + Ki * error_sum + Kd * error_dif;
            int leftSpeed = baseSpeed + correction;
            int rightSpeed = baseSpeed - correction;
            leftSpeed = constrain(leftSpeed, -255, 255);
            rightSpeed = constrain(rightSpeed, -255, 255);
            controlMotors(leftSpeed,rightSpeed);
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }

        // moveForward(baseSpeed);
        // delay(2000);
        }
}

void gotoSecondBox(){
    if (junctionCount == 1){
        turnRight(100
        );
        movetoJunction();
        junctionCount++;
        turnLeft(100
        );
        moveForward(baseSpeed);
        delay(1000); // have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 2){
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 3){
        turnLeft(100
        );
        movetoJunction();
        junctionCount--;
        turnRight(100
        );
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
}
void gotoThirdBox(){
    if (junctionCount == 1){
        turnRight(100
        );
        movetoJunction();
        junctionCount++;
        movetoJunction();
        junctionCount++;
        turnLeft(100
        );
        moveForward(baseSpeed);
        delay(1000); // have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 2){
        turnRight(100
        );
        movetoJunction();
        junctionCount++;
        turnLeft(100
        );
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
    if (junctionCount == 3){
        moveForward(baseSpeed);
        delay(1000);// have to decide the delay according to the distance
        stopMotors();
    }
}
void carryBoxTo(int junctiontoTurn){
    turnBack(80);
    movetoJunction();
    if (junctionCount < junctiontoTurn)
    {
        turnLeft(70);
        movetoJunction();
        junctionCount++;
        nextMoveUp(junctiontoTurn);//
    }
    else if (junctionCount > junctiontoTurn)
    {
        turnRight(100
        );
        movetoJunction();
        junctionCount--;
        nextMoveDown(junctiontoTurn);//
    }
    else if (junctionCount == junctiontoTurn)
    {
        moveForward(baseSpeed);//till the place where to place the box
        //********** Move forward and place the boxes *************
        turnBack(baseSpeed);
        movetoJunction();
        brake();
        }
}
void nextMoveUp(int junctiontoTurn){
    if(junctionCount < junctiontoTurn){
        movetoJunction();
        junctionCount++;
    }
    turnRight(70);
    digitalWrite(31,HIGH);
    delay(5000);
    //********** Move forward and place the boxes *************
    turnBack(baseSpeed);
    movetoJunction();
    brake();

}
void nextMoveDown(int junctiontoTurn){
    if(junctionCount > junctiontoTurn){
        movetoJunction();
        junctionCount--;
    }
    turnLeft(100
    );
    //********** Move forward and place the boxes *************
    turnBack(baseSpeed);
    movetoJunction();
    brake();
    

}
void movetoJunction(){
    //This function is to move the robo forward until it meets a junction
    // black==1
    // white=0
    while(true){
        int error=getError();
        
        error_sum += error;
        error_dif = error - lastError;
        int correction = Kp * error + Ki * error_sum + Kd * error_dif;
        int leftSpeed = baseSpeed + correction;
        int rightSpeed = baseSpeed - correction;
        leftSpeed = constrain(leftSpeed, -255, 255);
        rightSpeed = constrain(rightSpeed, -255, 255);
        Serial.println("222222222222222222222222222222");
        if (areAllSame(black))
        {
            stopMotors();
            delay(1000);
            return;
        }
        

        controlMotors(leftSpeed,rightSpeed);
    


}
}
int measureHeight(){
    //----------------
    int height = 10;
    return height;
}


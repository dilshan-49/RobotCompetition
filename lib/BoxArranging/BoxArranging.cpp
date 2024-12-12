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
        return;
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
        return;
        break;

    default:
        Serial.println("Error In color detection");
        break;
    }
    return;
}

void redDecending(){
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

void blueAsending(){
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

void gotoFirstBox(){
    if (junctionCount == 1){
        
        turnLeft(turnSpeed);
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }

        }
}

void gotoSecondBox(){
    if (junctionCount == 1){
        turnRight(turnSpeed);
        movetoJunction();
        junctionCount++;
        turnLeft(turnSpeed);
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
    if (junctionCount == 2){
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
    if (junctionCount == 3){
        turnLeft(turnSpeed);
        movetoJunction();
        junctionCount--;
        turnRight(turnSpeed);
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
}
void gotoThirdBox(){
    if (junctionCount == 1){
        turnRight(turnSpeed);
        movetoJunction();
        junctionCount++;
        moveForward(turnSpeed);
        delay(1000);
        movetoJunction();
        junctionCount++;
        turnLeft(turnSpeed);
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
    if (junctionCount == 2){
        turnRight(turnSpeed);
        movetoJunction();
        junctionCount++;
        turnLeft(turnSpeed);
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
    if (junctionCount == 3){
        while(true){
            PIDfollow();
            if(areAllSame(white)){
                stopMotors();
                delay(1000);
                return;
            }
            
        }
    }
}
void carryBoxTo(int junctiontoTurn){
    turnBack(turnSpeed);
    movetoJunction();
    if (junctionCount < junctiontoTurn)
    {
        turnLeft(turnSpeed);
        movetoJunction();
        junctionCount++;
        nextMoveUp(junctiontoTurn);//
    }
    else if (junctionCount > junctiontoTurn)
    {
        turnRight(turnSpeed);
        movetoJunction();
        junctionCount--;
        nextMoveDown(junctiontoTurn);//
    }
    else if (junctionCount == junctiontoTurn)
    {
    //move untill white meets
    while(true){
         PIDfollow();
        if(areAllSame(white)){
            stopMotors();
            delay(1000);
            // place the box
            blinkLED();

            turnBack(turnSpeed);
            movetoJunction();
            stopMotors();
            return;
        }
            
    }


        }
}
void nextMoveUp(int junctiontoTurn){
    if(junctionCount < junctiontoTurn){
        moveForward(turnSpeed);
        delay(1000);
        movetoJunction();
        junctionCount++;
    }
    turnRight(turnSpeed);
    // move untill white meets
    while(true){
         PIDfollow();
        if(areAllSame(white)){
            stopMotors();
            //place the box
            blinkLED();

            turnBack(turnSpeed);
            movetoJunction();
            stopMotors();
            return;
        }
            
    }

}
void nextMoveDown(int junctiontoTurn){
    if(junctionCount > junctiontoTurn){
        moveForward(turnSpeed);
        delay(1000);
        movetoJunction();
        junctionCount--;
    }
    turnLeft(turnSpeed);
//move untill white meets
    while(true){
         PIDfollow();
        if(areAllSame(white)){
            stopMotors();
            delay(1000);
            //place the box
            blinkLED();

            turnBack(turnSpeed);
            movetoJunction();
            stopMotors();
            return;
        }
            
    }


}
void movetoJunction(){
    //This function is to move the robo forward until it meets a junction
    // black==1
    // white=0

    while(true){
        PIDfollow();
        if (areAllSame(black))
        {
            stopMotors();
            delay(1000);
            return;
        }
        

        
    


}
}
int measureHeight(){
    //----------------
    int height = 10;
    return height;
}


void PIDfollow(){
        int error=getError();
        error_sum += error;
        error_dif = error - lastError;
        int correction = Kp * error + Ki * error_sum + Kd * error_dif;
        int leftSpeed = baseSpeed + correction;
        int rightSpeed = baseSpeed - correction;
        leftSpeed = constrain(leftSpeed, -255, 255);
        rightSpeed = constrain(rightSpeed, -255, 255);
        controlMotors(leftSpeed,rightSpeed);
}

void blinkLED(){
        digitalWrite(31,HIGH);
        delay(1000);
        digitalWrite(31,LOW);
        delay(1000);
}






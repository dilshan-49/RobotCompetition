#include <miniFunc.h>

void displayTask(int CaseNum)
{
    switch (CaseNum)
    {
    case 1:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, LOW);
        break;

    case 2:
        digitalWrite(Red, LOW);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, LOW);
        break;

    case 3:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, LOW);
        break;

    case 4:
        digitalWrite(Red, LOW);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, HIGH);
        break;

    case 5:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, HIGH);
        break;

    case 6:
        digitalWrite(Red, LOW);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, HIGH);
        break;

    case 7:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, HIGH);
        break;
    default:
        break;
    }
    delay(1500);
    digitalWrite(Red, LOW);
    digitalWrite(Blue, LOW);
    digitalWrite(Green, LOW);
}
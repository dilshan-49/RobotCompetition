#include <Decoder.h>

static void encoderPID();

static int error;
static int lastError;
static int errorSum;
static int errorDiff;
int array[15];

int getNum(int size)
{
    if (size < 4)
        return -1;
    int binArr[size];
    int maxVal, minVal = array[0];
    int sum = 0;
    for (int i = 1; i < size; i++)
    {
        if (array[i] > maxVal)
            maxVal = array[i];
        if (array[i] < minVal)
            minVal = array[i];
        Serial.println(array[i]);
    }
    Serial.print("Max - ");
    Serial.print(maxVal);
    Serial.print(" & Min - ");
    Serial.println(minVal);
    int threshold = (maxVal + minVal) / 2;

    for (int i = 0; i < size; i++)
    {
        binArr[i] = array[i] > threshold ? 1 : 0;
        Serial.print(binArr[i]);
        Serial.print(" - ");
    }
    if (!(binArr[size - 3] == binArr[size - 1]) || !(binArr[size - 1] == binArr[size - 2])) // check if 3 zeros at end
        return -1;
    int x;
    for (int i = 0; i < size - 3; i++)
    {
        x = binArr[i] * (1 << (size - 4 - i));
        Serial.println(x);
        sum += x;
    }
    Serial.println(sum);
    return sum % 5;
}

int ReadingWithPID()
{
    int x;
    int n = 0;
    bool whiteStrip = false;
    volatile int counter = 0;
    encL = 0;
    encR = 0;
    attachInterrupts();
    error = 0;
    lastError = 0;
    errorSum = 0;
    errorDiff = 0;
    while (true)
    {
        encoderPID();
        while (areAllSame(white)) // keep counting till the EOL
        {
            counter++;
            whiteStrip = true;
            Serial.print(counter);
            Serial.println(" - White Strip");
            x = 0;
            delay(5);
            readSensorVals(true);
            encoderPID();
            digitalWrite(Red, LOW);
            digitalWrite(Green, HIGH);
        }
        encoderPID();
        if (whiteStrip) // at the end of white strip
        {
            if (areAllSame(black)) // check if black strip
            {
                digitalWrite(Red, HIGH);
                digitalWrite(Green, LOW);
                whiteStrip = false;
                array[n] = counter;
                Serial.println(counter);
                n++;
                x = 0;
                counter = 0;
            }
            else
            {
                x++;
                encoderPID();
                if (x > 15)
                {
                    digitalWrite(Blue, HIGH);
                    stopMotors();
                    array[n] = counter; // at the end of encoded strips
                    Serial.println(array[n]);
                    for (int i = 0; i <= n; i++)
                    {
                        Serial.println(array[i]);
                    }

                    return n + 1;
                }
                delay(5);
            }
        }
    }
}

static void encoderPID()
{
    error = encL - encR;
    errorSum += error;
    errorDiff = error - lastError;
    lastError = error;
    int correction = 0.5 * error + 0.00 * errorSum + 0.02 * errorDiff;
    controlMotors(baseSpeed - correction, baseSpeed + correction);
    //    Serial.print(error);
    //    Serial.print(" - ");
    //    Serial.println(correction);
}
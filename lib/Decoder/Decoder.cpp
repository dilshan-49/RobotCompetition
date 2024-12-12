//#include <Decoder.h>

int array[15];

int startReading()
{
    int x;
    int n = 0;
    bool whiteStrip = false;
    int counter = 0;
    while (true)
    {
        readSensorVals();

        while (areAllWhite(readings, 8)) // keep counting till the EOL
        {
            counter++;
            whiteStrip = true;
            Serial.print(counter);
            Serial.println(" - White Strip");
            x = 0;
            delay(50);
            readSensorVals();
        }

        if (whiteStrip) // at the end of white strip
        {
            if (areAllBlack(readings, 8))
            {
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
                if (x > 8)
                {
                    array[n] = counter; // at the end of encoded strips
                    Serial.println(array[n]);
                    return n + 1;
                }
            }
        }
        delay(50);
        Serial.print(".");
    }
}

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
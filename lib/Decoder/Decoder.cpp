#include <Decoder.h>

int array[15];

int startReading()
{
    int n = 0;
    bool whiteStrip = false;
    while (true)
    {
        readSensorVals();
        int counter = 0;
        while (areAllWhite(readings, 8)) // keep counting till the EOL
        {
            counter++;
            bool whiteStrip = true;
            delay(50);
        }

        if (whiteStrip) // at the end of white strip
        {
            if (!(areAllBlack(readings, 8) || areAllWhite(readings, 8)))
            {
                array[n] = counter; // at the end of encoded strips
                return n;
            }
            whiteStrip = false;
            array[n] = counter;
            n++;
        }
        delay(50);
    }
}

int getNum(int size)
{
    int binArr[size + 1];
    int maxVal, minVal;
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i] > maxVal)
            maxVal = array[i];
        if (array[i] < minVal)
            minVal = array[i];
    }
    for (int i = 0; i < size; i++)
    {
        binArr[i] = array[i] > (maxVal + minVal) / 2 ? 1 : 0;
    }
    if (!(binArr[size] == binArr[size - 1]) || !(binArr[size - 1] == binArr[size - 2])) // check if 3 zeros at end
        return -1;

    for (int i = 0; i < size - 3; i++)
    {
    }
}
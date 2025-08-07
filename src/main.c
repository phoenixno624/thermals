#include "thermals.h"

#include <stdio.h>

int main(void)
{
    struct SENSOR sensors[SENSOR_MAX];
    unsigned short count = get_sensors(sensors);
    int i;

    for (i = 0; i < count; i++)
    {
        printf("Sensor Name: %s\n", sensors[i].name);
        printf("Sensor Temperature: %3.2f F\n", sensors[i].temperature);
    }

    return 0;
}
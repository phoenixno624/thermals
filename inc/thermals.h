#ifndef THERMALS_H
#define THERMALS_H

#include "types.h"
#include "lists.h"

#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define SENSOR_MAX 20

struct SENSOR
{
    char label[50];
    char input[50];
    float temperature;
    float critical_temperature;
    float emergency_temperature;
};

const BYTE get_sensors(struct NODE *);

#endif
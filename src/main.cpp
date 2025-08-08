#include <iostream>

#include "thermals.hpp"

using namespace std;
using namespace thermals::services;

int main(void)
{
    SensorsService sensorsService{};
    vector<Sensor> sensors = sensorsService.getSensors();

    for (const auto &sensor : sensors)
    {
        cout << "Sensor: " << sensor.label
             << "-------------\n"
             << "Temperature (C): " << sensor.temperature << '\n'
             << "Critical (C): " << sensor.critical << '\n'
             << "Emergency (C): " << sensor.emergency << '\n'
             << "Min (C): " << sensor.min << '\n'
             << "Max (C): " << sensor.max << '\n'
             << "Alarm (C): " << sensor.alarm << "\n\n"
    }
}
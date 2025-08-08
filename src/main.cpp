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
             << "-------------\n";
        cout << "Temperature (C): " << sensor.temperature << "\n";
        cout << "Critical (C): " << sensor.critical << "\n";
        cout << "Emergency (C): " << sensor.emergency << "\n";
        cout << "Min (C): " << sensor.min << "\n";
        cout << "Max (C): " << sensor.max << "\n";
        cout << "Alarm (C): " << sensor.alarm << "\n\n";
    }
}
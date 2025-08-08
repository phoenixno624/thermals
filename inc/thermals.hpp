#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <ranges>
#include <unordered_map>
#include <regex>

using namespace std;
using namespace filesystem;

namespace thermals::services
{
    struct Sensor
    {
        u_char number;
        string label;
        float temperature;
        float critical;
        float crit_hyst;
        float emergency;
        float min;
        float max;
        float alarm;
    };

    class SensorsService
    {
    private:
        const vector<path> getTempSensorFiles(
            const string &);
        const vector<Sensor> mapTempSensorFilesToSensors(const vector<path> &);

    public:
        SensorsService();
        const vector<Sensor> getSensors();
    };
}
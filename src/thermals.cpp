#include "thermals.hpp"

using namespace std;
using namespace filesystem;

namespace thermals::services
{
    static const string readFile(const string &filePath)
    {
        ifstream file(filePath);
        string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());

        return contents;
    }

    SensorsService::SensorsService() {}

    const vector<path> SensorsService::getTempSensorFiles(const string &root)
    {
        vector<path> paths;
        for (const auto &path : recursive_directory_iterator(root, directory_options::skip_permission_denied))
        {
            if (path.is_regular_file())
            {
                string filename = path.path().filename().string();
                if (filename.starts_with("temp"))
                {
                    paths.push_back(path);
                }
            }
        }
        return paths;
    }
    const vector<Sensor> SensorsService::mapTempSensorFilesToSensors(const vector<path> &filePaths)
    {
        unordered_map<string, unordered_map<u_char, vector<path>>> monitorsMap;
        regex deviceNumberRegex(R"(temp(\d+)_.*)");
        for (const auto &filePath : filePaths)
        {
            path parentPath = filePath.parent_path();

            auto filename = filePath.filename().string();
            smatch match;
            if (regex_match(filename, match, deviceNumberRegex))
            {
                int deviceNum = stoi(match[1]);
                monitorsMap[parentPath][deviceNum].push_back(filePath);
            }
        }

        vector<Sensor> sensors;
        for (const auto &[monitorName, sensorsMap] : monitorsMap)
        {
            for (const auto &[sensorNum, filePaths] : sensorsMap)
            {
                Sensor sensor{number : sensorNum};

                for (const auto &filePath : filePaths)
                {
                    string filename = filePath.filename().string();
                    string value = readFile(filePath);
                    if (filename.ends_with("label"))
                    {
                        sensor.label = value;
                    }
                    else if (filename.ends_with("input"))
                    {
                        sensor.temperature = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("crit"))
                    {
                        sensor.critical = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("emergency"))
                    {
                        sensor.emergency = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("crit_hyst"))
                    {
                        sensor.crit_hyst = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("min"))
                    {
                        sensor.min = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("max"))
                    {
                        sensor.max = stoi(value) / 1000.0f;
                    }
                    else if (filename.ends_with("alarm"))
                    {
                        sensor.alarm = stoi(value) / 1000.0f;
                    }
                }

                sensors.push_back(sensor);
            }
        }
        sort(sensors.begin(), sensors.end(), [](const Sensor sensor1, const Sensor sensor2)
             { return sensor1.label <= sensor2.label; });

        return sensors;
    }

    const vector<Sensor> SensorsService::getSensors()
    {
        const vector<path> tempSensorPaths = getTempSensorFiles("/sys/devices");
        // for (const auto &filePath : tempSensorPaths)
        // {
        //     cout << filePath << '\n';
        // }
        const vector<Sensor> sensors = mapTempSensorFilesToSensors(tempSensorPaths);

        return sensors;
    }
}
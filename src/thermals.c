#include "thermals.h"

static const BOOL is_directory(struct dirent *entry)
{
    if (strncmp(".", entry->d_name, 1) == 0 || strncmp("..", entry->d_name, 2) == 0)
    {
        return FALSE;
    }
    if (entry->d_type == 10)
    {
        return TRUE;
    }

    return FALSE;
}

static const BYTE get_temp_sensor_directories(const char *path, struct NODE **directories)
{
    BYTE count = 0;
    DIR *dir = opendir(path);
    if (!dir)
    {
        perror("opendir");
        return 0;
    }

    struct dirent *entry;
    struct NODE *head = *directories;
    while ((entry = readdir(dir)) != NULL)
    {
        if (is_directory(entry))
        {
            char hwmon_path[255];
            snprintf(hwmon_path, 255, "%s/%s", path, entry->d_name);

            DIR *hwmon_dir = opendir(hwmon_path);
            struct dirent *hwmon_entry;
            while ((hwmon_entry = readdir(hwmon_dir)) != NULL)
            {
                if (starts_with("temp", hwmon_entry->d_name))
                {
                    char temp_path[255];
                    snprintf(temp_path, 255, "%s/%s", hwmon_path, hwmon_entry->d_name);

                    head = (struct NODE *)malloc(sizeof(struct NODE));
                    head->data = strdup(temp_path);
                    head->next = NULL;
                    head = head->next;

                    count++;
                }
            }
            closedir(hwmon_dir);
        }
    }

    closedir(dir);

    struct NODE *current = directories;
    while (current != NULL)
    {
        printf(current->data);
        current = current->next;
    }

    return count;
}

const BYTE get_sensors(struct NODE *sensors)
{
    struct NODE *directories;

    return get_temp_sensor_directories("/sys/class/hwmon", &directories);
}
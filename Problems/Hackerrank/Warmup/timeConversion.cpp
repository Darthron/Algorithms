#include <iostream>

int main()
{
    std::string time;
    std::string res;
    int         hour;

    std::cin >> time;

    if ("12" == time.substr(0, 2))
    {
        if ('A' == time[8])
        {
            res = "00" + time.substr(2, 6);
        }
        else
        {
            res = time.substr(0, 8);
        }
    }
    else if ('A' == time[8])
    {
        res = time.substr(0, 8);
    }
    else
    {
        hour = std::stoi(time.substr(0, 2));

        hour += 12;

        res = std::to_string(hour) + time.substr(2, 6);
    }

    std::cout << res;
}

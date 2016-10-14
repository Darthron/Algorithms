/*
ID: razvan_10
PROG: friday
LANG: C++11
*/

#include <fstream>

std::ifstream mama("friday.in");
std::ofstream tata("friday.out");

int main()
{
    int  months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int  currYear;
    int  days[] = {0, 0, 0, 0, 0, 0, 0};
    int  currWeekDay;
    int  currMonth;
    bool leapYear;
    int  n;

    mama >> n;

    currYear = 1900;
    currWeekDay = 0;
    currMonth = 0;

    for (int index = 0; index < n; ++index)
    {
        if (0 == currYear % 100)
        {
            if (0 == currYear % 400)
            {
                ++months[1];
                leapYear = true;
            }
            else
            {
                leapYear = false;
            }
        }
        else if (0 == currYear % 4)
        {
            ++months[1];
            leapYear = true;
        }
        else
        {
            leapYear = false;
        }

        while (currMonth < 12)
        {
            ++days[(currWeekDay + 12) % 7];
            currWeekDay += months[currMonth];
            currWeekDay %= 7;

            ++currMonth;
        }

        ++currYear;
        currMonth = 0;
        if (leapYear)
        {
            --months[1];
        }
    }

    tata << days[5] << ' ' << days[6] << ' ';
    for (currWeekDay = 0; currWeekDay < 4; ++currWeekDay)
    {
        tata << days[currWeekDay] << ' ';
    }

    tata << days[4] << std::endl;
    return 0;
}

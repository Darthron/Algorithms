#include <iostream>

char
getNext(int (&letters)[26],
        char ch)
{
    int index;

    index = ch - 'a' + 1;

    while ( (index < 26) and
            (0 == letters[index]) )
    {
        ++index;
    }

    if (index == 26)
    {
        return 0;
    }

    --letters[index];

    return 'a' + index;
}

void
empty(int (&l)[26])
{
    for (int index = 0; index < 26; ++index)
    {
        l[index] = 0;
    }
}

int main()
{
    int         n;
    int         index;
    int         strIndex;
    int         letters[26];
    std::string res;
    std::string str;

    std::cin >> n;

    empty(letters);

    for (index = 0; index < n; ++index)
    {
        std::cin >> str;

        for (strIndex = 0; strIndex < str.size(); ++strIndex)
        {
            ++letters[str[strIndex] - 'a'];
        }

        strIndex = str.size() - 1;
        while ( (strIndex > 0) and
                (str[strIndex] <= str[strIndex - 1]) )
        {
            --strIndex;
        }

        if (0 == strIndex)
        {
            std::cout << "no answer" << std::endl;
            empty(letters);
            continue;
        }
        else
        {
            --strIndex;
        }

        for (int tempIndex = 0; tempIndex < strIndex; ++tempIndex)
        {
            --letters[str[tempIndex] - 'a'];
        }

        res = str;

        res[strIndex] = getNext(letters, str[strIndex]);

        ++strIndex;
        for (int tempIndex = 0; tempIndex < 26; ++tempIndex)
        {
            while (letters[tempIndex] > 0)
            {
                res[strIndex] = tempIndex + 'a';
                --letters[tempIndex];
                ++strIndex;
            }
        }

        std::cout << res << std::endl;
    }

    return 0;
}

#include "framework10.hpp"

namespace disappearing_0
{
    digit10 borrow(const digit10 divide, const digit10 by, digit10 buffer[])
    {
        auto ptr = buffer;
        digit10 count = 0;
        for (digit10 i = 0; i < 9; i++)
            if (divide.value % by.value == 0) {
                *ptr = i;
                ptr++;
                count++;
            }
        return count;
    }
}

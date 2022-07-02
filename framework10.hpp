#ifndef _D0_FRAMEWORK10_HPP
#define _D0_FRAMEWORK10_HPP

#include "framework.hpp"

namespace disappearing_0
{
    typedef int_fast8_t fast_decimal_t;
    class digit10: public digit<fast_decimal_t>
    {
    public:
        inline digit10();
        inline digit10(const fast_decimal_t);
        inline operator fast_decimal_t();

        inline digit10 & plus(const digit10);
        inline digit10 & minus(const digit10);
        inline digit10 & multiply(const digit10);
        inline digit10 & divide(const digit10, const digit10 borrow);

        inline const digit10 operator++(int);
        inline digit10 & operator++();
        inline const digit10 operator--(int);
        inline digit10 & operator--();

        inline bool disappeared() const;
        friend digit10 borrow(const digit10 divide, const digit10 by, digit10 buffer[]);
    };

    template<typename hand_t, typename player_t>
    class setting10
    {
    public:
        hand_t hands;
        fast_decimal_t start;
        player_t players;

        setting10(const hand_t hands, const player_t players);
    };

    template<typename hand_t, typename player_t>
    class status10
    {
    protected:
        fast_decimal_t * digits;

    public:
        const setting10<hand_t, player_t> & s;
        status10(const setting10<hand_t, player_t> &);
        inline ~status10();
    };


    inline digit10::digit10() { }
    inline digit10::digit10(const fast_decimal_t _val)
    { value = _val; }
    inline digit10::operator fast_decimal_t()
    { return value; }

    inline digit10 & digit10::plus(const digit10 other)
    {
        value += other.value;
        if (value >= 10)
            value -= 10;
        return *this;
    }
    inline digit10 & digit10::minus(const digit10 other)
    {
        value -= other.value;
        if (value < 0)
            value += 10;
        return *this;
    }
    inline digit10 & digit10::multiply(const digit10 other)
    {
        value *= other.value;
        value %= 10;
        return *this;
    }
    inline digit10 & digit10::divide(const digit10 other, const digit10 borrow)
    {
        value += borrow.value * 10;
        value /= other.value;
        return *this;
    }

    inline const digit10 digit10::operator++(int)
    {
        const auto temp = *this;
        value++;
        return temp;
    }
    inline digit10 & digit10::operator++()
    {
        value++;
        return *this;
    }
    inline const digit10 digit10::operator--(int)
    {
        const digit10 temp = *this;
        value--;
        return temp;
    }
    inline digit10 & digit10::operator--()
    {
        value--;
        return *this;
    }

    inline bool digit10::disappeared() const
    { return value == 0; }


    #define __STATUS10_TEMPLATE template<typename hand_t, typename player_t>

    __STATUS10_TEMPLATE
    status10<hand_t, player_t>::status10(const setting10<hand_t, player_t> & _s)
    {
        s = _s;
        digits = new fast_decimal_t[s.hands * s.players];
    }

    __STATUS10_TEMPLATE
    inline status10<hand_t, player_t>::~status10()
    { delete [] digits; }


    __STATUS10_TEMPLATE
    setting10<hand_t, player_t>::setting10(const hand_t _hands, const player_t _players)
    {
        hands = _hands;
        players = _players;
    }

    #undef __STATUS10_TEMPLATE
}


#endif

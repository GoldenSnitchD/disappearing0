#ifndef _D0_FRAMEWORK_HPP
#define _D0_FRAMEWORK_HPP

#include <cstdint>


namespace disappearing_0
{
    template<typename sdigit_t>
    class digit
    {
    protected:
        sdigit_t value;

    public:
        inline digit();
        inline digit(const sdigit_t);
        inline operator sdigit_t();

        inline digit & plus(const digit other, const digit radix);
        inline digit & minus(const digit other, const digit radix);
        inline digit & multiply(const digit other, const digit radix);
        inline digit & divide(const digit other, const digit borrow, const digit radix);

        inline const digit operator++(int);
        inline digit & operator++();
        inline const digit operator--(int);
        inline digit & operator--();

        inline bool disappeared() const;
        friend digit borrow(const digit divide, const digit by, digit buffer[], const digit<sdigit_t> radix);
    };


    template<typename sdigit_t, typename hand_t, typename player_t>
    class setting
    {
    public:
        sdigit_t radix;
        sdigit_t start;
        hand_t hands;
        player_t players;

        setting(const sdigit_t, const sdigit_t, const hand_t, const player_t);
    };


    template<typename sdigit_t, typename hand_t, typename player_t>
    class status
    {
    protected:
        sdigit_t * digits;

    public:
        const setting<sdigit_t, hand_t, player_t> & s;
        status(const setting<sdigit_t, hand_t, player_t> &);
        inline ~status();
    };


    #define __SDIGIT_TEMPLATE template<typename sdigit_t>

    __SDIGIT_TEMPLATE inline digit<sdigit_t>::digit() { }
    __SDIGIT_TEMPLATE inline digit<sdigit_t>::digit(const sdigit_t _val)
    { value = _val; }
    __SDIGIT_TEMPLATE inline digit<sdigit_t>::operator sdigit_t()
    { return value; }

    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::plus(const digit<sdigit_t> other, const digit<sdigit_t> radix)
    {
        value += other.value;
        if (value >= radix)
            value -= radix;
        return *this;
    }
    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::minus(const digit<sdigit_t> other, const digit<sdigit_t> radix)
    {
        value -= other.value;
        if (value < 0)
            value += radix;
        return *this;
    }
    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::multiply(const digit<sdigit_t> other, const digit<sdigit_t> radix)
    {
        value *= other.value;
        value %= radix;
        return *this;
    }
    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::divide(const digit<sdigit_t> other, const digit<sdigit_t> borrow, const digit<sdigit_t> radix)
    {
        value += borrow.value * radix;
        value /= other.value;
        return *this;
    }

    __SDIGIT_TEMPLATE inline const digit<sdigit_t> digit<sdigit_t>::operator++(int)
    {
        const auto temp = *this;
        value++;
        return temp;
    }
    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::operator++()
    {
        value++;
        return *this;
    }
    __SDIGIT_TEMPLATE inline const digit<sdigit_t> digit<sdigit_t>::operator--(int)
    {
        const auto temp = *this;
        value--;
        return temp;
    }
    __SDIGIT_TEMPLATE inline digit<sdigit_t> & digit<sdigit_t>::operator--()
    {
        value--;
        return *this;
    }

    __SDIGIT_TEMPLATE inline bool digit<sdigit_t>::disappeared() const
    { return value == 0; }
    __SDIGIT_TEMPLATE digit<sdigit_t> borrow(const digit<sdigit_t> divide, const digit<sdigit_t> by, digit<sdigit_t> buffer[], const digit<sdigit_t> radix)
    {
        auto ptr = buffer;
        digit<sdigit_t> count = 0;
        for (digit<sdigit_t> i = 0; i < radix - 1; i++)
            if (divide.value % by.value == 0) {
                *ptr = i;
                ptr++;
                count++;
            }
        return count;
    }

    #undef __SDIGIT_TEMPLATE


    #define __STATUS_TEMPLATE template<typename sdigit_t, typename hand_t, typename player_t>

    __STATUS_TEMPLATE
    status<sdigit_t, hand_t, player_t>::status(const setting<sdigit_t, hand_t, player_t> & _s)
    {
        s = _s;
        digits = new sdigit_t[s.hands * s.players];
    }

    __STATUS_TEMPLATE
    inline status<sdigit_t, hand_t, player_t>::~status()
    { delete [] digits; }


    __STATUS_TEMPLATE
    setting<sdigit_t, hand_t, player_t>::setting(const sdigit_t _radix, const sdigit_t _start, const hand_t _hands, const player_t _players)
    {
        radix = _radix;
        start = _start;
        hands = _hands;
        players = _players;
    }

    #undef __STATUS_TEMPLATE
}


#endif

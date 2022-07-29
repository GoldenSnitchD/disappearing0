#ifndef _D0_FRAMEWORK_HPP
#define _D0_FRAMEWORK_HPP

#include <concepts>
#include <ranges>
#include <memory>


namespace disappearing_0
{
    using std::signed_integral, std::unsigned_integral, std::unique_ptr;


    // Operations of single digits

    template<typename R>
    concept parameters = std::ranges::range<R> && std::signed_integral<std::ranges::range_value_t<R>>;

    template<signed_integral digit>
    using simple_operation = digit & (*)(digit &, const digit, const digit radix);
    template<signed_integral digit, signed_integral parameter_t>
    using parametric_operation = digit & (*)(digit &, const digit, const parameter_t, const digit radix);
    template<signed_integral digit, parameters parameters_t>
    using possible_parameters = parameters_t (*)(const digit, const digit);

    template<signed_integral digit, parameters parameters_t>
    class detailed_parametric_operation
    {
        using parameter_t = std::ranges::range_value_t<parameters_t>;

    public:
        parametric_operation<digit, parameter_t> operation;
        possible_parameters<digit, parameter_t> parameters;

        inline detailed_parametric_operation(
            const parametric_operation<digit, parameter_t> _operation,
            const possible_parameters<digit, parameter_t> _parameters
        ): operation(_operation), parameters(_parameters) { }
    };


    // Situation of the game

    template<signed_integral digit, unsigned_integral player_t>
    struct situation
    {
        unique_ptr<digit[]> digits;
        player_t current_player;
    };


    // Information about single players' specific turns

    template<unsigned_integral player_t, unsigned_integral hand_t>
    struct turn
    {
        hand_t outstretched_hand;
        player_t touched_player;
        hand_t touched_hand;
    };


    template<signed_integral digit, parameters parameters_t, unsigned_integral player_t, unsigned_integral hand_t>
    class setting
    {
    private:
        using parameter_t = std::ranges::range_value_t<parameters_t>;

    public:
        digit radix;
        hand_t hands;
        player_t players;
        unique_ptr<simple_operation<digit>[]> simple_operations;
        unique_ptr<detailed_parametric_operation<digit, parameter_t>[]> parametric_operations;

        inline setting(
            const digit _radix,
            const hand_t _hands,
            const player_t _players
        ): radix(_radix), hands(_hands), players(_players)
        { }  // TODO: init operations
    };


    template<signed_integral digit, parameters parameters_t, unsigned_integral player_t, unsigned_integral hand_t>
    struct game
    {
        const setting<digit, parameters_t, hand_t, player_t> game_setting;
        situation<digit, player_t> current;
        game(const setting<digit, parameters_t, hand_t, player_t> _setting): game_setting(_setting) { }
    };
}  // namespace disappearing_0


#endif

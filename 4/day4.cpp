#include <array>
#include <iostream>

/**
 * Only compile time stuff!!
 */

using Password = std::array<int, 6>;

// std::is_sorted is not constexpr until c++20
constexpr bool is_ascending(Password const& pw)
{
    for (auto it = pw.begin(); it != pw.end(); ++it)
    {
        if (   (it != pw.begin())
            && (*it < *(it - 1)) )
        {
            return false;
        }
    }
    return true;
}

constexpr bool non_3_group_double_sequence(Password const& pw)
{
    auto it = pw.begin();
    while(it != pw.end())
    {
        auto const val = *it;

        int sequence = 1;
        while(it++ != pw.end() - 1) // walk to last element
        {
            if (*it == val) ++sequence;
            else break; 
        }
        
        if (sequence == 2) return true;
    }

    return false;
}


constexpr bool sequence_contains_double_entry(Password const& pw)
{
    for (auto it = pw.begin(); it != pw.end(); ++it)
    {
        if (   (it != pw.begin())
            && (*it == *(it - 1)) )
        {
            return true;
        }
    }

    return false;
}

constexpr Password password_from_int(int to_convert)
{
    Password out {};

    int pos = 0;
    while (true)
    {
        int digit = to_convert % 10;
        *(out.end() - pos - 1) = digit;
        to_convert = to_convert/10;

        if (to_convert == 0)
        {
            return out;
        }

        ++pos;
    }

    return out;
}

static_assert(non_3_group_double_sequence(password_from_int(244445)) == false);
static_assert(non_3_group_double_sequence(password_from_int(244455)) == true);
static_assert(non_3_group_double_sequence(password_from_int(224445)) == true);

template <typename Predicate>
constexpr int unique_combinations(int begin,
                                  int end,
                                  Predicate pred)
{
    // why not
    if (begin > end) throw 0;

    int combination_counter = 0;

    for (int i = begin; i < end; ++i)
    {
        auto const pw = password_from_int(i);
        // using array because it is convenient to work with
        if (pred(pw))
        {
            ++combination_counter;
        }
    }

    return combination_counter;
}

int main()
{
    auto const part1_predicate = [](auto const& pw)
    {
        return sequence_contains_double_entry(pw) && is_ascending(pw);
    };

    auto const part2_predicate = [](auto const& pw)
    {
        return is_ascending(pw) && non_3_group_double_sequence(pw);
    };

    std::cout << "Part 1 solution: " << 
                  unique_combinations(138241, 674034, part1_predicate) << "\n";

    std::cout << "Part 2 solution: " << 
                  unique_combinations(138241, 674034, part2_predicate) << "\n";
}

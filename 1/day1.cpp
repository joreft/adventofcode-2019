#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * Note: This solution will overflow on large inputs!!!!
 */

std::vector<int64_t> parse_input_file(std::string const& file_name)
{
    std::ifstream input("input");
    std::string line;
    std::vector<int64_t> inputs;
    for (std::string line; std::getline(input, line);)
    {
        inputs.emplace_back(std::stoull(line));
    }
    return inputs;
}

constexpr int64_t calculate_needed_fuel_part1(int64_t mass)
{
    return mass/3 - 2;
}

static_assert(calculate_needed_fuel_part1(12) == 2);
static_assert(calculate_needed_fuel_part1(14) == 2);
static_assert(calculate_needed_fuel_part1(1969) == 654);
static_assert(calculate_needed_fuel_part1(100756) == 33583);

void print_part1_result()
{
    int64_t fuel_needed = 0;
    for (auto module_mass : parse_input_file("input"))
    {
        fuel_needed += calculate_needed_fuel_part1(module_mass);
    }

    std::cout << "Part 1, Fuel needed: " << fuel_needed << "\n";
}


constexpr int64_t calculate_needed_fuel_part2(int64_t mass)
{
    int64_t actual_needed_fuel = 0;

    int64_t to_be_calculated = mass;

    while (true)
    {
        auto instance_fuel_needed = calculate_needed_fuel_part1(to_be_calculated);
        if (instance_fuel_needed <= 0) break;

        actual_needed_fuel += instance_fuel_needed;
        to_be_calculated = instance_fuel_needed;
    } 

    return actual_needed_fuel;
}

void print_part2_result()
{
    int64_t fuel_needed = 0;
    for (auto module_mass : parse_input_file("input"))
    {
        fuel_needed += calculate_needed_fuel_part2(module_mass);
    }

    std::cout << "Part 2, Fuel needed: " << fuel_needed << "\n";
}

static_assert(calculate_needed_fuel_part2(14) == 2);
static_assert(calculate_needed_fuel_part2(1969) == 966);
static_assert(calculate_needed_fuel_part2(100756) == 50346);

int main()
{
    print_part1_result();
    print_part2_result();
}

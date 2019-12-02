#include <array>
#include <iostream>

/**
 * The solution doesn't care about error handling or overflows!
 */
constexpr const std::array gravity_assist_program = {
    #include "input"
};

template <size_t program_size>
constexpr std::array<int, program_size> 
            calculateProgram(std::array<int, program_size> program)
{
    for (int i = 0; i < program_size; i+=4)
    {
        int const opcode = program[i];
        int const input_pos1 = program[i + 1];
        int const input_pos2 = program[i + 2];
        int const storage_pos = program[i + 3];

        if (opcode == 1)
        {
            program[storage_pos] = program[input_pos1] + program[input_pos2];
        }
        else if (opcode == 2)
        {
            program[storage_pos] = program[input_pos1] * program[input_pos2];
        }
        else if (opcode == 99)
        {
            break;
        }
        else
        {
            throw 0;
        }
    }

    return program;
}

void part1_result()
{
    auto temp_program = gravity_assist_program;
    temp_program[1] = 12;
    temp_program[2] = 2;
    std::cout << "At position 0 of the program is '" <<
        calculateProgram(temp_program)[0] << "'\n";
}

template <size_t program_size>
constexpr std::pair<int, int>
    brute_force_specific_result(int expected_result, std::array<int, program_size> const& program)
{
    for (int i = 0; i < 100; ++i)
    {
        for (int u = 0; u < 100; ++u)
        {
            auto temp_program = program;
            temp_program[1] = i;
            temp_program[2] = u;
            if (calculateProgram(temp_program)[0] == expected_result)
            {
                return {i, u};
            }
        }
    }

    throw 0;
}

void part2_result()
{
    auto const result = brute_force_specific_result(19690720, gravity_assist_program);
    std::cout << "Verb: " << result.first << ", Noun: " << result.second << "\n";
}

int main()
{
    part1_result();
    part2_result();
}

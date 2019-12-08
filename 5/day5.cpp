#include <array>
#include <iostream>

/**
 * The solution doesn't care about error handling or overflows!
 */
constexpr const std::array gravity_assist_program = {
    #include "input"
};

template <size_t program_size>
std::array<int, program_size> 
            calculateProgram(std::array<int, program_size> program, int program_input)
{
    for (int pc = 0; pc < program_size;)
    {
        int i = pc;
        int const opcode = program[i] % 100;

        if (opcode == 1)
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;
            int const param3_mode = (program[i]/10000)%10;

            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];

            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];

            int const input3 = param3_mode == 0 ?
                                        program[i + 3]
                                      : program[i + 3];


            program[input3] = input2 + input1;
            pc += 4;
        }
        else if (opcode == 2)
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;
            int const param3_mode = (program[i]/10000)%10;

            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];

            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];

            int const storage_pos = param3_mode == 0 ?
                                        program[i + 3]
                                      : program[i + 3];


            program[storage_pos] = input1 * input2;
            pc += 4;
        }
        else if (opcode == 3)
        {
            int storage_pos = program[i + 1];
            program[storage_pos] = program_input;
            pc += 2;
        }
        else if (opcode == 4)
        {
            int pos = program[i + 1];
            std::cout << "Output: " << program[pos] << "\n";
            pc += 2;
        }

        else if (opcode == 5) // jump if true
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;
            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];
            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];

            if (input1)
            {
                pc = input2;
            }
            else
            {
                pc += 3;
            }
        }

        else if (opcode == 6) // jump if false
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;

            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];
            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];

            if (!input1)
            {
                pc = input2;
            }
            else
            {
                pc += 3;
            }
        }

        else if (opcode == 7) // less than
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;

            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];
            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];
            int const input3 = program[i + 3];

            if (input1 < input2)
            {
                program[input3] = 1;
            }
            else
            {
                program[input3] = 0;
            }
            pc += 4;
        }

        else if (opcode == 8) //equal
        {
            int const param1_mode = (program[i]/100)%10;
            int const param2_mode = (program[i]/1000)%10;

            int const input1 = param1_mode == 0 ?
                                        program[program[i + 1]]
                                      : program[i + 1];
            int const input2 = param2_mode == 0 ?
                                        program[program[i + 2]]
                                      : program[i + 2];
            int const input3 = program[i + 3];

            if (input1 == input2)
            {
                program[input3] = 1;
            }
            else
            {
                program[input3] = 0;
            }
            pc += 4;
        }

        else if (opcode == 99)
        {
            break;
        }

        else
        {
            std::cout << "invalid opcode " << program[i] << " at pc=" << pc << "\n";
            throw 0;
        }
    }

    return program;
}

void part1_result()
{
    auto temp_program = gravity_assist_program;
    std::cout << "Calculating part 1 program\n";
    calculateProgram(temp_program, 1);
}

void part2_result()
{
    auto temp_program = gravity_assist_program;
    std::cout << "Calculating part 2 program\n";
    calculateProgram(temp_program, 5);
}

int main()
{
    part1_result();
    part2_result();
}

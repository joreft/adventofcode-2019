#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>

struct Instruction
{
    char direction {};
    int length {};
};

template <typename StreamType>
std::vector<Instruction> parse_line(StreamType&& s)
{
    std::vector<Instruction> out{};
    for (std::string entry; std::getline(s, entry, ',');)
    {
        if (entry.size() < 2)
        {
            throw 0;
        }

        out.emplace_back(
                Instruction{entry[0], std::stoi(entry.substr(1, entry.size() - 1))});
    }
    return out;
}

std::pair<std::vector<Instruction>, 
          std::vector<Instruction> >
    parse_input_file(std::string const& file_name)
{
    std::ifstream input(file_name);

    std::string line1;
    std::getline(input, line1);
    auto const first = parse_line(std::stringstream(line1));

    std::string line2;
    std::getline(input, line2);
    auto const second = parse_line(std::stringstream(line2));

    return {first, second};
}

struct Point {
    int x{}; int y{};
    int steps_travelled {};

};
bool operator==(Point const& lhs, Point const& rhs)
{
    return (rhs.x == lhs.x) && (rhs.y == lhs.y);
}

std::vector<Point> all_visited_points(std::vector<Instruction> const& instructions)
{
    std::vector<Point> out;

    Point current_pos {};

    auto const add_point_in_dir = [&](char dir)
    {
        if (dir == 'R')
        {
            current_pos.x += 1;
        }
        else if (dir == 'L')
        {
            current_pos.x -= 1;
        }
        else if (dir == 'U')
        {
            current_pos.y += 1;
        }
        else if (dir == 'D')
        {
            current_pos.y -= 1;
        }
        current_pos.steps_travelled += 1;
    };

    for (auto const& instruction : instructions)
    {
        for (int i = 0; i < instruction.length; ++i)
        {
            add_point_in_dir(instruction.direction);
            out.push_back(current_pos);
        }
    }

    return out;
}

std::vector<Point> find_all_intersections(std::vector<Instruction> const& first,
                                          std::vector<Instruction> const& second)
{
    std::vector<Point> out;

    auto const all_points_first = all_visited_points(first);
    auto const all_points_second = all_visited_points(second);
    
    auto const found_in_second = [&all_points_second](Point const& to_search)
    {
        return   std::find(all_points_second.begin(), all_points_second.end(), to_search) 
              != all_points_second.end();
    };

    std::copy_if(all_points_first.begin(), all_points_first.end(), std::back_inserter(out), found_in_second);

    return out;
}

int longest_from_origo(std::vector<Point> points)
{
    int best_candidate = 99999999;
    for (auto const& point : points)
    {
        auto const candidate = std::abs(point.x) + std::abs(point.y); 
        if (candidate < best_candidate)
        {
            best_candidate = candidate;
        }
    }

    return best_candidate;
}

int length_best_intersection(std::vector<Instruction> const& first,
                             std::vector<Instruction> const& second)
{
    auto const all_points_first = all_visited_points(first);
    auto const all_points_second = all_visited_points(second);
    
    int best_candidate = std::numeric_limits<int>::max();

    for (int i = 0; i < all_points_first.size(); ++i)
    {
        for (int u = 0; u < all_points_second.size(); ++u)
        {
            if (all_points_first[i] == all_points_second[u])
            {
                auto const candidate = i+u+2;
                if (candidate < best_candidate)
                {
                    best_candidate = candidate;
                }
            }
        }

    }
    return best_candidate;
}

void part1_solution()
{
    auto const input = parse_input_file("input");
    auto const intersections = find_all_intersections(input.first, input.second);

    std::cout << "Part 1 solution is: " << longest_from_origo(intersections) << "\n";
}

void part2_solution()
{
    auto const input = parse_input_file("input");
    auto const len = length_best_intersection(input.first, input.second);

    std::cout << "Part 2 solution is: " << len << "\n";
}

int main()
{
    part1_solution();
    part2_solution();
}

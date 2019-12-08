#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <map>
#include <sstream>

struct OrbitProperties
{
    std::set<std::string> orbits;
    std::set<std::string> is_orbited_by;
};

using OrbitList = std::map<std::string, OrbitProperties>;


OrbitList parse_input_file(std::string const& file_name)
{
    std::ifstream input(file_name);

    OrbitList out;
    for (std::string line ; std::getline(input, line);)
    {
        std::stringstream orbitee_s(line);
        std::string orbitee;
        std::getline(orbitee_s, orbitee, ')');

        std::string orbiter = line.substr(orbitee.size() + 1);
        out[orbitee].orbits.insert(orbiter);
        out[orbiter].is_orbited_by.insert(orbitee);
    }
    return out;
}

int total_orbits_for_orbitee(std::string const& orbitee, OrbitList& list)
{
    int counter = 0;

    auto const& is_orbited_by = list[orbitee].is_orbited_by; 

    for (auto const& orbiter : is_orbited_by)
    {
        counter += total_orbits_for_orbitee(orbiter, list);
        counter +=1;
    }
    return counter;
}

int total_orbits(OrbitList& list)
{
    int counter = 0;
    for (auto const& p : list)
    {
        counter += total_orbits_for_orbitee(p.first, list);
    }
    return counter;
}

static int search_counter = 0;

std::vector<std::string> setunion(std::set<std::string> const& s1, std::set<std::string> const& s2)
{
    auto out = std::vector<std::string>{};

    std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), std::back_inserter(out));
    return out;
}


int recursive_search(std::string const& search_to, std::vector<std::string> const& search_set
       , OrbitList& list, int depth, std::vector<std::string>& visited)
{
    if (list.empty())
    {
        return -1;
    }
    if (std::find(search_set.begin(), search_set.end(), search_to) != search_set.end())
    {
        return depth; 
    }

    for (auto const& cand : search_set)
    {
        search_counter+=1;
        
        auto const search_union = setunion(list[cand].orbits, list[cand].is_orbited_by);
        if (std::find(visited.begin(), visited.end(), cand) == visited.end())
        {
            visited.push_back(cand);
            auto const res = recursive_search(search_to, search_union, list, depth + 1, visited);
            if (res != -1)
            {
                return res;
            }
        }
    }
    return -1;
}

int distance_from_to(std::string const& from, std::string const& to, OrbitList& list)
{
    auto const to_search = setunion(list[from].orbits, list[from].is_orbited_by);
    std::vector<std::string> visited{};
    return recursive_search(to, to_search, list, 0, visited) - 1; // -1 because we want orbital transfers 

}

int main()
{
    // Making use of operator[] with non-const
    auto dataset = parse_input_file("input");

    std::cout << "Part 1 solution is: " << total_orbits(dataset) << "\n";
    std::cout << "Part 2 solution is: " << distance_from_to("YOU", "SAN", dataset) << "\n";
    std::cout << "Searched " << search_counter << " nodes\n";
}


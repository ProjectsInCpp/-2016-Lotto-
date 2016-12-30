// Lotto.cpp : Defines the entry point for the console application.
//

#include <set>
#include <ctime>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#include <boost/random/uniform_int.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/linear_congruential.hpp>

using namespace std;

constexpr int ammOfNumbers = 6;
constexpr int maxVal = 49;
constexpr int amOfSets = 24;
constexpr const char* COMMA_SPACE = ", ";
constexpr const char* EOL = "\n";
constexpr const char* fileName = "results.txt";
using base_generator_type = boost::minstd_rand;
base_generator_type generator(1);
boost::uniform_int<> uni_dist(1, maxVal);

template<typename T>
string toString(T inArg)
{
    stringstream retVal;

    for (auto it : inArg)
    {
        retVal << std::setw(2) << std::left << it << COMMA_SPACE;
    }

    std::string stringedStream = retVal.str();
    return stringedStream.substr(0, stringedStream.size() - 2);
}

void print(std::vector<std::set<int>>& generatedSets)
{
    for (auto it : generatedSets)
    {
        std::cout << toString(it) << std::endl;
    }
}

set<int> sixLottoValues()
{
    boost::variate_generator<base_generator_type&, boost::uniform_int<> > uni(generator, uni_dist);
    set<int> retVal;

    for (int i = 0; retVal.size() < ammOfNumbers; i++)
    {
        retVal.emplace(uni());
    }

    return move(retVal);
}

vector<set<int>> generateSetsOfLottoVals()
{
    vector<set<int>> endVal;

    for (int i = 0; i < amOfSets; i++)
    {
        endVal.emplace_back(sixLottoValues());
    }

    return endVal;
}

void writeToFile(std::vector<std::set<int>>& endVal)
{
    std::ofstream file = std::ofstream(fileName);

    if (file.is_open())
    {
        for (auto it : endVal)
        {
            file << toString(it) << EOL;
        }
    }
}

int main()
{
    generator.seed(static_cast<unsigned int>(std::time(0)));

    vector<set<int>> generatedSets = generateSetsOfLottoVals();
    print(generatedSets);
    writeToFile(generatedSets);

	return 0;
}


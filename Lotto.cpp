// Lotto.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>
#include <set>
#include <memory>
#include <algorithm>
#include <fstream>

#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <ctime>

using namespace std;

constexpr int ammOfNumbers = 6;
constexpr int maxVal = 49;
constexpr int amOfSets = 30;

template<typename T>
string toString(T inArg)
{
    stringstream retVal{};

    for (auto it : inArg)
    {
        retVal << it << ",";
    }

    return retVal.str();
}

vector<int> getSixLottoValues();

typedef boost::minstd_rand base_generator_type;
base_generator_type generator(1);

boost::uniform_int<> uni_dist(1, 49);


int main()
{
    generator.seed(static_cast<unsigned int>(std::time(0)));

	int val = 3;
	int* valPtr = &val;

	vector<vector<int>> endVal;
	for (int i = 0; i < amOfSets; i++) 
	{
        endVal.push_back(getSixLottoValues());
	}

    for (auto it : endVal)
    {
        std::cout << toString(it) << std::endl;
    }

    {
        std::ofstream file{ "results.txt" };

        if (file.is_open())
        {
            for (auto it : endVal)
            {
                file << toString(it) << "END\n";
            }
        }
    }


	system("Pause");
	return 0;
}

vector<int> removeReplications(vector<int> aVal)
{
    set<int> inArgWithoutReplications{ aVal.begin(), aVal.end() };
    
    while(inArgWithoutReplications.size() < ammOfNumbers || inArgWithoutReplications.size() == 0)
    {
        aVal = getSixLottoValues();
        set<int> tempSet{ aVal.begin(), aVal.end() };
        inArgWithoutReplications = move(tempSet);
    }

    std::vector<int> unduplicatedVector{ inArgWithoutReplications.begin(), inArgWithoutReplications.end() };
    return move(unduplicatedVector);
}

vector<int> getSixLottoValues()
{ 


    boost::variate_generator<base_generator_type&, boost::uniform_int<> > uni(generator, uni_dist);

	vector<int> retVal {};
    
    for (int i = 0; i < ammOfNumbers; i++)
    {
        retVal.push_back(uni());
    }

    retVal = removeReplications(retVal);

	return std::move(retVal);
}



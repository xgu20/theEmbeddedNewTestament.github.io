#include "airline.h"
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

AirlineFeeCalculator* AirlineFeeCalculator::Create(Airline air)
{
    switch (air)
    {
    case Airline::delta:
        return DeltaCalculator::GetInstance();
    case Airline::united:
        return UnitedCalculator::GetInstance();
    case Airline::southwest:
        return SouthwestCalculator::GetInstance();
    default:
        break;
    }
    return nullptr;
}

vector<string> split_tolower(string s, char delim = ' '){
    vector<string> res;
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    std::stringstream ss(s);
    std::string token;
    while (std::getline(ss, token, delim) ) {
        if(token != "\0")
        res.push_back(token);
    }
    return res;
}

vector<float> processData(vector<string> ticketData)
{
    vector<float> res;
    for (auto& ticket : ticketData)
    {
        vector<string> data = split_tolower(ticket);
        float miles;
        try {
            miles = stof(data[1]);
        } catch (const char* exception) {
            cout << exception;
            throw;
        }
        Airline al;
        if (data[0] == "united")
        {
            al = Airline::united;
        }
        else if (data[0] == "delta")
        {
            al = Airline::delta;
        }
        else if (data[0] == "southwest")
        {
            al = Airline::southwest;
        }
        Cabin c;
        if (data[2] == "economy")
        {
            c = Cabin::economy;
        }
        else if (data[2] == "premium")
        {
            c = Cabin::premium;
        }
        else if (data[2] == "business")
        {
            c = Cabin::business;
        }
        AirlineFeeCalculator* clc = AirlineFeeCalculator::Create(al);
        cout << clc->getCost(c, miles) << endl;        
    }
    return res;
}

int main()
{
    vector<string> input{"United 150.0 Premium", "United 120.0 economy","United 100.0 business","Delta 60.0 economy","Delta 60.0 premium","Delta 60.0 Business", "SouthWest 1000.0 Economy", "SouthWest 4000.0 Economy"};
    processData(input);
    return 0;
}
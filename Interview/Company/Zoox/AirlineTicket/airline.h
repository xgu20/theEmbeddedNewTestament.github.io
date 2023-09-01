#pragma once

#include <memory>
#include <string>

using namespace std;

namespace Airfee
{
enum Airline
{
    united,
    delta,
    southwest,
};

enum Cabin
{
    economy,
    premium,
    business,
};

class AirlineFeeCalculator
{
public:
    virtual float getCost(Cabin c, float miles)=0;
    static AirlineFeeCalculator* Create(Airline air);
    virtual ~AirlineFeeCalculator() = default;
protected:
    float getOpCost(Cabin c, float miles)
    {
        float opCost = 0;
        switch(c)
        {
            case economy:
                opCost = 0;
                break;
            case premium:
                opCost = 25.;
                break;
            case business:
                opCost = 50. + 0.25 * miles;
                break;
        }
        return opCost;
    }
};

class UnitedCalculator : public AirlineFeeCalculator
{
public:
    static AirlineFeeCalculator* GetInstance()
    {
        static UnitedCalculator calc;
        return &calc;
    }

    float getCost(Cabin c, float miles) override
    {
        return getOpCost(c, miles) + miles * 0.75;
    }

private:
    UnitedCalculator(){}
};

class DeltaCalculator : public AirlineFeeCalculator
{
public:
    static AirlineFeeCalculator* GetInstance()
    {
        static DeltaCalculator calc;
        return &calc;
    }

    float getCost(Cabin c, float miles) override
    {
        return getOpCost(c, miles) + miles * 0.5;
    }

private:
    DeltaCalculator(){}
};

class SouthwestCalculator : public AirlineFeeCalculator
{
public:
    static AirlineFeeCalculator* GetInstance()
    {
        static SouthwestCalculator calc;
        return &calc;
    }

    float getCost(Cabin c, float miles) override
    {
        return 1. * miles;
    }

private:
    
    SouthwestCalculator(){}
};

}


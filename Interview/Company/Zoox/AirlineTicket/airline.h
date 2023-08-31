#pragma once

#include <memory>
#include <string>

using namespace std;

enum AirlineName
{
    United,
    Delta,
    Southwest,
};

class ICabin
{
public:
    virtual float GetOperatingCost() = 0;
    virtual float GetOperatingCost(float mile) = 0;
};

class Economy : public ICabin
{
public:

    virtual float GetOperatingCost(float mile) override
    {
        return GetOperatingCost();
    }

    virtual float GetOperatingCost() override
    {
        return 0;
    }
};

class Premium : public ICabin
{
public:

    virtual float GetOperatingCost(float mile) override
    {
        return GetOperatingCost();
    }

    virtual float GetOperatingCost() override
    {
        return 25;
    }
};

class Business : public ICabin
{
public:
    virtual float GetOperatingCost(float mile) override
    {
        return GetOperatingCost() + 0.25 * mile;
    }

    virtual float GetOperatingCost() override
    {
        return 25;
    }
};

class CabinFactory
{
public:
    static shared_ptr<ICabin> (string cabinStr)
    {
        if (cabinStr == "Economy")
        {
            return make_shared<ICabin>()
        }
    }
private:
    CabinFactory(){}
};

class IAirline
{
public:
    IAirline();
    ~IAirline();

    virtual float GetCost() = 0;
private:
    shared_ptr<ICabin> cabin;

};


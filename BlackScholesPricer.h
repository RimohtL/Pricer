#pragma once
#include "Option.h"

class BlackScholesPricer
{
public:
    BlackScholesPricer(Option*, double, double, double);
    ~BlackScholesPricer();

    double normalDistrib(double);
    double normalCont(double);
    double operator()();
    double delta();

private:
    Option* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;
};

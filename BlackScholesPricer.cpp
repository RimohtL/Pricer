#include "BlackScholesPricer.h"
#include <cmath>
#define NOMINMAX
#define M_PI 3.14159265358979323846  /* pi */

// Constructor
BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility) : _option(option), _asset_price(asset_price), _interest_rate(interest_rate), _volatility(volatility) { }

// Destructor
BlackScholesPricer::~BlackScholesPricer() { }

//Return the distribution of a standard normal distribution
double BlackScholesPricer::normalDistrib(double x) { return 1 / std::sqrt(2 * M_PI) * std::exp(-x * x / 2); }

double BlackScholesPricer::normalCont(double x) { return std::erfc(-x / std::sqrt(2)) / 2; }

// Returns the estimated price with the Black-Scholes formula
double BlackScholesPricer::operator()()
{
    double d1 = (1 / (_volatility * std::sqrt(_option->GetExpiry()))) * (std::log(_asset_price / _option->GetStrike()) + _option->GetExpiry() * (_interest_rate + 0.5 * _volatility * _volatility));
    double d2 = d1 - _volatility * std::sqrt(_option->GetExpiry());
    if (_option->GetOptionType() == OptionType::Call)
        if (_option->isDigital()) // Formula of Cash-or-nothing digital call option
            return normalCont(d2) * std::exp(-_interest_rate * _option->GetExpiry());
        else // Formula of call option
            return _asset_price * normalCont(d1) - _option->GetStrike() * std::exp(-_interest_rate * _option->GetExpiry()) * normalCont(d2);
    else
        if (_option->isDigital()) // Formula of Cash-or-nothing digital put option
            return normalCont(-d2) * std::exp(-_interest_rate * _option->GetExpiry());
        else // Formula of put option
            return -_asset_price * normalCont(-d1) + _option->GetStrike() * std::exp(-_interest_rate * _option->GetExpiry()) * normalCont(-d2);
}

// Returns the delta of the option
double BlackScholesPricer::delta()
{
    double d1 = (1 / (_volatility * std::sqrt(_option->GetExpiry()))) * (std::log(_asset_price / _option->GetStrike()) + _option->GetExpiry() * (_interest_rate + 0.5 * _volatility * _volatility));
    double d2 = d1 - _volatility * std::sqrt(_option->GetExpiry());

    if (_option->GetOptionType() == OptionType::Call)
        if (_option->isDigital()) // Delta of digital call
            //return dS;
            return normalDistrib(d2) * std::exp(-_interest_rate * _option->GetExpiry()) / (_asset_price * _volatility * std::sqrt(_option->GetExpiry()));
        else // Delta of call
            return normalCont(d1);
    else
        if (_option->isDigital()) // Delta of digital put
            return -normalDistrib(-d2) * std::exp(-_interest_rate * _option->GetExpiry()) / (_asset_price * _volatility * std::sqrt(_option->GetExpiry()));
        else // Delta of put
            return -normalCont(-d1);
}

#include "Option.h"

// Constructor
Option::Option(double expiry)
{
	if (expiry <= 0)
		throw std::invalid_argument("Expiry should be nonnegative");
	else
		_expiry = expiry;
}

// Destructor
Option::~Option() { }

// Non-overriden version returning the payoff of the last spot price of the vector
double Option::payoffPath(std::vector<double> spot_prices) { return payoff(spot_prices.at(spot_prices.size() - 1)); }

// Returns the maturity date of the option
double Option::GetExpiry() { return _expiry; }

// Non-overriden version returning the time steps for non path dependent options, i.e. only the time to maturity
std::vector<double> Option::getTimeSteps() {
	std::vector<double> timesteps{ 0, _expiry };
	return timesteps;
}

// Non overriden version returning false to indicate that the option is not asian
bool Option::isAsianOption() { return false; }

// Non overriden version returning false to indicate that the option is not american
bool Option::isAmericanOption() { return false; }

// Non overriden version returning false to indicate that the option is not digital
bool Option::isDigital() { return false; }

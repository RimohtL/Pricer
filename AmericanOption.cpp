#include "AmericanOption.h"

#pragma region AmericanOption
// Constructor
AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry)
{
	if (strike <= 0)
		throw std::invalid_argument("Strike should be nonnegative");
	else
		m_strike = strike;
}

// Destructor
AmericanOption::~AmericanOption() { }

// Overriden version returning true to indicate that this option is american
bool AmericanOption::isAmericanOption() { return true; }

// Overriden version returning the strike of the option
double AmericanOption::GetStrike() { return m_strike; }
#pragma endregion

#pragma region AmericanCallOption
// Constructor
AmericanCallOption::AmericanCallOption(double strike, double expiry) : AmericanOption(strike, expiry) { }

// Destructor
AmericanCallOption::~AmericanCallOption() { }

// Returns the type of the option, in this case a call
OptionType AmericanCallOption::GetOptionType() { return OptionType::Call; }

// Returns the payoff of a call option
double AmericanCallOption::payoff(double z)
{
	if (z < m_strike)
		return 0;
	else
		return z - m_strike;
}
#pragma endregion

#pragma region AmericanPutOption
// Constructor
AmericanPutOption::AmericanPutOption(double strike, double expiry) : AmericanOption(strike, expiry) { }

// Destructor
AmericanPutOption::~AmericanPutOption() { }

// Returns the type of the option, in this case a put
OptionType AmericanPutOption::GetOptionType() { return OptionType::Put; }

// Returns the payoff of a put option
double AmericanPutOption::payoff(double z)
{
	if (z > m_strike)
		return 0;
	else
		return m_strike - z;
}
#pragma endregion

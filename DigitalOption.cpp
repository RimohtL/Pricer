#include "DigitalOption.h"

#pragma region DigitalOption
// Constructor
DigitalOption::DigitalOption(double expiry, double strike) : Option(expiry)
{
	if (strike <= 0)
		throw std::invalid_argument("Strike should be nonnegative");
	else
		m_strike = strike;
}

// Destructor
DigitalOption::~DigitalOption() { }

// Overriden version returning the strike of the option
double DigitalOption::GetStrike() { return m_strike; }

// Overriden version returning true to indicate that this option is digital
bool DigitalOption::isDigital() { return true; }
#pragma endregion

#pragma region DigitalCallOption
// Constructor
DigitalCallOption::DigitalCallOption(double expiry, double strike) : DigitalOption(expiry, strike) { }

// Destructor
DigitalCallOption::~DigitalCallOption() { }

// Returns the type of the option, in this case a call
OptionType DigitalCallOption::GetOptionType() { return OptionType::Call; }

// Returns the payoff of a digital call option
double DigitalCallOption::payoff(double z)
{
	if (z >= m_strike)
		return 1;
	else
		return 0;
}
#pragma endregion

#pragma region DigitalPutOption
// Constructor
DigitalPutOption::DigitalPutOption(double expiry, double strike) : DigitalOption(expiry, strike) { }

// Destructor
DigitalPutOption::~DigitalPutOption() { }

// Returns the type of the option, in this case a put
OptionType DigitalPutOption::GetOptionType() { return OptionType::Put; }

// Returns the payoff of a digital put option
double DigitalPutOption::payoff(double z)
{
	if (z <= m_strike)
		return 1;
	else
		return 0;
}
#pragma endregion

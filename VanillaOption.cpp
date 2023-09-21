#include "VanillaOption.h"

#pragma region VanillaOption
//Constructor
VanillaOption::VanillaOption(double expiry, double strike) : Option(expiry)
{
	if (strike <= 0)
		throw std::invalid_argument("Strike should be nonnegative");
	else
		m_strike = strike;
}

// Destructor
VanillaOption::~VanillaOption() { }

// Overriden version returning the strike of the option
double VanillaOption::GetStrike() { return m_strike; }
#pragma endregion

#pragma region CallOption
//Constructor
CallOption::CallOption(double expiry, double strike) : VanillaOption(expiry, strike) { }

// Destructor
CallOption::~CallOption() { }

// Returns the type of the option, in this case a call
OptionType CallOption::GetOptionType() { return OptionType::Call; }

// Returns the payoff of a call option
double CallOption::payoff(double z) { return std::max(z - m_strike, 0.0); }
#pragma endregion

#pragma region PutOption
//Constructor
PutOption::PutOption(double expiry, double strike) : VanillaOption(expiry, strike) { }

// Destructor
PutOption::~PutOption() { }

// Returns the type of the option, in this case a put
OptionType PutOption::GetOptionType() { return OptionType::Put; }

// Returns the payoff of a put option
double PutOption::payoff(double z) { return std::max(m_strike - z, 0.0); }
#pragma endregion

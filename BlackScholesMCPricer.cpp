#include "BlackScholesMCPricer.h"
#include "MT.h"

// Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)
	: _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), _current_estimate(-1), _nb_paths(0) { }

// Destructor
BlackScholesMCPricer::~BlackScholesMCPricer() { }

// Returns the total number of paths generated
int BlackScholesMCPricer::getNbPaths()
{
	if (_nb_paths != 0)
		return _nb_paths;
	else
		throw std::invalid_argument("Error : No path has yet been generated.");
}

// Returns the current estimate of the option price
double BlackScholesMCPricer::operator()()
{
	if (_current_estimate == -1)
		throw std::invalid_argument("Error : No current estimate has yet been defined.");
	else
		return _current_estimate;
}

// Generates nb_paths number of paths
void BlackScholesMCPricer::generate(int nb_paths) {
	// This method doesn't work, so we will create a new mt generator
	/*MT& instance = MT::getInstance();
	std::mt19937 generator = instance.getGen();
	double normal = MT::rand_norm(generator);*/

	std::random_device rd;
	std::mt19937 generator(rd());
	double normal = MT::rand_norm(generator);

	double s_next, s_prev;
	double m = 0;

	if (_option->isAsianOption()) // Number of steps for asian options
		m = _option->getTimeSteps().size();
	else // Number of steps for european options
		m = 1;

	double expiry = _option->GetExpiry();
	double step = expiry / m;

	for (int i = 0; i < nb_paths; i++)
	{
		std::vector<double> spot_prices(m + 1); // Initialize new vector h(S0, ..., Sm)
		s_next = 0;	s_prev = _initial_price; // Initialize S0 and S1
		spot_prices.at(0) = s_prev; // Initialize price at t = 0

		for (int j = 1; j <= m; j++)	// Computing all spot prices for the current path
		{
			s_next = s_prev * std::exp(((_interest_rate - ((_volatility * _volatility) / 2)) * step) + (_volatility * std::sqrt(step) * normal));
			spot_prices.at(j) = s_next;
			s_prev = s_next;
		}
        
		_current_estimate = (_nb_paths * _current_estimate + _option->payoffPath(spot_prices)) / (_nb_paths + 1);
        _nb_paths++;
	}
}

// Returns the confidence interval of the current price
std::vector<double> BlackScholesMCPricer::confidenceInterval()
{
	std::vector<double> interval{_current_estimate - ((2 * _volatility) / (std::sqrt(_nb_paths))), _current_estimate + ((2 * _volatility) / (std::sqrt(_nb_paths))) };
	return interval;
}

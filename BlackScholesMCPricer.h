#pragma once
#include "Option.h"

class BlackScholesMCPricer
{
	public:
		BlackScholesMCPricer(Option*, double, double, double);
		~BlackScholesMCPricer();

		int getNbPaths();
		void generate(int);
		double operator()();
		std::vector<double> confidenceInterval();


	private:
		Option* _option;
		double _initial_price;
		double _interest_rate;
		double _volatility;
		double _current_estimate;
		int _nb_paths;
};


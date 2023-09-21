#include "CRRPricer.h"
#include "BinaryTree.h"
#include <cmath>

// Constructor
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) : _price(asset_price), _up(up), _down(down), _option(option), _interest_rate(interest_rate)
{
	if (option->isAsianOption()) // Check if the option is not asian
		throw std::invalid_argument("Error : The option is an Asian Option");
	else {
		if (down < interest_rate && interest_rate < up) { // Check for arbitrage
			_tree = BinaryTree<double>(depth);
			_exercise = BinaryTree<bool>(depth);
			this->compute();
		}
		else
			throw std::invalid_argument("Error : There is an arbitrage");
	}
}

// Overloaded constructor for TD8
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) : _price(asset_price), _option(option)
{
	if (option->isAsianOption()) // Check if the option is not asian
		throw std::invalid_argument("Error : The option is an Asian Option");
	else { // Compute Black-Scholes parameters
		double h = _option->GetExpiry() / depth;
		_up = std::exp((r + (std::pow(volatility, 2) / 2)) * h + volatility * std::sqrt(h)) - 1;
		_down = std::exp((r + (std::pow(volatility, 2) / 2)) * h - volatility * std::sqrt(h)) - 1;
		_interest_rate = std::exp(r * h) - 1;

		if (_down < _interest_rate && _interest_rate < _up) { // Check for arbitrage
            _tree = BinaryTree<double>(depth);
			_exercise = BinaryTree<bool>(depth);
		}
		else
			throw std::invalid_argument("Error : There is an arbitrage");
	}
}

// Destructor
CRRPricer::~CRRPricer() { }

// Initializes the tree with all prices
void CRRPricer::compute()
{
	double value = 0;
	for (int n = 0; n < _tree.getDepth() + 1; n++)
	{
		for (int i = 0; i < _tree.getLengthVec(n); i++)
		{
			value = _price * std::pow((1 + _up), i) * std::pow((1 + _down), n - i);
			_tree.setNode(n, i, value);
		}
	}
}

// Returns the payoff at a specified state of the tree
double CRRPricer::get(int step, int node) {	return _option->payoff(_tree.getNode(step, node)); }

// Returns a boolean indicating the exercise condition for american options
bool CRRPricer::getExercise(int step, int node) { return _exercise.getNode(step, node); }

// Display the tree
void CRRPricer::display() {	_tree.display(); }

// Compute the factorial of a number
double CRRPricer::facto(int n)
{
	if ((n == 0) || (n == 1))
		return 1;
	else
		return n * facto(n - 1);
}

// Compute the price of the option with the CRR method
double CRRPricer::operator()(bool closed_form)
{
	double q = (_interest_rate - _down) / (_up - _down);
	if (closed_form) // Compute price using closed formula
	{
		double value = 0;
		for (int i = 0; i < _tree.getDepth(); i++)
			value = value + (facto(_tree.getDepth()) / (facto(i) * facto(_tree.getDepth() - i))) * std::pow(q, i) * std::pow((1 - q), _tree.getDepth() - i) * this->get(_tree.getDepth(), i);
		return value * (1 / std::pow((1 + _interest_rate), _tree.getDepth()));
	}
	else { // Compute price by iterating through the tree
		BinaryTree<double> values = BinaryTree<double>(_tree.getDepth()); // Tree that will contain the prices of the option
		BinaryTree<bool> exercises = BinaryTree<bool>(_tree.getDepth()); // Tree that will contain the exercise conditions for american options

		// Compute prices at the last branch
		for (int i = 0; i < _tree.getLengthVec(_tree.getDepth()); i++)
		{
			values.setNode(values.getDepth(), i, this->get(values.getDepth(), i));
			exercises.setNode(values.getDepth(), i, false);
		}

		// Iterate through the tree in reverse order
		double price = 0;
		double intrinsic = 0;
		bool exerciseCondition = false;

		for (int n = _tree.getDepth() - 1; n >= 0; n--)
		{
			for (int i = 0; i < _tree.getLengthVec(n); i++)
			{
				price = (q * values.getNode(n + 1, i + 1) + (1 - q) * values.getNode(n + 1, i)) / (1 + _interest_rate);
				if (_option->isAmericanOption()) { // Compute price for american option
					intrinsic = this->get(n, i);

					if (intrinsic >= price) { // Compute exercise condition
						values.setNode(n, i, intrinsic);
						exerciseCondition = true;
						exercises.setNode(n, i, exerciseCondition);
					}
					else {
						values.setNode(n, i, price);
						exercises.setNode(n, i, exerciseCondition);
					}
				}
				else // Set price for vanilla options
					values.setNode(n, i, price);
			}
		}
		return values.getNode(0, 0); // Return the first price
	}
}

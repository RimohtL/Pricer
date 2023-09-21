#pragma once
#include "Option.h"
#include "BinaryTree.h"

class CRRPricer
{
	public:
		CRRPricer(Option*, int, double, double, double, double);
		CRRPricer(Option*, int, double, double, double);
		~CRRPricer();

		void compute();
		double get(int, int);
		double operator()(bool closed_form = false);
		void display();
		double facto(int);
		bool getExercise(int, int);

	private:
		BinaryTree<double> _tree;
		BinaryTree<bool> _exercise;
		Option* _option;
		double _up;
		double _down;
		double _price;
		double _interest_rate;
};

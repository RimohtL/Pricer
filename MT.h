#pragma once
#include <random>

class MT
{
	public:
		MT(const MT&) = delete; //To avoid creating copies of singleton
		MT& operator=(const MT&) = delete; //To avoid assigning copies of singleton

		static MT& getInstance(); //To access the class staticly, returns instance of singleton
		static double rand_unif(std::mt19937&);
		static double rand_norm(std::mt19937&);
		std::mt19937 getGen();

	private:
		MT(); //Constructor in private to not be able to instantiate it
		std::mt19937 _MTGen;
};

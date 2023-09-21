#include <iostream>
#include <random>
#include <string>
#include "AmericanOption.h"
#include "AsianOption.h"
#include "BinaryTree.h"
#include "BlackScholesPricer.h"
#include "BlackScholesMCPricer.h"
#include "CRRPricer.h"
#include "DigitalOption.h"
#include "MT.h"
#include "Option.h"
#include "VanillaOption.h"

int main()
{
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    
#pragma region TD5&6
    {
        std::cout << "******************************** TD 5 & 6 ********************************" << std::endl;
        std::cout << std::endl;
        
        {
            CallOption opt1(T, K);
            PutOption opt2(T, K);
            
            std::cout << std::endl << "================= European options 1 =================" << std::endl << std::endl;
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer call price = " << pricer1() << ", delta = " << pricer1.delta() << std::endl;
            
            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer put price = " << pricer2() << ", delta = " << pricer2.delta() << std::endl;
            std::cout << std::endl;
            
            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            
            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth = " << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed call price = " << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula call price = " << crr_pricer1(true) << std::endl;
            std::cout << std::endl;
            
            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth = " << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed put price = " << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula put price = " << crr_pricer2(true) << std::endl;
        }
    }
    
    {
        DigitalCallOption opt1(T, K);
        DigitalPutOption opt2(T, K);
        
        std::cout << std::endl << "================= European options 2 =================" << std::endl << std::endl;
        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer digital call price = " << pricer1() << ", delta = " << pricer1.delta() << std::endl;
            
            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer digital put price = " << pricer2() << ", delta = " << pricer2.delta() << std::endl;
            std::cout << std::endl;
            
            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;
            
            
            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth = " << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed digital call price = " << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula digital call price = " << crr_pricer1(true) << std::endl;
            std::cout << std::endl;
            
            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth = " << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed digital put price = " << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula digital put price = " << crr_pricer2(true) << std::endl;
        }
    }
    
     {
     std::cout << std::endl << "================= Binary Tree =================" << std::endl << std::endl;
    
     BinaryTree<bool> t1(3);
     t1.setDepth(3);
     t1.setNode(1, 1, true);
     t1.display();
     t1.setDepth(5);
     t1.display();
     t1.setDepth(3);
     t1.display();
     
     BinaryTree<double> t2;
     t2.setDepth(2);
     t2.setNode(2, 1, 3.14);
     t2.display();
     t2.setDepth(4);
     t2.display();
     t2.setDepth(3);
     t2.display();
     
     BinaryTree<int> t3;
     t3.setDepth(4);
     t3.setNode(3, 0, 188);
     t3.display();
     t3.setDepth(2);
     t3.display();
     t3.setDepth(4);
     t3.display();
     }
     #pragma endregion
    
#pragma region TD7
    {
        std::cout << std::endl;
        std::cout << "********************************** TD 7 **********************************" << std::endl;
        std::cout << std::endl;
        
        std::vector<Option*> opt_ptrs;
        opt_ptrs.push_back(new CallOption(T, K));
        opt_ptrs.push_back(new PutOption(T, K));
        opt_ptrs.push_back(new DigitalCallOption(T, K));
        opt_ptrs.push_back(new DigitalPutOption(T, K));


        std::vector<double> fixing_dates;
        for (int i = 1; i <= 5; i++) {
            fixing_dates.push_back(0.1 * i);
        }
        opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
        opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

        std::vector<double> ci;
        BlackScholesMCPricer* pricer;

        std::vector<std::string> options{ "Call", "Put", "Digital Call", "Digital Put", "Asian Call", "Asian Put" };
        int counter = 0;
        for (auto& opt_ptr : opt_ptrs) {
            pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
            do {
                pricer->generate(10);
                ci = pricer->confidenceInterval();
            } while (ci[1] - ci[0] > 1e-2);
            std::cout << "nb samples : " << pricer->getNbPaths() << std::endl;
            std::cout << "price of " << options[counter] << " : " << (*pricer)() << std::endl << std::endl;
            counter++;
        }
    }
    #pragma endregion

    #pragma region TD8
    std::cout << std::endl;
    std::cout << "********************************** TD 8 **********************************" << std::endl;
    std::cout << std::endl;
    {
        std::vector<Option*> opt_ptrs;
        opt_ptrs.push_back(new CallOption(T, K));
        opt_ptrs.push_back(new PutOption(T, K));
        opt_ptrs.push_back(new DigitalCallOption(T, K));
        opt_ptrs.push_back(new DigitalPutOption(T, K));
        opt_ptrs.push_back(new AmericanCallOption(T, K));
        opt_ptrs.push_back(new AmericanPutOption(T, K));

        CRRPricer* pricer;
        std::vector<std::string> options{ "Call", "Put", "Digital Call", "Digital Put", "American Call", "American Put" };
        for (auto& opt_ptr : opt_ptrs) {
            pricer = new CRRPricer(opt_ptr, 150, S0, r, sigma);
            pricer->compute();
            std::cout << "price : " << (*pricer)() << std::endl << std::endl;

            delete pricer;
            delete opt_ptr;
        }
    }
    #pragma endregion
}


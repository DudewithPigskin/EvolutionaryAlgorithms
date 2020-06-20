#pragma once

#include "radReg.h"
#include <cstdlib>
#include <math.h>
#include <stdio.h>
#include <iostream>



double hicam::radReg_t::rbf(solution_t &sol, double xi, int i){
          double e = exp((-1 * (xi - sol.param[i + 10]) * (xi - sol.param[i + 10]))/ (2 * sol.param[i + 20] * sol.param[i + 20]));
          return(e * sol.param[i]);

      }

double hicam::radReg_t::RBF(solution_t &sol, double xi, int K){
        double Ri = 0.0;
       
        for ( int i = 0; i < K; i++){
          Ri += rbf(sol, xi,i);
        }
        return (Ri);
      }

double hicam::radReg_t::f0(int n, solution_t &sol, int K){
        double fZero = 0.0;
        double diff = 0.0;
        double ri = 0.0;
        for (int i = 0; i < n; i++){
          ri = RBF(sol, x[i], K);
          diff = y[i] - ri;
          fZero += abs(diff) * abs(diff);
        }
        return(fZero/n);
      }



hicam::radReg_t::radReg_t()
    {
      number_of_objectives = 2; //fixed
      number_of_parameters = 30; //w, mu, sigma , or defined in K?
    }

hicam::radReg_t::~radReg_t() {}

     //copy-pasted from BD1_t
void hicam::radReg_t::set_number_of_objectives(size_t & number_of_objectives)
    {
      number_of_objectives = this->number_of_objectives;
    }

    //copy-pasted from BD1_t
void hicam::radReg_t::set_number_of_parameters(size_t & number_of_parameters)
    {
      this->number_of_parameters = number_of_parameters;
    }

    //copy-pasted from BD1_t -> is this even working? 
void hicam::radReg_t::get_param_bounds(vec_t & lower, vec_t & upper) const
    {
      lower.clear();
      lower.resize(number_of_parameters, 0);

      upper.clear();
      upper.resize(number_of_parameters, 20); //this should set the max value to 20?
  
    }

void hicam::radReg_t::define_problem_evaluation(solution_t & sol)
    {
      /*
       sol.param[0] : w
       sol.param[1] : mu
       sol.param[2] : sigma
       */
      
      sol.obj.resize(number_of_objectives);
      
      int size = 50;
      //double x [50] = {-2.13876, -0.843971, -2.77733 ,0.969594, 0.948479, 0.0596248, -2.81538, -2.68752, -2.66449, 1.43964, -1.82261, 0.75355, 1.77127, 1.50504, 0.563664, 0.934696, -0.964971, -0.0580217, -1.03172, 1.74479, 0.949619, -0.235184, -1.03222, -2.34456, -1.96341, 1.3474, -1.99459, -0.616371, 1.23675, -0.115709, -0.620406, -0.313958, -2.91901, -0.51485, -1.23434, 1.8188, -2.15125, 1.94123, -1.34461, 1.81213, -2.54684, -2.63072, 0.402378, -2.42504, 0.166079, -1.07568, -1.61749, -2.91959, -1.71093, 1.08362 };
      //double y [50]= {-10.4758, -4.80274, -23.3352, -1.80149, 5.61443, 1.73721, -33.2348, -32.3649, -27.0149, 14.9916, -9.4299, -12.8493, 12.8735, 2.71406, 3.78351, 2.43841, -6.41437, -10.7886, -0.705705, 3.52402, 10.0806, -9.5326, -0.447625, -14.892, -11.4165, 8.8522, -7.94916, 0.822361, 2.71519, 3.67672, 0.177861, -2.70773, -32.1672, -7.76417, -7.15321, 6.14037, -21.8601, -1.02493, -2.55413, 16.949, -23.3274, -29.4496, 12.4751, -18.4906, 1.72832, 1.86347, -2.40768, -27.5401, -1.73747, -1.90976};
      
      
      assert(sol.param.size() % 3 == 0);
      int K = (int) sol.param.size() / 3;
     // std::cout<< K << std::endl;      
      //f0
      //
      //
      sol.obj[0] = f0(size, sol, K);
     // sol.obj[0] = radReg_t::f0(size, &x[0], &y[0], &sol.param[0], &sol.param[K], sol.param[2*K], K);

      //sol.obj[1] = 1 ;

      //f1      
      double wsum = 0.0;
      for (int i = 0; i < K; i++){
        wsum += abs(sol.param[i]) * abs(sol.param[i]);
      }

      sol.obj[1] = wsum/K;

      sol.constraint = 0;
      
      assert(!isnan(sol.obj[0]));
      assert(!isnan(sol.obj[1]));
    }


std::string hicam::radReg_t::name() const
    {
      return "RadReg";
    }

bool hicam::radReg_t::get_pareto_set() //copy pasted from bd1.h
    {
      
      int K = 10;
      double w0[K] = {-0.04068505468,	0.00623802537,	-0.005540277454,	-0.04431483455,	0.00271712844,	0.001554722463,	-0.009529671233,	0.001780588799,	-0.0441371583,	0.001081215881};
      double mu0[K] = {-22.09974557,	-622.2415622,	-862.532566,	-2.783548356,	188.910576,	184.5873325,	145.7415981,	60.35160608,	-92.0797432,	51.45572459};
      double sigma0[K] = {-754.8907596,	64.34790079,	259.3125555,	1.067637847,	-416.0267074,	991.9062383,	494.3067851,	364.2688615,	-701.0523296,	-619.5470736};
      
    // row 28
      double w[K] = {-0.5529593476,	-0.3438004136,	-0.3152778121,	-0.4276245826,	-0.3507798782,	-0.5494719166,	0.1159878788,	-0.3829600916,	0.07842436575,	-0.5081503106};

      double mu[K] = {-2.75713371,	-4.757723893,	-18.14334058,	-2.72390863,	-2.731105144,	-2.758134096,	-968.422896,	-2.294301129,	-543.6367868,	-2.790488722};

      double sigma[K] = {1.172413504,	-7.848952747,	-811.6658769,	-1.482832778,	-1.113236805,	-1.280138971,	118.910152,	1.37167249,	-3.748520343,	-1.125398145};

      size_t pareto_set_size = 1;

      if (pareto_set.size() != pareto_set_size)
      {
        pareto_set.sols.clear();
        pareto_set.sols.reserve(pareto_set_size);

        solution_pt sol = std::make_shared<solution_t>(number_of_parameters, number_of_objectives);

        for (size_t i = 0; i < K; i++){
          sol->param[i] = w[i];
          sol->param[i+K] = mu[i];
          sol->param[i+20] = sigma[i]; 
        }

        for (size_t i = 0; i < number_of_parameters; i++){
          std::cout<<sol->param[i]<<" ";
        }
        define_problem_evaluation(*sol);
        std::cout<<"TEST:" <<std::endl;
        std::cout<<sol->obj[0]<<std::endl;
        std::cout<<sol->obj[1]<<std::endl;
        pareto_set.sols.push_back(sol);
       // igdx_available = true;
       // igd_available = true;
      }

      /*      
      size_t pareto_set_size = 15;
      
      // generate default front
      if (pareto_set.size() != pareto_set_size)
      {
        
        pareto_set.sols.clear();
        pareto_set.sols.reserve(pareto_set_size);
        
        // the front
        for (size_t i = 0; i < pareto_set_size; ++i)
        {
          solution_pt sol = std::make_shared<solution_t>(number_of_parameters, number_of_objectives);
          
          sol->param.fill(1.0);
          sol->param[0] = i / ((double)pareto_set_size - 1.0);
          define_problem_evaluation(*sol); // runs a feval without registering it.
          
          pareto_set.sols.push_back(sol);
         
        }
        
        igdx_available = true;
        igd_available = true;
      }

    

      return true;
 */
      return false;
    }

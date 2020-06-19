#pragma once


/*
Radial Regression issue
Implementation by 
K M Peelen.
S.W Garst
note: f0 en f1 kunnen efficienter berekend worden als we deze tegelijk berekenen (loop overhead)
*/


#include "../domination_based_MO_optimization/mohillvallea/fitness.h"
#include "../domination_based_MO_optimization/mohillvallea/population.h"
//#include <math.h>
//#include <cstdlib>

namespace hicam
{
  class radReg_t: public fitness_t
  {
  
  public:


   double rbf(solution_t &sol, double x, int i);
   double f0(int n,double *x,  double *y, solution_t &sol, int K);
   double RBF(solution_t &sol, double x, int K);

    radReg_t();
    ~radReg_t();
    void set_number_of_objectives(size_t & number_of_objectives);
    void set_number_of_parameters(size_t & number_of_parameters);
    void get_param_bounds(vec_t & lower, vec_t & upper) const;

    void define_problem_evaluation(solution_t & sol);
    
    std::string name() const;
    
    bool get_pareto_set();
    
    
    int size = 50;
    double x [50] = {-2.13876, -0.843971, -2.77733 ,0.969594, 0.948479, 0.0596248, -2.81538, -2.68752, -2.66449, 1.43964, -1.82261, 0.75355, 1.77127, 1.50504, 0.563664, 0.934696, -0.964971, -0.0580217, -1.03172, 1.74479, 0.949619, -0.235184, -1.03222, -2.34456, -1.96341, 1.3474, -1.99459, -0.616371, 1.23675, -0.115709, -0.620406, -0.313958, -2.91901, -0.51485, -1.23434, 1.8188, -2.15125, 1.94123, -1.34461, 1.81213, -2.54684, -2.63072, 0.402378, -2.42504, 0.166079, -1.07568, -1.61749, -2.91959, -1.71093, 1.08362 };
    double y [50]= {-10.4758, -4.80274, -23.3352, -1.80149, 5.61443, 1.73721, -33.2348, -32.3649, -27.0149, 14.9916, -9.4299, -12.8493, 12.8735, 2.71406, 3.78351, 2.43841, -6.41437, -10.7886, -0.705705, 3.52402, 10.0806, -9.5326, -0.447625, -14.892, -11.4165, 8.8522, -7.94916, 0.822361, 2.71519, 3.67672, 0.177861, -2.70773, -32.1672, -7.76417, -7.15321, 6.14037, -21.8601, -1.02493, -2.55413, 16.949, -23.3274, -29.4496, 12.4751, -18.4906, 1.72832, 1.86347, -2.40768, -27.5401, -1.73747, -1.90976};
/*
    radReg_t()
    {
      number_of_objectives = 2; //fixed
      number_of_parameters = 30; //w, mu, sigma , or defined in K?
    }
    ~radReg_t() {}

     //copy-pasted from BD1_t
    void set_number_of_objectives(size_t & number_of_objectives)
    {
      number_of_objectives = this->number_of_objectives;
    }

    //copy-pasted from BD1_t
    void set_number_of_parameters(size_t & number_of_parameters)
    {
      this->number_of_parameters = number_of_parameters;
    }

    //copy-pasted from BD1_t -> is this even working? 
    void get_param_bounds(vec_t & lower, vec_t & upper) const
    {
      lower.clear();
      lower.resize(number_of_parameters, 0);

      upper.clear();
      upper.resize(number_of_parameters, 20); //this should set the max value to 20?
  
    }


    double rbf(double w, double mu, double sigma, double x){
        double e = exp((-1 * (x - mu) * (x - mu))/ (2 * sigma * sigma));
        return(e * w);

    }

    double RBF(double *w, double *mu, double *sigma, double x, int K){
      double Ri = 0.0;
     
      for ( int i = 0; i < K; i++){
        Ri += rbf(*w, *mu, *sigma, x);
        w += 1;
        mu += 1;
        sigma +=1;
      }
      return (Ri);
    }

    double f0(int n, double *x,  double *y, double *w, double *mu, double *sigma, int K){
      double fZero = 0.0;
      double diff = 0.0;
      double ri = 0.0;
      for (int i = 0; i < n; i++){
        ri = RBF(w, mu, sigma, *x, K);
        diff = *y - ri;
        fZero += abs(diff) * abs(diff);

        y += 1;
        x += 1;

      }
      return(fZero/n);
    }
    void define_problem_evaluation(solution_t & sol)
    {
      /*
       sol.param[0] : w
       sol.param[1] : mu
       sol.param[2] : sigma
       */
      /*
      sol.obj.resize(number_of_objectives);
      
      int size = 50;
      double x [50] = {-2.13876, -0.843971, -2.77733 ,0.969594, 0.948479, 0.0596248, -2.81538, -2.68752, -2.66449, 1.43964, -1.82261, 0.75355, 1.77127, 1.50504, 0.563664, 0.934696, -0.964971, -0.0580217, -1.03172, 1.74479, 0.949619, -0.235184, -1.03222, -2.34456, -1.96341, 1.3474, -1.99459, -0.616371, 1.23675, -0.115709, -0.620406, -0.313958, -2.91901, -0.51485, -1.23434, 1.8188, -2.15125, 1.94123, -1.34461, 1.81213, -2.54684, -2.63072, 0.402378, -2.42504, 0.166079, -1.07568, -1.61749, -2.91959, -1.71093, 1.08362 };
      double y [50]= {-10.4758, -4.80274, -23.3352, -1.80149, 5.61443, 1.73721, -33.2348, -32.3649, -27.0149, 14.9916, -9.4299, -12.8493, 12.8735, 2.71406, 3.78351, 2.43841, -6.41437, -10.7886, -0.705705, 3.52402, 10.0806, -9.5326, -0.447625, -14.892, -11.4165, 8.8522, -7.94916, 0.822361, 2.71519, 3.67672, 0.177861, -2.70773, -32.1672, -7.76417, -7.15321, 6.14037, -21.8601, -1.02493, -2.55413, 16.949, -23.3274, -29.4496, 12.4751, -18.4906, 1.72832, 1.86347, -2.40768, -27.5401, -1.73747, -1.90976};
      
      
      assert(sol.param.size() % 3 == 0);
      int K = (int) sol.param.size() / 3;
      
      //f0
      //
      sol.obj[0] = f0(size, &x[0], &y[0], &sol.param[0], &sol.param[K], sol.param[2*K], K);

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


    std::string name() const
    {
      return "RadReg";
    }

    bool get_pareto_set()
    {
     return false;
    }
    */
   };
}

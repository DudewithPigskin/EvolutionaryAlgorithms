#pragma once


/*
Radial Regression issue
Implementation by 
K M Peelen.
S.W Garst

todo: kijken hoe we de datapunten hier in verwerken

note: f0 en f1 kunnen efficienter berekend worden als we deze tegelijk berekenen (loop overhead)

*/


#include "../domination_based_MO_optimization/mohillvallea/fitness.h"
#include "../domination_based_MO_optimization/mohillvallea/population.h"
#include <math.h>

namespace hicam
{
  class radReg_t: public fitness_t
  {
  public:


    radReg_t()
    {
      number_of_objectives = 2; //fixed
      number_of_parameters = 30; //w, mu, sigma , or defined in K?
    }
    ~radReg_t() {}

     //copy-pasted from BD1_t
    void set_number_of_objectives(size_t & number_of_objectives)
    {
      //this->number_of_objectives = 2;
      //number_of_objectives = this->number_of_objectives;
      this->number_of_objectives = number_of_objectives ;
    }

    //copy-pasted from BD1_t
    void set_number_of_parameters(size_t & number_of_parameters)
    {
      this->number_of_parameters = number_of_parameters; // times 3?
    }


      //copy-pasted from BD1_t
    void get_param_bounds(vec_t & lower, vec_t & upper) const
    {
      lower.clear();
      lower.resize(number_of_parameters, -1e308);
      lower[0] = 0.0;

      upper.clear();
      upper.resize(number_of_parameters, 1e308);
      upper[0] = 1.0;
    }

    void define_problem_evaluation(solution_t & sol)
    {
      /*
      sol.param[0] : w
      sol.param[1] : mu
      sol.param[2] : sigma
      */
      int size = 50;
      float x [size] = {-2.13876, -0.843971, -2.77733 ,0.969594, 0.948479, 0.0596248, -2.81538, -2.68752, -2.66449, 1.43964, -1.82261, 0.75355, 1.77127, 1.50504, 0.563664, 0.934696, -0.964971, -0.0580217, -1.03172, 1.74479, 0.949619, -0.235184, -1.03222, -2.34456, -1.96341, 1.3474, -1.99459, -0.616371, 1.23675, -0.115709, -0.620406, -0.313958, -2.91901, -0.51485, -1.23434, 1.8188, -2.15125, 1.94123, -1.34461, 1.81213, -2.54684, -2.63072, 0.402378, -2.42504, 0.166079, -1.07568, -1.61749, -2.91959, -1.71093, 1.08362 };
      float y [size]= {-10.4758, -4.80274, -23.3352, -1.80149, 5.61443, 1.73721, -33.2348, -32.3649, -27.0149, 14.9916, -9.4299, -12.8493, 12.8735, 2.71406, 3.78351, 2.43841, -6.41437, -10.7886, -0.705705, 3.52402, 10.0806, -9.5326, -0.447625, -14.892, -11.4165, 8.8522, -7.94916, 0.822361, 2.71519, 3.67672, 0.177861, -2.70773, -32.1672, -7.76417, -7.15321, 6.14037, -21.8601, -1.02493, -2.55413, 16.949, -23.3274, -29.4496, 12.4751, -18.4906, 1.72832, 1.86347, -2.40768, -27.5401, -1.73747, -1.90976};
      
      int K = this->number_of_parameters/3;

      //f0
      float totalerror = 0;
      for (int point = 0; point < size ;point++) {
        float suberror = y[point];
        for (int radial = 0; radial < K; radial++){
          int index = 3 * radial;
          suberror -= sol.param[index] * exp( (-1*(x[point]-sol.param[index+1]))  / ( 2*pow( sol.param[index+2] ,2 )) );
        }
        totalerror += pow(suberror,2);// assumption: number is never complex (left out absolute around suberror)
      }
      sol.obj[0] = totalerror / size;
      
      //f1
      float stability = 0;
      for (int radial = 0; radial<K; radial++){
        int index = 3 * radial;
        stability += pow(sol.obj[index],2);
      }
      sol.obj[1] = stability / K;
    }

    std::string name() const
    {
      return "RadReg";
    }

    bool get_pareto_set()
    {

      size_t pareto_set_size = 5000;

      //generate default front
      if (pareto_set.size() != pareto_set_size)
      {

        pareto_set.sols.clear();
        pareto_set.sols.reserve(pareto_set_size);

        for (size_t i = 0; i < pareto_set_size; ++i)
        {
          solution_pt sol = std::make_shared<solution_t>(number_of_parameters, number_of_objectives);
          sol->param.fill(1.0);
          sol->param[0] = i / ((double)pareto_set_size - 1.0);
          define_problem_evaluation(*sol);

          pareto_set.sols.push_back(sol);
        }

        igdx_available = true;
        igd_available = true;
      }
      return true;
    }
   };
}
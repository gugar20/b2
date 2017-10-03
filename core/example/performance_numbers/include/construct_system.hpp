
#pragma once

#include <bertini2/system.hpp>

template<typename NumType> using Vec = Eigen::Matrix<NumType, Eigen::Dynamic, 1>;
using dbl = bertini::dbl;
using mpfr = bertini::mpfr;

namespace demo{


	using Node = std::shared_ptr<bertini::node::Node>;
	using Variable = std::shared_ptr<bertini::node::Variable>;




	auto ConstructSystem1()
	{
		using bertini::MakeVariable;
        using bertini::MakeInteger;
        using bertini::MakeFloat;

	    auto x1 = MakeVariable("x1");
	    auto x2 = MakeVariable("x2");
	    auto x3 = MakeVariable("x3");
	    auto x4 = MakeVariable("x4");
        
        auto p1 = MakeFloat("3.2");
        auto p2 = MakeFloat("-2.8");
        auto p3 = bertini::MakeFloat("3.5");
        auto p4 = MakeFloat("-3.6");
        
        std::vector<Node> params{p1, p2, p3, p4};

	    auto f1 = pow(x1,3)*params[0] + x1*x1*x2*params[1] + x1*x2*x2*params[2] + x1*x3*x3*params[3] + x1*x4*x4*params[0]
	     + x1*params[1]+ x2*x2*x2*params[2] + x2*pow(x3,2)*params[3] + x2*x4*x4*params[0] + x2*params[1] + 1;
	     
	    auto f2 = x1*x1*x1*params[2] + x1*x1*x2*params[3] + x1*x2*x2*params[0] + x1*x3*x3*params[1] + x1*x4*x4*params[2]
	     + x1*params[3] + x2*x2*x2*params[0] + x2*x3*x3*params[1] + x2*x4*x4*params[2] + x2*params[3] - 1;
	     
	    auto f3 = x1*x1*x3*params[0] + x1*x2*x3*params[1] + x2*x2*x3*params[2] + x3*x3*x3*params[3] + x3*pow(x4,2)*params[0] + x3*params[1] + 2;

	    auto f4 = pow(x1,2)*x4*params[2] + x1*x2*x4*params[3] + x2*x2*x4*params[0] + x3*x3*x4*params[1] + x4*x4*x4*params[2] + x4*params[3] - 3;

	    // make an empty system
	    bertini::System Sys;

	    // add the functions.  we could elide the `auto` construction above and construct directly into the system if we wanted
	    Sys.AddFunction(f1);
	    Sys.AddFunction(f2);
	    Sys.AddFunction(f3);
	    Sys.AddFunction(f4);

	    // make an affine variable group
	    bertini::VariableGroup vg{x1, x2, x3, x4};
	    Sys.AddVariableGroup(vg);

	    return Sys;
	}



} // namespace demo


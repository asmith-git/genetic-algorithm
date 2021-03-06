//	Copyright 2017 Adam Smith
//	Licensed under the Apache License, Version 2.0 (the "License");
//	you may not use this file except in compliance with the License.
//	You may obtain a copy of the License at
// 
 //	http://www.apache.org/licenses/LICENSE-2.0
//
//	Unless required by applicable law or agreed to in writing, software
//	distributed under the License is distributed on an "AS IS" BASIS,
//	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//	See the License for the specific language governing permissions and
//	limitations under the License.
   
#ifndef ASMITH_GA_OPTIMISATION_PROBLEM_HPP
#define ASMITH_GA_OPTIMISATION_PROBLEM_HPP

#include <cstdint>
#include "base_genetic_algorithm.hpp"

namespace asmith {
	template<class T, class F>
	class optimisation_problem {
	public:
		typedef T input_t;
		typedef T output_t;
		
		virtual ~optimisation_problem() throw() {}
		virtual size_t get_dimensions() const throw() = 0;
		virtual base_genetic_algorithm::objective_mode get_objective_mode() const throw() = 0;
		virtual input_t get_minimum_bound(const size_t) const throw() = 0;
		virtual input_t get_maximum_bound(const size_t) const throw() = 0;
		virtual output_t operator()(const input_t* const) const throw() = 0;
	};
}

#endif
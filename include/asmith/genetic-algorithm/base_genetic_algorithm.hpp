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
   
#ifndef ASMITH_GA_BASE_GENETIC_ALGORITHM_HPP
#define ASMITH_GA_BASE_GENETIC_ALGORITHM_HPP

#include <cstdint>
namespace asmith {
	class base_genetic_algorithm {
	public:
		enum objective_mode : int8_t {
			MINIMISE_PROBLEM,
			MAXIMISE_PROBLEM
		};
	protected:
		virtual size_t get_initial_population_count() const throw() = 0;
		virtual size_t get_parent_count() const throw() = 0;
		virtual size_t get_child_count() const throw() = 0;
		virtual size_t get_survivor_count() const throw() = 0;
		
		virtual objective_mode get_objective_mode() const throw() = 0;

		virtual void epoch() throw() = 0;

		// Operators
		virtual bool termination_condition() const throw() = 0;
	public:
		virtual ~base_genetic_algorithm() throw() {}
	};
}
#endif
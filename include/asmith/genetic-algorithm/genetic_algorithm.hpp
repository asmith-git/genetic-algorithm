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

#ifndef ASMITH_BASE_GENETIC_ALGORITHM_HPP
#define ASMITH_BASE_GENETIC_ALGORITHM_HPP

#include "base_genetic_algorithm.hpp"

template<class GENOME>
class genetic_algorithm : public base_genetic_algorithm {
public:
	typedef GENOME genome_t;
private:
	protected:
	virtual genome_t* get_population() throw() = 0;
	virtual const genome_t* get_population() const throw() = 0;

	// Operators
	virtual void seed(genome_t&) const throw() = 0;
	virtual const genome_t& select_parent() throw() = 0;
	virtual void crossover(const genome_t* const, genome_t&) throw() const = 0;
	virtual float assess_fitness(const genome_t&) const throw() = 0;
	virtual const genome_t& select_survivor() throw() = 0;

	// Inherited from base_genetic_algorithm
	virtual void epoch() const throw() override {
		const size_t popC = get_population_count();
		const size_t parC = get_parent_count();
		const size_t chiC = get_child_count();
	}
public:
	virtual ~genetic_algorithm() throw() {}

};
  
  #endif
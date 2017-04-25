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

#include "genetic_algorithm.hpp"

template<class GENOTYPE>
class advanced_genetic_algorithm : public genetic_algorithm<GENOTYPE> {
protected:
	virtual uint64_t generate_random() const throw() {
		uint64_t tmp = rand();
		tmp <<= 32L;
		tmp |= rand();
		return tmp;
	}

	inline const genome_t& select_random(const genome_t* const aGenomes, const size_t aSize) const throw() {
		return aGenomes[generate_random() % aSize];
	}
public:
	advanced_genetic_algorithm() {
	
	}
	
	virtual ~advanced_genetic_algorithm() throw() {
	
	}
};
  
  #endif
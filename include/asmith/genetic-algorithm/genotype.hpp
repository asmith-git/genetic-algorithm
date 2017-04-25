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
   
#ifndef ASMITH_GENOTYPE_HPP
#define ASMITH_GENOTYPE_HPP

#include <cstdint>

template<class T, size_t S, class F = float>
struct genotype {
	typedef T gene_t;
	typedef F fitness_t;
	enum{ GENE_COUNT = S };
	
	gene_t genes[GENE_COUNT];
	fitness_t fitness;
	
	inline size_t get_gene_count() const throw() { return GENE_COUNT; }
	inline fitness_t get_fitness() const throw() { return fitness; }
	inline void set_fitness(const fitness_t aFitness) throw() { fitness = aFitness; }
	inline gene_t* get_genes() throw() { return genes; }
	inline const gene_t* get_genes() const throw() { return genes; }
};

#endif
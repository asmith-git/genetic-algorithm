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

	// Selection
	
	inline const genome_t& select_random(const genome_t* const aGenomes, const size_t aSize) const throw() {
		return aGenomes[generate_random() % aSize];
	}

	// Mutation
	
	void mutation_replacement(genome_t& aGenome, const uint8_t aChance, typename genome_t::gene_t aValue) const throw() {
		const size_t s = aGenome.get_gene_count();
		typename::genome_t::gene_t g* const = aGenome.get_genes();
		for(size_t i = 0; i < s; ++i) {
			if(generate_random() % 100 < aChance) g[i] = aValue;
		}
	}

	void mutation_perturbation(genome_t& aGenome, const uint8_t aChance, typename genome_t::gene_t aStep) const throw() {
		const size_t s = aGenome.get_gene_count();
		typename::genome_t::gene_t g* const = aGenome.get_genes();
		for(size_t i = 0; i < s; ++i) {
			if(generate_random() % 100 < aChance) g[i] += generate_random() % 100 < 50 ? -aStep : aStep;
		}
	}
	
	// Crossover
	
	void crossover_uniform(genome_t& aGenome, typename genome_t::gene_t aValue) const throw() {
		const size_t p = get_parent_count();
		const size_t s = aGenome.get_gene_count();
		typename::genome_t::gene_t g* const = aGenome.get_genes();
		const uint8_t increment = 100 / p;
		
		for(size_t i = 0; i < s; ++i) {
			uint8_t chance = generate_random() % 100;
			for(size_t j = 0; j < p; ++j) {
				if(chance <= increment) {
					g[i] = mParents[j].get_genes()[i];
					break;
				}else {
					chance -= increment;
				}
			}
		}
	}
	
public:
	advanced_genetic_algorithm() {
	
	}
	
	virtual ~advanced_genetic_algorithm() throw() {
	
	}
};
  
  #endif
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

#ifndef ASMITH_GA_ADV_GENETIC_ALGORITHM_HPP
#define ASMITH_GA_ADV_GENETIC_ALGORITHM_HPP

#include <random>
#include "genetic_algorithm.hpp"

namespace asmith {
	template<class GENOTYPE>
	class advanced_genetic_algorithm : public genetic_algorithm<GENOTYPE> {
	public:
		enum { MAX_PARENTS = 128 };
	protected:
		virtual int generate_random() const throw() {
			static std::mt19937 RNG;
			static std::uniform_int_distribution<std::mt19937::result_type> DISTRIBUTION(0,std::numeric_limits<int>::max());
			static bool ONCE = true;
			if(ONCE) {
				ONCE = false;
				RNG.seed(std::random_device()());
			}
			return DISTRIBUTION(RNG);
		}

		// Selection
		
		inline const genotype_t& select_random(const genotype_t* const aGenomes, const size_t aSize) const throw() {
			return aGenomes[generate_random() % aSize];
		}

		// Mutation
		
		void mutation_replacement(genotype_t& aGenome, const uint8_t aChance, typename genotype_t::gene_t aValue) const throw() {
			const size_t s = aGenome.get_gene_count();
			typename::genotype_t::gene_t g* const = aGenome.get_genes();
			for(size_t i = 0; i < s; ++i) {
				if(generate_random() % 100 < aChance) g[i] = aValue;
			}
		}

		void mutation_perturbation(genotype_t& aGenome, const uint8_t aChance, typename genotype_t::gene_t aStep) const throw() {
			const size_t s = aGenome.get_gene_count();
			typename::genotype_t::gene_t g* const = aGenome.get_genes();
			for(size_t i = 0; i < s; ++i) {
				if(generate_random() % 100 < aChance) g[i] += generate_random() % 100 < 50 ? -aStep : aStep;
			}
		}
		
		// Crossover
		
		void crossover_uniform(genotype_t& aGenome, typename genotype_t::gene_t aValue) const throw() {
			const size_t p = get_parent_count();
			const size_t s = aGenome.get_gene_count();
			typename::genotype_t::gene_t g* const = aGenome.get_genes();
			const uint8_t increment = 100 / p;
			
			for(size_t i = 0; i < s; ++i) {
				uint8_t chance = generate_random() % 100;
				for(size_t j = 0; j < p; ++j) {
					if(chance <= increment) {
						g[i] = mParents[j]->get_genes()[i];
						break;
					}else {
						chance -= increment;
					}
				}
			}
		}
		
		void crossover_single_point(genotype_t& aGenome, typename genotype_t::gene_t aValue) const throw() {
			uint16_t points[MAX_PARENTS];
			uint16_t order[MAX_PARENTS];
			
			const size_t p = get_parent_count();
			const size_t s = aGenome.get_gene_count();
			typename::genotype_t::gene_t g* = aGenome.get_genes();
				
			// Calculate order
			for(uint16_t i = 0; i < p; ++i) order[i] {
				bool repeat = true;
				size_t j = 0;
				while(repeat) {
					repeat = false;
					j = generate_random() % p;
					for(uint16_t k = 0; k < i; ++k) {
						if(j == order[k]) {
							repeat = true;
							break;
						}
					}
				}
				order[i] = j;
			}
			
			// Crossover;
			const size_t block = s / p;
			size_t offset = 0;
			for(size_t i = 1; i < p; ++i) {
				memccpy(g + offset ,mParents[order[i]]=>get_genes() + offset, block);
				offset += block;
			}
		}
		
	public:
		advanced_genetic_algorithm() {
		
		}
		
		virtual ~advanced_genetic_algorithm() throw() {
		
		}
	};
}
#endif
	  
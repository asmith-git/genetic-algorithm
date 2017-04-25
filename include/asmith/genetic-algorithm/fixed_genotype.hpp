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
   
#ifndef ASMITH_GA_FIXED_GENOTYPE_HPP
#define ASMITH_GA_FIXED_GENOTYPE_HPP

#include "genotype.hpp"

namespace asmith {
	template<class T, size_t S, class F = float>
	class fixed_genotype : public genotype<T,F> {
	public:
		enum{ GENE_COUNT = S };
	private:
		gene_t mGenes[GENE_COUNT];
		fitness_t mFitness;
	public:
		// Inherited from genotype
		size_t get_gene_count() const throw() override { return GENE_COUNT; }
		fitness_t get_fitness() const throw() override { return mFitness; }
		void set_fitness(const fitness_t aFitness) throw()  override { mFitness = aFitness; }
		gene_t* get_genes() throw() override { return mGenes; }
		const gene_t* get_genes() const throw() override { return mGenes; }
	};
}

#endif
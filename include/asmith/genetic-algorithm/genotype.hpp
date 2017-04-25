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
   
#ifndef ASMITH_GA_GENOTYPE_HPP
#define ASMITH_GA_GENOTYPE_HPP

#include <cstdint>

namespace asmith {
	template<class T, class F>
	class genotype {
	public:
		typedef T gene_t;
		typedef F fitness_t;
		
		virtual ~genotype() throw() {}
		virtual size_t get_gene_count() const throw() = 0;
		virtual fitness_t get_fitness() const throw() = 0;
		virtual void set_fitness(const fitness_t aFitness) throw() = 0;
		virtual gene_t* get_genes() throw() = 0;
		virtual const gene_t* get_genes() const throw() = 0;
	};
}

#endif
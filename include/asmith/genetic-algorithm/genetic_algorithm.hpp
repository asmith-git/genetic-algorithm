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

#ifndef ASMITH_GA_GENETIC_ALGORITHM_HPP
#define ASMITH_GA_GENETIC_ALGORITHM_HPP

#include "base_genetic_algorithm.hpp"

namespace asmith {
	template<class GENOTYPE>
	class genetic_algorithm : public base_genetic_algorithm {
	public:
		typedef GENOTYPE genotype_t;
	private:
		size_t mParentsSize;
		size_t mChildrenSize;
		size_t mSurvivorsSize;
		size_t mPopulationSize;
	protected:
		genotype_t mMin;
		genotype_t mMax;
		const genotype_t** mParents;
		genotype_t* mChildren;
		genotype_t* mSurvivors;
		genotype_t* mPopulation;
		size_t mEpochs;
		size_t mParentsSelected;
		size_t mSurvivorsSelected;
	private:
		template<class T>
		static bool reallocate_buffer(T*& aBuffer, size_t& aOldSize, const size_t aNewSize) {
			if(! aBuffer) {
				aBuffer = new T[aNewSize];
				aOldSize = aNewSize;
				return true;
			}else if(aOldSize < aNewSize) {
				delete[] aBuffer;
				aBuffer = new T[aNewSize];
				aOldSize = aNewSize;
				return true;
			}
			return false;
		}
	protected:
		// Operators
		virtual void seed(genotype_t&) const throw() = 0;
		virtual const genotype_t& select_parent() const throw() = 0;
		virtual void crossover(genotype_t&) const throw() = 0;
		virtual void mutate(genotype_t&) const throw() = 0;
		virtual typename genotype_t::fitness_t assess_fitness(const genotype_t&) const throw() = 0;
		virtual const genotype_t& select_survivor() throw() = 0;

		// Inherited from base_genetic_algorithm
		virtual void epoch() throw() override {
			const size_t parC = get_parent_count();
			const size_t chiC = get_child_count();
			const size_t surC = get_survivor_count();
			
			// Allocate memory for parent and child storage
			reallocate_buffer<const genotype_t*>(mParents, mParentsSize, parC);
			reallocate_buffer<genotype_t>(mChildren, mChildrenSize, chiC);
			
			// Generate children
			for(size_t i = 0; i < chiC; ++i) {
				for(mParentsSelected = 0; mParentsSelected < parC; ++mParentsSelected) {
					mParents[mParentsSelected] = &select_parent();
				}
				genotype_t& c = mChildren[i];
				crossover(c);
				mutate(c);
				const typename genotype_t::fitness_t f = assess_fitness(c);
				c.set_fitness(f);
				if(f < mMin.get_fitness()) mMin = c;
				else if(f > mMin.get_fitness()) mMax = c;
			}
			
			// Select survivors
			reallocate_buffer<genotype_t>(mSurvivors, mSurvivorsSize, surC);
			for(mSurvivorsSelected = 0; mSurvivorsSelected < surC; ++mSurvivorsSelected) {
				mSurvivors[mSurvivorsSelected] = select_survivor();
			}
			std::swap(mPopulation, mSurvivors);
			std::swap(mPopulationSize, mSurvivorsSize);
		}
	public:
		genetic_algorithm() :
			mParentsSize(0),
			mChildrenSize(0),
			mSurvivorsSize(0),
			mPopulationSize(0),
			mParents(nullptr),
			mChildren(nullptr),
			mSurvivors(nullptr),
			mPopulation(nullptr),
			mEpochs(0),
			mParentsSelected(0),
			mSurvivorsSelected(0)
		{}
		
		virtual ~genetic_algorithm() throw() {
			if(mParents) delete[] mParents;
			if(mChildren) delete[] mChildren;
			if(mSurvivors) delete[] mSurvivors;
			if(mPopulation) delete[] mPopulation;
		}

		virtual genotype_t operator()() throw() {
			mEpochs = 0;
			mMin.set_fitness(std::numeric_limits<genotype_t::fitness_t>::max());
			mMax.set_fitness(std::numeric_limits<genotype_t::fitness_t>::min());
			
			// Seed population
			reallocate_buffer(mPopulation, mPopulationSize, get_initial_population_count());
			const size_t popC = mPopulationSize;
			for(size_t i = 0; i < popC; ++i) {
				genotype_t& c = mPopulation[i];
				seed(c);
				const typename genotype_t::fitness_t f = assess_fitness(c);
				c.set_fitness(f);
				if(f < mMin.get_fitness()) mMin = c;
				else if(f > mMin.get_fitness()) mMax = c;
			}
			
			// Run epochs
			while(! termination_condition()) {
				epoch();
				++mEpochs;
			}
			
			return get_objective_mode() == MINIMISE_PROBLEM ? mMin : mMax;
		}
	};
}  
#endif
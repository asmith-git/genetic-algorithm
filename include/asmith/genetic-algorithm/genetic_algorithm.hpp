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

template<class GENOME, class FITNESS = float>
class genetic_algorithm : public base_genetic_algorithm {
public:
	typedef GENOME genome_t;
	typedef FITNESS fitness_t;
private:
	size_t mParentsSize;
	size_t mChildrenSize;
	size_t mSurvivorsSize;
	size_t mPopulationSize;
protected:
	genome_t* mParents;
	genome_t* mChildren;
	genome_t* mSurvivors;
	genome_t* mPopulation;
	size_t mEpochs;
private:
	static bool reallocate_buffer(genome_t*& aBuffer, size_t& aOldSize, const size_t aNewSize) {
		if(! aBuffer) {
			aBuffer = new genome_t[aNewSize];
			aOldSize = aNewSize;
			return true;
		}else if(mChildrenSize < chiC) {
			delete[] aBuffer;
			aBuffer = new genome_t[aNewSize];
			aOldSize = aNewSize;
			return true;
		}
		return false;
	}
protected:
	// Operators
	virtual void seed(genome_t&) const throw() = 0;
	virtual const genome_t& select_parent() const throw() = 0;
	virtual void crossover(const genome_t* const, genome_t&) throw() const = 0;
	virtual fitness_t assess_fitness(const genome_t&) const throw() = 0;
	virtual const genome_t& select_survivor() throw() = 0;

	// Inherited from base_genetic_algorithm
	virtual void epoch() const throw() override {
		const size_t parC = get_parent_count();
		const size_t chiC = get_child_count();
		const size_t surC = get_survivor_count();
		
		// Allocate memory for parent and child storage
		reallocate_buffer(mParents, mParentsSize, parC);
		reallocate_buffer(mChildren, mChildrenSize, chiC);
		
		// Generate children
		for(size_t i = 0; i < chiC; ++i) {
			for(size_t j = 0; j < parC; ++j) mParents[j] = select_parent();
			crossover(mParents, mChildren[i]);
			mutate(mChildren[i]);
		}
		
		// Select survivors
		reallocate_buffer(mSurvivors, mSurvivorsSize, surC);
		for(size_t i = 0; i < surC; ++i) {
			mSurvivors[i] = select_survivor();
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
		mPopulation(nullptr)
		mEpochs(0)
	{}
	
	virtual ~genetic_algorithm() throw() {
		if(mParents) delete[] mParents;
		if(mChildren) delete[] mChildren;
		if(mSurvivors) delete[] mSurvivors;
		if(mPopulation) delete[] mPopulation;
	}

	virtual void operator()() throw() {
		mEpochs = 0;
		
		// Seed population
		reallocate_buffer(mPopulation, mPopulationSize, get_population_count());
		const size_t popC = mPopulationSize;
		for(size_t i = 0; i < popC; ++i) {
			seed(pop[i]);
		}
		
		// Run epochs
		while(! termination_condition()) {
			epoch();
			++mEpochs;
		}
	}
};
  
  #endif
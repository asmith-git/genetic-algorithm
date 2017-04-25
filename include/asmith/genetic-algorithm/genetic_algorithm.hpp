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
	size_t mParentsSize;
	size_t mChildrenSize;
	size_t mSurvivorsSize;
protected:
	genome_t* mParents;
	genome_t* mChildren;
	genome_t* mSurvivors;
protected:
	virtual genome_t* get_population() throw() = 0;
	virtual const genome_t* get_population() const throw() = 0;

	// Operators
	virtual void seed(genome_t&) const throw() = 0;
	virtual const genome_t& select_parent() const throw() = 0;
	virtual void crossover(const genome_t* const, genome_t&) throw() const = 0;
	virtual float assess_fitness(const genome_t&) const throw() = 0;
	virtual const genome_t& select_survivor() throw() = 0;

	// Inherited from base_genetic_algorithm
	virtual void epoch() const throw() override {
		const size_t popC = get_population_count();
		const size_t parC = get_parent_count();
		const size_t chiC = get_child_count();
		const size_t surC = get_survivor_count();
		
		// Allocate memory for parent storage
		if(! mParents) {
			mParents = new genome_t[parC];
			mParentsSize = parC;
			mParentsSize = parC;
		}else if(mParentsSize < parC) {
			delete[] mParents;
			mParents = new genome_t[parC];
			mParentsSize = parC;
		}
		
		// Allocate memory for child storage
		if(! mChildren) {
			mChildren = new genome_t[chiC];
		}else if(mChildrenSize < chiC) {
			delete[] mChildrenSize;
			mChildren = new genome_t[chiC];
			mChildrenSize = chiC;
		}
		
		// Allocate memory for survivor storage
		if(! mSurvivors) {
			mSurvivors = new genome_t[surC];
		}else if(mSurvivorsSize < surC) {
			delete[] mSurvivorsSize;
			mSurvivors = new genome_t[surC];
			mSurvivorsSize = surC;
		}
		
		// Generate children
		for(size_t i = 0; i < chiC; ++i) {
			for(size_t j = 0; j < parC; ++j) mParents[j] = select_parent();
			crossover(mParents, mChildren[i]);
			mutate(mChildren[i]);
		}
		
		// Select survivors
		for(size_t i = 0; i < surC; ++i) {
			mSurvivors[i] = select_survivor();
		}
	}
public:
	genetic_algorithm() :
		mParentsSize(0),
		mChildrenSize(0),
		mSurvivorsSize(0),
		mParents(nullptr),
		mChildren(nullptr),
		mSurvivors(nullptr)
	{}
	
	virtual ~genetic_algorithm() throw() {
		if(mParents) delete[] mParents;
		if(mChildren) delete[] mChildren;
		if(mSurvivors) delete[] mSurvivors;
	}

};
  
  #endif
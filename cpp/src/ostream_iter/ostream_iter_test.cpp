/****************************************************************************/
/*	Project:																*/
/*	File:		ostream_iter.cpp											*/
/*	Date: 		28/09/2022													*/
/*	Name: 		Boaz Faitelson												*/
/*	Reviewer:																*/
/*	Version: 	1.00														*/
/****************************************************************************/
#include <cassert>

#include <iostream> 

#include "complexes.hpp" 	// class Complex
#include "ostream_iter.hpp"
/****************************************************************************/
int main()
{
	ilrd::OstreamIter<int> iter(std::cout);

	int nums[] = {1, 2, 3, 4};
	
	std::copy(&nums[0], &nums[4], iter);

	ilrd::Complex complexArr[4];
	ilrd::Complex complexNum(1,2);
	complexArr[0] = complexNum;

	for (size_t i = 0; i < 4; ++i)
	{
		complexArr[i + 1] = complexArr[i] + complexNum;
	}

	ilrd::OstreamIter<ilrd::Complex> compIter(std::cout);	

	std::copy(&complexArr[0], &complexArr[4], compIter);

	return 0;
}

/*******************************Function Definitions*************************/

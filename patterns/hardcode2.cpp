#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

void threadFunction(int i) {
	// do complex calculations
}

void main3() {
	std::vector<std::thread> vHardcodedAmountThreads;
	std::vector<std::thread> vMaxAmountThreads;

	// hard coded example:
	for (int i = 0; i < 10; ++i) { 
		vHardcodedAmountThreads.emplace_back(threadFunction, i);
	}

	// max amount example:
	unsigned int nthreads = std::thread::hardware_concurrency();
	for (int i = 0; i < nthreads; ++i) { 
		vMaxAmountThreads.emplace_back(threadFunction, i);
	}

	// join threads
	for (auto& t : vHardcodedAmountThreads) {t.join();}
	for (auto& t : vMaxAmountThreads) { t.join(); }
}


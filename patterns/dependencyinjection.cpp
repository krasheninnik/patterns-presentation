#include <string>
#include <iostream>
#include <fstream>

class ILogger { public: virtual void log(std::string msg) {}; };

class CliLogger: public ILogger {
public:	void log(std::string msg) {	std::cout << msg << std::endl; }
};

class FileLogger : public ILogger {
public:
	FileLogger() { fileStream = std::ofstream("uniqueLogName.txt"); }
	void log(std::string msg) {	fileStream << msg << std::endl; }
private:
	std::ofstream fileStream;
};

class Solver {
public:
	Solver(ILogger* _logger) { logger = _logger; }

	void solveProblem() {
		logger->log("Initialization");
		// init solver
		logger->log("Solve");
		// solve system
		logger->log("Save result");
		// save result
	}

private:
	ILogger* logger;
};

void main1() {
	Solver s = Solver(new FileLogger());
	s.solveProblem();
}





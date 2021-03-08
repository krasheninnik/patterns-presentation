#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <thread>
#include <cstdlib>

class WelcomeHardCode {
public: 
	void great() {
		std::cout << "Hello world!" << std::endl;
	}
};

class WelcomeEnv {
public: 
	WelcomeEnv() {
		const char* env_p = std::getenv("WelcomeString");
		greatPhrase = env_p ? env_p : "Hello world!";
	}

	void great() {
		std::cout << greatPhrase << std::endl;
	}

private: 
	std::string greatPhrase;
};


void main4() {
	WelcomeHardCode whd = WelcomeHardCode();
	WelcomeEnv wenv = WelcomeEnv();
	whd.great();
	wenv.great();
}



#ifndef _BRUTE_HPP_
#define _BRUTE_HPP_

#include <fstream>
#include <iostream>
#include <string>

#include "key.hpp"

class Brute {
private:
	std::vector<Key> T;

public:
	Brute(const std::string&);
	void perm(std::string prefix, int n, int k, Key key);	
	
	void decrypt(const std::string&);
	std::string intToBitString(long x, int pad);
};

#endif

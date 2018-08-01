#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

#include "key.hpp"
#include "brute.hpp"

std::string me;
std::string encrypted;
std::string table_filename;
bool verbose = false;

Brute::Brute(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
}



void Brute::perm(std::string prefix, int n, int k, Key key){
	
	if (k == 0) {
		Key ssum;
		//std::cout << "in" << "\n";
		Key passkey = Key(prefix);
		//std::cout << "in1" << "\n";
		ssum = passkey.subset_sum(T,verbose);
		//std::cout << "in2" << "\n";
		//Key key = Key(encrypted);
		//std::cout << "in3" << "\n";
		if(ssum == key){
			std::cout << prefix << "\n";
			return;
		}
		return;
		
	}
	         // std::cout << "in4" << "\n";
	for(int i = 0; i < n; ++i){
		//std::cout << "in5" << "\n";
		std::string news = prefix + ALPHABET[i];
		//std::cout << "in6" << "\n";
		perm(news,n,k-1,key);
		//std::cout << "in7" << "\n";
	}
}

void Brute::decrypt(const std::string& encrypted){
	Key key = Key(encrypted);
	perm("",32,C,key);
	// your code here
 	//int length = C;
 	//int bitlen = N;
 	//std::string finalstr = "";
 	//Key ssum;
 	//Key ssum2;

	/*
 	//std::cout << "2^n " << pow(2,N) << '\n';
 	for (long i = 0; i < pow(2,N); i++) {
		std::string test = intToBitString(i,N);
     		finalstr = "";
     		//	std::cout << test << '\n';
     		for(long j = 0; j < N ; j+=5){
      	
     		std::string nums = test.substr(j,5); //5 bit substring
        	//std::cout << "j " << j << '\n';
        	//std::cout << "i " << i << '\n';
      		//std::cout << "nums " << nums << '\n';
        	int bin = std::stoi(nums,nullptr,2); //bit string to number
      		//std::cout << "bin " << bin << '\n';
      		char character = ALPHABET[bin]; //from binary number to a character
      		//std::cout << "character " << character << '\n';
      		finalstr+= character;//build a word
      	
   		 }	
    	// std::cout << "final string " << finalstr << '\n';
     */
     	//Key key = Key(finalstr);
     	//Key key2 = Key(encrypted);
     
     	//ssum = key.subset_sum(T,verbose);
     	//ssum2 = key2.subset_sum(T,verbose);

     	//if(ssum == key2){
     	//	std::cout << finalstr << '\n';
    	// }	
     //ssum.show();
     //ssum2.show();
  	// }
}
/*
std::string Brute::intToBitString(long x, int pad){
 
 std::string str = "";
 while(x){
 	if(x&1)
  		str+= '1';
  	else
   		str+= '0';
  	x>>=1;
 }
  
  while(str.length() < pad){
   str+='0';
  }
  std::reverse(str.begin(), str.end());
  return str;
}
*/
void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Brute force cracking of Subset-sum password with " 
		<< B << " bits precision\n"
	    << "USAGE: " << me << " <encrypted> <table file> [options]\n"
		<< "\nArguments:\n"
		<< " <encrypted>:   encrypted password to crack\n"
		<< " <table file>:  name of file containing the table to use\n"
		<< "\nOptions:\n"
		<< " -h|--help:     print this message\n"
		<< " -v|--verbose:  select verbose mode\n\n";
	exit(0);
}

void initialize(int argc, char* argv[]) {
	me = argv[0];
	if (argc < 3) usage("Missing arguments");
	encrypted = argv[1];
	table_filename = argv[2];
	for (int i=3; i<argc; ++i) {
		std::string arg = argv[i];
		if (arg == "-h" || arg == "--help") usage();
		else if (arg == "-v" || arg == "--verbose") verbose = true;
		else usage("Unrecognized argument: " + arg);
	}
}


int main(int argc, char *argv[]){
	

	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	    	//std::cout << "bef" << "\n";
	initialize(argc, argv);
	//std::cout << "main" << "\n"; 
	Brute b(table_filename);
	b.decrypt(encrypted);
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;		 	 		     	
	std::cout << "elapsed time: " << elapsed_seconds.count();
	
				 	 		     	 			
	return 0;
}

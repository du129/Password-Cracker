#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include "key.hpp"
#include "symbol.hpp"

std::string me;
std::string encrypted;
std::string table_filename;

std::map<Key,std::string> map;
bool verbose = false;
int count = 0;
Symbol::Symbol(const std::string& filename) {
	T.resize(N);
	std::string buffer;
    std::fstream input(filename.c_str(), std::ios::in);
    for (int i = 0; i < N; i++) {
        std::getline(input, buffer);
        T[i].set_string(buffer);
    }
    input.close();
	
    //std::map<Key,std::string> map;
	// insert your code here
}

void Symbol::perm(std::string prefix, int n, int k, Key key){
	if(k==0){
		Key ssum;
		
		int a = C/2;
		if(C % 2 != 0)a++;
		for(int i = 0; i < a ; i++){
			prefix += "a";
		}
		
		Key passkey((std::string(prefix)));
		ssum = passkey.subset_sum(T,verbose);

		map.insert(std::pair<Key,std::string>(ssum,prefix));
		count++;
		//std::cout<<count <<'\n';
		//std::cout<< prefix << "\n";
		return;
	}
	for(int i = 0; i < n ; ++i){
		std::string news = prefix + ALPHABET[i];
		perm(news,n,k-1,key);
	}
}
void Symbol::back(std::string prefix, int n, int k, Key key){
	//std::cout<<"here\n";
	if(k == 0){
		
		int a = C/2;
		
		//std::cout << C/2;

		std::string as = "";

		for(int i = 0; i < a  ; i++){
			as += "a";
		//	std::cout<<as<<'\n';
		}
		as += prefix;
		
		prefix = as;
		//std::cout<<prefix <<'\n';

		Key prefkey((std::string(prefix)));
	//	std::map<Key,std::string>::iterator it;
		//std::cout << prefix << "\n";
//		Key result = key - prefkey;
		Key begin = prefkey.subset_sum(T,verbose);
		//std::cout<<begin.tostring()<<'\n';
		Key first = key;
		first -= begin;
		
		//std::cout<<first.tostring()<<'\n';

		std::map<Key,std::string>::iterator it = map.find(first);
		if(it != map.end()){
			std::string funec = map.find(first)->second;
			Key kfunec = Key(funec);

			kfunec += prefkey;
			std::string result = kfunec.tostring();
			std::cout << result << '\n';
		}
		//std::cout<<map.size() << '\n';
		return;
	}
	for(int i = 0; i < n ; ++i){
		std::string news = prefix + ALPHABET[i];
		back(news,n,k-1,key);
	}
}


void Symbol::decrypt(const std::string& encrypted){
	Key key((std::string(encrypted)));
	int k = C/2;
	perm("",32,k,key);
	if(C % 2 != 0){
		back("",32,k+1,key);
	}else{
		back("",32,k,key);
	}
		
/*	
	Key key = Key("vvg5kr");
	Key key2 = Key("aaa5kr");
	key.show();
	key2.show();
	key -= key2;
	key.show();
	key += key2;
	key.show();
*/	
}

void usage(const std::string& error_msg="") {
	if (!error_msg.empty()) std::cout << "ERROR: " << error_msg << '\n';
	std::cout << me << ": Symbol table-based cracking of Subset-sum password"
		<< " with " << B << " bits precision\n"
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

	initialize(argc, argv);
	Symbol d(table_filename);
	d.decrypt(encrypted);
	// insert your code here
	end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end-start;               
	std::cout << "elapsed time: " << elapsed_seconds.count();

	return 0;
}

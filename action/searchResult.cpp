#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
 
using namespace std;

template <typename A, typename B>
multimap<B, A> flip_map(map<A,B> & src) {

    multimap<B,A> dst;

    for(typename map<A, B>::const_iterator it = src.begin(); it != src.end(); ++it)
        dst.insert(pair<B, A>(it -> second, it -> first));

    return dst;
}

int main(int argc, char* argv[])
{
	if(argc < 3) {
		cerr << "Please Enter the File Name." << endl;
		return -1;
	}
	
	ifstream ifs(argv[1]);
	if(!ifs.is_open()) {
		cerr << "ERROR: FILE OPEN FAILED." << endl;
		return -1;
	}
	
	string str = "";
	map<int,int> index_vc; 
	map<int,int> ptxt_vc;
	while(ifs >> str) {
		istringstream iss(str);
		int v;
		while(iss >> v) {
			int ind = 0;
			ptxt_vc[v]++;
			if(1<= v && v <=12)
				ind = 1;
			else if(13<=v && v<=21)
				ind = 2;
			else if(22<=v && v<=29)
				ind = 3;	
			else if(30<=v && v<=36)	
				ind = 4;
			else if(37<=v && v<=51)
				ind = 5;
			else if(52<=v && v<=61)
				ind = 6;
			else if(62<=v && v<=66)
				ind = 7;
			else if(67<=v && v<=74)
				ind = 8;	
			else if(75<=v && v<=85)
				ind = 9;
			else if(86<=v && v<=99)
				ind = 10;						
			index_vc[ind]++;
		}
	}
	ifs.close();
	
	multimap<int, int> dst1 = flip_map(index_vc);
	multimap<int, int> dst2 = flip_map(ptxt_vc);
	
	ofstream ofs1(argv[2]);
	int cnt = 0;
	for(auto it = dst1.rbegin(); it != dst1.rend(); it++){
		if(cnt < 5) {
			ofs1 << it->second << "\n";
			cnt++;
		}
	}	
	ofs1.close();
	
	ofstream ofs2("ptxt.txt");
	ofs2 << dst2.rbegin()->second <<".ptxt" << endl;
	ofs2.close();
	return 0;
}

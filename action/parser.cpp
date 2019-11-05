#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3) {
		cerr << "Please enter the file names" << endl;
		return -1;
	}
	
	ifstream ifs(argv[1]);
	if(!ifs.is_open()) {
		cerr << "ERROR: CANNOT READ FILE\n" << endl;
		return -1;
	}
	string res ="";		
	string str, comp="명사", pronoun = "대명사";
	int line = 0;
	string::iterator s, e, sep; 
	while(getline(ifs,str)) {
		if(line%3==1) {
			s = str.begin();
			e = find(s,str.end(),'+');
			while((sep = find(s,e,'/'))!= str.end()) {
				string noun = string(sep+1,e);
				const char* p = noun.data();
				if(strstr(p,comp.data()) && strstr(p,pronoun.data())==NULL) {
					string add = str.substr(s-str.begin(),sep-s);
					int n;
					n = add.find_first_not_of("\t\v\n");
					if ( n != string::npos )
					add.replace(0, n,"");
					n = add.find_last_not_of("\t\v\n");
					if ( n != string::npos )
					add.replace(n+1, add.length()-n,"");
					res+= add;
					res+="|";
				}
				s = e+1;
				e = find(s,str.end(),'+');
			}
		}
		++line;
	}
	ifs.close();
	
	ofstream ofs(argv[2]);
	ofs << res;
	ofs.close();
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

#define MOD 1000000007
#define PB push_back
#define INS insert
#define MP make_pair
#define LL long long int
#define II int
#define SS string
#define sortArray(n) sort(begin(n), end(n))
#define sortVector(n) sort(n.begin(), n.end()) 

#define TRACE
#ifdef TRACE
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
	template <typename Arg1>
	void __f(const char* name, Arg1&& arg1){
		cerr << name << " : " << arg1 << std::endl;
	}
	template <typename Arg1, typename... Args>
	void __f(const char* names, Arg1&& arg1, Args&&... args){
		const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1<<" | ";__f(comma+1, args...);
	}
#else
#define trace(...)
#endif

LL offset=0;



vector<vector<string> > readFiles(II isz, string fileName){
	vector<vector<string> > ret;
	vector<string> temp;
	string line;
	ifstream myfile (fileName);
	myfile.seekg(offset);
	trace(offset);
	if (myfile.is_open()){
		while (getline (myfile,line)){
			offset += line.length()+1;
			char sub[100];
			std::strcpy(sub, line.c_str());
			char *br = strtok(sub,",");
			temp.clear();
			while(br != NULL){
				string str(br);
				temp.PB(br);br = strtok(NULL," ");
			}
			ret.PB(temp);
			if(ret.size() ==  isz) {
				myfile.close();
				return ret;
			}
		}
		myfile.close();
	}
	return ret;
}	

void init(){
	offset = 0;
}
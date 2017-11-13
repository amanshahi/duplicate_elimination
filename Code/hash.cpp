#include <bits/stdc++.h>
#include "readFiles.h"


using namespace std;

#define MOD 1000000007
#define MOD2 1000003
#define PB push_back
#define INS insert
#define MP make_pair
#define LL long long int
#define II int
#define SS string
#define sortArray(n) sort(begin(n), end(n))
#define sortVector(n) sort(n.begin(), n.end()) 

II a[100002];

vector<vector<string> > toHash;
vector<vector<pair<string,II> > > finalHash;
vector<pair<string,II> > st;
vector<string> toFlush;
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
	
II findInSet(set<II> setname, II element){
	if(setname.find(element) != setname.end()) return 1;
	return 0;
}

II findInVector(vector<II> vectorname, II element){
	if(find(vectorname.begin(), vectorname.end(), element) != vectorname.end()) return 1;
	return 0;
}

II findInMap(map<II,II> mapname, II element){
	if(mapname.find(element) != mapname.end()) return 1;
	return 0;
}

II printVector(vector<II> vectorname){
    for(auto j: vectorname){
        cout << j << " ";
    }
    cout << endl;
}


II printSet(set<II> setname){
    for(auto j: setname){
        cout << j << " ";
    }
    cout << endl;
}


II printMap(map<II,II> mapname){
    for(auto j: mapname){
        cout << j.first << " " << j.second << endl;
    }
}

II printPairVector(vector<pair<II,II> > vectorname){
    for(auto j:vectorname){
        cout << j.first << " " << j.second << endl;
    }
}


LL XpowerY(LL x, LL y, LL m){
	LL ans=1;
	x=x%m;
	while(y>0){
		if(y%2==1)
			ans=(ans*x)%m;
		x=((x%m)*(x%m))%m;
		y=y>>1;
	}
	return ans%m;
}

II getLines(){
	ifstream myfile ("data.txt");
	string line;
	getline(myfile,line);
	vector<string> temp;
	char sub[100];
	std::strcpy(sub, line.c_str());
	char *br = strtok(sub," ");
	temp.clear();
	while(br != NULL){
		string str(br);
		temp.PB(br);br = strtok(NULL," ");
	}
	return temp.size();
}

II check(II temp, string s, II index){
	II fl=0;
	for(II i=0;i<finalHash[temp].size();i++){
		if(finalHash[temp][i].first == s) {fl=1;break;}
	}
	if(fl == 0) finalHash[temp].PB(MP(s,index));
	return fl;
}

II calcuateHash(string s){
	LL ans=0,temp=1,x=s.length();
	reverse(s.begin(), s.end());
	for(II i=0;i<x;i++){
		if(s[i] >= '0' && s[i] <= '9') {
			ans = (ans + (s[i]-'0')*temp)%MOD2;
			temp=(temp*13)%MOD2;
		}
	}
	reverse(s.begin(), s.end());
	return ans%MOD2;
}

II main(II argc, char * argv[]){
	if(argc == 2){
		II sz=getLines();
		ofstream myfile;
		myfile.open ("out1.txt");
		II totalLines = 0, isz=(atoi(argv[1])-1)*(262144/sz), osz=(262144/sz);
		for(II i=0;i<1000037;i++) finalHash.PB(st);
		while(1){
			toHash = readFiles(isz);
			if(toHash.size() == 0) break;
			for(II i=0;i<toHash.size();i++){
				string s=toHash[i][0];
				for(II k=1;k<toHash[i].size();k++) {
					for(II j=0;j<3-(int)toHash[i][k].length();j++) {s+="0";}
					s+=toHash[i][k];
				}
				LL temp = calcuateHash(s);
				if(check(temp, s, i) == 0){
					string ss="";
					for(II j=0;j<toHash[i].size();j++) {ss+=toHash[i][j]; ss+=" ";}
		            toFlush.PB(ss);
					totalLines++;
					if(toFlush.size() == osz){
						for(II k=0;k<toFlush.size();k++) myfile << toFlush[k] << endl;
						toFlush.clear();
					}
				}
			}
		}
		for(II k=0;k<toFlush.size();k++) myfile << toFlush[k] << endl;
		toFlush.clear();
	    myfile.close();
		cout << "TotalLines : " << totalLines << endl;
	}
	else{
		cout << "Some error occurred!\n";
	}
	return 0;
}	
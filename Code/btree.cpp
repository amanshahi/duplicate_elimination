#include <bits/stdc++.h>
#include "readFiles.h"

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

II a[100002];
II totalLines = 0;

vector<vector<string> > toHash;
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
class BTreeNode{
    LL *keys;
    LL t;
    BTreeNode **C;
    LL n;
    bool leaf;
    public:
        BTreeNode(LL _t, bool _leaf);   
        II insertNonFull(LL k);
        II splitChild(LL i, BTreeNode *y);
        II traverse();
        BTreeNode *search(LL k);
    friend class BTree;
};
class BTree{
    BTreeNode *root;
    LL t;  
    public:
        BTree(LL _t){root = NULL;t = _t;}
        II traverse()
        {if (root != NULL) root->traverse();}
        BTreeNode* search(LL k)
        {  return (root == NULL)? NULL : root->search(k); }
        II insert(LL k);
};
BTreeNode::BTreeNode(LL t1, bool leaf1){
    t = t1;
    leaf = leaf1;
    keys = new LL[2*t-1];
    C = new BTreeNode *[2*t];
    for(II i=0;i<2*t-1;i+=1) {
        keys[i]=0;
        C[i] = NULL;
    }
    C[2*t-1] = NULL;
    n = 0;
}
II BTreeNode::traverse(){
    II i;
    for (i = 0; i < n; i+=1){
        if (leaf == false)
            C[i]->traverse();
        cout << " " << keys[i];
    }
    if (leaf == false)
        C[i]->traverse();
    return 0;
}
BTreeNode *BTreeNode::search(LL k){
    II i = 0;
    while (i < n && k > keys[i])
        i+=1;
    if (keys[i] == k)
        return this;
    if (leaf == true)
        return NULL;
    return C[i]->search(k);
}
II BTree::insert(LL k){
    if (root == NULL){
        root = new BTreeNode(t, true);
        root->keys[0] = k; 
        root->n = 1;
    }
    else {
        if (root->n == 2*t-1){
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            II i = 0;
            if (s->keys[0] < k)
                i+=1;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else
            root->insertNonFull(k);
    }
    return 0;
}
II BTreeNode::insertNonFull(LL k){
    II i = n-1;
    if (leaf == true){
        while (i >= 0 && keys[i] > k){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else{
        while (i >= 0 && keys[i] > k)
            i--;
        if (C[i+1]->n == 2*t-1){
            splitChild(i+1, C[i+1]);
            if (keys[i+1] < k)
                i+=1;
        }
        C[i+1]->insertNonFull(k);
    }
    return 0;
}
II BTreeNode::splitChild(LL i, BTreeNode *y){
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (II j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];
    if (y->leaf == false){
        for (II j = 0; j < t; j++)
            z->C[j] = y->C[j+t];
    }
    else{
        (y)->C[1] = (y)->C[0];
        (y)->C[0] = z;
        z->C[0] = (y)->C[1];
    }
    y->n = t - 1;
    for (II j = n; j >= i+1; j--)
        C[j+1] = C[j];
    C[i+1] = z;
    for (II j = n-1; j >= i; j--)
        keys[j+1] = keys[j];
    keys[i] = y->keys[t-1];
    n = n + 1;
    return 0;
}

LL convertToInt(string s){
    LL ans=0,temp=1;;
    reverse(s.begin(), s.end());
    for(II i=0;i<s.length();i+=1) {
        ans+=(s[i]-'0')*temp;
        temp*=10;
    }
    reverse(s.begin(), s.end());
    return ans;
}

II main(II argc, char * argv[]){
    II maxNodes=3;
    if(argc == 2){
        II sz=getLines();
        II osz=(262144/sz),isz=(atoi(argv[1])-1)*(262144/sz);
        ofstream myfile;
        myfile.open ("out.txt");
        BTree hashSearch(maxNodes);
        while(1){
            toHash = readFiles(isz);
            if(toHash.size() == 0) break;   
            for(II i=0;i<toHash.size();i+=1){
                string s=toHash[i][0];
                for(II k=1;k<toHash[i].size();k++){
                    for(II j=0;j<3-(int)toHash[i][k].length();j++) {s+="0";}
                    s+=toHash[i][k];
                }
                LL ins = convertToInt(s);
                if(hashSearch.search(ins) == NULL) {
                    hashSearch.insert(ins);
                    string ss="";
                    for(II j=0;j<toHash[i].size();j++) {ss+=toHash[i][j]; ss+=" ";}
                    toFlush.PB(ss);
                    totalLines++;
                }
                if(toFlush.size() == osz){
                    for(II j=0;j<toFlush.size();j++) myfile << toFlush[j] << endl;
                    toFlush.clear();
                }
            }
        }
        for(II j=0;j<toFlush.size();j++) myfile << toFlush[j] << endl;
        toFlush.clear();
        myfile.close();
        cout << "TotalLines : " << totalLines << endl;
    }
    else{
        cout << "Some error occurred!\n";
    }
    return 0;
}
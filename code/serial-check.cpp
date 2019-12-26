#pragma GCC optimize(3)
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <vector>
#include <fstream>
#include <queue>
#include <ctime>
#include <omp.h>
using namespace std;

#define INF 0x3f3f3f3f
struct edge{int to,cost;};
typedef pair<int,int> P;   
int n,m,cnt;
long long checksum;
fstream f,ss;
vector<edge> G[14081999];
int d[14081999];
int source[999];
 
void dijkstra(int s){
    priority_queue<P,vector<P>,greater<P> > que;
    fill(d,d+n,INF);
    d[s]=0;
    que.push(P(0,s));
    while(!que.empty()){
        P p=que.top();
        que.pop();
        int v=p.second;
        if(d[v]<p.first) continue;
        for(int i=0;i<G[v].size();i++){
            edge e=G[v][i];
            if(d[e.to]>d[v]+e.cost){
                d[e.to]=d[v]+e.cost;
                que.push(P(d[e.to],e.to));
            }
        }
    }
}

void readfile(){
	char ch;
	for(int i=0;i<7;i++){
		string sTmp;
		getline(f,sTmp);
	}
	int s,t,co;
	for(int i=0;i<m;++i){
        f>>ch>>s>>t>>co;
        G[s-1].push_back({t-1,co});
	}
	string sTmp;
	while(ss>>ch&&ch=='c'){getline(ss,sTmp);}
	ss>>sTmp,ss>>sTmp,ss>>sTmp>>cnt;
	//cout<<cnt<<endl;
	while(ss>>ch&&ch=='c'){getline(ss,sTmp);}
	ss>>source[0];
	if(cnt>1)
		for(int i=1;i<cnt;i++)
			ss>>ch>>source[i];
}

int main(int argc, char** argv){
    string Path(argv[2]);
    Path="../data/USA-road-"+Path+".";
    if(strcmp(argv[1],"CTR")==0){
    	Path=Path+"CTR.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=14081816,m=34292496;
	}
	else if(strcmp(argv[1],"NE")==0){
		Path=Path+"NE.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=1524453,m=3897636;
	}
	else if(strcmp(argv[1],"NY")==0){
		Path=Path+"NY.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=264346,m=733846;
	}		
    if(!f.is_open()||!ss.is_open()){cout<<"Error opening file"<<endl;return -1;}
    cout<<"Reading..."<<endl;
    readfile();
	string kind(argv[1]);
	string fpath="../bin/USA-road-"+(string)argv[2]+"."+kind+".chk";
	ofstream f1(fpath);
	f1<<"g "<<n<<" "<<m<<endl;
	for(int i=0;i<cnt;i++){
		checksum=0;
		dijkstra(source[i]);
		for(int j=0;j<n;j++)
			checksum=(checksum+d[j])&(((long long)1<<62)-1);
		f1<<"d "<<checksum<<endl;
    }
    cout<<"The result is successfully saved in '../bin/."<<endl;
 	return 0;
}


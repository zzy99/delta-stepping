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
#define N 14081999
int delta,tnum;
struct edge{int to,cost;};
struct req{int v,w;};  
int n,m,maxbucket,cnt;
fstream f,ss;
vector<edge> G[N];
int tent[N];
vector<int> B[N];
vector<int> S;
vector<req> REQ;
int source[999];
double runtime[999];
double totaltime,averagetime;

bool bempty(){
	for(int i=0;i<=maxbucket;i++)
		if(!B[i].empty())
			return false;
	return true;
}

void relax(int w,int d){
	if(d<tent[w]){
		if(tent[w]!=INF){
			vector<int>::iterator res=find(B[tent[w]/delta].begin(),B[tent[w]/delta].end(),w);
			if(res!=B[tent[w]/delta].end())
				B[tent[w]/delta].erase(res);
		}
		B[d/delta].push_back(w);
		if(d/delta>maxbucket) maxbucket=d/delta;
		tent[w]=d;
	}
}
 
void deltastepping(int s){
	maxbucket=0;
	for(int i=0;i<n;i++)
		tent[i]=INF;
	relax(s,0);
	int j=0;
	omp_set_num_threads(4);
	while(!bempty()){
		S.clear();
		while(!B[j].empty()){
			REQ.clear();
			#pragma omp for
			for(int i=0;i<B[j].size();i++){
				int vv=B[j][i];
				for(int k=0;k<G[vv].size();k++)
					if(G[vv][k].cost<=delta){
						req r;
						r.v=G[vv][k].to;
						r.w=tent[vv]+G[vv][k].cost;
						REQ.push_back(r);
					}
				S.push_back(vv);
			}
			B[j].clear();
			#pragma omp for
			for(int i=0;i<REQ.size();i++)
				relax(REQ[i].v,REQ[i].w);
		}
		REQ.clear();
		#pragma omp for
		for(int i=0;i<S.size();i++){
			int vv=S[i];
			for(int k=0;k<G[vv].size();k++)
				if(G[vv][k].cost>delta){
					req r;
					r.v=G[vv][k].to;
					r.w=tent[vv]+G[vv][k].cost;
					REQ.push_back(r);
				}
		}
		#pragma omp for
		for(int i=0;i<REQ.size();i++)
			relax(REQ[i].v,REQ[i].w);
		j++;
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
	clock_t startTime1,startTime2,endTime;
    startTime1 = clock();
    string Path(argv[2]);
    Path="../data/USA-road-"+Path+".";
    if(strcmp(argv[1],"CTR")==0){
    	Path=Path+"CTR.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=14081816,m=34292496;
		delta=4000;
	}
	else if(strcmp(argv[1],"NE")==0){
		Path=Path+"NE.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=1524453,m=3897636;
		delta=3000;
	}
	else if(strcmp(argv[1],"NY")==0){
		Path=Path+"NY.";
		f.open(Path+"gr");
		ss.open(Path+"ss");
		n=264346,m=733846;
		delta=10;
	}		
    if(!f.is_open()||!ss.is_open()){cout<<"Error opening file"<<endl;return -1;}
    cout<<"Reading..."<<endl;
    readfile();
	startTime2 = clock();
	cout<<"The read time is: "<<(double)(startTime2 - startTime1)/CLOCKS_PER_SEC<<"s"<<endl;
	//cin>>delta>>tnum;
	string kind(argv[1]);
	string fpath="../bin/USA-road-"+(string)argv[2]+"."+kind+".res";
	ofstream f1(fpath);
	f1<<"g "<<n<<" "<<m<<endl;
	cnt=1;
	for(int i=0;i<cnt;i++){
		startTime2 = clock();
		deltastepping(source[i]);
		endTime = clock();
		runtime[i]=(double)(endTime - startTime2)/CLOCKS_PER_SEC;
		f1<<"t "<<runtime[i]<<endl;
		totaltime+=runtime[i];
    }
    averagetime=(double)totaltime/cnt;
    cout<<"The average run time is "<<averagetime<<"s."<<endl;
    cout<<"The result is successfully saved in '../bin/."<<endl;
 	return 0;
}


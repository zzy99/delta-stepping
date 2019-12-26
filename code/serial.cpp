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
fstream f,ss;
vector<edge> G[14081999];
int d[14081999];
int source[999];
double runtime[999];
double totaltime,averagetime;
 
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
	clock_t startTime1,startTime2,endTime;
    startTime1 = clock();
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
		dijkstra(source[i]);
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


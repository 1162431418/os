#include<bits/stdc++.h>
#define N 105
#define M 105
//N表示系统中进程的最大值，M表示可利用资源的种类的最大值 
using namespace std;
int Available[M];//可利用资源向量
int Max[N][M];//最大需求矩阵
int Allocation[N][M];//分配矩阵
int Need[N][M];//需求矩阵 
int Work[M];//安全性算法的工作向量
int Request[M];//请求向量 
bool Fnish[N];//判断系统是否安全的标志 
int n,m;//n表示进程数，m表示可利用的资源的种类数 
bool check(){//判断是否所有的Fnish均为true 
	for(int i=1;i<=n;i++){
		if(Fnish[i]!=true) return false;
	}
	return true;
}
bool secure(){
	for(int i=1;i<=m;i++) Work[i]=Available[i];//初始化工作向量与Available相等 
	for(int i=1;i<=n;i++) Fnish[i]=false;//初始化Fnish[N]全为false 
	while(!check()){
		bool flag=false;//判断Fnish是否改变的标志 
		for(int i=1;i<=n;i++){
			if(Fnish[i]) continue;
			int res=1;
			for(int j=1;j<=m;j++){
				if(Need[i][j]>Work[j]){
					res=0;
					break;			
				}				
			}
			if(res){
				Fnish[i]=true;
				flag=true;
				for(int j=1;j<=m;j++){
					Work[j]=Work[j]+Allocation[i][j];//释放资源 
				}	
			}
		}
		if(!flag) return false;//一轮扫描如果Fnish没有发生变化，那么之后扫描也不会发生变化，所以此时不安全 
	}
	return true;
}
void banker(){
	int T;//T表示测试组数 
	scanf("%d",&T);
	while(T--){
		int k;
		scanf("%d",&k);
		int flag=0;
		for(int i=1;i<=m;i++){
			scanf("%d",&Request[i]);
			if(Request[i]>Need[k][i]){
				flag=1;
			} 
		}
		for(int j=1;j<=m&&flag==0;j++){
			if(Request[j]>Available[j]){
				flag=2;
			}
		} 
		if(flag==1)printf("所需资源超过它所要求的最大值。\n");
		else if(flag==2)printf("尚无足够资源。\n");
		else{
			for(int j=1;j<=m;j++){
				Available[j]=Available[j]-Request[j];
				Allocation[k][j]=Allocation[k][j]+Request[j];
				Need[k][j]=Need[k][j]-Request[j];	
			}
			if(secure()){
				printf("系统安全，可分配。\n");
			}
			else{
				printf("系统不安全，不予分配。\n");
				for(int j=1;j<=m;j++){
					Available[j]=Available[j]+Request[j];
					Allocation[k][j]=Allocation[k][j]-Request[j];
					Need[k][j]=Need[k][j]+Request[j];	
				}
			} 
		}
	} 
}
int main(){
	freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++) scanf("%d",&Available[i]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++) scanf("%d",&Max[i][j]);
		for(int j=1;j<=m;j++) scanf("%d",&Allocation[i][j]),Available[j]-=Allocation[i][j];
		for(int j=1;j<=m;j++) scanf("%d",&Need[i][j]);
	}
	if(secure()) printf("初始系统安全。\n"),banker();
	else printf ("初始系统不安全。\n");
	return 0;
}

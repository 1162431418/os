#include<bits/stdc++.h>
#define N 105
#define M 105
//N��ʾϵͳ�н��̵����ֵ��M��ʾ��������Դ����������ֵ 
using namespace std;
int Available[M];//��������Դ����
int Max[N][M];//����������
int Allocation[N][M];//�������
int Need[N][M];//������� 
int Work[M];//��ȫ���㷨�Ĺ�������
int Request[M];//�������� 
bool Fnish[N];//�ж�ϵͳ�Ƿ�ȫ�ı�־ 
int n,m;//n��ʾ��������m��ʾ�����õ���Դ�������� 
bool check(){//�ж��Ƿ����е�Fnish��Ϊtrue 
	for(int i=1;i<=n;i++){
		if(Fnish[i]!=true) return false;
	}
	return true;
}
bool secure(){
	for(int i=1;i<=m;i++) Work[i]=Available[i];//��ʼ������������Available��� 
	for(int i=1;i<=n;i++) Fnish[i]=false;//��ʼ��Fnish[N]ȫΪfalse 
	while(!check()){
		bool flag=false;//�ж�Fnish�Ƿ�ı�ı�־ 
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
					Work[j]=Work[j]+Allocation[i][j];//�ͷ���Դ 
				}	
			}
		}
		if(!flag) return false;//һ��ɨ�����Fnishû�з����仯����ô֮��ɨ��Ҳ���ᷢ���仯�����Դ�ʱ����ȫ 
	}
	return true;
}
void banker(){
	int T;//T��ʾ�������� 
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
		if(flag==1)printf("������Դ��������Ҫ������ֵ��\n");
		else if(flag==2)printf("�����㹻��Դ��\n");
		else{
			for(int j=1;j<=m;j++){
				Available[j]=Available[j]-Request[j];
				Allocation[k][j]=Allocation[k][j]+Request[j];
				Need[k][j]=Need[k][j]-Request[j];	
			}
			if(secure()){
				printf("ϵͳ��ȫ���ɷ��䡣\n");
			}
			else{
				printf("ϵͳ����ȫ��������䡣\n");
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
	if(secure()) printf("��ʼϵͳ��ȫ��\n"),banker();
	else printf ("��ʼϵͳ����ȫ��\n");
	return 0;
}

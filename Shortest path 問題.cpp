#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream> 
using namespace std;

#define N 50
int disp[N];
double edge[N][N],width[N][N];
bool visited[N] = {false};
bool through[N][N];
const int inf = 999999;
ifstream in("test3.txt");
ofstream out("t2_out.txt");

int main(){
	int prev[N];//當前結點的上一個結點
	int row=-1;
	string tmps;
	fill(edge[0],edge[0] + N * N,inf);
	fill(disp,disp + N,inf);
	while(getline (in,tmps)){
        row++;
    }
    in.close();
    ifstream in("test3.txt");
	int start_point,end_point,trans;
	int n;//點的數量
	in>>n;
	cout<<"圖形共"<<n<<"個點(0~"<<n-1<<")"<<row<<"個邊"<<endl<<endl<<"請輸入來源節點:";
	cin>>start_point;
	cout<<"請輸入目的節點:"; 
	cin>>end_point; 
	if(start_point == end_point) {
	cout<<"起點和終點不可相同!";
	return(1);
	}
	if(start_point>(n-1) || end_point>(n-1)){ 
		cout<<"請輸入符合規定的節點編號!";
		return (1);
		}
	cout<<"請輸入交通方式(1步行、2腳踏車、3機車、4轎車、5巴士) : "; 
	cin>>trans; 
	int a,b,all_limit[5],limit[N][N][N];
	double c,d;
	for(int i=0;i < row;i++)
	{
		//cout<<"第"<<i<<"個"<<endl; 
		in>>a>>b>>c>>d>>all_limit[0]>>all_limit[1]>>all_limit[2]>>all_limit[3]>>all_limit[4];
		if(a == b)  {
		cout<<"資料中有 self-loop的邊!";
		return (1);
		}
		if(c<=0 || d<=0){ 
		cout<<"距離、路幅值需均為正實數!";
		return (1);
		}
		if(a>(n-1) || b>(n-1)){ 
		cout<<"資料中有不符規定的節點編號!";
		return (1);
		}
		edge[a][b] = c;
		width[a][b] = d; 
		through[a][b] = true;//先預設每條路線都可通過 
		for(int k=0;k<5;k++)
		limit[a][b][k]=all_limit[k];
		if(d<0.5) all_limit[4]=0;
		else if(d<1.5) all_limit[3]=0;
		else if(d<2) all_limit[2]=0;
		else if(d<4) all_limit[1]=0;
		else if(d<6) all_limit[0]=0;	//路幅限制 
		//cout<<"交通限制為:"<<limit[0]<<" "<<limit[1]<<" "<<limit[2]<<" "<<limit[3]<<" "<<limit[4]<<endl;
		if(all_limit[5-trans]==0) through[a][b]=false; //若選擇的交通工具不能通過此道路，則設through[a][b]為false 
		//cout<<"可否通過:"<<through[a][b]<<endl;
	}
	
	for(int i=0;i<N;i++){
		prev[i] = i;
		edge[i][i] = 0;
	}
		
	disp[start_point] = 0;
	for(int i = 0;i < n;i++){
		//cout<<endl<<"第"<<i<<"回合:"<<endl;
		int u = -1,min = inf;
		for(int j = 0;j < n;j++){
			if(visited[j] == false && disp[j] <= min)
			{
				u = j;
				min = disp[j];
			}
			//cout<<"到 Node"<<u<<"的最短距離:"<<min<<endl;
		}	
		
		if(u == -1)
			break;
		
		visited[u] = true;
		for(int v = 0;v < n;v++){
			if(visited[v] == false && edge[u][v] != inf && through[u][v] == true)
			{
				if(disp[u] + edge[u][v] < disp[v]){
					disp[v] = disp[u] + edge[u][v];
					prev[v] = u;
//prev=目前結點的上一個節點
				} 		
			}
		}		
	}

//起點到各個點的最短路徑
	
	for (int i=0;i<n;i++)
	{
		//cout<<"起點"<<start_point<<"到"<<i<<"的最短距离為: "<<disp[i]<<endl;
	}
	
	stack<int> myStack;
	int temp = end_point;
	myStack.push(end_point);//加終點 
	int i=0,test;
	double distance[N];
	while(start_point != temp){
		distance[i]=edge[prev[temp]][temp];
		temp = prev[temp];
		myStack.push(temp);
		i++;
    //temp=目前點的上一個結點
	}
	double dis[N];
	for (int k=0,j=(i-1); k<i,j>=0; k++,j--)
    dis[j] = distance[k];
	cout<<endl<<"Node "<<start_point<<" 到 Node "<<end_point<<endl<<"最短路徑為: ";
	out<<endl<<"Node "<<start_point<<" 到 Node "<<end_point<<endl<<"最短路徑為: ";
	int j=0,save[N];
	while(!myStack.empty()){
		//cout<<myStack.top();
		save[j]=myStack.top();
		cout<<save[j];
		out<<save[j];
		j++;
		myStack.pop(); 
		if(!myStack.empty()) {
		cout<<"->";
		out<<"->";
	}
	}
	double sum=0;
	for (i=0;i<(j-1);i++)
	sum+=dis[i];
	cout<<endl<<"總距離為:"<<sum<<endl;
	out<<endl<<"總距離為:"<<sum<<endl;
	for (i=0;i<(j-1);i++){
	cout<<endl<<"Node"<< save[i]<<" 到 Node "<<save[i+1]<<endl<<"距離為:"<<dis[i]<<endl
	<<"路幅為:"<<width[save[i]][save[i+1]]<<endl<<"通行限制為:"<<limit[save[i]][save[i+1]][0]
	<<limit[save[i]][save[i+1]][1]<<limit[save[i]][save[i+1]][2]<<limit[save[i]][save[i+1]][3]<<limit[save[i]][save[i+1]][4]<<endl;
	out<<endl<<"Node"<< save[i]<<" 到 Node "<<save[i+1]<<endl<<"距離為:"<<dis[i]<<endl
	<<"路幅為:"<<width[save[i]][save[i+1]]<<endl<<"通行限制為:"<<limit[save[i]][save[i+1]][0]
	<<limit[save[i]][save[i+1]][1]<<limit[save[i]][save[i+1]][2]<<limit[save[i]][save[i+1]][3]<<limit[save[i]][save[i+1]][4]<<endl;
	}
	in.close();
	out.close();
	return 0;
}
 

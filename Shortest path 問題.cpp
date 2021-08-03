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
	int prev[N];//��e���I���W�@�ӵ��I
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
	int n;//�I���ƶq
	in>>n;
	cout<<"�ϧΦ@"<<n<<"���I(0~"<<n-1<<")"<<row<<"����"<<endl<<endl<<"�п�J�ӷ��`�I:";
	cin>>start_point;
	cout<<"�п�J�ت��`�I:"; 
	cin>>end_point; 
	if(start_point == end_point) {
	cout<<"�_�I�M���I���i�ۦP!";
	return(1);
	}
	if(start_point>(n-1) || end_point>(n-1)){ 
		cout<<"�п�J�ŦX�W�w���`�I�s��!";
		return (1);
		}
	cout<<"�п�J��q�覡(1�B��B2�}�񨮡B3�����B4�⨮�B5�ڤh) : "; 
	cin>>trans; 
	int a,b,all_limit[5],limit[N][N][N];
	double c,d;
	for(int i=0;i < row;i++)
	{
		//cout<<"��"<<i<<"��"<<endl; 
		in>>a>>b>>c>>d>>all_limit[0]>>all_limit[1]>>all_limit[2]>>all_limit[3]>>all_limit[4];
		if(a == b)  {
		cout<<"��Ƥ��� self-loop����!";
		return (1);
		}
		if(c<=0 || d<=0){ 
		cout<<"�Z���B���T�Ȼݧ��������!";
		return (1);
		}
		if(a>(n-1) || b>(n-1)){ 
		cout<<"��Ƥ������ųW�w���`�I�s��!";
		return (1);
		}
		edge[a][b] = c;
		width[a][b] = d; 
		through[a][b] = true;//���w�]�C�����u���i�q�L 
		for(int k=0;k<5;k++)
		limit[a][b][k]=all_limit[k];
		if(d<0.5) all_limit[4]=0;
		else if(d<1.5) all_limit[3]=0;
		else if(d<2) all_limit[2]=0;
		else if(d<4) all_limit[1]=0;
		else if(d<6) all_limit[0]=0;	//���T���� 
		//cout<<"��q���:"<<limit[0]<<" "<<limit[1]<<" "<<limit[2]<<" "<<limit[3]<<" "<<limit[4]<<endl;
		if(all_limit[5-trans]==0) through[a][b]=false; //�Y��ܪ���q�u�㤣��q�L���D���A�h�]through[a][b]��false 
		//cout<<"�i�_�q�L:"<<through[a][b]<<endl;
	}
	
	for(int i=0;i<N;i++){
		prev[i] = i;
		edge[i][i] = 0;
	}
		
	disp[start_point] = 0;
	for(int i = 0;i < n;i++){
		//cout<<endl<<"��"<<i<<"�^�X:"<<endl;
		int u = -1,min = inf;
		for(int j = 0;j < n;j++){
			if(visited[j] == false && disp[j] <= min)
			{
				u = j;
				min = disp[j];
			}
			//cout<<"�� Node"<<u<<"���̵u�Z��:"<<min<<endl;
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
//prev=�ثe���I���W�@�Ӹ`�I
				} 		
			}
		}		
	}

//�_�I��U���I���̵u���|
	
	for (int i=0;i<n;i++)
	{
		//cout<<"�_�I"<<start_point<<"��"<<i<<"���̵u�Z�ì�: "<<disp[i]<<endl;
	}
	
	stack<int> myStack;
	int temp = end_point;
	myStack.push(end_point);//�[���I 
	int i=0,test;
	double distance[N];
	while(start_point != temp){
		distance[i]=edge[prev[temp]][temp];
		temp = prev[temp];
		myStack.push(temp);
		i++;
    //temp=�ثe�I���W�@�ӵ��I
	}
	double dis[N];
	for (int k=0,j=(i-1); k<i,j>=0; k++,j--)
    dis[j] = distance[k];
	cout<<endl<<"Node "<<start_point<<" �� Node "<<end_point<<endl<<"�̵u���|��: ";
	out<<endl<<"Node "<<start_point<<" �� Node "<<end_point<<endl<<"�̵u���|��: ";
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
	cout<<endl<<"�`�Z����:"<<sum<<endl;
	out<<endl<<"�`�Z����:"<<sum<<endl;
	for (i=0;i<(j-1);i++){
	cout<<endl<<"Node"<< save[i]<<" �� Node "<<save[i+1]<<endl<<"�Z����:"<<dis[i]<<endl
	<<"���T��:"<<width[save[i]][save[i+1]]<<endl<<"�q�歭�:"<<limit[save[i]][save[i+1]][0]
	<<limit[save[i]][save[i+1]][1]<<limit[save[i]][save[i+1]][2]<<limit[save[i]][save[i+1]][3]<<limit[save[i]][save[i+1]][4]<<endl;
	out<<endl<<"Node"<< save[i]<<" �� Node "<<save[i+1]<<endl<<"�Z����:"<<dis[i]<<endl
	<<"���T��:"<<width[save[i]][save[i+1]]<<endl<<"�q�歭�:"<<limit[save[i]][save[i+1]][0]
	<<limit[save[i]][save[i+1]][1]<<limit[save[i]][save[i+1]][2]<<limit[save[i]][save[i+1]][3]<<limit[save[i]][save[i+1]][4]<<endl;
	}
	in.close();
	out.close();
	return 0;
}
 

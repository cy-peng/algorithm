#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

void heap(int arr[], int n, int i) 
{ 
    int root = i; 
    int l = 2*i ;
    int r = 2*i + 1;
    // If left child is larger than root 
    if (l < n && arr[l] > arr[root]) 
        root = l; 
  
    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[root]) 
        root = r; 
  
    // If largest is not root 
    if (root != i) 
    { 
        swap(arr[i], arr[root]); 
  
        // Recursively heapify the affected sub-tree 
        heap(arr, n, root); 
    } 
} 
  
// main function to do heap sort 
void heapSort(int arr[], int n) 
{ 	

    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--) 
        heap(arr, n, i);
  
    // One by one extract an element from heap 
    for (int i=n-1; i>0; i--) 
    { 
        // Move current root to end 
        swap(arr[0], arr[i]); 
  
        // call max heapify on the reduced heap 
        heap(arr, i, 0); 
    } 
} 

void save(int old[], int arr[]) 
{ 	
	int n=sizeof(arr);
	for (int i=0;i<n;i++)
	old[i]=arr[i];
}

int main() {
    ifstream fin;
    istringstream is;
    string s;
    int x[50],y[50];
    int n,count=0,i=0,j=0;
    fin.open("test2.txt");
    
    while(getline(fin,s)) {
        is.clear();
        is.str(s);
        while(is>>n) {
        	count++;
        	if(count%2==0){
        		y[i]=n;
        		i++;
			}
			else{
				x[j]=n;
				j++;
			}
        }
    }
 
    
    
    int sum=0,A[25]={0},B[25]={0};
    for(int i=0;i<count/2;++i)
    sum+=x[i];
    sum=sum/count;//x�y�Ъ������ 
    cout<<"x�y�Ъ������:"<<sum<<endl<<endl;  
    
    for(int i=0;i<count/2;i++){ //�N�y�Ш̧�x�b�����I����AB����
    if(x[i]<sum) 
    A[i]=x[i];
    if(x[i]>sum)
    B[i]=x[i];
	}
	
	int ax[25]={0},ay[25]={0},bx[25],by[25]={0},k=0,p=0;
    for(int i=0;i<count/2;i++){
    	if(A[i]!=0){
    	k++;
    	ax[k]=A[i];
    	ay[k]=y[i];
    	}
    	if(B[i]!=0){
    	p++;
    	bx[p]=B[i];
    	by[p]=y[i];
    	}
    	
	}
		cout<<"A��";
		for(i=1;i<=count/4;i++)
    	cout<<"("<<ax[i]<<","<<ay[i]<<")";
   		cout<<endl; 				            //a��
   		cout<<"B��";
   		for(i=1;i<=count/4;i++)
    	cout<<"("<<bx[i]<<","<<by[i]<<")";		//b�� 
   		cout<<endl;
   		int brank[25];
   		for(i=1;i<=count/4;i++){
   		int rank=0,o=1;
    	while(by[i]){
    	if(by[i]>ay[o])
		rank++;
		brank[i]=rank;
		if(o>count/4) break;
		o++;
		}}
	
	for(i=0;i<=count/4;i++)
	brank[i]=brank[i+1];
	
    heapSort(brank,count/4);
    cout<<"Rank���ƧǬ�:";
    for(i=0;i<count/4;i++)
	cout<<brank[i]<<" ";
	
    int summ=0;
   	for(int i=0;i<count/4;i++)
    summ+=brank[i];
	
	cout<<endl<<"(1)�ɮפ��Ҧ��I���ӼƬ�"<<count/2<<endl;
    cout<<"(2)�̤jRank��"<<brank[count/4-1]<<endl;
    cout<<"(3)�̤pRank��"<<brank[0]<<endl;
    cout<<"(4)����Rank��"<<summ/(count/4);
    return 0;
}

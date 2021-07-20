#include<iostream>
#include<climits>     
using namespace std;

// 此函数返回不包含在 Tset 中的顶点的最小距离 
int minimumDist(int dist[], bool Tset[]) 
{
	int min=INT_MAX,index;
              
	for(int i=0;i<6;i++) 
	{
		if(Tset[i]==false && dist[i]<=min)      
		{
			min=dist[i];
			index=i;
		}
	}
	return index;
}

void Dijkstra(int graph[6][6],int src) // 使用的邻接矩阵是 6x6 
{
	int dist[6]; // 整数数组来计算每个节点的最小距离。                           
	bool Tset[6];// 布尔数组，用于标记每个节点的已访问/未访问。
	
	// 设置除初始节点外的具有无穷远距离的节点，并将它们标记为未访问。
	for(int i = 0; i<6; i++)
	{
		dist[i] = INT_MAX;
		Tset[i] = false;	
	}
	
	dist[src] = 0;   // 源顶点距离设置为零。            
	
	for(int i = 0; i<6; i++)                           
	{
		int m=minimumDist(dist,Tset); 
		Tset[m]=true;
		for(int i = 0; i<6; i++)                  
		{
			// 更新特定节点的最小距离。
			if(!Tset[i] && graph[m][i] && dist[m]!=INT_MAX && dist[m]+graph[m][i]<dist[i])
				dist[i]=dist[m]+graph[m][i];
		}
	}
	cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i = 0; i<6; i++)                      
	{ 
		char str=65+i; // Ascii 值
		cout<<str<<"\t\t\t"<<dist[i]<<endl;
	}
}

int main()
{
	int graph[6][6]={
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0}};
	Dijkstra(graph,0);
	system("pause");
	return 0;	                        
}

#include <bits/stdc++.h> 
using namespace std ;

#define V 18
vector<pair<int, int>> adj[V];

void addEdge( int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
}

void printGraph() 
{ 
    int v, w; 
    for (int u = 1; u <=V; u++) 
    { 
        cout << "Node " << u << " makes an edge with \n"; 
        for (auto it = adj[u].begin(); it!=adj[u].end(); it++) 
        { 
            v = it->first; 
            w = it->second; 
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n"; 
        } 
        cout << "\n"; 
    } 
} 

int main ()
{
   int u = 0, v = 0, w = 0;

	ifstream file("Dataset.txt");
	string str;

	while (getline(file, str))
	{
		istringstream ss(str);
		ss >> u;
		ss >> v;
		ss >> w;
		addEdge( u, v, w);
	}

	//printGraph();
    return 0;
	
}
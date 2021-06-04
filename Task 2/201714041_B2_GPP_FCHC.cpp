#include <bits/stdc++.h>
using namespace std;

#define sigma 100
#define V 18
#define loop 10
#define State pair<vector<int>, vector<int>>

vector<pair<int, int>> adj[V+1]; //vertices(1-18)..adj[0] is empty
vector <int> a_cost;
vector <int> a_count;

void addEdge(int u, int v, int wt)
{
	adj[u].push_back(make_pair(v, wt));
}

void create_graph(string s)
{
	int u = 0, v = 0, w = 0;
	ifstream file(s);
	string str;

	while (getline(file, str))
	{
		istringstream ss(str);
		ss >> u;
		ss >> v;
		ss >> w;
		addEdge(u, v, w);
	}
}

int cost(State s)
{
	vector<int> s1 = s.first, s2 = s.second;
	int w = 0;
	for (int i = 0; i < s1.size(); i++)
	{
		for (auto it = adj[s1[i]].begin(); it != adj[s1[i]].end(); it++)
		{
			int v = it->first;
			for (int j = 0; j < s2.size(); j++)
			{
				if (v == s2[j])
				{
					w = w + it->second;
					break;
				}
			}
		}
	}
	return w;
}

State heuristics1(vector<int> set1, vector<int> set2)
{
	int p1, p2;

	p1 = rand() % set1.size();
	p2 = rand() % set2.size();

	swap(set1[p1], set2[p2]);

	return State(set1, set2);
}

State heuristics2(vector<int> set1, vector<int> set2)
{
	array<int, V> s;

	for (int i = 0; i < V / 2; i++)
	{
		s[i] = set1[i];
		s[V / 2 + i] = set2[i];
	}

	unsigned seed = 0;
	shuffle(s.begin(), s.end(), default_random_engine(seed)); //find out what seed does

	for (int i = 0; i < V / 2; i++)
	{
		set1[i] = s[i];
		set2[i] = s[V / 2 + i];
	}

	return State(set1, set2);
}

vector<pair<State, int>> HillClimbing (vector<int> set1, vector<int> set2)
{
	int count = 0, i = 0;
	vector<pair<State, int>> result;
	State current = State(set1, set2), neighbour;
	double ran;
	while (true)
	{
		for (i = 0; i < sigma; i++)
		{
			ran = (double)rand() / (RAND_MAX + 1.0);
			if (ran < 0.5)
				neighbour = heuristics1(set1, set2);
			else
				neighbour = heuristics2(set1, set2);
			
			if (cost(neighbour) < cost(current))
				break;
		}

		if (i == sigma)
		{
			a_cost.push_back(cost(current));
            a_count.push_back(count);
			int temp = *min_element(a_cost.begin() , a_cost.end() );
			result.push_back(make_pair(current, temp));
			return result;
		}

		current = neighbour;
		set1 = current.first;
		set2 = current.second;

		count++;
	}
}

void avg_calc(vector <int> w, vector <int> c)
{
	double avg_cost = 0 ;
    double avg_count = 0 ;

    for(int i = 0 ; i < w.size() ; i++)
    {
        avg_cost = avg_cost + (double)w[i];
        avg_count = avg_count + (double)c[i];
    }
 
    avg_cost = avg_cost / (double)w.size();
    avg_count = avg_count / (double)c.size();
 
    cout << "Average Cost: " << avg_cost << endl;
    cout << "Average Count: " << floor(avg_count) << endl;
}

void print_result(vector<pair<State, int>> res)
{
	cout<<"Sigma: "<< sigma <<endl;
	cout << "Min Cost: " << res.begin()->second << endl;
	cout << "SetA: ";

	for (auto it = res.begin(); it != res.end(); it++)
	{
		for (int i = 0; i < V / 2; i++)
		{
			cout << it->first.first[i] << " ";
		}
	}
	cout << endl;
	cout << "SetB: ";

	for (auto it = res.begin(); it != res.end(); it++)
	{
		for (int i = 0; i < V / 2; i++)
		{
			cout << it->first.second[i] << " ";
		}
	}
	cout<<endl;
}

int main()
{
	vector <pair<State, int>> res;
	vector <int> set1, set2;
	string data;

	data = "Dataset.txt";

	create_graph(data);

	//initialize 2 sets of current state
	set1 = {1, 3, 9, 5, 6, 11, 7, 13, 14};
	set2 = {2, 4, 8, 10, 12, 15, 16, 18, 17};
	
	for (int i = 0; i < loop; i++)
	{
		res = HillClimbing(set1, set2);
		//set1 = res.begin()->first.first;
		//set2 = res.begin()->first.second;
	}

	avg_calc(a_cost , a_count);
	print_result(res);
	
	return 0;
}
	
/*** *对数据结构进行优化 
 *g++ :    30.2004s for 400 trials	output 20
 *g++ -O2: 17.2598s for 400 trials	output 20
 *g++ -O2: 1728.53s for 40000 trials output 17
 * **/
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <assert.h>
using namespace std;


class Graph
{
public:
	bool isEdgeExist(int s, int t, vector< list<int> > &_storage1)
	{
		list<int> &edges = _storage1[s];
		for(int adjacent : edges)
		{
			if(adjacent == t) 
			{
				return true;
			}
		}
		return false;
	}
	void initGraph()
	{
		_storage.resize(num);
		ifstream fin("kargerMinCut.txt");
		string line;
		stringstream stream;
		while(getline(fin, line))
		{
			int vertex, adjacent;
			stream.clear();
			stream << line;
			stream >> vertex;
			while(stream >> adjacent)
			{
				_storage[vertex-1].push_back(adjacent - 1);
			}
		}
	}
	void contract(int a, int b, vector< list<int> > &_storage1)
	{
//		cout << "before: " << endl;
//		print(_storage1);
		_storage1[a].remove(b);
		_storage1[b].remove(a);
		list<int>::iterator iter;
		for(iter = _storage1[b].begin(); iter != _storage1[b].end(); iter++)
		{
			_storage1[*iter].remove(b);
			if(a != *iter) 
			{
				_storage1[*iter].push_back(a);
				_storage1[a].push_back(*iter);
			}
		}
		_storage1[b].clear();
//		cout << "after:"  << endl;
//		print(_storage1);
	}

	int minCut()
	{
		int count = 0;
		int n ;
		int min = num * (num-1) / 2;
		int a, b;
		int flag;
		int t = 40000;
		srand( (unsigned) time(NULL) );
		while (t > 0)
		{
			vector< list<int> > _storage1 = _storage;
			n = _storage1.size();
			while(n > 2)
			{
				a = rand() % num;
				b = rand() % num;
				if(isEdgeExist(a,b,_storage1))
				{
					contract(a,b,_storage1);
					flag = b;
					n--;
				}
			}
			/*
			for(int i = 0; i < _storage.size(); i++)
			{
				if(!_storage1[i].empty())
				{
					count = _storage1[i].size();
//					cout <<  "cut :"  << count << endl;
					break;
				}
			}*/
			count = _storage1[a].size();
		if(count  < min) min = count;
			t --;
		}
			return min;
	//		return count;
	}
	void print( vector<list<int> > _storage1)
	{	
		for(int i = 0; i < num; i++)
		{
			cout << i  << " ";
			list<int>::iterator iter;
			for( iter = _storage1[i].begin(); iter != _storage1[i].end(); iter++ )
			{
				cout << *iter  << " ";
			}
			cout << endl;
		}
	}


private:
	vector< list<int> > _storage;
	int num = 200;
};

int main()
{
	clock_t start, end;
	start = clock();
	Graph graph;
	int cut;
	graph.initGraph();
	cut = graph.minCut();
	end = clock();
	cout << "running time:" << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;

	cout << "cut:" << cut << endl;
	return 0;
}


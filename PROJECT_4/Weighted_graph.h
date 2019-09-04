#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#include <iostream>
#include <limits>
#include "Exception.h"

/*****************************************
 * UW User ID:  bmalapat
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2019
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

class Weighted_graph {
	
	private:

		static const double INF;
		double **graph;
		int num_vertices;
		int num_edges;
		int *node_d;
		bool *node_state;
		double *weight;

		
		void connection_checker(int s) const;
		bool state(int n) const;
		void extract_min(double &min, size_t &min_index) const;

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double minimum_spanning_tree( int ) const;
		bool is_connected() const;

		void insert( int, int, double );
		
	

	// Friends

	friend std::ostream &operator << ( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Enter definitions for all public functions here

Weighted_graph ::Weighted_graph(int n)
{
	num_edges = 0;
	
	//Initializing number of vertices in graph
	num_vertices = n;
	
	//degree of each node
	node_d = new int[n];
	node_state = new bool[n];
	
	//Adjacency matrix for graph of size (n x n)
	graph = new double *[n];
	weight = new double [n];
	
	for(int i=0; i<n; ++i)
	{
		graph[i] = new double[n];
		weight[i] = INF;
		node_state[i] = false;
		node_d[i] = 0;
	}
	
	//initialising weight of edges
	for(int i=0; i<n; ++i)
	{
		//edge going from node to itself
		graph[i][i] = 0;

		//init all nodes to INF
		for(int j=0; j<n; ++j)
		{
			graph[i][j] = INF;
		}
		
	}
	
}

Weighted_graph :: ~Weighted_graph(){
	
	//memory deallocation
	delete[] node_d;
	node_d = nullptr;
	
	delete[] node_state;
	node_state = nullptr;
	
	for(int i=0; i<num_vertices; ++i)
	{
		delete[] graph[i];
		graph[i] = nullptr;
	}
	
	delete[] graph;
	graph = nullptr;
	
	delete[] weight;
	weight = nullptr;
	
	num_vertices =0;
	num_edges =0;
	
}

int Weighted_graph :: degree(int n) const{
	if((n <0) || (n >= num_vertices))
		throw illegal_argument();
	
	if(node_d[n] < 0)
		return 0;
	
	return node_d[n];
}

int Weighted_graph:: edge_count() const{
	if(num_edges < 0)
		return 0;
	
	return num_edges;
}

double Weighted_graph :: adjacent (int m, int n) const{
	
	if( (m < 0) || (m >= num_vertices) || (n < 0) || (n >=num_vertices))
		throw illegal_argument();
//vertices are equal, edge to itself is 0 weight	
	if(m == n)
		return 0;
//if the vertices are not adjacent it would return INF or else return the weight of the edge b/n them	
	else 
		return graph[m][n];
}

bool Weighted_graph :: state(int n) const{
	
	if(n < 0 || n > num_vertices)
		throw illegal_argument();
	
	return node_state[n];
}

void Weighted_graph :: connection_checker(int s) const
{
	//the node is discovered
	node_state[s] = true;
	int node_num{0};
	
	while(node_num < num_vertices)
	{
		//visiting the next adjacent node which hasn't yet been visited recursively
		if(!node_state[node_num] && (graph[s][node_num] != INF))
			connection_checker(node_num);
		
		node_num++;
	}
	
	return;
	
}

void Weighted_graph:: extract_min(double & min_weight, size_t & min_index) const{
	
	//resetting the min value
	min_weight = INF;
	
	for(int i=0; i<num_vertices; i++)
	{
//visit an undiscovered node whose weight is less than the current weight
		if( (weight[i] < min_weight) && (!node_state[i]))
		{
			min_weight = weight[i];
			min_index = i;
		}
	}

	return;
}


double Weighted_graph ::minimum_spanning_tree(int r) const{
	
	if(r >= num_vertices || r <0 )
		throw illegal_argument();
	
	int u{r};
	
	double min_weight{INF};
	size_t min_index{0};
	
	double MST_weight{0};
	size_t node{0};
	
	
	//Initialisation of node weight array and graph-node tracer
	for(int i=0; i<num_vertices;++i)
	{
				
		//and none of them have been discovered
		node_state[i] = false;
		
		//Initially all weight of all nodes are INF
		weight[i] = INF;

		
	}
	
	
//Running this loop for all the nodes in the connected graph

	while(node < num_vertices)
	{
//the current node is first discovered
		node_state[u] = true;
		
//assigning the weight of the nodes connected to 'u' node
		for(int v=0; v<num_vertices; ++v)
		{
			if(graph[u][v] < weight[v])
				weight[v] = graph[u][v];
			
		}
	
	extract_min(min_weight, min_index);

	if(min_weight != INF)
	{
		u = min_index;
		MST_weight += min_weight;
		
	}	
	
	else
		return MST_weight;
	
	//moving to the next node from 'u'
	node+=1;
}

return MST_weight;

}

bool Weighted_graph :: is_connected() const{
	
	//initially node is undiscovered
	for(int i=0; i<num_vertices; i++)
			node_state[i] = false;
	
	if(num_vertices == 0)
		return true;
	
	int node_num{0};
	
	//filling the node_states based on whether they are connected or not
	connection_checker(node_num);
	
	//going through each node and checking if any one is undiscovered, i.e the graph is not connected
	while(node_num < num_vertices)
	{
		if(!node_state[node_num])
		{
			return node_state[node_num];
		}
		
		node_num++;
			
	}
	
	return true;
	
}


void Weighted_graph:: insert(int m, int n, double w)
{
	
	if( (n >= num_vertices) || (m == n) || (m>= num_vertices)|| (m < 0) ||  (n < 0) || (w < 0) || (w == INF))
		throw illegal_argument();
		
//if weight == 0 and edge exists b/n m,n we are going to remove that edge
if(w == 0)
	{
		if( (graph[m][n] < INF) && (graph[n][m] < INF) ){
		
		node_d[m]-=1;
		node_d[n]-=1;
		
		num_edges-=1;
		
		graph[m][n] = INF;
		graph[n][m] = INF;
	}
		else
			return;
	}	
	
else if( w != 0 ){
	
	if((graph[m][n] != INF) || (graph[n][m] != INF))
	{
		graph[m][n] = w;
		graph[n][m] = w;
	}
	
	if((graph[m][n] == INF) && (graph[n][m] == INF)){
		
		node_d[m]+=1;
		node_d[n]+=1;
		
		num_edges+=1;
		
		graph[m][n] = w;
		graph[n][m] = w;
	
		
	}
}
	
	else
	{
		node_d[m]+=1;
		node_d[n]+=1;
		
		num_edges+=1;
		
		graph[m][n] = w;
		graph[n][m] = w;
	}


}

std::ostream &operator << ( std::ostream &out, Weighted_graph const &graph ) {
	// Your implementation

	return out;
}


#endif

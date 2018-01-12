// A C++ program for Dijkstra's  algorithm.

#include <stdio.h>
#include <limits.h>
#include <iostream>

// Number of vertices in the graph
#define V 9

//a number beyond the possible maximum distance of any path
#define maxDist 900


/*Looks for a specific vertrice in the array and returns its position in the array*/
int find (int target , int arr[V][2])
{
	for (int i = 0; i < V; i++)
	{
		if (target == arr[i][0])
			return i;
	}
}

/*Finds the next vertrice with the minimum distance that we haven't analyzed yet and returns its position in the dist array*/
int findNextV(int dist[V][2] , int passed[V][2])
{
	int min = maxDist;
	int target;
	for(int i = 0; i < V;i++)
	{
		//if the distance of the vertrice is the minimum, and it's record on the "passed" array equals zero
		if ((dist[i][1] < min)&&(passed[dist[i][0]][1] == 0))
		{
			min = dist[i][1];
			target = i;
		}
	}
	return target;
}

/*Prints the array*/
void print(int dist[V][2])
{
	for (int i = 0; i < V; i++)
	{
		std::cout << dist[i][0];
		std::cout << " |";
		std::cout << dist[i][1];
		std::cout << std::endl;
	}
}


void dijkstra(int graph[V][V])
{
	//Each Vertice has a record on the array with its number (dist[i][0]) and its shortest distance from the begining (dist[i][1])
	int dist[V][2];

	//initialization of dist. The Vertice 0 is the start so it has distance of 0. 
	//Every other Vertice has a distance of maxDist because it hasn't been analyzed yet
	dist[0][0] = 0;
	dist[0][1] = 0;
	for (int i = 1; i < V; i++)
	{
		dist[i][0] = i;
		dist[i][1] = maxDist;
	}

	//Each Vertice has a record on the array with its number (passed[i][0]) and whether it has been analyzed yet or not (passed[i][1])
	// 0 : the vertice has not been analyzed , 1 : the vertice has been analyzed
	int passed[V][2];

	//stores the position on the dist array of the next Vertice to be analyzed
	int next;

	//stores the position on the dist array for the Vertice we are checking against
	int target;

	//Initialization of passed
	for (int i = 0; i < V; i++)
	{
		passed[i][0] = i;
		passed[i][1] = 0;
	}

	//Each loop will analyze one Vertice
	for (int i = 0; i < V; i++)
	{

		next = findNextV(dist, passed);
		//Each loop will analyze the relation of the Vertice to all other Vertices
		for (int j = 0; j < V; j++)
		{
			//Checks whether there is a link to the two Vertices
			if (graph[next][j] != 0)
			{
				//Checks if the linked Vertice is already analyzed. If it is we can ignore it
				if (passed[j][1] == 0)
				{
					target = find(j, dist);
					//Checks if the new route to the linked Vertice has lower distance from the start, than the one already recorded
					if (graph[next][j] + dist[next][1] < dist[target][1])
					{
						dist[target][1] = graph[next][j] + dist[next][1];
						passed[next][1] = 1;
					}
				}
			}
		}
	}

	print(dist);

}

int main()
{
	/* adjacency matrix representation of the path */
	int graph[V][V] = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
	{ 4, 0, 8, 0, 0, 0, 0, 11, 0 },
	{ 0, 8, 0, 7, 0, 4, 0, 0, 2 },
	{ 0, 0, 7, 0, 9, 14, 0, 0, 0 },
	{ 0, 0, 0, 9, 0, 10, 0, 0, 0 },
	{ 0, 0, 4, 14, 10, 0, 2, 0, 0 },
	{ 0, 0, 0, 0, 0, 2, 0, 1, 6 },
	{ 8, 11, 0, 0, 0, 0, 1, 0, 7 },
	{ 0, 0, 2, 0, 0, 0, 6, 7, 0 }
	};

	dijkstra(graph);
	system("pause");
	return 0;
}


/*
Problem Statement:
Design and implement Parallel Breadth First Search (BFS)
and Depth First Search (DFS) using OpenMP.
*/

// --------------------------------------------------
// BFS:
// Level-wise traversal
// Uses Queue
//
// DFS:
// Depth-wise traversal
// Uses Recursion / Stack
//
// --------------------------------------------------
// Parallel BFS:
// Parallelism happens LEVEL-WISE
//
// Example:
//
//         0
//       /   \
//      1     2
//     / \   / \
//    3   4 5   6
//
// Thread 1 -> process 1
// Thread 2 -> process 2
//
// Then:
//
// Thread 1 -> 3
// Thread 2 -> 4
// Thread 3 -> 5
// Thread 4 -> 6
//
// --------------------------------------------------
// Parallel DFS:
// Parallelism happens BRANCH-WISE
//
// Thread 1 explores:
// 1 -> 3 -> 4
//
// Thread 2 explores:
// 2 -> 5 -> 6
//
// --------------------------------------------------
// Time Complexities
//
// Sequential BFS  : O(V + E)
// Parallel BFS    : O((V + E)/p)
//
// Sequential DFS  : O(V + E)
// Parallel DFS    : O((V + E)/p)
//
// V = Vertices
// E = Edges
// p = Threads / Processors
// --------------------------------------------------

#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

// ================= GRAPH CLASS =================

class Graph
{
    int V;

    // Adjacency list
    // adj[i] stores neighbors of node i
    vector<vector<int>> adj;

public:

    // Constructor
    Graph(int V)
    {
        this->V = V;

        // Resize adjacency list
        adj.resize(V);
    }

    // Add edge in undirected graph
    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // ==================================================
    //              SEQUENTIAL BFS
    // ==================================================

    void sequentialBFS(int start)
    {
        // Visited array
        vector<bool> visited(V, false);

        // Queue used in BFS
        queue<int> q;

        // Mark start node visited
        visited[start] = true;

        // Push starting node
        q.push(start);

        while(!q.empty())
        {
            // Get front node
            int node = q.front();

            // Remove from queue
            q.pop();

            // Print node
            cout << node << " ";

            // Traverse neighbors
            for(int neighbor : adj[node])
            {
                // Visit unvisited neighbors
                if(!visited[neighbor])
                {
                    visited[neighbor] = true;

                    // Add neighbor into queue
                    q.push(neighbor);
                }
            }
        }
    }

    // ==================================================
    //              PARALLEL BFS
    // ==================================================

    void parallelBFS(int start)
    {
        vector<bool> visited(V, false);

        queue<int> q;

        visited[start] = true;

        q.push(start);

        while(!q.empty())
        {
            int node;

            // Critical section:
            // Only one thread accesses queue at a time
            #pragma omp critical
            {
                node = q.front();
                q.pop();
            }

            cout << node << " ";

            // Parallelize neighbor traversal
            // Different neighbors handled by different threads
            #pragma omp parallel for
            for(int i = 0; i < adj[node].size(); i++)
            {
                int neighbor = adj[node][i];

                if(!visited[neighbor])
                {
                    visited[neighbor] = true;

                    // Queue is shared resource
                    // Prevent race condition
                    #pragma omp critical
                    {
                        q.push(neighbor);
                    }
                }
            }
        }
    }

    // ==================================================
    //              DFS UTILITY FUNCTION
    // ==================================================

    void dfsUtil(int node, vector<bool>& visited)
    {
        // Mark node visited
        visited[node] = true;

        // Print node
        cout << node << " ";

        // Parallel traversal of neighbors
        #pragma omp parallel for
        for(int i = 0; i < adj[node].size(); i++)
        {
            int neighbor = adj[node][i];

            if(!visited[neighbor])
            {
                // Recursive DFS call
                dfsUtil(neighbor, visited);
            }
        }
    }

    // ==================================================
    //              PARALLEL DFS
    // ==================================================

    void parallelDFS(int start)
    {
        vector<bool> visited(V, false);

        dfsUtil(start, visited);
    }
};

// ==================================================
//                  MAIN FUNCTION
// ==================================================

int main()
{
    // Set number of OpenMP threads
    omp_set_num_threads(4);

    // Create graph with 7 vertices
    Graph g(7);

    // Add edges
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,5);
    g.addEdge(2,6);

    // ==================================================
    //                  BFS
    // ==================================================

    cout << "Sequential BFS: ";

    // Start timer
    double start = omp_get_wtime();

    g.sequentialBFS(0);

    // End timer
    double end = omp_get_wtime();

    cout << "\nTime: " << end-start << " seconds\n";

    // --------------------------------------------------

    cout << "\nParallel BFS: ";

    start = omp_get_wtime();

    g.parallelBFS(0);

    end = omp_get_wtime();

    cout << "\nTime: " << end-start << " seconds\n";

    // ==================================================
    //                  DFS
    // ==================================================

    cout << "\nParallel DFS: ";

    start = omp_get_wtime();

    g.parallelDFS(0);

    end = omp_get_wtime();

    cout << "\nTime: " << end-start << " seconds\n";

    return 0;
}
#include <iostream>
#include <climits>
using namespace std;

const int NUM_NODES = 5;

// Function to find the node with the minimum distance value
int getMinDistanceNode(int distances[], bool visited[], int totalNodes) 
{
    int minDistance = INT_MAX, minIndex = -1;

    for (int node = 0; node < totalNodes; node++) 
    {
        if (!visited[node] && distances[node] < minDistance) {
            minDistance = distances[node];
            minIndex = node;
        }
    }
    return minIndex;
}

// Recursive function to display the path from source to destination
void printPath(int predecessors[], int node) 
{
    if (predecessors[node] == -1)  
        return;

    printPath(predecessors, predecessors[node]);  
    cout << " -> " << char(node + 'A');  
}

// Dijkstra's Algorithm implementation
void dijkstraAlgorithm(int graph[NUM_NODES][NUM_NODES], int sourceNode, int destinationNode) 
{
    int distances[NUM_NODES];  
    bool visited[NUM_NODES] = { false };       
    int predecessors[NUM_NODES];        

    for (int i = 0; i < NUM_NODES; i++) 
    {
        distances[i] = INT_MAX;
        predecessors[i] = -1;  
    }

    distances[sourceNode] = 0;

    for (int i = 0; i < NUM_NODES - 1; i++) 
    {
        int currentNode = getMinDistanceNode(distances, visited, NUM_NODES);
        visited[currentNode] = true;

        for (int adjacentNode = 0; adjacentNode < NUM_NODES; adjacentNode++) 
        {
            if (!visited[adjacentNode] && graph[currentNode][adjacentNode] > 0 &&
                distances[currentNode] != INT_MAX && 
                distances[currentNode] + graph[currentNode][adjacentNode] < distances[adjacentNode])
            {
                
                predecessors[adjacentNode] = currentNode;
                distances[adjacentNode] = distances[currentNode] + graph[currentNode][adjacentNode];  
            }
        }
    }

    // Output
    cout << "Shortest Path from " << char(sourceNode + 'A') << " to " << char(destinationNode + 'A') << ":\n";
    
    if (distances[destinationNode] == INT_MAX) 
    {
        cout << "No path exists between " << char(sourceNode + 'A') << " and " << char(destinationNode + 'A') << "." << endl;
    } else 
    {
        cout << "Cost: " << distances[destinationNode] << endl;
        cout << "Path: " << char(sourceNode + 'A');
        printPath(predecessors, destinationNode);  
        cout << endl;
    }
}

// Function to get valid vertex input from the user
char getValidVertexInput(const string& prompt) 
{
    char vertex;
    cout << prompt;
    cin >> vertex;

    while (vertex < 'A' || vertex >= 'A' + NUM_NODES)
    {
        cout << "Invalid input. " << prompt;
        cin >> vertex;
    }
    return vertex;
}

int main() 
{
    int adjacencyMatrix[NUM_NODES][NUM_NODES] = 
    {
        {0, 2, 5, 1, 0},  // A
        {2, 0, 0, 3, 2},  // B
        {5, 0, 0, 2, 0},  // C
        {1, 3, 2, 0, 4},  // D
        {0, 2, 0, 4, 0}   // E
    };

    char sourceVertex = getValidVertexInput("Enter the starting vertex (A to E): ");
    char destinationVertex = getValidVertexInput("Enter the ending vertex (A to E): ");

    int sourceNode = sourceVertex - 'A';
    int destinationNode = destinationVertex - 'A';

    dijkstraAlgorithm(adjacencyMatrix, sourceNode, destinationNode);

    return 0;
}

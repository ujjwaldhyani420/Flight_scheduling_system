#include <bits/stdc++.h>
using namespace std;

vector<string> cities(9);

class edge
{
public:
    int u;
    int v;
    int weight;
};

// CHEAPEST FLIGHT WITHIN K STOPS STARTS

// helper for cheapest flight within k stops
int helper(int u, int k, int dst, vector<vector<int>> &DP, vector<vector<pair<int, int>>> &GRAPH)
{
    if (u == dst) // destination reached no more price to be paid
        return DP[u][k] = 0;
    if (k == -1) // can't reach
        return INT_MAX;
    if (DP[u][k] != -1)
        return DP[u][k];
    int result = INT_MAX;
    for (int i = 0; i < GRAPH[u].size(); i++)
    {
        int v = GRAPH[u][i].first;
        int price = GRAPH[u][i].second;
        int temp = helper(v, k - 1, dst, DP, GRAPH);
        if (temp != INT_MAX)
            result = min(result, temp + price);
    }
    DP[u][k] = result;
    return DP[u][k];
}

// retrieving path from DP
void findingPath(int u, int k, int dst, vector<int> &path, vector<vector<int>> &DP, vector<vector<pair<int, int>>> &GRAPH)
{
    if (u == dst)
    {
        path.push_back(u);
        return;
    }
    if (k == -1)
        return;
    path.push_back(u);
    int result = INT_MAX, next = -1;
    // u -> v
    for (int i = 0; i < GRAPH[u].size(); i++)
    {
        int v = GRAPH[u][i].first;
        int price = GRAPH[u][i].second;
        int temp = DP[v][k - 1];
        // u -> v .... dst
        // price    temp
        if (temp != INT_MAX && result > temp + price) // smaller found
        {
            next = v;
            result = temp + price;
        }
    }
    if (next != -1)
        findingPath(next, k - 1, dst, path, DP, GRAPH);
}

// program for shortestFlightWithKstops
void findShortestPathWithinKStops(int n, int src, int dst, int k, vector<vector<pair<int, int>>> &Graph)
{
    int numFlights = 9;
    // DP[i][j] means shortestPath from src to i within j stops
    vector<vector<int>> DP(n, vector<int>(k + 1, -1)); // ith TO dest within k stop
    vector<int> path;
    int result = helper(src, k, dst, DP, Graph);
    if (result == INT_MAX)
    {
        return;
    }
    findingPath(src, k, dst, path, DP, Graph);
    cout << "\n\nPath for shortest Distance flight from " << cities[src] << " to " << cities[dst] << " within " << k << " stops would be :\n\n";
    for (auto x : path)
        cout << cities[x] << "  -->  ";
    cout << "BON VOYAGE";
    cout << "\n\n";
    cout << "Distance for this journey would be : " << result * 100 << " miles\n\n";
}

// CHEAPEST FLIGHT WITHIN K STOPS STARTS ENDS

// Part 2

void directedGraph(vector<vector<int>> &Graph)
{
    Graph = vector<vector<int>>(7);
    // adding all the edges
    edge edges[11];
    edges[0].u = 2, edges[0].v = 1;
    edges[1].u = 1, edges[1].v = 3;
    edges[2].u = 3, edges[2].v = 2;
    edges[3].u = 0, edges[3].v = 3;
    edges[4].u = 0, edges[4].v = 2;
    edges[5].u = 0, edges[5].v = 4;
    edges[6].u = 4, edges[6].v = 0;
    edges[7].u = 5, edges[7].v = 2;
    edges[8].u = 4, edges[8].v = 5;
    edges[9].u = 5, edges[9].v = 6;
    edges[10].u = 6, edges[10].v = 5;
    // edges[11].u = 3, edges[11].v = 5;
    // edges[12].u = 3, edges[12].v = 4;
    // edges[13].u = 5, edges[13].v = 4;
    for (int i = 0; i < 11; i++)
        Graph[edges[i].u].push_back(edges[i].v);
}
// Strongly Connected Components
void DFS_Tarjan_Algo(int u, vector<int> &Disc, vector<int> &Low,
                     stack<int> &myStack, vector<bool> &presentInStack, vector<vector<int>> &Graph, vector<vector<int>> &SCC)
{
    static int time;
    Disc[u] = Low[u] = time;
    time += 1;
    myStack.push(u);
    presentInStack[u] = true;
    for (auto v : Graph[u])
    {
        // not visited
        if (Disc[v] == -1)
        {
            DFS_Tarjan_Algo(v, Disc, Low, myStack, presentInStack, Graph, SCC);
            Low[u] = min(Low[u], Low[v]);
        }
        // visited + presentInStack => backEdge found
        else if (presentInStack[v] == true)
        {
            Low[u] = min(Low[u], Disc[v]);
        }
    }
    // whole operation is done
    // head node of a connected unit
    if (Low[u] == Disc[u])
    {
        vector<int> SC;
        while (myStack.top() != u)
        {
            // cout << myStack.top() << " ";
            SC.push_back(myStack.top());
            presentInStack[myStack.top()] = false;
            myStack.pop();
        }
        // cout << myStack.top() << " \n";
        SC.push_back(myStack.top());
        presentInStack[myStack.top()] = false;
        myStack.pop();
        SCC.push_back(SC);
    }
}

void find_SCC_Tarjan(vector<vector<int>> &Graph)
{
    int N = Graph.size();
    vector<int> Disc(N, -1), Low(N, -1);
    vector<bool> presentInStack(N, false);
    stack<int> myStack;
    vector<vector<int>> SCC;
    for (int i = 0; i < N; i++)
        if (Disc[i] == -1)
            DFS_Tarjan_Algo(i, Disc, Low, myStack, presentInStack, Graph, SCC);
    for (int i = 0; i < SCC.size(); i++)
    {
        cout << i + 1 << ". => ";
        for (auto x : SCC[i])
            cout << cities[x] << " -> ";
        cout << cities[SCC[i][0]] << "\n";
    }
}

// Bipartite Graph
void undirectedGraph(vector<vector<int>> &Graph)
{
    Graph = vector<vector<int>>(7);
    // adding all the edges
    edge edges[8];
    edges[0].u = 0, edges[0].v = 1;
    edges[1].u = 0, edges[1].v = 2;
    edges[2].u = 1, edges[2].v = 2;
    edges[3].u = 1, edges[3].v = 6;
    edges[4].u = 1, edges[4].v = 3;
    edges[5].u = 1, edges[5].v = 4;
    edges[6].u = 5, edges[6].v = 4;
    edges[7].u = 5, edges[7].v = 3;
    // edges[8].u = 4, edges[8].v = 5;
    // edges[9].u = 5, edges[9].v = 6;
    // edges[10].u = 6, edges[10].v = 5;
    // edges[11].u = 3, edges[11].v = 5;
    // edges[12].u = 3, edges[12].v = 4;
    // edges[13].u = 5, edges[13].v = 4;
    for (int i = 0; i < 8; i++)
    {
        Graph[edges[i].u].push_back(edges[i].v);
        Graph[edges[i].v].push_back(edges[i].u);
    }
}

void bipartiteGraph(vector<vector<int>> &Graph)
{
    Graph = vector<vector<int>>(6);
    // adding all the edges
    edge edges[6];
    edges[0].u = 0, edges[0].v = 3;
    edges[1].u = 0, edges[1].v = 4;
    edges[2].u = 1, edges[2].v = 4;
    edges[3].u = 1, edges[3].v = 5;
    edges[4].u = 2, edges[4].v = 3;
    edges[5].u = 2, edges[5].v = 5;
    // edges[6].u = 5, edges[6].v = 4;
    // edges[7].u = 5, edges[7].v = 3;
    // edges[8].u = 4, edges[8].v = 5;
    // edges[9].u = 5, edges[9].v = 6;
    // edges[10].u = 6, edges[10].v = 5;
    // edges[11].u = 3, edges[11].v = 5;
    // edges[12].u = 3, edges[12].v = 4;
    // edges[13].u = 5, edges[13].v = 4;
    for (int i = 0; i < 6; i++)
    {
        Graph[edges[i].u].push_back(edges[i].v);
        Graph[edges[i].v].push_back(edges[i].u);
    }
}

// Articulation Points
void DFS_Tarjan_Algo_AP(int u, vector<int> &Disc, vector<int> &Low,
                        vector<bool> &AP, vector<int> &Parent, vector<vector<int>> &Graph)
{
    static int time;
    Disc[u] = Low[u] = time;
    time += 1;
    int children = 0;
    for (auto v : Graph[u])
    {
        // not visited
        if (Disc[v] == -1)
        {
            children++;
            Parent[v] = u;
            DFS_Tarjan_Algo_AP(v, Disc, Low, AP, Parent, Graph);
            Low[u] = min(Low[u], Low[v]);
            // special case for ROOT node
            if (Parent[u] == -1 && children > 1)
                AP[u] = true;
            // NON ROOT node
            // child can not reach out to ancestor
            if (Parent[u] != -1 && Low[v] >= Disc[u])
                AP[u] = true;
        }
        // visited => backEdge || crossEdge found
        else if (Parent[u] != v)
        {
            Low[u] = min(Low[u], Disc[v]);
        }
    }
}

void find_Articulation(vector<vector<int>> &Graph)
{
    int N = Graph.size();
    vector<int> Disc(N, -1), Low(N, -1), Parent(N, -1);
    vector<bool> AP(N, false);
    for (int i = 0; i < N; i++)
        if (Disc[i] == -1)
            DFS_Tarjan_Algo_AP(i, Disc, Low, AP, Parent, Graph);
    cout << "Articulation points are : ";
    for (int i = 0; i < AP.size(); i++)
    {
        if (AP[i] == true)
            cout << "(" << cities[i] << "), ";
    }
    cout << "\n";
}

// Bridges
void DFS_Tarjan_Algo_Bridges(int u, vector<int> &Disc, vector<int> &Low,
                             vector<pair<int, int>> &Bridge, vector<int> &Parent, vector<vector<int>> &Graph)
{
    static int time;
    Disc[u] = Low[u] = time;
    time += 1;
    // int children = 0;
    for (auto v : Graph[u])
    {
        // not visited
        if (Disc[v] == -1)
        {
            // children++;
            Parent[v] = u;
            DFS_Tarjan_Algo_Bridges(v, Disc, Low, Bridge, Parent, Graph);
            Low[u] = min(Low[u], Low[v]);
            // checking
            if (Low[v] > Disc[u])
            {
                Bridge.push_back({u, v});
            }
        }
        // visited => backEdge || crossEdge found
        else if (Parent[u] != v)
        {
            Low[u] = min(Low[u], Disc[v]);
        }
    }
}

void find_Bridges(vector<vector<int>> &Graph)
{
    int N = Graph.size();
    vector<int> Disc(N, -1), Low(N, -1), Parent(N, -1);
    vector<pair<int, int>> Bridge;
    for (int i = 0; i < N; i++)
        if (Disc[i] == -1)
            DFS_Tarjan_Algo_Bridges(i, Disc, Low, Bridge, Parent, Graph);
    cout << "Bridges are : ";
    for (int i = 0; i < Bridge.size(); i++)
    {
        int u = Bridge[i].first;
        int v = Bridge[i].second;
        cout << "(" << cities[u] << "  =>  " << cities[v] << "), ";
    }
    cout << "\n";
}

// bipartite
void Bipartite(vector<vector<int>> &Graph)
{
    int N = Graph.size();
    vector<int> Color(N, -1);
    // 0 -> black
    // 1 -> white
    // -1 -> unvisited
    queue<int> myQ;
    Color[0] = 0;
    myQ.push(0);
    bool bipartite = true;
    while (!myQ.empty())
    {
        int u = myQ.front();
        myQ.pop();
        for (auto v : Graph[u])
        {
            if (Color[v] == -1)
            {
                Color[v] = !Color[u];
                myQ.push(v);
            }
            else if (Color[v] == Color[u])
            {
                bipartite = false;
            }
        }
    }
    if (bipartite == false)
    {
        cout << "Graph is not bipartite\n";
    }
    else
    {
        cout << "Graph is bipartite\n";
        cout << "Group 1 : ";
        for (int i = 0; i < N; i++)
        {
            if (Color[i] == 0)
                cout << cities[i] << ", ";
        }
        cout << "\n";
        cout << "Group 2 : ";
        for (int i = 0; i < N; i++)
        {
            if (Color[i] == 1)
                cout << cities[i] << ", ";
        }
        cout << "\n";
    }
}

// Probability Seat Assignment problem
void nthPersonGetsNthSeat()
{
    cout << "Enter number of passengers\n";
    int n;
    cin >> n;
    if (n == 1)
    {
        cout << "The probability that " << n << "th person would get to sit on his own seat is " << 1 << "\n";
        return;
    }
    vector<double> DP(n + 1, 0);
    DP[1] = 1.0;
		for(int i = 2 ; i <= n; i++)
			DP[i] = 1/i + ((i-2)/i)*DP[i-1];

    cout << "The probability that " << n << "th person would get to sit on his own seat is " <<  DP[n] << "\n";
}

int main()
{
    cities[0] = "London, England";
    cities[1] = "Paris, France";
    cities[2] = "New York City, United States";
    cities[3] = "Moscow, Russia";
    cities[4] = "Dubai, United Arab Emirates";
    cities[5] = "Tokyo, Japan";
    cities[6] = "Singapore";
    cities[7] = "Los Angeles, United States";
    cities[8] = "Barcelona, Spain";
    // adding all the edges
    edge edges[14];
    edges[0].u = 0, edges[0].v = 1, edges[0].weight = 4;
    edges[1].u = 0, edges[1].v = 7, edges[1].weight = 8;
    edges[2].u = 1, edges[2].v = 7, edges[2].weight = 11;
    edges[3].u = 1, edges[3].v = 2, edges[3].weight = 8;
    edges[4].u = 2, edges[4].v = 8, edges[4].weight = 2;
    edges[5].u = 7, edges[5].v = 8, edges[5].weight = 7;
    edges[6].u = 7, edges[6].v = 6, edges[6].weight = 1;
    edges[7].u = 8, edges[7].v = 6, edges[7].weight = 6;
    edges[8].u = 2, edges[8].v = 5, edges[8].weight = 4;
    edges[9].u = 6, edges[9].v = 5, edges[9].weight = 2;
    edges[10].u = 2, edges[10].v = 3, edges[10].weight = 7;
    edges[11].u = 3, edges[11].v = 5, edges[11].weight = 14;
    edges[12].u = 3, edges[12].v = 4, edges[12].weight = 9;
    edges[13].u = 5, edges[13].v = 4, edges[13].weight = 10;

    // creating the graph
    vector<vector<pair<int, int>>> Graph(10); // 1 2 3 4 .. 9 nodes
    vector<vector<int>> G2;
    directedGraph(G2);
    vector<vector<int>> G3, G4;
    undirectedGraph(G3);
    bipartiteGraph(G4);

    // find_SCC_Tarjan(G2);
    // find_Articulation(G3);
    // find_Bridges(G3);
    // Bipartite(G3);

    for (int i = 0; i < 14; i++)
    {
        Graph[edges[i].u].push_back({edges[i].v, edges[i].weight});
        Graph[edges[i].v].push_back({edges[i].u, edges[i].weight});
    }

    char choice = 'Y';
    cout << "----------------------------------------------------" << endl;
    cout << "FLIGHT SCHEDULING SYSTEM IN C++" << endl;
    cout << "----------------------------------------------------" << endl;
    while (choice == 'y' || choice == 'Y')
    {
        vector<int> weights(100, INT_MAX);
        vector<bool> setMST(100, false);
        int src, dst, K;
        int node;
        int answer;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "Choose an action from the tasks pane to continue.";
        cout << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        cout << "\nPress 1 to find the shortest distance flight from a source to destination within K stops.(Dynamic Programming + Graphs)" << endl
             << endl;
        cout << "Press 2 to find the strongly connected components" << endl
             << endl;
        cout << "Press 3 to find the articulation point in our graph" << endl
             << endl;
        cout << "Press 4 to find the bridges in our graph" << endl;

        cout << "\nPress 5 to find whether our graph is bipartite or not"
             << endl;
        cout << "\nPress 6 for Airplane Seat Assignment Probability" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        int step;
        cin >> step;
        switch (step)
        {
        case 1:
            cout << "Enter the src (0-8), the destination and the stops limit\n";
            cin >> src >> dst >> K;
            findShortestPathWithinKStops(9, src, dst, K, Graph);
            break;
        case 2:
            find_SCC_Tarjan(G2);
            break;
        case 3:
            find_Articulation(G3);
            break;
        case 4:
            find_Bridges(G3);
            break;
        case 5:
            Bipartite(G4);
            break;
        case 6:
            nthPersonGetsNthSeat();
            break;
        }
        cout << endl
             << "Press y to continue." << endl;
        cin >> choice;
        system("cls");
    }
    return 0;
}

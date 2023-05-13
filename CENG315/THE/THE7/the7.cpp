#include "the7.h"
using namespace std;

// Implement your solution after this line
int INF = INT_MAX;

vector<vector<int>> dijkstra(std::vector<Road> roads, int n, int source, int destination)
{
    vector<vector<int>> result;

    vector<vector<pair<int, int>>> adj_list; // adjacency list of the graph
    vector<int> min_distance(n, INF);
    vector<int> predecessor(n, -1);
    adj_list.resize(n);
    // initialize distances and set up the priority queue
    for (int i = 0; i < roads.size(); i++)
    {
        int pair1 = roads[i].buildings.first;
        int pair2 = roads[i].buildings.second;
        int time = roads[i].time;

        adj_list[pair1].emplace_back(time, pair2);
    }

    min_distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.emplace(0, source);

    // main loop
    while (!pq.empty())
    {
        // Extract the node with the minimum distance
        int distance = pq.top().first;
        int pair1 = pq.top().second;
        pq.pop();

        // Skip the node if it has already been processed
        if (distance > min_distance[pair1])
            continue;

        // Update the minimum distance and predecessor for each neighbor
        for (int i = 0; i < adj_list[pair1].size(); i++)
        {
            int time = adj_list[pair1][i].first;
            int pair2 = adj_list[pair1][i].second;

            int alt = distance + time;
            if (alt < min_distance[pair2])
            {
                min_distance[pair2] = alt;
                predecessor[pair2] = pair1;
                pq.emplace(alt, pair2);
            }
        }
    }
    result.push_back(min_distance);
    result.push_back(predecessor);
    return result;
}

vector<int> Func(int n, std::vector<Road> roads, vector<int> &path, int &time, int &new_way, int x, int y, int l, int &min, int a)
{
    vector<int> temp_min_distance;
    vector<int> temp_predecessor;
    vector<int> temp_path;
    stack<int> stack1;
    int dp = a ? x : y;
    for (int i = 0; i < path.size(); i++)
    {
        int p1 = path[i] < dp ? path[i] : dp;
        int p2 = path[i] >= dp ? path[i] : dp;
        temp_min_distance = dijkstra(roads, n, p1, p2)[0];
        temp_predecessor = dijkstra(roads, n, p1, p2)[1];
        if ((time + 2 * temp_min_distance[p2] < l) && temp_min_distance[p2] < min)
        {
            min = temp_min_distance[p2];
            new_way = i;
            int temp = p2;
            while (temp != -1)
            {
                temp_path.insert(temp_path.begin(), temp);
                temp = temp_predecessor[temp];
            }

            if (path[i] == temp_path[0])
            {
                for (int j = 0; j <= temp_path.size() - 2; j++)
                {
                    stack1.push(temp_path[j]);
                }
                while (!stack1.empty())
                {
                    temp_path.push_back(stack1.top());
                    stack1.pop();
                }
            }
            else
            {
                for (int j = temp_path.size() - 1; j > 0; j--)
                {
                    stack1.push(temp_path[j]);
                }
                while (!stack1.empty())
                {
                    temp_path.insert(temp_path.begin(), stack1.top());
                    stack1.pop();
                }
            }
        }
    }
    // PrintRange(temp_path.begin(), temp_path.end());
    return temp_path;
}

void CanCatch(int n, std::vector<Road> roads, int s, int d, int x, int y, int l, int printPath)
{
    // You can change these variables. These are here for demo only.
    std::vector<int> path;
    vector<int> min_distance = dijkstra(roads, n, s, d)[0];
    vector<int> predecessor = dijkstra(roads, n, s, d)[1];
    bool dorm = false;
    bool printer = false;
    string result = "";
    int cost = INT_MAX;
    int time = min_distance[d];

    if (time > l)
    {
        cout << "IMPOSSIBLE" << endl;
    }
    else
    {
        int temp = d;
        while (temp != -1)
        {
            path.insert(path.begin(), temp);
            temp = predecessor[temp];
            if (temp == x)
                printer = true;
            if (temp == y)
                dorm = true;
        }

        int new_way = -1;

        if (dorm && !printer)
        {
            vector<int> temp_path = Func(n, roads, path, time, new_way, x, y, l, cost, 1);
            if (new_way != -1)
            {
                printer = true;
                time += (2 * cost);
                for (int i = temp_path.size() - 1; i > 0; i--)
                {
                    path.insert(path.begin() + new_way + 1, temp_path[i]);
                }
            }
        }
        else if (printer && !dorm)
        {
            vector<int> temp_path = Func(n, roads, path, time, new_way, x, y, l, cost, 0);
            if (new_way != -1)
            {
                dorm = true;
                time += (2 * cost);
                for (int i = temp_path.size() - 1; i > 0; i--)
                {
                    path.insert(path.begin() + new_way + 1, temp_path[i]);
                }
            }
        }
        else
        {
            new_way = -1;
            vector<int> temp_path = Func(n, roads, path, time, new_way, x, y, l, cost, 1);
            if (new_way != -1)
            {
                printer = true;
                time += (2 * cost);
                for (int i = temp_path.size() - 1; i > 0; i--)
                {
                    path.insert(path.begin() + new_way + 1, temp_path[i]);
                }
            }
            cost = INF;
            new_way = -1;
            vector<int> temp_path2 = Func(n, roads, path, time, new_way, x, y, l, cost, 0);
            if (new_way != -1)
            {
                dorm = true;
                time += (2 * cost);
                for (int i = temp_path2.size() - 1; i > 0; i--)
                {
                    path.insert(path.begin() + new_way + 1, temp_path2[i]);
                }
            }
        }
        if (dorm && printer)
            result = "BOTH ";

        else if (dorm)
            result = "DORM ";

        else if (printer)
            result = "PRINTER ";

        else
            result = "DIRECTLY ";

        cout << "YES " << result << time << "MINUTES" << endl;

        if (printPath)
        {
            PrintRange(path.begin(), path.end());
        }
    }
}
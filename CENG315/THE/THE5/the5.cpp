#include "the5.h"
using namespace std;

int indexFinder(int id, vector<Room *> maze)
{
	for (int i = 0; i < maze.size(); i++)
	{
		if (id == maze[i]->id)
			return i;
	}
}

bool contains(int i, vector<int> path)
{
	for (int j = 0; j < path.size(); j++)
	{
		if (path[j] == i)
			return true;
	}
	return false;
}

vector<int> maze_trace(vector<Room *> maze)
{
	vector<int> path;
	stack<int> visited;
	stack<int> neighbors;

	int roomId = maze[0]->id;

	neighbors.push(roomId);
	visited.push(roomId);

	while (!neighbors.empty())
	{
		bool pushed = false;
		path.push_back(roomId);
		int index = indexFinder(roomId, maze);

		if (maze[index]->content == '*')
		{
			while (!visited.empty())
			{
				path.push_back(visited.top());
				visited.pop();
			}
			break;
		}

		if (visited.empty() || visited.top() != roomId)
			visited.push(roomId);

		for (int i = maze[roomId]->neighbors.size() - 1; i >= 0; i--)
		{
			if (!contains(maze[index]->neighbors[i]->id, path))
			{
				neighbors.push(maze[index]->neighbors[i]->id);
				pushed = true;
			}
		}

		if (!pushed)
		{
			visited.pop();
			roomId = visited.top();
		}
		else
		{
			roomId = neighbors.top();
			neighbors.pop();
		}
	}

	return path;
}

#include <bits/stdc++.h>
using namespace std;

#define ROW 8
#define COL 8

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> > pPair;

struct cell
{
	int parent_i, parent_j;
	double f, g, h;
};

bool isValid(int row, int col)
{
	return (row >= 0) && (row < ROW) &&
		   (col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col)
{
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

bool isDestination(int row, int col, Pair dest)
{
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double Heuristics1(int row, int col, Pair dest)
{
	return ((double)sqrt((row - dest.first) * (row - dest.first) + (col - dest.second) * (col - dest.second)));
}

double Heuristics2(int row, int col, Pair dest)
{
	double i = ((double)(abs(row - dest.first) + abs(col - dest.second)));
	return i;
}

void tracePath(cell cellDetails[][COL], Pair dest)
{
	printf("\nThe Path is ");
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));
	while (!Path.empty())
	{
		pair<int, int> p = Path.top();
		Path.pop();
		cout << "-> "
			 << "(" << p.first << "," << p.second << ") ";
	}

	return;
}

void aStarSearch(int grid[][COL], Pair src, Pair dest, int hs)
{
	if (isValid(src.first, src.second) == false)
	{
		printf("Source is invalid\n");
		return;
	}

	if (isValid(dest.first, dest.second) == false)
	{
		printf("Destination is invalid\n");
		return;
	}
	// Either the source or the destination is blocked
	if (isUnBlocked(grid, src.first, src.second) == false ||
		isUnBlocked(grid, dest.first, dest.second) == false)
	{
		cout << "Source or the destination is blocked" << endl;
		return;
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pPair> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();
		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		//----------- 1st Successor (UP) ------------
		for (int k = i-1; k >= 0; k--)
		{
			if(isUnBlocked(grid,k,j) == false)
			break;
			if (isValid(k, j) == true)
			{
				if (isDestination(k, j, dest) == true)
				{
					cellDetails[k][j].parent_i = i;
					cellDetails[k][j].parent_j = j;
					cout << "The destination cell is found" << endl;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}

				else if (closedList[k][j] == false &&
						 isUnBlocked(grid, k, j) == true)
				{
					gNew = cellDetails[i][j].g + 1.0;

					if (hs == 1)
					{
						hNew = Heuristics1(k, j, dest);
					}
					else
					{
						hNew = Heuristics2(k, j, dest);
					}

					fNew = gNew + hNew;

					if (cellDetails[k][j].f == FLT_MAX ||
						cellDetails[k][j].f > fNew)
					{
						openList.insert(make_pair(fNew, make_pair(k, j)));
						cellDetails[k][j].f = fNew;
						cellDetails[k][j].g = gNew;
						cellDetails[k][j].h = hNew;
						cellDetails[k][j].parent_i = i;
						cellDetails[k][j].parent_j = j;
					}
				}
			}
			else
			{
				break;
			}
			
		}

		//----------- 2nd Successor (DOWN) ------------
		for (int k = i + 1; k < 8; k++)
		{
			if(isUnBlocked(grid,k,j) == false)
			break;

			if (isValid(k, j) == true)
			{
				if (isDestination(k, j, dest) == true)
				{
					cellDetails[k][j].parent_i = i;
					cellDetails[k][j].parent_j = j;
					cout << "The destination cell is found" << endl;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}
				else if (closedList[k][j] == false &&
						 isUnBlocked(grid, k, j) == true)
				{
					gNew = cellDetails[i][j].g + 1.0;
					if (hs == 1)
					{
						hNew = Heuristics1(k, j, dest);
					}
					else
					{
						hNew = Heuristics2(k, j, dest);
					}
					fNew = gNew + hNew;

					if (cellDetails[k][j].f == FLT_MAX ||
						cellDetails[k][j].f > fNew)
					{
						openList.insert(make_pair(fNew, make_pair(k, j)));
						cellDetails[k][j].f = fNew;
						cellDetails[k][j].g = gNew;
						cellDetails[k][j].h = hNew;
						cellDetails[k][j].parent_i = i;
						cellDetails[k][j].parent_j = j;
					}
				}
			}
			else
			{
				break;
			}
			
		}

		//----------- 3rd Successor (RIGHT) ------------

		for (int k = j+1; k < 8; k++)
		{
			if(isUnBlocked(grid,i,k) == false)
			break;
			if (isValid(i, k) == true)
			{
				if (isDestination(i, k, dest) == true)
				{
					cellDetails[i][k].parent_i = i;
					cellDetails[i][k].parent_j = j;
					cout << "The destination cell is found" << endl;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}

				else if (closedList[i][k] == false &&
						 isUnBlocked(grid, i, k) == true)
				{
					gNew = cellDetails[i][j].g + 1.0;
					if (hs == 1)
					{
						hNew = Heuristics1(i, k, dest);
					}
					else
					{
						hNew = Heuristics2(i , k, dest);
					}
					fNew = gNew + hNew;

					if (cellDetails[i][k].f == FLT_MAX ||
						cellDetails[i][k].f > fNew)
					{
						openList.insert(make_pair(fNew, make_pair(i, k)));
						cellDetails[i][k].f = fNew;
						cellDetails[i][k].g = gNew;
						cellDetails[i][k].h = hNew;
						cellDetails[i][k].parent_i = i;
						cellDetails[i][k].parent_j = j;
					}
				}
			}
			else break;
		}

		//----------- 4th Successor (LEFT) ------------

		for (int k = j-1; k >= 0; k++)
		{
			if(isUnBlocked(grid,i,k) == false)
			break;

			if (isValid(i, k) == true)
			{
				if (isDestination(i, k, dest) == true)
				{
					cellDetails[i][k].parent_i = i;
					cellDetails[i][k].parent_j = j;
					cout << "The destination cell is found" << endl;
					tracePath(cellDetails, dest);
					foundDest = true;
					return;
				}

				else if (closedList[i][k] == false &&
						 isUnBlocked(grid, i, k) == true)
				{
					gNew = cellDetails[i][j].g + 1.0;
					if (hs == 1)
					{
						hNew = Heuristics1(i, k, dest);
					}
					else
					{
						hNew = Heuristics2(i , k, dest);
					}
					fNew = gNew + hNew;

					if (cellDetails[i][k].f == FLT_MAX ||
						cellDetails[i][k].f > fNew)
					{
						openList.insert(make_pair(fNew, make_pair(i, k)));
						cellDetails[i][k].f = fNew;
						cellDetails[i][k].g = gNew;
						cellDetails[i][k].h = hNew;
						cellDetails[i][k].parent_i = i;
						cellDetails[i][k].parent_j = j;
					}
				}
			}
			else break;
		}
	}

	if (foundDest == false)
		cout << "Failed to find the Destination Cell" << endl;

	return;
}

int main()
{
	int grid[ROW][COL] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1},
			{1, 0, 0, 0, 0, 1, 1, 1},
			{1, 0, 1, 1, 0, 1, 0, 1},
			{1, 0, 1, 1, 0, 1, 0, 1},
			{1, 0, 1, 1, 0, 1, 0, 1},
			{1, 0, 1, 1, 1, 1, 0, 1},
			{1, 0, 0, 0, 0, 0, 0, 1},
			{1, 1, 1, 1, 1, 1, 1, 1}};

	Pair src = make_pair(3, 2);

	Pair dest = make_pair(3, 7);

	aStarSearch(grid, src, dest, 1);

	return (0);
}

//The Path is -> (3,2) -> (5,2) -> (5,5) -> (1,5) -> (1,7) -> (3,7)
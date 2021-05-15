#include "Graph.h"

Graph::Graph()
{
	_mat = { {0, 0, 13, 15, 0, 0},
			 {28, 0, 0, 20, 0, 0},
			 {0, 0, 0, 0, 30, 0},
			 {0, 0, 0, 0, 39, 31},
			 {0, 21, 0, 39, 0, 0},
			 {18, 0, 0, 0, 0, 0} };
}

Graph::Graph(vector<vector<int>> source)
{
	if (source.size() > 0 && source.size() == source[0].size())
	_mat = source;
}

int Graph::RoadLength(int dep, int arr)
{
	dep--;
	arr--;
	if (arr >= 0 && arr < _mat.size() && dep >= 0 && dep < _mat.size())
	{
		return _mat[dep][arr];
	}
	else
	{
        return 0;
	}
}

int Graph::MinLength(int dep, int arr)
{
	if (dep == arr) return 0;	

	dep--;
	arr--;

	// preparing
	_minRoad.clear();
	_checkedList.clear();
	for (int i = 0; i < _mat.size(); i++)
	{
		_minRoad.push_back(10000);
		_checkedList.push_back(false);
	}

	// starting from departure node
	// road from dep to dep will be infinity
	for (int i = 0; i < _mat.size(); i++)
	{
		if (RoadLength(dep + 1, i + 1) > 0)
		{			
			_minRoad[i] = min(_minRoad[i], RoadLength(dep + 1, i + 1));
		}
	}
	_checkedList[dep] = true;

	// for avoid looping
	int k = _mat.size() * 2;
	// now check other elements
	while (!IsAllChecked() && k > 0)
	{
		k--;
		for (int i = 0; i < _mat.size(); i++)
		{
			if (!_checkedList[i])
			{
				for (int j = 0; j < _mat.size(); j++)
				{
					if (RoadLength(i + 1, j + 1) > 0)
					{
						_minRoad[j] = min(_minRoad[j], _minRoad[i] + RoadLength(i + 1, j + 1));
					}
				}
				_checkedList[i] = true;
			}
		}
	}

	return _minRoad[arr];
}

bool Graph::IsAllChecked()
{
	for (int i = 0; i < _checkedList.size(); i++)
	{
		if (!_checkedList[i]) return false;
	}
	return true;
}

int Graph::Size()
{
    return _mat.size();
}

// Komivoyzer
vector<int> Graph::Komivoyazer()
{
    _way = vector<int>();
    _cop = _mat;
    SetInfInsteadZero();

    while (!IsSearchEnd())
    {
        RowsReduction();
        ColumnsReduction();

        SetMarks();

        int r = 0, c = 0;
        FindMaxMark(r, c);

        InsertWay(r, c);

        SetInf(r, c);

        _cop[c][r] = -5;
    }

    return _way;
}

void Graph::SetInfInsteadZero()
{
    for (int i = 0; i < _cop.size(); i++)
    {
        for (int j = 0; j < _cop.size(); j++)
        {
            if (_cop[i][j] == 0)
            {
                _cop[i][j] = -5;
            }
        }

        //_cop[i][i] = -5;
    }
}

bool Graph::IsSearchEnd()
{
    for (int i = 0; i < _cop.size(); i++)
    {
        for (int j = 0; j < _cop.size(); j++)
        {
            if (_cop[i][j] >= 0)
            {
                return false;
            }
        }
    }
    return true;
}

void Graph::RowsReduction()
{
    for (int i = 0; i < _cop.size(); i++)
    {
        int min = 10000;
        // search minimum
        for (int j = 0; j < _cop.size(); j++)
        {
            if (_cop[i][j] < min && _cop[i][j] >= 0)
            {
                min = _cop[i][j];
            }
        }
        // decrease
        for (int j = 0; j < _cop.size(); j++)
        {
            _cop[i][j] = _cop[i][j] - min;
        }
    }
}

void Graph::ColumnsReduction()
{
    for (int i = 0; i < _cop.size(); i++)
    {
        int min = 10000;
        // search minimum
        for (int j = 0; j < _cop.size(); j++)
        {
            if (_cop[j][i] < min && _cop[j][i] >= 0)
            {
                min = _cop[j][i];
            }
        }
        // decrease
        for (int j = 0; j < _cop.size(); j++)
        {
            _cop[j][i] = _cop[j][i] - min;
        }
    }
}

int Graph::MinInRow(int r, int c)
{
    int min = 10000;
    for (int i = 0; i < _cop.size(); i++)
    {
        if (i != c && _cop[r][i] < min && _cop[r][i] >= 0)
        {
            min = _cop[r][i];
        }
    }
    return min;
}

int Graph::MinInColumn(int r, int c)
{
    int min = 10000;
    for (int i = 0; i < _cop.size(); i++)
    {
        if (i != r && _cop[i][c] < min && _cop[i][c] >= 0)
        {
            min = _cop[i][c];
        }
    }
    return min;
}

void Graph::SetMarks()
{
    vector<vector<int>> t;
    for (int i = 0; i < _cop.size(); i++)
    {
        vector<int> row;
        for (int j = 0; j < _cop.size(); j++)
        {
            row.push_back(0);
            if (_cop[i][j] == 0)
            {
                row[j] = MinInRow(i, j) + MinInColumn(i, j);
            }
        }
        t.push_back(row);
    }
    _marks = t;
}

void Graph::FindMaxMark(int &r, int &c)
{
    int max = 0;
    // set first zero as max
    bool f = true;
    for (int i = 0; i < _cop.size() && f; i++)
    {
        for (int j = 0; j < _cop.size() && f; j++)
        {
            if (i != j && _cop[i][j] == 0)
            {
                r = i;
                c = j;
                max = _marks[i][j];
                f = false;
            }
        }
    }
    // find max
    for (int i = 0; i < _marks.size(); i++)
    {
        for (int j = 0; j < _marks.size(); j++)
        {
            if (_marks[i][j] > max && _cop[i][j] >= 0)
            {
                max = _marks[i][j];
                r = i;
                c = j;
            }
        }
    }
}

void Graph::SetInf(int r, int c)
{
    for (int i = 0; i < _cop.size(); i++)
    {
        _cop[r][i] = -5;
        _cop[i][c] = -5;
    }
}

void Graph::InsertWay(int dep, int arr)
{
    if (_way.size() == 0)
    {
        _way.push_back(dep);
        _way.push_back(arr);
    }
    else
    {
        // search dep point
        unsigned int ind = 0;
        while (ind < _way.size() && _way[ind] != dep) ind++;
        if (ind < _way.size())
        {
            // dep is last element
            if (ind + 1 == _way.size())
            {
                _way.push_back(arr);
            }
            // check next element
            else if (ind + 1 == _way.size() && _way[ind + 1] != arr)
            {
                _way.insert(_way.begin() + ind + 1, arr);
            }
        }
        // check arr point
        else
        {
            ind = 0;

            while (ind < _way.size() && _way[ind] != arr) ind++;
            if (ind < _way.size())
            {
                _way.insert(_way.begin() + ind, dep);
            }
            // no dep or arr point
            else
            {
                _way.push_back(dep);
                _way.push_back(arr);
            }
        }
    }
}

string Graph::GetWay()
{
    string res = "";
    if (_way.size() > 0)
    {
        res = to_string(_way[0] + 1);
        for (int i = 1; i < _way.size(); i++)
        {
            res += "->" + to_string(_way[i] + 1);
        }
    }
    return res;
}

int Graph::WaySize()
{
    int res = 0;
    if (_way.size() > 1)
    {
        res = RoadLength(_way[0] + 1, _way[1] + 1);
        for (int i = 1; i < _way.size() - 1; i++)
        {
            res += RoadLength(_way[i] + 1, _way[i + 1] + 1);
        }
        res += RoadLength(_way[_way.size() - 1] + 1, _way[0] + 1);
    }
    return res;
}

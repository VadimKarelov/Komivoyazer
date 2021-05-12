#pragma once
#include <vector>
#include <string>
using namespace std;

class Graph
{
protected:
	// adjacency matrix
	vector<vector<int>> _mat;

    // road for komivoyazer
    vector<int> _way;

private:
    // for komivoyzer
    vector<vector<int>> _cop;

    void SetInfInsteadZero();

    bool IsSearchEnd();

    void RowsReduction();

    void ColumnReduction();

    vector<vector<int>> _marks;

    int MinInRow(int i, int j);

    int MinInColumn(int i, int j);

    void SetMarks();

    void FindMaxMark(int &r, int &c);

    void SetInf(int r, int c);

    void InsertWay(int dep, int arr);

	// for search
	vector<int> _minRoad;
	vector<bool> _checkedList;

    bool IsAllChecked();

public:
	Graph();

	Graph(vector<vector<int>> source);

	// departure and arrival, start with 1
	int RoadLength(int dep, int arr);

	int MinLength(int dep, int arr);

    int Size();

    vector<int> Komivoyazer();

    string GetWay();

    int WaySize();
};

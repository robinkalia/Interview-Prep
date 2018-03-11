// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// Shortest path in a Binary Maze
// Given a MxN matrix where each element can either be 0 or 1. We need to find the shortest path between a given source cell to a destination cell. The path can only be created out of a cell if its value is 1.
//
// Expected time complexity is O(MN).
//
// For example –
//
// Input:
// mat[ROW][COL]  = {{1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//                   {1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
//                   {1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
//                   {0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
//                   {1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
//                   {1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
//                   {1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//                   {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//                   {1, 1, 0, 0, 0, 0, 1, 0, 0, 1 }};
// Source = {0, 0};
// Destination = {3, 4};
//
// Output:
// Shortest Path is 11 

#include <iostream>
#include <map>
#include <vector>
#include <queue>

class Cell 
{
private:
    std::pair<int32_t, int32_t> pos;
    bool visited;
    int32_t currDist;
    bool value;

public:
    static const int32_t INVALID_DIST = -1;
    static const vector<int32_t> rowVals = {-1, 0, 0, 1};
    static const vector<int32_t> colVals = {0, -1, 1, 0};

    Cell() : pos(std::pair<int32_t,int32_t>(0,0)), value(false), visited(false), currDist(0) {
    }

    ~Cell() {
        this->visited = false;
        this->currDist = INVALID_DIST; 
    }

    void setValues(const std::pair<int32_t, int32_t>& position, bool cellValue=false, bool visitedCell=false, int32_t dist=0) {
        this->pos = position;
        this->value = cellValue;
        this->visited = visitedCell;
        this->currDist = dist;
    }

    void setVisited(bool visitedCell) {
        this->visited = visitedCell;
    }

    void setCurrDist(int32_t currDistVal) {
        this->currDist = currDistVal;
    }

    std::pair<int32_t, int32_t> getPos() const {    return this->pos;   }
    bool getVisited() const {   return this->visited;       };
    bool getValue() const   {   return this->value;     }
    int32_t getCurrDist() const { return this->currDist; }
};


class Maze {
private:
    std::vector<std::vector<Cell> > mazeCells;
    
public:

    bool isValidCoordinates(const std::pair<int32_t, int32_t>& point) {
        return ( (point.first >= 0) && (point.second >= 0) && 
                 (point.first < this->rowSize()) && (point.second < this->colSize()));
    }
    int32_t rowSize()   {   return mazeCells.size(); }
    int32_t colSize()   {   return (this->rowSize() > 0) ? mazeCells[0].size() : 0; }
    int32_t findDis(const std::pair<int32_t, int32_t>& src, const std::pair<int32_t, int32_t>& dest);
};


int32_t Maze::findDis(const std::pair<int32_t, int32_t>& src, const std::pair<int32_t, int32_t>& dest) 
{
    if (!(this->isValidCoordinates(src) && this->isValidCoordinates(dest) && 
          mazeCells[src.first][src.second].getValue() == 1 && mazeCells[dest.first][dest.second].getValue() == 1)) {
        return Cell::INVALID_DIST;
    }
    
    std::queue<Cell> cellQueue;
    cellQueue.push(mazeCells[src.first][src.second]);

    while (!cellQueue.empty()) {
        Cell frontCell = cellQueue.front();
        if (frontCell.getPos() == dest) {
            return frontCell.getCurrDist();
        }

        cellQueue.pop();

        for (int32_t i=0; i<Cell::rowVals.size(); i++) {
            int32_t neighborCellX = frontCell.getPos().first + Cell::rowVals[i];
            int32_t neighborCellY = frontCell.getPos().second + Cell::colVals[i];

            if (!this->isValidCoordinates(std::pair<int32_t, int32_t>(neighborCellX, neighborCellY))) {
                continue;
            }

            Cell neighborCell = mazeCells[neighborCellX][neighborCellY];
            neighborCell.setVisited(true);
            neighborCell.setCurrDist(frontCell.getCurrDist()+1);
            cellQueue.push(neighborCell);
        }
    }

    return Cell::INVALID_DIST;
}
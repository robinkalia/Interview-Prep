// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// There are a total of n courses you have to take, labeled from 0 to n - 1.
//
// Some courses may have prerequisites, for example to take course 0 you have to first take course 1, which is expressed as a pair: [0,1]
//
// Given the total number of courses and a list of prerequisite pairs, return the ordering of courses you should take to finish all courses.
//
// There may be multiple correct orders, you just need to return one of them. If it is impossible to finish all courses, return an empty array.
//
// For example:
//
// 2, [[1,0]]
// There are a total of 2 courses to take. To take course 1 you should have finished course 0. So the correct course order is [0,1]
//
// 4, [[1,0],[2,0],[3,1],[3,2]]
// There are a total of 4 courses to take. To take course 3 you should have finished both courses 1 and 2. 
// Both courses 1 and 2 should be taken after you finished course 0. So one correct course order is [0,1,2,3]. Another correct ordering is[0,2,1,3].

#include <iostream>
#include <stdint.h>
#include <map>
#include <vector>
#include <tuple>

class Solution {
public:
    
    bool generateGraphAM(std::vector<std::vector<int32_t>>& graphAM, const std::vector<std::pair<int, int>>& prerequisites) {
        for (int32_t i=0; i<graphAM.size(); i++) {
            graphAM[i] = std::vector<int32_t>(graphAM.size(),0);
        }
        
        for (auto it=prerequisites.begin(); it != prerequisites.end(); ++it) {
            if (it->first == it->second)    return false;
            if (graphAM[it->first][it->second] == 0) 
                graphAM[it->first][it->second] = 1;
            else if (graphAM[it->first][it->second] == -1)
                return false;
            graphAM[it->second][it->first] = -1;
        }
        
        return true;
    }
    
    std::vector<int> findOrder(int numCourses, std::vector<std::pair<int, int>>& prerequisites) {
        std::vector<int> orderedSubjects; 
        if (prerequisites.size() == 0)  {
            for (int32_t i=numCourses-1; i>=0; --i)     orderedSubjects.push_back(i);
            return orderedSubjects;
        }
        std::vector<std::vector<int32_t>> graphAM(numCourses);
        if (!generateGraphAM(graphAM,prerequisites))
            return std::vector<int>();
        
        int32_t inputTraverse = 1, tSortTraverse = 1;
        std::map<int32_t,int32_t> numVertices, tSortVertices;
        for (int32_t i=0; i<numCourses; ++i) {
            numVertices.insert(std::make_pair(i,0));
            tSortVertices.insert(std::make_pair(i,0));
        }
        
        int32_t startingVertex = -1;
        for (int32_t i=0; i<numCourses; i++) {
            int32_t negCount = 0;
            for (int32_t j=0; j<graphAM[i].size(); ++j) {
                negCount += (graphAM[i][j] < 0) ? 1 : 0;
            }
            if (negCount == 0)   {
                startingVertex = i;
                break;
            }
        }
        if (startingVertex == -1)   return std::vector<int>();
        
        bool cycleDetected = false;
        bool unvisitedVertexCond = true;
        
        do {
            topologicalSort(startingVertex, graphAM, inputTraverse, tSortTraverse, numVertices, tSortVertices, cycleDetected);
            if (cycleDetected)  break;
            unvisitedVertexCond = false;
            for (int32_t i=0; i<numVertices.size(); i++) {
                if (numVertices[i] == 0) {
                    startingVertex = i;
                    unvisitedVertexCond = true;
                    break;
                }
            }
        } while ((unvisitedVertexCond == true) && (cycleDetected == false));
        
        if (cycleDetected == true)  return std::vector<int>();
        
        std::map<int32_t,int32_t> tSortOrderMap;
        for (auto const& elem : tSortVertices)    tSortOrderMap.insert(std::make_pair(elem.second-1,elem.first));
        for (auto const& elem : tSortOrderMap)    orderedSubjects.push_back(elem.second);
        
        return orderedSubjects;        
    }
    
    void topologicalSort(int32_t& vertex, const std::vector<std::vector<int32_t>>& graphAM, int32_t& inputTraverse, int32_t& tSortTraverse, std::map<int32_t,int32_t>& numVertices, std::map<int32_t,int32_t>& tSortVertices, bool& cycleDetected) {
        if (cycleDetected)  return;
        
        numVertices[vertex] = inputTraverse++;
        for (int32_t i=0; i<graphAM[vertex].size(); i++) {
            if (graphAM[vertex][i] == 1) {
                if (numVertices[i] == 0) {
                    topologicalSort(i, graphAM, inputTraverse, tSortTraverse, numVertices, tSortVertices, cycleDetected);
                } else if (tSortVertices[i] == 0) {
                    cycleDetected = true;
                    return;
                }    
            }
        }
        
        tSortVertices[vertex] = tSortTraverse++;
    }
};
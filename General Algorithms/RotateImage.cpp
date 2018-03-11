// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// You are given an n x n 2D matrix representing an image.
//
// Rotate the image by 90 degrees (clockwise).
//
// Note:
// You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. DO NOT allocate another 2D matrix and do the rotation.
//
// Example 1:
//
// Given input matrix =
// [
//   [1,2,3],
//   [4,5,6],
//   [7,8,9]
// ],
//
// 1 4 7    7 4 1
// 2 5 8    8 5 2
// 3 6 9    9 6 3
// rotate the input matrix in-place such that it becomes:
// [
//   [7,4,1],
//   [8,5,2],
//   [9,6,3]
// ]
// Example 2:
//
// Given input matrix =
// [
//   [ 5, 1, 9,11],
//   [ 2, 4, 8,10],
//   [13, 3, 6, 7],
//   [15,14,12,16]
// ],
//
// 5  2  13  15         15 13 2 5
// 1  4   3  14         14 3  4 1
// 9  8   6  12         12 6  8 9
// 11 10  7  16         16 7 10 11
//
// rotate the input matrix in-place such that it becomes:
// [
//   [15,13, 2, 5],
//   [14, 3, 4, 1],
//   [12, 6, 8, 9],
//   [16, 7,10,11]
// ]

#include <iostream>
#include <stdint.h>
#include <vector>
#include <assert.h>

using namespace std;

class Solution {

public:
    void reflect(vector<vector<int> >& matrix, int32_t n, int32_t w) {
        for (int32_t i=0; i<n; i++)
            for (int32_t j=0; j<n/2; j++) {
                int32_t temp = matrix[i][j];
                matrix[i][j] = matrix[i][w - 1 - j];
                matrix[i][w-1-j] = temp;
            }
    }

    void transpose(vector<vector<int> >& matrix, int32_t n) {
        for (int32_t i=0; i<n; i++)
            for (int32_t j=i+1; j<n; j++) {
                int32_t temp = matrix[i][j];
                matrix[i][j] = matrix[j][i];
                matrix[j][i] = temp;
            }
    }

    void rotate(vector<vector<int> >& matrix) {
        int32_t h = matrix.size();
        int32_t w = matrix[0].size();
        assert(w == h);

        transpose(matrix, h);
        reflect(matrix, h, w);
    }
};

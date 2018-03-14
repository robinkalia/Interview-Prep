// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
//
// Now your job is to find the total Hamming distance between all pairs of the given numbers.
//
// Example:
// Input: 4, 14, 2
//
// Output: 6
//
// Explanation: In binary representation, the 4 is 0100, 14 is 1110, and 2 is 0010 (just
// showing the four bits relevant in this case). So the answer will be:
// HammingDistance(4, 14) + HammingDistance(4, 2) + HammingDistance(14, 2) = 2 + 2 + 2 = 6.
// Note:
// Elements of the given array are in the range of 0 to 10^9
// Length of the array will not exceed 10^4.

#include <iostream>
#include <stdint.h>
#include <math.h>
#include <vector>

using namespace std;

class Solution {
public:
    int64_t totalHammingDistance(vector<int>& nums) {
        vector<vector<uint8_t>> numsInBits;
        for (auto num: nums) {
            vector<uint8_t> numInBits;
            do {
                numInBits.push_back(num%2);
            } while ((num >> 1) > 0);
            numsInBits.push_back(numInBits);
        }
        
        int64_t hammingDist = 0;
        for (int32_t i=0; i<nums.size()-1; i++)
            for (int32_t j=i+1; j<nums.size(); j++) {
                hammingDist += abs(int64_t(numsInBits[i].size()) - int64_t(numsInBits[j].size()));
                int32_t smallerIndex = (numsInBits[i].size() > numsInBits[j].size()) ? numsInBits[j].size() : numsInBits[i].size();
                for (int32_t m=0; m<smallerIndex; m++) {
                    hammingDist += (numsInBits[i][m] != numsInBits[j][m]) ? 1 : 0;
                }
            }
        
        return hammingDist;
    }
};
// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// Reverse bits of a given 32 bits unsigned integer.
//
// For example, given input 43261596 (represented in binary as 00000010100101000001111010011100), return 964176192 (represented in binary as 00111001011110000010100101000000).
//
// Follow up:
// If this function is called many times, how would you optimize it?

#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        vector<uint8_t> reversedBits;
        do {
            reversedBits.push_back(n%2);
        } while ((n >> 1) > 0);
        
        for (int32_t i=reversedBits.size(); i< (1 << 5); i++) {
            reversedBits.push_back(0);
        }
        
        uint32_t reversedN = 0;
        for (int32_t i=(1<<5)-1; i>=0; --i) {
            reversedN += (reversedBits[i]) ? (1 << ((1 << 5) -1 - i)) : 0;
        }
        
        return reversedN;
    }
};
// Robin Kalia
// robinkalia@berkeley.edu

// Problem:
// Compute Integral image
// For a position (i,j) in the Matrix, Integral(i,j) = Sum of all matrix values (0<= x <= i, 0<= y<= j) 

#include <iostream>
#include <stdint.h>
#include <vector>

using namespace std;

class Image {

public:
    vector<vector<int64_t> > computeIntegralImage(const vector<vector<int32_t> >& image) {
        int32_t h = image.size();
        int32_t w = image[0].size();

        vector<vector<int64_t> > integralImage = vector<vector<int64_t> >(h, vector<int64_t>(w,0));
        for (int32_t i=0; i<h; i++)
            for (int32_t j=0; j<w; j++) {
                int64_t dimIntegralImagePixel = (i>=1)&&(j>=1) ? integralImage[i-1][j-1] : 0;
                int64_t upperIntegralImagePixel = (i>=1) ? integralImage[i-1][j] : 0;
                int64_t leftIntegralImagePixel = (j>=1) ? integralImage[i][j-1] : 0;
                integralImage[i][j] = image[i][j] + (integralImage[i-1][j] + integralImage[i][j-1] - dimIntegralImagePixel);
            }

        return integralImage;
    }
};


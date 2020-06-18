#include <complex.h>

using namespace std;

#ifndef BEP_EDGE_FFT_H
#define BEP_EDGE_FFT_H

class FFT{
public:
    void compute(complex<short> *input, complex<short> *output , int n, int mode);
    void compute(complex<double> *input, complex<double> *output , int n, int mode);
};


#endif //BEP_EDGE_FFT_H

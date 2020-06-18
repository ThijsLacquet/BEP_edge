#include <complex.h>
#include "FFT.h"

#ifndef BEP_EDGE_OFDM_H
#define BEP_EDGE_OFDM_H


class OFDM {
private:
    int fftsize;
    //FFT myFFT;
public:
    OFDM(int fftsize);
    //void compute_OFDM(complex<double> *input, complex<double> *output, int nb_symbols);
};


#endif //BEP_EDGE_OFDM_H

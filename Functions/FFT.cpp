#include "FFT.h"
#include <fftw3.h>
//#include <inc/cufftw.h>

using namespace std;

void FFT::compute(std::complex<short> *input, complex<short> *output, int n, int mode) {
    complex<double> *inputDouble = (complex<double>*) malloc (sizeof(complex<double>) * n);
    complex<double> *outputDouble = (complex<double>*) malloc (sizeof(complex<double>) * n);

    //Copy input from complex<short> to complex<double>
    for (int i = 0; i < n; i++) {
        inputDouble[i] = complex<double>((double) (input[i].real()), (double) (input[i].imag()));
    }

    compute(inputDouble, outputDouble, n, mode);

    //Copy output from complex<double> to complex<short>
    for (int i = 0; i < n; i++) {
        output[i] = complex<short>(outputDouble[i].real(), outputDouble[i].imag());
    }

    free(inputDouble);
    free(outputDouble);
}

void FFT::compute(std::complex<double> *input, complex<double> *output, int n, int mode) {
    fftw_plan plan = fftw_plan_dft_1d(n, reinterpret_cast<fftw_complex*>(input),
            reinterpret_cast<fftw_complex*>(output), mode, FFTW_ESTIMATE);

    fftw_execute(plan);
    fftw_destroy_plan(plan);
}





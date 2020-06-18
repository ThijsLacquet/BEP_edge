/*
 * Author: Thijs Lacquet
 * Based on ofdm_mod.c of the openairinterface5g project,
 * https://gitlab.eurecom.fr/oai/openairinterface5g/-/blob/master/openair1/PHY/MODULATION/modulation_common.h
 */

#include "OFDM.h"
#include "FFT.h"

/*
 * @param fftsize Size of OFDM symbol
 */
OFDM::OFDM(int fftsize) {
    OFDM::fftsize = fftsize;
    //FFT myFFT = FFT(fftsize);
}

/*
 * @param nb_symbols Number of OFDM symbols in a block
 * @param nb_prefix_samples The number of prefix/suffix/zero samples
*/
/*void OFDM::compute_OFDM(complex<double> *input, complex<double> *output, int nb_symbols) {
    for (int i = 0; i < nb_symbols; i++) {
        complex<double> *temp = (complex<double>*) malloc(sizeof(complex<double>) * fftsize);
        myFFT.compute_IFFT(&input[i * this.fftsize], temp);

        //Cyclic prefix
        /*output_ptr = &output[(i * this.fftsize) + ((i + 1) * nb_prefix_samples)];


        int j = fftsize - 1;
        int k = -1;

        while (k >= -nb_prefix_samples) {
            output_ptr[k] = output_ptr[j];
            k--;
            j--;
        }*//*

        complex<double>* output_ptr = &output[this.fftsize];

        for (int j = 0; j < this.fftsize; j++) {
            output_ptr[j] = temp[2 * j];
        }

        free(temp);
    }
}*/
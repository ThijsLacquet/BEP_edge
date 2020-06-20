#include <stdlib.h>
#include <complex.h>

using namespace std;

#ifndef BEP_EDGE_QAM_H
#define BEP_EDGE_QAM_H

class QAM {
private:
    short *i_setpoints;
    short *q_setpoints;
    int n;

public:
    QAM(int n);
    ~QAM();
    void compute_QAM(short *input, complex<short>* output, size_t samples);
    void compute_deQAM(complex<short> *input, short *output, size_t samples);
};


#endif //BEP_EDGE_QAM_H

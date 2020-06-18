#include "mathextension.h"
#include <math.h>

double absext(std::complex<double> input) {
    double realmag;
    double complexmag;
    if (real(input) > 0) {
        realmag = real(input);
    } else {
        realmag = -real(input);
    }

    if (imag(input) > 0) {
        complexmag = imag(input);
    } else {
        complexmag = -imag(input);
    }

    return sqrt(pow(realmag, 2) + pow(complexmag, 2));
}

double absext(double input) {
    if (input > 0) {
        return input;
    } else {
        return -input;
    }
}

#pragma once

#include <vector>
#include <complex>

// FFT 2つ目の引数を-2*M_PI/NにするとFFT
// 2*M_PI/NにするとIFFT（IFFTのときは計算結果をNで除算する必要がある）
void fft(int n, double theta, std::vector<std::complex<double> > &a){
    int m, mh, i, j, k, irev;
    std::complex<double> w, x;

    i = 0;
    for (j = 1; j < n - 1; j++) {
        for (k = n >> 1; k > (i ^= k); k >>= 1);
        if (j < i) {
            x = a[j];
            a[j] = a[i];
            a[i] = x;
        }
    }
    for (mh = 1; (m = mh << 1) <= n; mh = m) {
        irev = 0;
        for (i = 0; i < n; i += m) {
            w = std::complex<double>(std::cos(theta * irev), std::sin(theta * irev));
            for (k = n >> 2; k > (irev ^= k); k >>= 1);
            for (j = i; j < mh + i; j++) {
                k = j + mh;
                x = a[j] - a[k];
                a[j] += a[k];
                a[k] = w*x;
            }
        }
    }
}
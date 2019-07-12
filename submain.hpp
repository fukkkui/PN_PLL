#include <iostream>
#include <vector>
#include <complex>
#include "PhaseNoise.hpp"
#include "fft.hpp"

using COM = std::complex<double>;
using VCOM = std::vector<COM>;
using V = std::vector<double>;

V submain(int N, double Bandwidth){
	V PN_phase(N);
	VCOM PN_amplitude(N);
	double Ts = 1.0 / Bandwidth; //Sampling interval
	double f0 = 5.015e9; //Carrier frequency
	double Cvco = 10e-22; // VCO quality parameter
	double Cxtl = 30e-25; // refference oscillator quality parameter
	double kpd = 1.0; //phase detector gain
	double omega_lp = 10e5; //corner frequency
	double Sqrt_Ccontr = sqrt(10e11) / kpd; //control node of VCO quality

	PLL_Sec(PN_phase, N, Cvco, Cxtl, kpd, omega_lp, Ts, Sqrt_Ccontr, f0);
	Make_PN(PN_phase, N, PN_amplitude);
	fft(N, -2.0*std::acos(-1.0)/N, PN_amplitude);

	V PSD(N);
	for(int i = 0; i < N/2; i++){
		PSD[i] = pow(abs(PN_amplitude[i + N/2]), 2);
		PSD[i + N/2] = pow(abs(PN_amplitude[i]), 2);
	}

	return PSD;
}
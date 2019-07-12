#pragma once

#include <vector>
#include <complex>
#include <random>

using COM = std::complex<double>;
using V = std::vector<double>;
using VCOM = std::vector<COM>;

//PLL with second order filter
void PLL_Sec(V &Phase, int N, double Cvco, double Cxtl, double kpd, double omega_lp, double Ts, double Sqrt_Ccontr, double f0){
	std::random_device seed;
	std::default_random_engine generator(seed());
	double variance = Ts;
	std::normal_distribution<double> dist(0.0, sqrt(variance));

	V a_xtl(N, 0);
	V gamma(N, 0);
	V beta(N, 0);
	V a_pll(N, 0);

	Phase.resize(N);
	Phase[0] = 0.0;
	for(int i = 1; i < N; i++){
		gamma[i] = (1.0 - omega_lp * Ts) * gamma[i - 1] - kpd * omega_lp * Ts * beta[i - 1];
		beta[i] = beta[i - 1] + Sqrt_Ccontr * Ts * gamma[i] + sqrt(Cvco) * dist(generator);
		a_pll[i] = a_xtl[i - 1] + beta[i];
		a_xtl[i] = a_xtl[i - 1] + sqrt(Cxtl) * dist(generator);
		Phase[i] = 2.0 * std::acos(-1.0) * f0 * a_pll[i];
	}
}

void Make_PN(V &Phase, int N, VCOM &PhaseNoise){
	PhaseNoise.resize(N);
	for(int i = 0; i < N; i++){
		PhaseNoise[i] = COM(std::cos(Phase[i]), std::sin(Phase[i]));
	}
}
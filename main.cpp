#include <iostream>
#include <vector>
#include "submain.hpp"

using V = std::vector<double>;

int main(){
	int N = 131072;
	double Bandwidth = 20e6;

	V PSD(N, 0);
	V PSD_part(N, 0);

	int loop = 100;
	for(int i = 0; i < loop; i++){
		PSD_part = submain(N, Bandwidth);
		for(int j = 0; j < N; j++){
			PSD[j] += PSD_part[j];
		}
	}

	//SSB
	V PSD_SSB(N/2-1, 0);
	double Cen = 20.0 * log10((double)N);
	double Spa = 10.0 * log10(Bandwidth/(double)N);
	for(int i = 0; i < N/2 - 1; i++){
		PSD_SSB[i] = 10.0 * log10(PSD[i + N/2 + 1]/(double)loop) - Cen - Spa;
	}
}
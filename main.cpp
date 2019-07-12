#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "submain.hpp"

using V = std::vector<double>;
using VV = std::vector<V>;

void fileW_csv(std::string filename, VV &data){
    int Nd = data.size();
    int Ld = data.front().size();
    std::ofstream os(filename);
    for(int i = 0; i < Ld; i++){
        for(int j = 0; j < Nd; j++){
            os << data[j][i] << ",";
        }
        os << std::endl;
    }
    os.close();
}

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

	VV PSD_SSB_file(2, V(N/2 - 1,0));
	for(int i = N/2; i < N-1; i++){
		//offset frequency (log scale)
		PSD_SSB_file[0][i - N/2] = (-Bandwidth/2.0 + ((double)(i + 1) * Bandwidth / (double)N) )/1e3;
		PSD_SSB_file[1][i - N/2] = PSD_SSB[i - N/2];
	}

	std::string file = "PSD.csv";
	fileW_csv(file, PSD_SSB_file);
}
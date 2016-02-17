#include "minimum.h"

void main() {
        std::ifstream input("input.txt");
        std::ofstream output1("output1.txt");
		std::ofstream output2("output2.txt");
		std::ofstream output3("output3.txt");
		std::ofstream output4("output4.txt");
		minimum A;
		double x0;
        input >> A.eps >> x0;
        
        
        A.Dichotomy(output1);
        A.GoldenSection(output2);
		A.Fibonachi(output3);
		A.minInter(x0, output4);
}
#include <iostream>
using namespace std;

int main() {
	
	// Given P(POS), P(DOOR|POS) and P(DOOR|¬POS)
	double a = 0.0002 ; //P(POS) = 0.002
	double b = 0.6    ; //P(DOOR|POS) = 0.6
	double c = 0.05   ; //P(DOOR|¬POS) = 0.05
	
	// Compute P(¬POS) and P(POS|DOOR)
	double d = 1 - a ;               //P(¬POS)
	double e = (b*a)/((a*b)+(d*c)) ; //P(POS|DOOR)
	
	// Print Result
	cout << "P(POS|DOOR)= " <<    e    << endl;
	
	return 0;
}
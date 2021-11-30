#include "printer.hpp"
#include "calc.hpp"

int main(){

	int a,b,sum;
	a = 0;
	b = 0;
	std::cout<<"Enter two numbers: ";
	std::cin>>a>>b;
	sum = calculate(a,b);
	
	print(std::to_string(a) + " + " + std::to_string(b) + " = " + std::to_string(sum));

	return 0;
}

#include "ZedBoard.h"
#include <iostream>


int main(){

	ZedBoard zb;
	int value;
	std::cin>>value;
	zb.SetLedByValue(value);
	return 0;

}

#include <iostream>
#include <list>
#include "inttypes.h"
#include "../../../../../libopenss-framework/AddressRange.hxx"

using namespace std;
using namespace OpenSpeedShop;
using namespace Framework;


int main(){
	long int x = 5;
	long int y = 6;
	long int z = 7;
	uint64_t x_address = uint64_t(&x);
	uint64_t y_address = uint64_t(&y);
	uint64_t z_address = uint64_t(&z);
	Address testxAddress(x_address);
	Address testyAddress(y_address);
	Address testzAddress(z_address);
	AddressRange testRange(testxAddress, testzAddress);
	if (testRange.doesContain(testyAddress)){
		cout << "PASS" << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
	
 return 0;
}

#include <iostream>
#include <fstream>
using namespace std;


int main ( int argc, char** argv ) {

	ofstream file("Eded.bin", ios::out | ios::binary );
	
	// Sample byte array to be saved as a bit stream
	uint16_t a[10] = {1,2,3,4,5,12,7,8,9,10}; 
	uint16_t temp = 0x8000;

	int i = 0 ;//counts the no of shifts of temp for Right
	int j = 0;
	uint16_t out = 0; // Write Buffer
	int sz = 0;
	

	for (int x = 0; x < 10; x++) {

		temp = 0x8000; // pre load temp with 0b10000000
		
		// calculate amount of bits(avalilable room)
		while ((a[x] & (temp >> j)) == 0) {
			j++;
		}

		// Adjustment at the end of a buffer
		if (sz > j) {
			out |= a[x] >> sz - j;	// fill part of the byte to write buffer
			cout << (int)out << endl;	
			file.write ( (char*)&out, sizeof ( uint16_t ) ); //Write WORD to a file

			out = 0; // ready wirte buffer for next bits
			out |= a[x] << sz ; // fill write buffer with leftover bits of previous byte
			cout << (int)out << endl;
			sz = 16 - sz ;
			j = 0;
			continue;
			
		}

		temp >>= sz; // shift bit for free space
		

		while ((a[x] & (temp)) == 0) { 
			i++;
			temp >>= 1;	
		}
		
		a[x] = a[x] << (i);
		out |= a[x];
		sz = 16 - i; // bit width of  the shifted value
	
		cout << (int)out << endl;
		i = 0;
		j = 0;

	}

	cin.get ( );
	file.close ( );
	return 0;
}

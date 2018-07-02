#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void Writebits ( string filename, uint8_t* bytearray, int arrlen);

int main ( int argc, char** argv ) {

	uint8_t bytarr[] = { 1,2,3,4,5,6 };
	Writebits ( "dec.bin", bytarr ,6);

	cin.get ( );
	return 0;
}

void Writebits ( string filename, uint8_t* bytearray, int arrlen) {

	ofstream file ( filename, ios::out | ios::binary );

	uint8_t temp = 0x80;

	int i = 0;//counts the no of shifts of temp for Right
	int j = 0;//counts location of bit sequance from the left
	uint8_t out = 0; // Write Buffer
	int sz = 0; // bitwidth


	for (int x = 0; x <= arrlen; x++) {

		temp = 0x80; // pre load temp with 0b10000000

		// calculate amount of bits(avalilable room)
		while ((*bytearray & (temp >> j)) == 0) {
			j++;
		}

		// Adjustment at the end of a buffer
		if (sz > j) {
			out |= *bytearray >> sz - j;	// fill part of the byte to write buffer
			file.write ( (char*)&out, sizeof ( uint8_t ) ); //Write WORD to a file
			cout << int ( out ) << endl;
			out = 0; // ready wirte buffer for next bits
			out |= *bytearray << sz; // fill write buffer with leftover bits of previous byte
			sz = 8 - sz;
			j = 0;
			continue;

		}
		temp >>= sz; // shift bit for free space
		while ((*bytearray & (temp)) == 0) {
			i++;
			temp >>= 1;
		}
		*bytearray = *bytearray << (i);
		out |= *bytearray;
		sz = 8 - i; // bit width of  the shifted value
		i = 0;
		j = 0;
		bytearray++;
	}
	cout << int ( out ) << endl;
	file.write ( (char*)&out, sizeof ( uint8_t ) ); //Write WORD to a file
	file.close ( );



}

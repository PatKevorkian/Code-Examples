#include <iostream>
#include <iomanip>
using namespace std;
#include <string>
#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;
#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::StreamTransformationFilter;
#include "cryptopp/des.h"
using CryptoPP::DES_EDE3;
#include "cryptopp/modes.h"
using CryptoPP::ECB_Mode;
#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

int main(int argc, char* argv[])
{
    byte key[CryptoPP::DES_EDE3::DEFAULT_KEYLENGTH] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23};



	string plain = "The quick brown fox jumped over the lazy dog’s back";
	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "key: " << encoded << endl;


	/*********************************\
	\*********************************/

	try
	{
		cout << "plain text: " << plain << endl;

		ECB_Mode< DES_EDE3 >::Encryption e;
		e.SetKey(key, sizeof(key));

		// The StreamTransformationFilter adds padding
		//  as required. ECB and CBC Mode must be padded
		//  to the block size of the cipher.
		StringSource(plain, true, 
			new StreamTransformationFilter(e,
				new StringSink(cipher)
			) // StreamTransformationFilter      
		); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// Pretty print
	encoded.clear();
	StringSource(cipher, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		ECB_Mode< DES_EDE3 >::Decryption d;
		d.SetKey(key, sizeof(key));

		// The StreamTransformationFilter removes
		//  padding as required.
		StringSource s(cipher, true, 
			new StreamTransformationFilter(d,
				new StringSink(recovered)
			) // StreamTransformationFilter
		); // StringSource

		cout << "recovered text: " << recovered << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	return 0;
}


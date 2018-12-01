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
using CryptoPP::CFB_Mode;
#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

int main(int argc, char* argv[])
{
    byte key[CryptoPP::DES_EDE3::DEFAULT_KEYLENGTH] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x45,0x67,0x89,0xab,0xcd,0xef,0x01,0x23};

	byte iv[DES_EDE3::BLOCKSIZE] = {0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef};


	string plain = "The quick brown fox jumped over the lazy dog’s back";
	string cipher, encoded, recovered;

	/*********************************\
	\*********************************/

	// Pretty print key
	encoded.clear();
	StringSource(key, sizeof(key), true,new HexEncoder(new StringSink(encoded)));
	cout << "key: " << encoded << endl;

	// Pretty print iv
	encoded.clear();
	StringSource(iv, sizeof(iv), true,new HexEncoder(new StringSink(encoded)));
	cout << "iv: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		cout << "plain text: " << plain << endl;

		CFB_Mode< DES_EDE3 >::Encryption e;
		e.SetKeyWithIV(key, sizeof(key), iv);
        
        // CFB mode must not use padding. Specifying
        //  a scheme will result in an exception
        StringSource(plain, true,new StreamTransformationFilter(e,new StringSink(cipher)));
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
	StringSource(cipher, true,new HexEncoder(new StringSink(encoded))); // StringSource
	cout << "cipher text: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		CFB_Mode< DES_EDE3 >::Decryption d;
		d.SetKeyWithIV(key, sizeof(key), iv);

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


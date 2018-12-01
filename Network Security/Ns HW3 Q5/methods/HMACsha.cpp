using namespace std;
#include <string>
#include <iostream>
#include <cstdlib>
#include "cryptopp/cryptlib.h"
using CryptoPP::Exception;
#include "cryptopp/hmac.h"
using CryptoPP::HMAC;
#include "cryptopp/sha.h"
using CryptoPP::SHA1;
#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
#include "cryptopp/filters.h"
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::HashFilter;
using CryptoPP::HashVerificationFilter;
#include "cryptopp/secblock.h"
using CryptoPP::SecByteBlock;

int main(int argc, char* argv[])
{

    
    byte key[HMAC< SHA1 >::DEFAULT_KEYLENGTH] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef, 0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01};

	string plain = "The quick brown fox jumped over the lazy dog’s back";
	string mac, encoded;

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

	cout << "plain text: " << plain << endl;

	/*********************************\
	\*********************************/

	try
	{
		HMAC< SHA1 > hmac(key, sizeof(key));

		StringSource(plain, true, 
			new HashFilter(hmac,
				new StringSink(mac)
			) // HashFilter      
		); // StringSource
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	/*********************************\
	\*********************************/

	// Pretty print MAC
	encoded.clear();
	StringSource(mac, true,
		new HexEncoder(
			new StringSink(encoded)
		) // HexEncoder
	); // StringSource
	cout << "hmac: " << encoded << endl;

	/*********************************\
	\*********************************/

	try
	{
		HMAC< SHA1 > hmac(key, sizeof(key));
		const int flags = HashVerificationFilter::THROW_EXCEPTION | HashVerificationFilter::HASH_AT_END;

		// Tamper with message
		// plain[0] ^= 0x01;

		// Tamper with MAC
		// mac[0] ^= 0x01;
	
		StringSource(plain + mac, true, 
			new HashVerificationFilter(hmac, NULL, flags)
		); // StringSource

		cout << "Verified message" << endl;
	}
	catch(const CryptoPP::Exception& e)
	{
		cerr << e.what() << endl;
		exit(1);
	}

	return 0;
}


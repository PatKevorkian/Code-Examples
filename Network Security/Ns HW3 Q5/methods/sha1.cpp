#include <iomanip>
using namespace std;
#include <iostream>
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
#include "cryptopp/sha.h"

int main(int argc, char* argv[])
{
 
    CryptoPP::SHA1 hash;
    string message = "The quick brown fox jumped over the lazy dog’s back";
    string digest;
    
    cout<<"Message: "<<message<<endl;
    StringSource s(message, true, new CryptoPP::HashFilter(hash, new HexEncoder(new StringSink(digest))));
    
    cout<<"SHA1 Hash: " << digest << endl;
	return 0;
}

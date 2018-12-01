#include <iomanip>
using namespace std;
#include <iostream>
#include <string>
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

int main(int argc, char* argv[])
{
    
    byte digest[ CryptoPP::Weak::MD5::DIGESTSIZE ];
    std::string message = "The quick brown fox jumped over the lazy dog’s back";
    cout<< "Message: "<<message<<endl;
    CryptoPP::Weak::MD5 hash;
    hash.CalculateDigest( digest, (const byte*)message.c_str(), message.length() );
    
    CryptoPP::HexEncoder encoder;
    std::string output;
    
    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();
    
    std::cout<<"MD5 Hash: " << output << std::endl;


	return 0;
}


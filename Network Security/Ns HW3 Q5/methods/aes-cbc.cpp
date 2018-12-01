#include <iostream>
#include <iomanip>
#include <string>

#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"

using namespace std;

int main(int argc, char* argv[]) {

    //used to ignore warning that argv is not used.
    char *prog = argv[0];
    (void)argc;


    byte key[CryptoPP::AES::DEFAULT_KEYLENGTH] = {0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef, 0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0x01};
    byte iv[CryptoPP::AES::BLOCKSIZE] = {0x12,0x34,0x56,0x78,0x90,0xab,0xcd,0xef, 0x34,0x56,0x78,0x90,0xab,0xcd,0xef,0x12};
    
    //
    // String and Sink setup
    //
    string plaintext = "The quick brown fox jumped over the lazy dog’s back";
    string ciphertext;
    string decryptedtext;



    // AES Mode
    cout << "AES Mode: CBC" << endl;



    //Plain Text
    cout << "Plain Text (" << plaintext.size() << " bytes)" << endl;
    cout << plaintext;
    cout << endl << endl;

    //Cipher Text
    CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( ciphertext ) );
    stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plaintext.c_str() ), plaintext.length() + 1 );
    stfEncryptor.MessageEnd();

    //Cipher Text Out
    cout << "Cipher Text (" << ciphertext.size() << " bytes)" << endl;

    for(string::size_type i = 0; i < ciphertext.size(); i++ ) {

        cout << "0x" << hex << (0xFF & static_cast<byte>(ciphertext[i])) << " ";
    }

    cout << endl << endl;

    //Decrypt
    CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedtext ) );
    stfDecryptor.Put( reinterpret_cast<const unsigned char*>( ciphertext.c_str() ), ciphertext.size() );
    stfDecryptor.MessageEnd();

    //Decrypt Result
    cout << "Decrypted Text: " << endl;
    cout << decryptedtext;
    cout << endl << endl;

    return 0;
}

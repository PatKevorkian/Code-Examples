#include <iostream>
#include <string>
using namespace std;

class Vigenere
{
public:
    string key;
    
    Vigenere(string key)
    {
        for(int i = 0; i < key.size(); ++i)
        {
            if(key[i] >= 'A' && key[i] <= 'Z')
                this->key += key[i];
            else if(key[i] >= 'a' && key[i] <= 'z')
                this->key += key[i] + 'A' - 'a';
        }
    }
    
    string encrypt(string text)
    {
        string out;
        
        for(int i = 0, j = 0; i < text.length(); ++i)
        {
            char c = text[i];
            
            if(c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if(c < 'A' || c > 'Z')
                continue;
            
            out += (c + key[j] - 2*'A') % 26 + 'A';
            j = (j + 1) % key.length();
        }
        
        return out;
    }
    
    string decrypt(string text)
    {
        string out;
        
        for(int i = 0, j = 0; i < text.length(); ++i)
        {
            char c = text[i];
            
            if(c >= 'a' && c <= 'z')
                c += 'A' - 'a';
            else if(c < 'A' || c > 'Z')
                continue;
            
            out += (c - key[j] + 26) % 26 + 'A';
            j = (j + 1) % key.length();
        }
        
        return out;
    }
};

int main()
{
    string cipherkey;
    string plaintext;

    
    cout<<"Input Cipher key (1-7 chars): ";
    getline (cin, cipherkey);
    
    Vigenere cipher(cipherkey);
    
    cout<<"Input plaintext (encrypt): ";
    getline (cin, plaintext);
    
    string encrypted = cipher.encrypt(plaintext);
    string decrypted = cipher.decrypt(encrypted);
    
    cout << plaintext << endl;
    cout << "Encrypted: " << encrypted << endl;
    
    cout << "Decrypted: " << decrypted << endl;
}

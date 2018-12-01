#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


int main()
{
    std::vector<char> CipherText;
    char tmp;
    
    ifstream fin("/Users/PatrickKevorkian/Desktop/TheCipher.txt");
    cout<<"The Cipher Text is: " << endl << endl;
    
    while(fin >> tmp)
    {
        CipherText.push_back(tmp);
        cout<<tmp;
    }
    
    int count = 0;
    double length = CipherText.size();
    char alph[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    
    cout<< endl << endl << "The Alphabet is: " << alph << endl << endl ;
    
    for(int i = 0 ; i < 26 ; i++)
    {
        for(int j = 0 ; j <= length ; j++)
        {
            if (alph[i] == CipherText[j])
                count++;
                
        }
        cout << " Frequency of letter " << alph[i] << " is " << count << " or " << (count * 100)/ length << "%." << endl;
        count = 0;
    }
        
    CipherText.clear();
    return 0;
}

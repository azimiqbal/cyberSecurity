#include <iostream>
#include <string>
using namespace std;

class VigCipher {
private:
    int counter;
public:
    string k;
    VigCipher(string k); //constructor
    string keyStream(string key, string message); //increases the size of the key to match the length of pt
    string encryption(string plaintext);          //encrypts the plaintext
    string decryption(string ciphertext);         //decrypts the ciphertext

};

VigCipher::VigCipher(string k){  //generate key

    for (int i = 0; i < k.size(); ++i) {
        if (k[i] >= 'A' && k[i] <= 'Z') //ignore what aren't letters, and capitalize everything.
            this->k += k[i];
        else if (k[i] >= 'a' && k[i] <= 'z')
            this->k += k[i] + 'A' - 'a';
    }
}

string VigCipher::keyStream(string key, string message){
    int temp = message.size();
    for (int i = 0; ; i++)
    {
        if (temp == i)
            i = 0;
        if (key.size() == message.size())
            break;
        key.push_back(key[i]);
    }
    return key;
}


string VigCipher::encryption(string plaintext){
    string encrypt;
    for (int i = 0, j = 0; i < plaintext.length(); ++i){
        char p = plaintext[i];
    if (p >= 'a' && p <= 'z')
        p += 'A' - 'a';
    else if (p < 'A' || p > 'Z')
        continue;
        encrypt += (p + k[j] - 2 * 'A') % 26 + 'A';
        j = (j + 1) % k.length();
    }
    return encrypt;
}

    string VigCipher::decryption(string ciphertext){
        string decrypt;
        for (int i = 0, j = 0; i < ciphertext.length(); ++i)
        {
            char c = ciphertext[i];

            if (c >= 'a' && c <= 'z')  //ignore what aren't letters, and capitalize everything.
                c += 'A' - 'a';
            else if (c < 'A' || c > 'Z')
                continue;

            decrypt += (c - k[j] + 26) % 26 + 'A';  //the actual decryption happens here
            j = (j + 1) % k.length();
        }

        return decrypt;
    }

int main()
{
    /*
    VigCipher vigenere("Kongsberg");
    string plaintext = "The quick brown fox jumps over the lazy dog.";
    string encryption = vigenere.encryption(plaintext);
    string decryption = vigenere.decryption(encryption);
    string s = vigenere.keyStream(vigenere.k, plaintext);
    cout <<"ENCRYPTION:" <<endl;
    cout << "Plaintext: "<< plaintext << endl;
    cout << "The keystream is: " << s << endl;
    cout << "Ciphertext: " << encryption << endl << endl;
    cout <<"DECRYPTION:" <<endl;
    cout <<"Ciphertext: " << "DVRWMJGBHBCJTXPBAAWDFUNFVKNOZNFQESX" << endl;
    cout << "The keystream is: " << s << endl;
    cout << "Plaintext: " << decryption << endl;
     */

    VigCipher vigenere ("Norway");
    VigCipher vig("Oslo");
    string plaintext = "The quick brown fox jumps over the lazy dog.";
    string encryption = vigenere.encryption(plaintext);
    string decryption = vigenere.decryption(encryption);
    string encrypt = vig.encryption(plaintext);
    string decrypt = vig.decryption(encryption);
    string s = vigenere.keyStream(vigenere.k, plaintext);
    string sa = vig.keyStream(vig.k, plaintext);

    cout <<"ENCRYPTION:" <<endl;
    cout << "Plaintext 1 is: "<< plaintext << endl;
    cout << "Keystream 1 is: " << s << endl;
    cout << "Plaintext 2 is: " << encryption << endl;
    cout << "Keystream 2 is: " << sa << endl;
    cout << "Ciphertext is: " << encrypt << endl << endl;

    cout <<"DECRYPTION:" <<endl;
    cout <<"Ciphertext 2 is: " << "HZPEIANYPJZKBXZLXMXDGGGSFLSSZSKMRGR" << endl;
    cout << "Keystream 2 is: " << sa << endl;
    cout << "Ciphertext 1: " << decrypt << endl;
    cout << "Keystream 1 is: " << s << endl;
    cout << "Plaintext is: " << decryption << endl;
}

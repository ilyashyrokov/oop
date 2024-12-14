#include <iostream>
#include <string>
using namespace std;

class EncryptionStrategy {
public:
    virtual ~EncryptionStrategy() {}
    virtual  string encrypt(const  string& data, char key) = 0;
    virtual  string decrypt(const  string& data, char key) = 0;
};


class XOREncryption : public EncryptionStrategy {
public:
     string encrypt(const  string& data, char key) override {
         string result = data;
        for (size_t i = 0; i < result.size(); ++i) {
            result[i] ^= key;
        }
        return result;
    }

     string decrypt(const  string& data, char key) override {
        return encrypt(data, key);
    }
};


class ECBMode : public EncryptionStrategy {
private:
    XOREncryption xorCipher;

public:
     string encrypt(const  string& data, char key) override {
        return xorCipher.encrypt(data, key);
    }

     string decrypt(const  string& data, char key) override {
        return xorCipher.decrypt(data, key);
    }
};


class CBCMode : public EncryptionStrategy {
private:
    XOREncryption xorCipher;
    char initializationVector = 'I'; 

public:
     string encrypt(const  string& data, char key) override {
         string result = data;
        char previousBlock = initializationVector;

        for (size_t i = 0; i < result.size(); ++i) {
            result[i] ^= previousBlock; 
            result[i] = xorCipher.encrypt( string(1, result[i]), key)[0];
            previousBlock = result[i];
        }
        return result;
    }

     string decrypt(const  string& data, char key) override {
         string result = data;
        char previousBlock = initializationVector;

        for (size_t i = 0; i < result.size(); ++i) {
            char currentBlock = result[i];
            result[i] = xorCipher.decrypt( string(1, result[i]), key)[0];
            result[i] ^= previousBlock; 
            previousBlock = currentBlock;
        }
        return result;
    }
};


class EncryptionContext {
private:
    EncryptionStrategy* strategy;

public:
    EncryptionContext(EncryptionStrategy* strategy) : strategy(strategy) {}

    void setStrategy(EncryptionStrategy* newStrategy) {
        strategy = newStrategy;
    }

     string encrypt(const  string& data, char key) {
        return strategy->encrypt(data, key);
    }

     string decrypt(const  string& data, char key) {
        return strategy->decrypt(data, key);
    }
};

int main() {
     string text = "Hello, World!";
    char key = 'K';

    ECBMode ecbMode;
    CBCMode cbcMode;

    EncryptionContext context(&ecbMode);


     string encrypted = context.encrypt(text, key);
     string decrypted = context.decrypt(encrypted, key);

     cout << "ECB Encrypted: " << encrypted <<  endl;
     cout << "ECB Decrypted: " << decrypted <<  endl;


    context.setStrategy(&cbcMode);

    encrypted = context.encrypt(text, key);
    decrypted = context.decrypt(encrypted, key);

     cout << "CBC Encrypted: " << encrypted <<  endl;
     cout << "CBC Decrypted: " << decrypted <<  endl;

    return 0;
}

#include <iostream>
#include <bitset>
#include <vector>
#include <random>
#include <string>


using namespace std;

const float e = 2.718281828;

const int bitSize = 701;

bool isPrime(int num) {
    if (num <= 1)
        return false;

    int sqrtNum = sqrt(num);
    for (int i = 2; i <= sqrtNum; ++i) {
        if (num % i == 0)
            return false;
    }

    return true;
}

int nextPrime(int num) {
    while (true) {
        num++;
        if (isPrime(num))
            return num;
    }
}

size_t shortSize = sizeof(short);

class Bitset {
public:
    unsigned short* bits;
    size_t size;

    Bitset(size_t size) : size(size) {
        size_t numShorts = (size + 15) / shortSize;
        bits = new unsigned short[numShorts]();
    }

    Bitset() {
        size_t numShorts = (1 + 15) / shortSize;
        bits = new unsigned short[numShorts]();
    }

    void set(size_t index) {
        if (index >= size) {
            cout << "Index out of range." << endl;
            return;
        }

        size_t shortIndex = index / shortSize;
        size_t bitIndex = index % shortSize; 

        bits[shortIndex] |= (1 << bitIndex);
    }

    bool test(size_t index) const {
        if (index >= size) {
            cout << "Index out of range." << endl;
            return false;
        }

        size_t shortIndex = index / 16;
        size_t bitIndex = index % 16; 

        return (bits[shortIndex] & (1 << bitIndex)) != 0;
    }

    void resize(size_t new_size) {
        size_t numShorts = (new_size + 15) / 16;
        unsigned short* newBits = new unsigned short[numShorts]();

        size_t minSize = min(size, new_size);
        for (size_t i = 0; i < minSize; i++) {
            newBits[i] = bits[i];
        }

        delete[] bits;
        bits = newBits;
        size = new_size;
    }
};




class BloomFilter {
public:

    Bitset bitSet;

    vector<vector<int>> hashCoefficients;
    size_t numHashFunctions;
    size_t tableSize;
    size_t bit_per_item;

    void generateHashCoefficients(int size) {
        srand(NULL);
        for (size_t i = 0; i < numHashFunctions; ++i) {
            hashCoefficients.push_back({ rand() % size, rand() % size , rand() % size, rand() % size });
        }

    }

    size_t computeHashValue(const string& address, vector<int>& coeffs) {
        vector<int> tokens;
        size_t pos = 0;
        string token;
        string ipCopy = address;
        while ((pos = ipCopy.find('.')) != string::npos) {       // 
            token = ipCopy.substr(0, pos);                       //   strip('.') -> vec<int>
            tokens.push_back(stoi(token));                       // 
            ipCopy.erase(0, pos + 1);                            // 
        }
        tokens.push_back(stoi(ipCopy));

        size_t hashValue = 0;
        for (size_t i = 0; i < 4; ++i) {
            hashValue += tokens[i] * coeffs[i];                  // calc hash value
        }

        return hashValue;
    }


    BloomFilter(size_t predictedSize, double mistakeFreq) {

        numHashFunctions = ceil(log(mistakeFreq)/log(0.5));
        bit_per_item = ceil(numHashFunctions / (log(2) / log(e)));

        tableSize = nextPrime(bit_per_item * predictedSize);


        bitSet.resize(tableSize);

        generateHashCoefficients(tableSize);
    }

    void insert(const string& ipAddress) {
        for (auto coeffs : hashCoefficients) {
            size_t index = computeHashValue(ipAddress, coeffs) % bitSet.size; // calc hash value
            bitSet.set(index);
        }
    }

    bool contains(const string& ipAddress) {
        for (auto& coeffs : hashCoefficients) {                                    // check all hash func
            size_t index = computeHashValue(ipAddress, coeffs) % bitSet.size;
            if (!bitSet.test(index)) {
                return false;
            }
        }
        return true;
    }

};

int main() {

    BloomFilter bloomFilter(1000000, 0.0001);
    
    bloomFilter.insert("192.168.0.1");
    bloomFilter.insert("10.0.0.1");
    bloomFilter.insert("172.16.0.1");
    bloomFilter.insert("192.168.1.1");
    bloomFilter.insert("10.0.0.2");
    bloomFilter.insert("172.16.0.2");
    bloomFilter.insert("192.168.2.1");
    bloomFilter.insert("10.0.0.3");
    bloomFilter.insert("172.16.0.3");
    bloomFilter.insert("192.168.3.1");
    
    cout << bloomFilter.contains("172.16.0.2") << endl;
    cout << bloomFilter.contains("192.168.2.1") << endl;
    cout << bloomFilter.contains("10.0.0.3") << endl;
    cout << bloomFilter.contains("172.16.0.3") << endl;
    cout << bloomFilter.contains("192.168.3.1") << endl;
    cout << bloomFilter.contains("10.0.0.4") << endl;
    cout << bloomFilter.contains("172.16.0.4") << endl;
    cout << bloomFilter.contains("192.168.4.1") << endl;
    cout << bloomFilter.contains("10.0.0.5") << endl;
    cout << bloomFilter.contains("172.16.0.5") << endl;





    return 0;
}

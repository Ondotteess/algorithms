#include <iostream>
#include <bitset>
#include <vector>
#include <random>
#include <string>


using namespace std;


const int bitSize = 701;


class BloomFilter {
private:

    bitset<bitSize> bitSet;                    
    vector<vector<int>> hashCoefficients;      
    size_t numHashFunctions;                   

    void generateHashCoefficients() {
        srand(NULL);
        for (size_t i = 0; i < numHashFunctions; ++i) {
            hashCoefficients.push_back({ rand() % bitSize , rand() % bitSize , rand() % bitSize, rand() % bitSize });
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

public:
    BloomFilter(size_t predictedSize, double mistakeFreq) {
        numHashFunctions = ceil(-log(mistakeFreq) / log(2));     


        // tableSize = -1 * (elementCount * log(desiredFalsePositiveRate)) / (log(2)^2)
        //      bitset const value !

        generateHashCoefficients();                                     
    }

    void insert(const string& ipAddress) {
        for ( auto coeffs : hashCoefficients) {                                 
            size_t index = computeHashValue(ipAddress, coeffs) % bitSet.size(); // calc hash value
            bitSet.set(index);                                                  
        }
    }

    bool contains(const string& ipAddress) {
        for ( auto& coeffs : hashCoefficients) {                                    // check all hash func
            size_t index = computeHashValue(ipAddress, coeffs) % bitSet.size();     
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
 
    cout << bloomFilter.contains("172.16.0.2")   << endl;
    cout << bloomFilter.contains("192.168.2.1")  << endl;
    cout << bloomFilter.contains("10.0.0.3")     << endl;
    cout << bloomFilter.contains("172.16.0.3")   << endl;
    cout << bloomFilter.contains("192.168.3.1")  << endl;
    cout << bloomFilter.contains("10.0.0.4")     << endl;
    cout << bloomFilter.contains("172.16.0.4")   << endl;
    cout << bloomFilter.contains("192.168.4.1")  << endl;
    cout << bloomFilter.contains("10.0.0.5")     << endl;
    cout << bloomFilter.contains("172.16.0.5")   << endl;

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

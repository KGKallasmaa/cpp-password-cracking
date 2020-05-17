#include <iostream>
#include "hash/hashcalculator.h"
#include "hash/picosha2.h"
#include "hash/md5.h"
#include <string>


using namespace std;


bool HashCalculator::are_equal(const string &a, const string &b) {
    return equal(a.begin(), a.end(),
                 b.begin(), b.end(),
                 [](char a, char b) {
                     return tolower(a) == tolower(b);
                 });
}


string HashCalculator::calculate_hash(const string hash_type, const string &str) {
    if (hash_type.compare("MD5") == 0) {
        string data_hex_digest;
        md5 hash;
        hash.update(str.begin(), str.end());
        hash.hex_digest(data_hex_digest);
        return data_hex_digest;
    } else if (hash_type.compare("SHA256") == 0) {
        vector<unsigned char> hash(picosha2::k_digest_size);
        picosha2::hash256(str.begin(), str.end(), hash.begin(), hash.end());
        return picosha2::bytes_to_hex_string(hash.begin(), hash.end());
    }
    cerr << "Hash can't be with size " << str.size() << ". Input hash was " << str << endl;
    return "";
}
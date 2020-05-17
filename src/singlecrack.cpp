#include "singlecrack.h"
#include "permutations.h"
#include <iostream>
#include <fstream>
#include "hash/hashcalculator.h"

using namespace std;


vector <string> SingleCrack::read_file(const string &filename) {
    //Source:https://gist.github.com/sergnechaev/d788ce3623935efa58e6ef1af668b8af

    ifstream ifs(filename);

    vector <string> lines;

    if (!ifs) {
        cerr << "Cannot open file: " << filename << endl;


    } else {

        for (string line; getline(ifs, line);) {
            lines.push_back(line);
        }
    }

    return lines;
}


void SingleCrack::dictionary_crack(string const &og_hash) {
    //Checks if the hash matches to the hashes of 10M most common passwords

    vector <string> common_passwords = read_file("./data/common_passwords.txt");

    HashCalculator hashCalculator;
    string hash_type = og_hash.size() == 64 ? "SHA256" : "MD5";


    for (int i = 0; i < common_passwords.size(); i++) {
        if (password.compare("_______________NOT_______________FOUND_______________") == 0) {
            if (hashCalculator.are_equal(hashCalculator.calculate_hash(hash_type, common_passwords[i]), og_hash)) {
                password = common_passwords[i];
            }
        }
    }
}


string SingleCrack::crack_hash(string og_hash) {
    //Maximum password len = 89

    //Perform dictionary cracking. A lot of passwords are quite common
    cout << "Testing for dictionary passwords" << endl;
    dictionary_crack(og_hash);
    if (password.compare("_______________NOT_______________FOUND_______________") != 0) {
        auto discovered_password = password;
        password = "_______________NOT_______________FOUND_______________";
        return discovered_password;
    }
    cout << "Testing for uncommon passwords" << endl;
    Permutations permutations;
    // Use bruteforce
    return permutations.bruteforce(og_hash);
}
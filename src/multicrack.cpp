#include "multicrack.h"
#include "singlecrack.h"
#include <iostream>
#include <map>
#include <set>
#include <fstream>

using namespace std;


void MultiCrack::multi_crack_hash(const string &filename) {
    SingleCrack singleCrack;

    //Get passwords we need to check
    vector <string> passwords_to_crack = singleCrack.read_file(filename);

    cout << "Found " << passwords_to_crack.size() << " passwords to crack. There are "<<set<string>(passwords_to_crack.begin(),passwords_to_crack.end() ).size()<<" unique passwords" << endl;
    //Storing previously fetched passwords and hashes in the dictionary
    map <string, string> hash_password = {};

    vector <string> cracked_passwords;

    for (int i = 0; i < passwords_to_crack.size(); i++) {
        //We have not cracked that password
        string og_hash = passwords_to_crack[i];
        if (hash_password.find(passwords_to_crack[i]) == hash_password.end()) {
            string password = singleCrack.crack_hash(og_hash);
            hash_password[og_hash] = password;
            cracked_passwords.push_back(password);
            cout << "Found a password: " << password << endl;
        }
            // We have cracked that password already
        else {
            string password = hash_password.at(og_hash);
            cracked_passwords.push_back(password);
            cout << "Found a password: " << password << endl;
        }
    }
    cout << "Finished cracking " << cracked_passwords.size() << " passwords." << endl;
    cout << "Writing passwords to the results file" << endl;

    //Write results to file
    ofstream outFile("./results/results.txt");
    for (const auto &e : cracked_passwords) outFile << e << "\n";
}


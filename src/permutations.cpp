/**
 * Password generation is not my code
 * Source:https://www.geeksforgeeks.org/generate-passwords-given-character-set/
*/

#include <iostream>
#include <cmath>
#include <thread>
#include "permutations.h"
#include "hash/hashcalculator.h"


using namespace std;


void Permutations::generate(char *arr, int i, string s, int len, string const &og_hash) {
    if (i >= 0) {
        if (password.compare("_______________NOT_______________FOUND_______________") == 0) {
            if (i == 0) {
                HashCalculator hashCalculator;

                string hash_type = og_hash.size() == 64 ? "SHA256" : "MD5";
                string calc_hash = hashCalculator.calculate_hash(hash_type, s);

                if (hashCalculator.are_equal(calc_hash, og_hash)) {
                    password = s; //password is defined in permutations.h
                }

            } else {
                for (int j = 0; j < len; j++) {
                    string appended = s + arr[j];
#pragma omp parallel
                    {
#pragma omp task
                        generate(arr, i - 1, appended, len, og_hash);
#pragma omp task
                        generate(arr, i - 2, appended, len, og_hash);
#pragma omp task
                        generate(arr, i - 3, appended, len, og_hash);
#pragma omp task
                        generate(arr, i - 4, appended, len, og_hash);
                    }
                }
            }
        }
    }
    return;
}


string Permutations::crack(char *arr, int len, string const &og_hash) {
    for (int i = 1; i <= len; i++) {
        if (password.compare("_______________NOT_______________FOUND_______________") == 0) {
            auto pw_combo_count = pow(len, i);
            cout << "Testing passwords up to length " << i << ". Maximum password combinations " << pw_combo_count
                 << endl;
            generate(arr, i, "", len, og_hash);
        }
    }
    return password;
}


string Permutations::bruteforce(string og_hash) {
    char arr[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
                  'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
                  'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                  'Y', 'Z', ' ', '!', '"', '#', '$', '%', '&', ' ', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';',
                  '<', '>', '=', '?', '@', '{', '|', '}', '~'}; // Can't add ' character

    unsigned int n = std::thread::hardware_concurrency();
    cout << "Code can be run in " << n << " threads. Are you doing it?" << endl;


    int len = sizeof(arr) / sizeof(arr[0]);
    return crack(arr, len, og_hash);
}
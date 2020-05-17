#pragma once
#include <string>

using namespace std;

class Permutations {

public:
    string password = "_______________NOT_______________FOUND_______________";
    /**
    * Default constructor
    */
    Permutations() = default; //c++11 The default constructor is explicitly stated.

    /**
    *
    * @param og_hash = the hash you want to crack
    * @return  the cracked password
    */
    string bruteforce(string og_hash);

private:

    /**
     *
     * @param arr = the array of characters that can be in the password
     * @param i = the current maximum password length
     * @param s = the current password candidate
     * @param len = maximum password length
     * @param og_hash = the hash you want to crack
     */
    void generate(char *arr, int i, string s, int len, string const &og_hash);


    /**
     *
     * @param arr =  the array of characters that can be in the password
     * @param len  = maximum password length
     * @param og_hash = the hash you want to crack
     * @return the cracked password
     */
    string crack(char *arr, int len, string const &og_hash);




};
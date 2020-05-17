#pragma once


#include <string>

using namespace std;

class MultiCrack {

public:

    /**
    * Default constructor
    */
    MultiCrack() = default; //c++11 The default constructor is explicitly stated.

    /**
*
* @param filename = the file where the MD5 hashes are located
* @return = cracked passwords in a file src/results.txt
*/
    void multi_crack_hash(const std::string &filename);
};
#pragma once


class HashCalculator {

public:


    /**
    * Default constructor
    */
    HashCalculator() = default; //c++11 The default constructor is explicitly stated.

    /**
* @param hash_type = the kind of hash you want to calculate. Can be MD5 or SHA256
* @param str = the string you you want to calculate the hash of
* @return = the hash of the string
*/
    std::string calculate_hash(const std::string hash_type, const std::string &str);

    /**
     *
     * @param a string 1
     * @param b string 2
     * @return returns if two strings are equal (case is not important)
     */
    bool are_equal (const std::string &a, const std::string &b);
};
#pragma once

#include <vector>
#include <string>

using namespace std;

class SingleCrack {

public:
     string password = "_______________NOT_______________FOUND_______________";
    /**
    * Default constructor
    */
    SingleCrack() = default; //c++11 The default constructor is explicitly stated.

    /**
*
* @param og_hash = the hash the user wants to crack
* @return = cracked password
*/
    std::string crack_hash(std::string og_hash);

    /**
     * @param file_name = the file where passwords are located
     * @return = array of most common password
     */
    std::vector <std::string> read_file(const std::string &filename);


private:
    /**
 * @param og_hash = the has the user wants to crack
 * @return = the cracked password, if it's a very common password
 */
    void dictionary_crack(std::string const &og_hash);
};
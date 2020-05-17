#pragma once

#include <string>

class PasswordScore {

public:

    /**
    * Default constructor
    */
    PasswordScore() = default; //c++11 The default constructor is explicitly stated.

    /**
*
* @param password = the password you want to score
* @return = the classification of the passwords score, from lowest to highest, [DICTIONARY,WEAK,MODERATE,STRONG]
*/
    std::string give_password_score(const std::string& password);

    /**
     *
     * @param password  = the password you want to calculate the cracking time of
     * @return the estimate cracking time in hours. It assumes that 2 million passwords are checked per second.
     */
    float password_cracking_time_in_hours(const std::string& password);
};
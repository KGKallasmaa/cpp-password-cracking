#include "singlecrack.h"
#include "password_score.h"
#include <cmath>

using namespace std;

string PasswordScore::give_password_score(const string &password) {
    SingleCrack singleCrack;

    //Check if password is dictionary
    vector <string> dictionary_passwords = singleCrack.read_file("./data/common_passwords.txt");

    if (std::find(dictionary_passwords.begin(), dictionary_passwords.end(), password) != dictionary_passwords.end()) {
        return "DICTIONARY";
    }

    /*
     * Measure password score
     * Source: https://www.codespeedy.com/password-strength-checker-in-cpp/
    */

    int l_case = 0, u_case = 0, digit = 0, special = 0;
    int l = password.length(), i;
    for (i = 0; i < l; i++) {
        if (islower(password[i])) {
            l_case = 1;
        }
        if (isupper(password[i])) {
            u_case = 1;
        }
        if (isdigit(password[i])) {
            digit = 1;
        }
        if (!isalpha(password[i]) && !isdigit(password[i])) {
            special = 1;
        }
    }

    if (l_case && u_case && digit && special && l >= 8) {
        return "STRONG";

    } else if ((l_case + u_case + digit + special >= 3) && l >= 6) {
        return "MODERATE";
    }
    return "WEAK";
}

float PasswordScore::password_cracking_time_in_hours(const string &password) {
    if (give_password_score(password).compare("DICTIONARY") == 0) {
        return 0.0;
    }
    auto nr_of_passwords_checked_per_second = 2000000.0;
    //Checking password characteristics
    auto nr_of_numbers = 10;
    auto nr_of_small_letters = 26;
    auto nr_of_big_letters = 26;
    auto nr_of_special_characters = 27;

    int l_case = 0, u_case = 0, digit = 0, special = 0;
    int l = password.length(), i;
    for (i = 0; i < l; i++) {
        if (islower(password[i])) {
            l_case = 1;
        }
        if (isupper(password[i])) {
            u_case = 1;
        }
        if (isdigit(password[i])) {
            digit = 1;
        }
        if (!isalpha(password[i]) && !isdigit(password[i])) {
            special = 1;
        }
    }
    //How many passwords we have to check?
    auto total_nr_of_chars = nr_of_numbers * digit + nr_of_small_letters * l_case + nr_of_big_letters * u_case +
                             nr_of_special_characters * special;
    auto max_nr_of_passwords_to_check = pow(total_nr_of_chars, password.size());
    //Convert results to hours
    return max_nr_of_passwords_to_check / nr_of_passwords_checked_per_second / 3600;
}




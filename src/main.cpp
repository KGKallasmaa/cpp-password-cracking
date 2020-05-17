
#include <iostream>
#include "hashcrack.h"

using namespace std;


int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "You have entered too few arguments" << endl;
        return EXIT_FAILURE;
    }
    string function_name = argv[1];

    /*
     * Help
     * * arg1 = function name
     */

    if ((function_name.compare("-h")) == 0) {
        cout<<""<< endl;
        cout<<"single_crack= crack a single hash. You need to provide the password hash"<< endl;
        cout<<"multi_crack= crack multiple hashes. You need to provide the location of hash file"<< endl;
        cout<<"password_score= get password score of a single password. You need to provide the password"<< endl;
        cout<<"cracking_time= get password cracking time of a single password. You need to provide the password"<< endl;
        return EXIT_SUCCESS;
    }

    if (argc != 3) {
        if (argc > 3) {
            cerr << "You have entered too few arguments" << endl;
        } else {
            cerr << "You have entered too many arguments" << endl;
        }
        return EXIT_FAILURE;
    }
    /*
     * SINGLE CRACK
     * * arg1 = function name
     * * arg2 = password
     */

    if ((function_name.compare("single_crack")) == 0) {
        string og_hash = argv[2];
        SingleCrack singleCrack;
        string cracked_password = singleCrack.crack_hash(og_hash);
        cout << "Your cracked password is: " << cracked_password << endl;
    }
        /*
         * MULTI CRACK
         * * arg1 = function name
         * * arg2 = file_name
         */

    else if ((function_name.compare("multi_crack")) == 0) {
        string file_name = argv[2];
        MultiCrack multiCrack;
        multiCrack.multi_crack_hash(file_name);
        cout << "Finished cracking all of the given passwords. Results are stored in the results folder" << endl;
    }

        /*
        * PASSWORD SCORE
        * * arg1 = function name
        * * arg2 = password
        */

    else if ((function_name.compare("password_score")) == 0) {
        string password = argv[2];
        PasswordScore passwordScore;
        string score = passwordScore.give_password_score(password);
        cout << "Your password score is: " << score << endl;
    }

        /*
    * CRACKING TIME
    * * arg1 = function name
    * * arg2 = password
    */

    else if ((function_name.compare("cracking_time")) == 0) {
        string password = argv[2];
        PasswordScore passwordScore;
        float cracking_time_in_hours = passwordScore.password_cracking_time_in_hours(password);
        cout << "Estimated cracking time " << cracking_time_in_hours << " hours" << endl;
    } else {
        cout << "The function (" << function_name << ") that you're trying to reach does not exist!" << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

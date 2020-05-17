#include <iostream>

#include "hashcrack.h"

using namespace std;

int testcount = 0;


bool password_was_cracked_correctly(string str1, string str2) {
    return str1.compare(str2) == 0;
}

bool cmp_b(bool a, bool b) {
    return a == b;
}

bool lists_are_equal(vector <string> list1, vector <string> list2) {
    return list1 == list2;
}


#define TEST_CRACKED_PASSWORD(a, str1, str2) cout << "Test " << ++testcount << ". " << a << ": " << ((password_was_cracked_correctly(str1,str2)) ? "OK" :"FAIL") << endl
#define TEST_TIME(a, b1, b2) cout << "Test " << ++testcount << ". " << a << ": " << (cmp_b(b1,b2) ? "OK" :"FAIL") << endl
#define TEST_MULTIPLE_CRACKED_PASSWORDS(a, list1, list2) cout << "Test " << ++testcount << ". " << a << ": " << ((lists_are_equal(list1,list2)) ? "OK" :"FAIL") << endl


void test_single() {
    cout << "--Test single_crack" << endl;
    SingleCrack singleCrack;


    //Testing: common passwords

    //Password
    string og_hash = "5F4DCC3B5AA765D61D8327DEB882CF99";
    auto cracked_password = singleCrack.crack_hash(og_hash);
    auto expected_password = "password";
    TEST_CRACKED_PASSWORD("Simple password cracking for MD5 hash. Original password: password", expected_password,
                          cracked_password);

    //1234
    og_hash = "03AC674216F3E15C761EE1A5E255F067953623C8B388B4459E13F978D7C846F4";
    cracked_password = singleCrack.crack_hash(og_hash);
    expected_password = "1234";
    TEST_CRACKED_PASSWORD("Simple password cracking for SHA256 hash. Original password: 1234", expected_password,
                          cracked_password);

    //kodu
    og_hash = "cf1254c1f74c634318db1510c7573c2b";
    cracked_password = singleCrack.crack_hash(og_hash);
    expected_password = "kodu";
    TEST_CRACKED_PASSWORD("Simple password cracking for MD5 hash. Original password: kodu", expected_password,
                          cracked_password);
}

void test_multiple() {
    cout << "--Test multi_crack" << endl;
    SingleCrack singleCrack;
    MultiCrack multiCrack;
    multiCrack.multi_crack_hash("./data/to_crack_hash.txt");
    vector <string> cracked_passwords = singleCrack.read_file("./results/results.txt");
    vector <string> v = {"ter1", "ter2", "Ter", "aab", "aab"};
    TEST_MULTIPLE_CRACKED_PASSWORDS("Testing if multiple passwords were cracked correctly", cracked_passwords, v);
}

void test_score() {
    cout << "--Test password_score" << endl;
    PasswordScore passwordScore;

    string dictionary_password = "love";
    string weak_password = "Namee";
    string moderate_password = "Code#1";
    string strong_password = "CodeSpeedy@1213";

    string dictionary_password_score = passwordScore.give_password_score(dictionary_password);
    string weak_password_score = passwordScore.give_password_score(weak_password);
    string moderate_password_score = passwordScore.give_password_score(moderate_password);
    string strong_password_score = passwordScore.give_password_score(strong_password);

    TEST_CRACKED_PASSWORD("love is a dictionary password", "DICTIONARY",
                          dictionary_password_score);

    TEST_CRACKED_PASSWORD("Namee is a weak password", "WEAK",
                          weak_password_score);
    TEST_CRACKED_PASSWORD("Code#1 is a moderate password", "MODERATE",
                          moderate_password_score);
    TEST_CRACKED_PASSWORD("CodeSpeedy@1213 is a strong password", "STRONG",
                          strong_password_score);
}


void test_cracking_time() {
    cout << "--Test cracking_time" << endl;
    PasswordScore passwordScore;
    //Define passwords
    string dictionary_password = "love";
    string weak_password = "namee";
    string moderate_password = "Code#1";
    string strong_password = "CodeSpeedy@1213";
    //Calculate cracking time
    float d_time = passwordScore.password_cracking_time_in_hours(dictionary_password);
    float w_time = passwordScore.password_cracking_time_in_hours(weak_password);
    float m_time = passwordScore.password_cracking_time_in_hours(moderate_password);
    float s_time = passwordScore.password_cracking_time_in_hours(strong_password);
    //Test
    bool d_is_instant = d_time == 0.0;
    bool w_is_small = w_time < 1.0 / 60.0; //one minute
    bool m_is_small = m_time > 10.0 / 60.0; //10 minutes
    bool s_is_small = s_time > 1.0; //more than 1h
    bool s_is_better_than_m = s_time > m_time;

    TEST_TIME("Dictionary passwords are cracked instantly", d_is_instant, true);
    TEST_TIME("Small passwords are cracked under a minute", w_is_small, true);
    TEST_TIME("Medium passwords are cracked in more than 1 minute", m_is_small, true);
    TEST_TIME("Strong passwords take more to crack than medium", s_is_better_than_m, true);
    TEST_TIME("Strong passwords are cracked in more than 1 hour", s_is_small, true);
}

int main(int argc, char *argv[]) {
    test_single();
    test_multiple();
    test_score();
    test_cracking_time();

    cout << "Test count: " << testcount << endl;
    return EXIT_SUCCESS;
}

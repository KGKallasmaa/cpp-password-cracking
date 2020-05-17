# Password cracking
This repository holds the code that allows you to do crack MD5 and SHA256 hashes.
The code was written as the final project of the <a href="https://courses.cs.ut.ee/2020/cpp/spring">CPP course</a>.

The maximum password length can be 89 characters long, but it can be easily increased, by updating the character set.


# Building the executable

```
make clean
make output
```

# Building the lib

```
make clean
make
```

# Testing code

The tests of this code are located in the tests folder in a file named hashcrackertest.cpp

```
make clean
make test
...
...
Test count: 13
```

# Functionality

The code can perform four tasks:

1. single_crack
2. multi_crack
3. password_score
4. cracking_time

If you forget the exact syntax or the required arguments you can the -h command

```
./output -h

single_crack= crack a single hash. You need to provide the password hash
multi_crack= crack multiple hashes. You need to provide the location of hash file
password_score= get password score of a single password. You need to provide the password
cracking_time= get password cracking time of a single password. You need to provide the password
```


# Single crack 

Single crack can crack the given MD5 or SHA256 hash. 

To crack the password the program at first checks, if the password is a dictionary password.
Dictionary passwords are passwords that are words found in the English dictionary or they are commonly used passwords. For example, xxxxxx, is a dictionary password.
In total <a href="https://github.com/danielmiessler/SecLists/blob/master/Passwords/Common-Credentials/10-million-password-list-top-1000000.txt">10 million</a> of the post popular dictionary passwords are used.

<b>Example:</b>

Let's assume that you want to crack a hash 5d41402abc4b2a76b9719d911017c592

To do that you need to enter the following command

```
./output single_crack 5d41402abc4b2a76b9719d911017c592
```

This results in the following output
```
./output single_crack 5d41402abc4b2a76b9719d911017c592
Testing for dictionary passwords
Testing for uncommon passwords
Code can be run in 4 threads. Are you doing it?
Testing passwords up to length 1. Maximum password combinations 89
Testing passwords up to length 2. Maximum password combinations 7921
...
Testing passwords up to length 5. Maximum password combinations 5.58406e+09
Your cracked password is: hello
```

The program assumes that your computer has 4 cors. If you have less than that, the code still works, but it will
not be as efficient. If you have more, then by changing the permutations.cpp file the execution speed of the program can
be increased.

# Multi crack 

To find the passwords corresponding to multiple hashes, the program executes the single crack functionality 
sequentially.

<b>Example:</b>

Let's assume that the hashes, that you want to crack, are located at ./data/to_crack_hash.txt

To find the corresponding passwords, enter the following command

```
./output multi_crack ./data/to_crack_hash.txt
```

This results in the following output
```
./output multi_crack ./data/to_crack_hash.txt
Found 5 passwords to crack. There are 4 unique passwords
Testing for dictionary passwords
...
Found a password: ter1
...
Finished cracking all of the given passwords. Results are stored in the results folder
```

If your program finishes then the passwords can be found in ./results/results.txt.

If you run the code multiple times, the results file will be overwritten every time you run the code. 


# Password score 

Password score allows you to estimate how strong your password is.

There are four password categories:

1. "DICTIONARY"
2. "WEAK"
3. "MODERATE"
4. "STRONG"

Dictionary passwords are the weakest passwords. These passwords should not be used, as they can be cracked almost instantly.

Weak passwords are passwords that are less than 6 characters long or they don't have that have at least 3 of 4 four attributes: one lower case character,
one upper case charter, one digit, one special charter.

Moderate passwords are passwords that are at least 6 characters long and that have at least 3 of 4 four attributes: one lower case character,
one upper case charter, one digit, one special charter.

Strong passwords are passwords that are at least 8 characters long and that have all of the 4 four attributes: one lower case character,
one upper case charter, one digit, one special charter.


<b>Example:</b>

Let's assume that you want to know the score of the password: "cpp-course-2020"

To find it, enter the following command

```
./output password_score cpp-course-2020
```

This results in the following output
```
./output password_score cpp-course-2020
Your password score is: MODERATE
```

# Cracking time 

Cracking time allows you to estimate how long it takes (in hours) to crack your password.
The program assumes that 2,000,000 million passwords can be check per second.

To find the cracking estimate, the program at first checks if the password is a dictionary password.

If so, it returns 0.0.

If not, it calculates how big is the password character set. At first, the program can choose from 89 characters.

If the password doesn't contain any numbers, the size of the character set is reduced by 10.

If the password doesn't contain any lower case letters, the size of the character set is reduced by 26.

If the password doesn't contain any upper case letters, the size of the character set is reduced by 26.

If the password doesn't contain any special character, the size of the character set is reduced by 27.

Then the program calculates the number of passwords it has to check by calculating the power of the size of the character set and the password length.
The get the cracking time in hours, the program divides the number of checkable passwords by 7,200,000,000 (2,000,000*3,600)

<b>Example:</b>

Let's assume that you want to know how long it would take to crack: "cpp-course-2020"

To find it, enter the following command

```
./output cracking_time cpp-course-2020
```

This results in the following output
```
./output cracking_time cpp-course-2020
Estimated cracking time 1.35761e+17 hours
```

The cracking estimation is somewhat primitive and you're more than welcome to improve it.

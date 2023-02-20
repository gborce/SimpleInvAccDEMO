// utility.h
// a collection of general purpose functions
// Date of last modification:  09/6/2002
// Added dashline() function
// Improved lowercaseString() and uppercaseString() functions.

#ifndef _UTILITY_H_SEEN_
#define _UTILITY_H_SEEN_
#include <iostream>
#include <fstream>
#include <strstream>
#include <string>
#include <cctype>
#include <cstdlib>


using namespace std;
const int DASHDEFAULT = 60;

char lower(char c);    // used by lowercaseString()
char raise(char c);    // used by uppercaseString()

int setInt();           // allows safe input of integer data.
double setReal();       // allows safe input of floating data.
int stringToInt(string& s); // converts s to int. returns 0 if invalid.
string intToString(int n); // converts n to string.
string intToString(int n, unsigned len); // converts n to a string length len
                                     // left-padded with zeros
void uppercaseString(string& s); // converts s to upper case.
void lowercaseString(string& s); // converts s to lower case.
bool more(string what); // handles dialog to see if user wants to
                        // continue a repeating process.
                        // Usage:  do{...commands...} while (more("things"));
bool yes();             // handles typical yes/no dialog with user
                        // Usage: ... if(yes()) {...commands...}
void moneyDisplay(double d, bool newline = false); 
                        // output in monetary format with $
string setPhoneString();      // allows safe input of a phone number 
string setAddrString();  // sets an address string from the keyboard

void openOutputFile(ofstream& outfile); // open a file stream for writing
void openInputFile(ifstream& infile); // open a file stream for reading

void dashline(int size = DASHDEFAULT, char c = '-'); // draws a line of dashes

#endif

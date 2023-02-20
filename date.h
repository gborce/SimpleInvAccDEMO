// File: date.h
// A simple implementation of a date class.

#ifndef _DATE_H_
#define _DATE_H_
#include <iostream>
#include <fstream>
#include <string>   // stl string class

using namespace std;

class Date {
 public:
  friend ostream& operator<<(ostream& out, const Date& d) 
    { d.display();   return out; }
  friend istream& operator>>(istream& in, Date& d)
    { d.set();   return in; }
  Date();  // default constructor initializes host obj to  base date.
  Date(unsigned m, unsigned d, unsigned y);  
                                  // constructs Date from month/day/year
  void set();  // interactively sets data for host obj from keyboard
               // Guarantees a valid date.
  void set(unsigned m, unsigned d, unsigned y);
                                // sets host object from args if valid.
                                // otherwise sets host object to base date.
  void setToToday();            // sets host object to today's date
                                // using the system clock (see timetst.cc)
  void display(bool shortform = true) const;  // displays the host object
      // shortform is  mm/dd/yyyy  (e.g.,  03/22/2002
      // longform is  dayname, month dd, yyyy (e.g., Friday, Sep 13, 2002)
  void write(ofstream& out) const;  // writes a date object to file
  void read(ifstream& in) ;         // reads a date object from file
  string getWeekDay() const; // returns the day of the week for host object
  bool operator<(const Date& d) const;   // comparison: host < d
  bool operator==(const Date& d) const; // comparison: host == d
  bool operator<=(const Date& d) const; // comparison: host <= d
  int  operator-(const Date& d) const; // computes number of days (host - d)
  Date operator+(int days) const;      // computes the date (host + days)
  void operator+=(int days);           // changes host to (host + days)
  static bool leapyear(unsigned year);     // tests year for leap year
  static unsigned yeardays(unsigned year);   
                                       // returns number of days in year
  static unsigned monthdays(unsigned month, unsigned year); 
                                      // returns days in month
  static string monthname(unsigned month);     // returns name of month
 
 private:
  unsigned long mDsb;    // days since base date
  Date(unsigned long dsb);     // private constructor creates Date from dsb
  void setDsb (unsigned month, unsigned day, unsigned year); 
                                               // computes and sets mDsb
  void getMDY (unsigned& m, unsigned& d, unsigned& y) const; 
                                              //computes m/d/y from mDsb
  static unsigned mBaseYear; 
};

#endif

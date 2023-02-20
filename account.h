/**********************************************************************
 *
 *  Bruce Gjorgjievski
 *  file: account.h
 *  Desc: Definitions for the enhanced account class
 *
 **********************************************************************/

#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip.h>
#include "date.h"
#include "invlist.h"

using namespace std;

class Account {
 public:
  friend ostream& operator<<(ostream& out, const Account& a) 
    { a.display();   return out; }
  friend istream& operator>>(istream& in, Account& a)
    { a.set();   return in; }

  Account (); //default constructor, init. acc. to 0

  Account& clone() { return (*this); }
  void set();  // interactively sets data for host obj from keyboard
  bool edit(); //offers to edit the data fields
  void display(bool brief = true) const;  // displays the host object
  void write(ofstream& out) const;  // writes a time object to file
  void read(ifstream& in) ;         // reads a time object from file
  //portfolio handling functions
  void addInv();  //interactively adds investment to portfolio
  bool removeInv(string which); //interactively removes investment from portfolio
  void updateInv(Date when, string which); //updates individual investment or the entire portfolio
  void displayInv(string which="ALL"); //displays individual investment or the entire portfolio
  bool managePortfolio(); //packages the previous three functions

  double getCurrValue(); //returns the current value of the portfolio
  void clearPortfolio(); //completely clears the portfolio
  bool portfolioIsEmpty(); 
  bool isInPortfolio(string which);
  //getters
  string getID() const { return mID; } // returns ID
  string getName() const { return mName; } // returns Name
  string getAddress() const { return mAddress; } // returns Address
  string getPhone() const { return mPhone; }// returns Phone
  Date getDate() const { return mDate; }// returns Date

 private:
  //fields
  string mID, mName, mAddress, mPhone;
  Date mDate;
  InvestList portfolio;
  //constants
  static unsigned MAX_ID;
  //setters
  void setID () ;
  void setName () ;
  void setAddress () ;
  void setPhone () ;
  void setDate ();
}
;
#endif

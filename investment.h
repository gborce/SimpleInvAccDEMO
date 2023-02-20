/**********************************************************************
 *
 *  Borce Gjorgjievski, HW9, Investment Abstract Class
 *  file: investment.h
 *  Modified: Nov 24, 2002
 *  Desc: Definitions for the investment class
 *
 **********************************************************************/

#ifndef _INVESTMENT_H_
#define _INVESTMENT_H_
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip.h>
#include <time.h>
#include <stdlib.h>
#include "date.h"

using namespace std;

class Investment {
 public:
  Investment (string invType):mInvType(invType) {}; //default constructor
  virtual ~Investment() {}; //virtual destructor

  virtual void set();  // interactively sets data for host obj from keyboard
  virtual bool edit();
  virtual void display() const;  // displays the host object
  virtual void write(ofstream& out) const;  // writes host object to file
  virtual void read(ifstream& in) ;         // reads host object from file
  virtual void update (Date when) = 0; //updates the inv with random*volatility val
  virtual Investment* newInvestment() = 0;
  virtual Investment* clone() = 0;
  virtual double computeCurrentValue() = 0; //computes teh current value of the inv
  //getters
  string getID() const { return mInvID; } // returns ID
  string getName() const { return mInvName; } // returns Name
  string getInvType() const { return mInvType; } // returns Type
  Date getDate() const { return mDate; }// returns Date
  double getVolatility() const { return volatility; } //returns volatility
  double getRand(double v); //returns a random number from -v to +v
  //statics
  static int MAX_ID, MAX_DAYS;
 protected:
  double currentValue ; //stores teh current value of the investment
  double volatility;  // gives the ranges in which the inv can randomize
  Date lastUpdate;  //the date of the last update() running
 private:
  //fields
  string mInvID, mInvName, mInvType;
  Date mDate;
  
  //setters
  void setID ();
  void setName ();
  void setDate () ;
  void setVolatility();
}
;
#endif

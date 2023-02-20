/**********************************************************************
 *
 *  Borce Gjorgjievski, HW10, Bond, Stock, MMSavings derived classes
 *  file: invDerived.h
 *  Modified:  Dec 4, 2002
 *  Desc: Definitions for the Bond, Stock, MMsavings classes
 *
 **********************************************************************/

#ifndef _INVDERIVED_H_
#define _INVDERIVED_H_
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip.h>
#include "investment.h"

using namespace std;

class Stock : public Investment{
 public:
  Stock () : Investment ("Stock") {}

  void set();  // interactively sets data for host obj from keyboard
  bool edit(); //edits the member variables
  void display() const;  // displays the host object
  void write(ofstream& out) const;  // writes host object to file
  void read(ifstream& in) ;         // reads host object from file
  void update (Date when);
  double computeCurrentValue();
  Stock* newInvestment () {return new Stock;}
  Stock* clone() {return new Stock(*this);}
  //getters
  double getSharePrice() const { return mSharePrice; } // Initial SharePrice
  double getCurrSharePrice() const { return mCurrSharePrice; } // Currentl SharePrice
  int getNumShares() const { return mNumShares; } // returns NumShares

 private:
  //fields
  double mSharePrice, mCurrSharePrice;
  int mNumShares;

  //setters
  void setSharePrice ();
  void setNumShares ();
}
;

class Bond : public Investment{
  friend class InvestList;
 public:
  Bond () : Investment ("Bond") {}

  void set();  // interactively sets data for host obj from keyboard
  bool edit(); //edits the member variables
  void display() const;  // displays the host object
  void write(ofstream& out) const;  // writes host object to file
  void read(ifstream& in) ;         // reads host object from file
  void update (Date when);
  double computeCurrentValue ();
  Bond* newInvestment() {return new Bond;}
  Bond* clone() {return new Bond(*this);}
  //getters
  double getPurchPrice() const { return mPurchPrice; } // returns PurchPrice
  double getFaceValue() const { return mFaceValue; } // returns Face Value
  double getCoupon () const { return mCoupon; } // returns Coupon
  int getYrs2Mature() const { return mYrs2Mature; } // returns Yrs2Mature
  string getSPrating () const { return mSPrating; } //return S&P rating
  double getCurrPurchasePrice() const { return mCurrPurchPrice; } //returns the current purchase price (after updates)

 private:
  //fields
  double mPurchPrice, mFaceValue, mCoupon, mCurrPurchPrice;
  int mYrs2Mature;
  string mSPrating;

  bool validRating(string r) const;
  //setters
  void setPurchPrice ();
  void setFaceValue ();
  void setCoupon ();
  void setYrs2Mature ();
  void setSPrating ();
}
;

class MMsavings : public Investment{
 public:
  MMsavings () : Investment ("MMsavings") {}

  void set();  // interactively sets data for host obj from keyboard
  bool edit(); // edits the member variables
  void display() const;  // displays the host object
  void write(ofstream& out) const;  // writes host object to file
  void read(ifstream& in) ;         // reads host object from file
  void update (Date when);
  double computeCurrentValue();
  MMsavings* newInvestment () {return new MMsavings;}
  MMsavings* clone() {return new MMsavings(*this);}
  //getters
  double getSharePrice() const { return mSharePrice; } // returns SharePrice
  double getNumShares() const { return mNumShares; } // returns NumShares
  double getInitIRate() const { return mInitIRate; } // returns mInitIRate
  double getCurrIRate() const { return mCurrIRate; } // returns mCurrIRate

 private:
  //fields
  double mSharePrice; //almost always $1
  double mNumShares; //initial number of shares
  double mCurrNumShares; //current number of shares
  double mInitIRate;
  double mCurrIRate; //typically 2-3%

  //setters
  void setSharePrice ();
  void setNumShares ();
  void setInitIRate ();

}
;


#endif

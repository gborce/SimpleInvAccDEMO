/**********************************************************************
 *
 *  Borce Gjorgjievski
 *  file: invlist.h
 *  Desc: Definitions for the investment & InvFactory class
 *
 **********************************************************************/

#ifndef _INVLIST_H_
#define _INVLIST_H_

#include <iostream>
#include <map>
#include <string>
#include "date.h"
#include "investment.h"
#include "invDerived.h"

/*********** Les Static Factorie **************************/
class InvFactory {
 public:
  static Investment* create();  // interactively determines which
  // kind of object is needed, then
  // constructs one in dynamic memory.
  static Investment* create(int iTypno); // silently constructs an 
  // object based on its invType.
  static int getTypeNbr(string iTypName); // returns (index+1) of 
  // iTypeName in the ITNAME[] array.

  static string ITNAME[];       // = {"Stock", "Bond", "MMsavings"};
  enum ITYPES {stock = 1, bond, mmsavings};
  static const int ITCOUNT = 3;
};

/************** The Investment List class **************/

class InvestList {
 public:
  InvestList(); //default constructor
  InvestList(const InvestList& il); //copy constructor
  ~InvestList(); //destructor
  InvestList& operator=(const InvestList& il); //assignment operator
  void set(); //allows entering Investment items, uses InvFactory::create
              // and then calls inser for insertion of the items in the map
  bool insert(Investment *ip); //inserts ip if not in map, else returns false
  bool remove(string which); //removes ID 'which', if not found return false
  bool edit(string which); //allows changing of the data fields
  void display(string which="ALL") const; //displays which or ALL list members
  bool isEmpty() const; //returns true if list is empty
  bool isInList(string which) const; //returns true if IF 'which' is in list 
  void write(ofstream&) const; //writes list to a file
  void read(ifstream&);  //reads list from a file
  double getCurrentValue() { return mCurrentValue; }
  void update (Date when, string which); //updates all objects in list
  void clearAll(); //frees all pointers and clears the map
 private:
  double mCurrentValue;
  //have private typedefs to avoid bulky types
  typedef map <string,Investment*>::const_iterator imap_const_iter;
  typedef map <string,Investment*>::iterator imap_iter;

  void computeCurrentValue(); //computes and stores the current value
  imap_const_iter find(string which) const;//returns an iterator to ID 'which' 

  map <string, Investment*> imap; //the container used to implement the list
};

#endif

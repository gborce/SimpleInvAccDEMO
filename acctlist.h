/**********************************************************************
 *
 *  Bruce Gjorgjievski
 *  file: acctlist.h
 *  Desc: Definitions for the account list class
 *
 **********************************************************************/

#ifndef _ACCTLIST_H_
#define _ACCTLIST_H_

#include <iostream>
#include <map>
#include <string>
#include "date.h"
#include "account.h"

class AcctList {
 public:
  AcctList(); //default constructor
  AcctList(const AcctList& il); //copy constructor
  ~AcctList(); //destructor
  AcctList& operator=(const AcctList& il); //assignment operator
  void set(); //allows entering Account items
  bool edit();  //allows modifying of individual accounts
  bool insert(Account a); //inserts ap if not in map, else returns false
  bool remove(string which); //removes ID 'which', if not found return false
  void display(string which="ALL") const; //displays which or ALL list members
  bool managePortfolio(); //add, remove, display investments
  string findID(); //finds acct. ID based on part of the acct. name
  bool isEmpty() const; //returns true if list is empty
  bool isInList(string which) const; //returns true if IF 'which' is in list 
  void write(ofstream&) const; //writes list to a file
  void read(ifstream&);  //reads list from a file
  void update (); //updates all objects in list 
 private:
  //have private typedefs to avoid bulky types
  typedef map <string,Account>::const_iterator amap_const_iter;
  typedef map <string,Account>::iterator amap_iter;

  amap_const_iter find(string which) const;//returns an iterator to ID 'which' 
  void clearAll();  //clears the map

  map <string,Account> amap; //the container used to implement the list
};

#endif

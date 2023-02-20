/**********************************************************************
 *
 *  Borce Gjorgjievski, Putting it all together
 *  file: option.h
 *  Modified: Dec 4, 2002
 *  Desc: Option classes
 *
 **********************************************************************/

#ifndef _OPTION_H
#define _OPTION_H

#include "acctlist.h"
#include "optParams.h"

class Option {
 public:
  virtual ~Option() {}
  virtual void execute() = 0;
  string getOptName() {return mOptName;}
 protected:
  Option(string name): mOptName(name) {}
  string mOptName;
  static bool mListChanged;   // initialize to false
  static AcctList mAcctLst;  // initialize to default
};

class OptReadAcct : public Option {   // read the AccountList from a file
 public:
  OptReadAcct() :
    Option(OPTNAME[eOptReadAcct]) {}
  void execute();
};
class OptAddAcct : public Option {  // add Accounts to the AccountList
 public:
  OptAddAcct() :
    Option(OPTNAME[eOptAddAcct]) {}
  void execute();
};
class OptDisplayAcct : public Option {  // display one or all Accounts
 public:
  OptDisplayAcct() :
    Option(OPTNAME[eOptDisplayAcct]) {}
  void execute();
};
class OptFindAcct : public Option {  // find the acctID for an Account
 public:
  OptFindAcct() :
    Option(OPTNAME[eOptFindAcct]) {}
  void execute();
};
class OptEditAcct : public Option {  // edit an Account
 public:
  OptEditAcct() :
    Option(OPTNAME[eOptEditAcct]) {}
  void execute();
};
class OptManageAcct : public Option {  // manage the portfolio for an Account
 public:
  OptManageAcct() :
    Option(OPTNAME[eOptManageAcct]) {}
  void execute();
};
class OptUpdateAcct : public Option {  // update portfolio for one or all Accounts
 public:
  OptUpdateAcct() :
    Option(OPTNAME[eOptUpdateAcct]) {}
  void execute();
};

class OptRemoveAcct : public Option { // remove an Account from the list
 public:
  OptRemoveAcct() :
    Option(OPTNAME[eOptRemoveAcct]) {}
  void execute();
};
class OptWriteAcct : public Option {  // write the AccountList to a file
 public:
  OptWriteAcct() :
    Option(OPTNAME[eOptWriteAcct]) {}
  void execute();
};
class OptQuit : public Option {  // quit the program
 public:
  OptQuit() :
    Option(OPTNAME[eOptQuit]) {}
  void execute();
};

#endif

// File: optParams.h

// This file contains data that characterizes the Option hierarchy.
// Whenever a new class is derived from Option appropriate changes
// must be made to the following items.

#ifndef _OPT_PARAMS_H_
#define _OPT_PARAMS_H_

#include <string>
using namespace std;

enum {OPTCOUNT = 10};
enum OptTypes {	eOptReadAcct,
	        eOptAddAcct,
		eOptDisplayAcct,
		eOptFindAcct,
		eOptManageAcct,
		eOptUpdateAcct,
		eOptEditAcct,
		eOptRemoveAcct,
		eOptWriteAcct,
		eOptQuit
};



const string OPTNAME[] = {
  "Read Account List", 
  "Add Accounts", 
  "Display Accounts", 
  "Find an Account ID",
  "Manage Accounts",
  "Update Account",
  "Edit Account", 
  "Remove Account", 
  "Write Account List", 
  "Quit"
};



#endif

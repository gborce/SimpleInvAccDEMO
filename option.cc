/**********************************************************************
 *
 *  Borce Gjorgjievski, Putting it all together
 *  file: option.cc
 *  Modified: Dec 4, 2002
 *  Desc: Option classes
 *
 **********************************************************************/

#include "utility.h"
#include "option.h"

//static vars
bool Option::mListChanged = false;
AcctList Option::mAcctLst ;


void OptReadAcct::execute() {
  ifstream infile;

  cout << getOptName() << endl;
  //open files etc.
  openInputFile(infile);
  mAcctLst.read(infile);
  infile.close();
  mListChanged = true;
}

void OptAddAcct::execute() {
  cout << getOptName() << endl;
  mAcctLst.set();
  mListChanged = true;
}

void OptDisplayAcct::execute() {
  string id;
  cout << getOptName() << endl;
  cout << "Enter the account ID to display or \"ALL\": ";
  getline(cin, id);
  uppercaseString(id);
  mAcctLst.display(id);
}

void OptFindAcct::execute() {
  cout << getOptName() << endl;
  mAcctLst.findID();
}

void OptEditAcct::execute() {
  cout << getOptName() << endl;
  if (mAcctLst.edit())
    mListChanged = true;
}

void OptManageAcct::execute() {
  cout << getOptName() << endl;
  if (mAcctLst.managePortfolio())
    mListChanged = true;
}

void OptUpdateAcct::execute() {
  cout << getOptName() << endl;
  mAcctLst.update();
}

void OptRemoveAcct::execute() {
  string which;

  cout << getOptName() << endl;
  cout << "Enter the ID of the account to be removed: ";
  getline(cin, which);
  mAcctLst.remove(which);
  mListChanged = true;
}

void OptWriteAcct::execute() {
  ofstream outfile;

  cout << getOptName() << endl;
  //open file, etc.
  openOutputFile(outfile);
  mAcctLst.write(outfile);
  outfile.close();
  mListChanged = false;
}

void OptQuit::execute() {
  cout << getOptName() << endl;
  //if mListChanged ask to save, otherwise quit
  if (mListChanged)
    {
      cout << "Account List may have been changed.\n";
      cout << "Do you want to quit without saving(y/n)?";
      if (!yes()) {
	cout << " Returning to menu\n";
	return;
      }
    }
  exit(0);
}

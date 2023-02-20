/**********************************************************************
 *
 *  Bruce Gjorgjievski
 *  file: acctlist.cc
 *  Desc: Implementation for the account list class
 *
 **********************************************************************/

#include "utility.h"
#include "acctlist.h"

AcctList::AcctList() //default constructor
{
  //clear the local map
  amap.clear();
}

AcctList::~AcctList() //destructor
{
  clearAll(); 
}

void AcctList::set() //allows entering infinite Account items
{
  Account a;

  do {
    a.clearPortfolio();
    a.set();
    if (!insert(a))
      cerr << "Error: that account ID already exists!";
    cout << "Another Account(y/n)? ";
  } while (yes());
}

bool AcctList::edit() //edits data in individual accounts
{
  amap_iter f;
  string acctID("");
  bool e = false;

  do{
    
    cout << "Enter the ID of the Account to be edited: ";
    getline(cin, acctID); 
    
    uppercaseString(acctID);
    f = amap.find(acctID);
    if (f==amap.end())
      cout << "ID " << acctID <<" was not found\n";
    else
      if(f->second.edit())
	e=1;
    cout << "Another account edit (y/n)?";
  } while (yes());
  return e;
}

bool AcctList::insert(Account a) //inserts a if not in map, else returns false
{
  if (find(a.getID())==amap.end()) //not found
    {
      amap[a.getID()] = a;
      return true;
    }
  else
    return false;
}
bool AcctList::remove(string which) //removes ID 'which', if not found return false
{
  amap_iter f;

  uppercaseString(which);
  f = amap.find(which);
  if (f==amap.end())
    {
      cout << "ID " << which <<" was not found\n";
      return false;
    }
  else
    {
      f->second.display(false);
      cout << "Are your sure you want to remove this item (y/n)?";
      if(yes())
	amap.erase(which);
      return true;
    }
  return false;
}
void AcctList::display(string which) const //displays which or ALL list members
{
  const int DASHLEN = 40;
  amap_const_iter i,f;

  dashline(DASHLEN,'=');
  uppercaseString(which);
  if (!which.compare("ALL") )
  {
    for (i=amap.begin();i!=amap.end();++i)
      {
	i->second.display(false);
	dashline(DASHLEN,'=');
      }
  } //if which
  else 
    {
      f = amap.find(which);
      if (f==amap.end())
	cout << "ID " << which <<" was not found\n";
      else
	{
	  f->second.display(false);
	  dashline(DASHLEN,'=');
	}
    }
}

bool AcctList::managePortfolio() //add, remove, display investments
{
  amap_iter f;
  string which;
  bool e = false;;

  do{
    cout << "Enter the ID of the Account to be managed: ";
    getline (cin, which);
    uppercaseString(which);
    f = amap.find(which);
    if (f==amap.end())
      cout << "ID " << which <<" was not found\n";
    else
      e = f->second.managePortfolio();
    
    cout << "Do you want to manage another account (y/n) ? " ;
  } while (yes());
  
  return e;
}

string AcctList::findID() //find an acct. ID based on part of acct. name
{
  string s, n;
  amap_const_iter i;
  string::size_type pos = string::npos;

  cout << "Enter a substring of the account name: ";
  getline (cin, s);
  uppercaseString(s);
  for (i=amap.begin();i!=amap.end();++i)
    {
      n =i->second.getName();
      uppercaseString(n);
      pos = n.find(s,0);
      if (pos != string::npos)
	{
	  cout << "Name: " << n << "\tID: " << i->second.getID() << " (y/n)? ";
	  if (yes())
	    {
	      cout << "Requested Account ID is: " << i->second.getID() << endl;
	      return i->second.getID();
	    }
	}
    }
  cout << s << " not found\n";
  return "NOT FOUND";
}

bool AcctList::isEmpty() const //returns true if list is empty
{
  return amap.empty();
}
bool AcctList::isInList(string which) const // true if 'which' is in list
{
  return (amap.count(which) != 0);
}
void AcctList::write(ofstream& out) const //writes list to a fale
{
    amap_const_iter i;

  //first goes the count
    out << amap.size() << endl;
  //then goes an iterator through the list
  for (i=amap.begin();i!=amap.end();++i) 
    i->second.write(out);
}

void AcctList::read(ifstream& in)  //reads list from a file, ignores duplicate IDs, reports to cerr
{
  Account a;
  int c;  
  
  //read the count
  in >> c >> ws;
  for(int i = 0; i < c; ++i) {
    a.clearPortfolio();
    a.read(in);
    if (!insert(a))
      cerr << "Duplicate ID "<<a.getID()<<", record ignored"<<endl;
  }//for i

}

void AcctList:: update () //updates all objects in list 
{
 amap_iter i,f;
 string which;
 Date when;

 cout << "Enter the date of the update: " ;
 cin >> when;
 cout << "Enter the ID of the Account to be updated (or \"ALL\"): ";
 getline(cin,which);

  uppercaseString(which);
  //update ALL the account, ALL the investments within them
  if (!which.compare("ALL") )
    for (i=amap.begin();i!=amap.end();++i)
	i->second.updateInv(when,"ALL");
  else
    {
      //update only a specific account, ALL the investments within it
      f = amap.find(which);
      if (f==amap.end())
        cout << "ID " << which <<" was not found\n";
      else
	f->second.updateInv(when,"ALL");
    }

}

///////////////////////////////////////////////////  private

AcctList::amap_const_iter AcctList::find(string which) const //returns an iterator to ID 'which'
{
  return amap.find(which); //returns iterator to found item or end()
}

void AcctList::clearAll()
{
  amap.clear();
}

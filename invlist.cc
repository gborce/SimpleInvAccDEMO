/**********************************************************************
 *
 *  Borce Gjorgjievski, HW10 Investment List & InvFactory Class
 *  file: invlist.cc
 *  Modified:  Dec 4, 2002
 *  Desc: Implementation for the investment list & InvFactory class
 *
 **********************************************************************/
#include "utility.h"
#include "invlist.h"

const int DASHLEN=40;

/************************ class InvFactory ***************************/

string InvFactory::ITNAME[] = {"Stock", "Bond", "MMsavings"};

Investment* InvFactory::create()  // interactively contructs object
{
  Investment* ip;
  int choice=0;

  do {
    for (int i=0;i<ITCOUNT;i++)
	cout << "\t("<<i+1<<") "<<ITNAME[i]<<endl;

    cout << "Item type: " << flush;
    choice = setInt();
  } while (choice<1 || choice >ITCOUNT);
  //create object of the given type by calling the other create
  ip = create(choice);
  ip->set();
  return ip;
}

Investment* InvFactory::create(int iTypno) //silently constructs object
{
  switch(iTypno)
    {
    case 1: return new Stock;
    case 2: return new Bond;
    case 3: return new MMsavings;
    default: //unsupported type, exit to avoid further corruption
      cerr << "Unsupported investment type: " << iTypno << "! Aborting...\n";
      exit(1);
    }//switch
}

int InvFactory::getTypeNbr(string iTypName) // returns (index+1) of
                                        // iTypeName in the ITNAME[] array.
{                                       // 0 if not found
  for(int i=0;i<ITCOUNT;i++)
    if (!iTypName.compare(ITNAME[i]))
      return ++i;
  
  return (0);
}

/************************ class InvestList *****************************/

InvestList::InvestList() //default constructor
{
  //clear the local map
  imap.clear();
  mCurrentValue =0; //init curr val
}
InvestList::InvestList(const InvestList& il) //copy constructor
{
  //populate the host imap with il.imap
  imap_const_iter i;
  Investment *ip;
  string id;

  for (i=il.imap.begin(); i!=il.imap.end();++i)
    {
      id = i->second->getID();
      ip = i->second->clone();
      imap[id] = ip;      
    }

}
InvestList::~InvestList() //destructor
{
  clearAll();
}

InvestList& InvestList::operator=(const InvestList& il) //assignment operator
{
  imap_const_iter i;
  Investment *ip;
  string id;

  //check if assigning to itself
  if (this == &il)
    return (*this);
  //we need to delete everything from the host imap and replace it with il.imap
  clearAll();
  //populate the host imap with il.imap
  for (i=il.imap.begin(); i!=il.imap.end();++i)
    {
      id = i->second->getID();
      ip = i->second->clone();
      imap[id] = ip;      
    }
  //return the reference
  return (*this);
}
void InvestList::set() //allows entering Investment items, uses InvFactory::create
             // and then calls insert for insertion of the items in the map
{
  Investment *ip;
  
  do {
    ip = InvFactory::create();
    if (!insert(ip))
      cerr << "Insertion of Investment with ID " << ip->getID() << "failed\n";
  }while (more("investment"));
}

bool InvestList::insert(Investment *ip) //inserts ip if not in map, else returns false
{
  if (find(ip->getID())==imap.end()) //not found
    {
      imap[ip->getID()] = ip;
      return true;
    }
  else
    return false;
}
bool InvestList::remove(string which) //removes ID 'which', if not found return false
{
  imap_iter f;

  uppercaseString(which);
  f = imap.find(which);
  if (f==imap.end())
    {
      cout << "ID " << which <<" was not found\n";
      return false;
    }
  else
    {
      f->second->display();
      cout << "Are your sure you want to remove this item (y/n)?";
      if(yes())
	{
	  delete f->second; //release the memory
	  imap.erase(which);
	  return true;
	}
    }
  return false;
}

bool InvestList::edit(string which) //edits the data fields
{
  imap_iter f;

  uppercaseString(which);
  f = imap.find(which);
  if (f==imap.end())
    cout << "ID " << which <<" was not found\n";
  else
    {
      cout << "Editing ...\n";
    if(f->second->edit())
      return true; //edit the found investment
    }
  return false;
}


void InvestList::display(string which) const //displays which or ALL list members
{
  imap_const_iter i,f;

  dashline(DASHLEN,'=');
  uppercaseString(which);
  if (!which.compare("ALL") )
  {
    for (i=imap.begin();i!=imap.end();++i)
      {
	i->second->display();
	dashline(DASHLEN,'=');
      }
  } //if which
  else 
    {
      f = imap.find(which);
      if (f==imap.end())
	cout << "ID " << which <<" was not found\n";
      else
	{
	  f->second->display();
	  dashline(DASHLEN,'=');
	}
    }
}
bool InvestList::isEmpty() const //returns true if list is empty
{
  return imap.empty();
}
bool InvestList::isInList(string which) const // true if 'which' is in list
{
  return (imap.count(which) != 0);
}
void InvestList::write(ofstream& out) const //writes list to a file
{
    imap_const_iter i;

  //first goes the count
    out << imap.size() << endl;
  //then goes an iterator through the list
  for (i=imap.begin();i!=imap.end();++i) 
    {
      //the Investment type int code
      out << InvFactory::getTypeNbr(i->second->getInvType()) << endl;
      i->second->write(out);
    }
}
void InvestList::read(ifstream& in)  //reads list from a file, ignores duplicate IDs, reports to cerr
{
  Investment* ip;
  int c,type;  

  //read the count
  in >> c >> ws;
  for(int i = 0; i < c; ++i) {
    in >> type >>ws;
    ip = InvFactory::create(type);
    ip->read(in);
    if (!insert(ip))
      cerr << "Duplicate ID "<<ip->getID()<<", record ignored"<<endl;
  }//for i

}

void InvestList::update (Date when, string which) 
{
  imap_iter i,f;

  uppercaseString(which);
  if (!which.compare("ALL") )
    for (i=imap.begin();i!=imap.end();++i)
	i->second->update(when);
  else
    {
      f = imap.find(which);
      if (f==imap.end())
        cout << "ID " << which <<" was not found\n";
      else
	f->second->update(when);
    }
}

//private

void InvestList::computeCurrentValue()
{
  imap_const_iter i;

  mCurrentValue =0;
  for (i=imap.begin();i!=imap.end();++i)
    mCurrentValue += i->second->computeCurrentValue();
}

InvestList::imap_const_iter InvestList::find(string which) const //returns an iterator to ID 'which'
{
  return imap.find(which); //returns iterator to found item or end()
}

void InvestList::clearAll()
{
  imap_const_iter i;

  //free all the pointers in the list
  for (i=imap.begin();i!=imap.end();++i)
    delete i->second;
  //clear the map
  imap.clear();
}

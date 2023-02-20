/**********************************************************************
 *
 *  Borce Gjorgjievski, HW10, Enhanced Account Class
 *  file: account.cc
 *  Modified:  Dec 4, 2002
 *  Desc: Implementation for the enhanced account class
 *
 **********************************************************************/

#include "account.h"
#include "utility.h"

//static 
unsigned Account::MAX_ID = 7;


Account::Account () :  //default constructor, init. acc.
  mID(""), mName(""), mAddress(""), mPhone(""), mDate()
{
}

void Account::set()   // interactively sets data for host obj from keyboard
{
    //name
    setName();
    //id
    setID();
    //phone
    setPhone();
    //address
    setAddress();
    //date
    setDate();
    //portfolios
    cout << "Do you want ot add your portfolio now (y/n)?";
    if (yes())
      portfolio.set();
}

void Account::setID () 
{
  string temp("");
  do {
    cout << "Account ID (exactly " << MAX_ID << " symbols!): " << flush;
    cin >> temp;
  } while (temp.size() != MAX_ID);
  mID.assign(temp); 
}
void Account::setName () 
{ 
  cout << "Name: " << flush;
  cin >> ws;
  getline( cin, mName);
}
void Account::setAddress () 
{ 
  mAddress.assign(setAddrString()); 
}
void Account::setPhone () 
{
  mPhone.assign(setPhoneString()); 
}
void Account::setDate ()
{
  cout << "Date that this account was established: " << endl;
  cin >> mDate;
}
bool Account::edit() //offers the user to edit any of the fields
{
  bool e = false;

  cout << "Name: " << getName() << "\tChange(y/n)? "; 
  if (yes()) { setName(); e=1;}
  cout << "Address: " << getAddress() << "\tChange(y/n)? ";
  if (yes()) { setAddress(); e=1; }
  cout << "Phone: " << getPhone() << "\tChange(y/n)? ";
  if (yes()) { setPhone(); e=1; }
  cout << "Account Date: " << getDate() << "\tChange(y/n)? ";
  if (yes()) { setDate(); e=1; }
  //ask if wants to edit portfolio
  cout << "Edit Investment Portflio? ";
  if (yes()) 
    {
      portfolio.display();
      do {
	cout << "Enter the ID of the Investment to be edited: ";
	string invID("");
	getline(cin, invID);
	portfolio.edit(invID);
	e = 1;
	cout << "Another Investment edit(y/n)? ";
      } while (yes());

    } //if
  return e;
}

void Account::display(bool brief) const  // displays the host object
{
  if (brief) {
    cout << mName << "\t" << mID << "\t" << mDate << endl;
    return;
  }
  //long format
  cout << "Name:\t" << mName << "\tID:\t" << mID << endl;
  cout << "Address: " << mAddress << endl;
  cout << "Phone: " << mPhone << "\tAccount date: ";
  mDate.display(false);
  cout << endl << "Investment Portfolio: \n";
  portfolio.display("ALL");
  cout << endl;
}
void Account::write(ofstream& out) const   // writes host object to file
{
  out << mName << endl << mID << endl << mPhone << endl << mAddress << endl;
  mDate.write(out);
  portfolio.write(out);
}
void Account::read(ifstream& in)          // reads host object from file
{
  in >> ws;
  getline(in, mName);
  in >> ws >> mID >> ws;;
  getline (in, mPhone);
  getline (in, mAddress);
  in >> ws;
  mDate.read(in);
  portfolio.read(in);
}
//portfolio handling functions
void Account::addInv()  //interactively adds investment to portfolio
{
  portfolio.set();
}
bool Account::removeInv(string which) //interactively removes investment from portfolio
{
  if (portfolio.remove(which)) return true;
  return false;
}
void Account::updateInv(Date when, string which) //updates individual investment or the entire portfolio
{
  portfolio.update(when,which);
}
void Account::displayInv(string which/* ="ALL" */) //displays individual investment or the entire portfolio
{
  portfolio.display(which);
}

bool Account::managePortfolio() //packages add, remove and display
{
  string which;
  int choice, e=false;

  while(1) {
    cout << "\t\t1. Display Portfolio \n";
    cout << "\t\t2. Add Investments to Portfolio \n";
    cout << "\t\t3. Remove an investment from Portfolio \n";
    cout << "\t\t4. Exit this function \n";
    cout << "\t\tYour choice?";
    choice = setInt();
    if (choice<1 || choice>4) continue;
    switch(choice) 
      {
      case 1: 
	cout << "Enter the ID to display (or All): "; 
	getline(cin,which);
	displayInv(which); 
	break;
      case 2: 
	addInv(); 
	e=1;  
	break;
      case 3: 
	cout << "Enter the ID to remove: ";
	getline(cin, which);
	if(removeInv(which)) e=1; 
	break;
      default: return e;
      }
  }
  return e;
}

double Account::getCurrValue() //returns the current value of the portfolio
{
  return portfolio.getCurrentValue();
}
void Account::clearPortfolio() //completely clears the portfolio
{
  portfolio.clearAll();
}
bool Account::portfolioIsEmpty()
{
  return portfolio.isEmpty(); 
}
bool Account::isInPortfolio(string which)
{
  return portfolio.isInList(which);
}


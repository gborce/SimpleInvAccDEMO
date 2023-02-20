/**********************************************************************
 *
 *  Borce Gjorgjievski, HW9, Adding edit functions
 *  file: investment.cc
 *  Modified:  Nov 24, 2002
 *  Desc: Implementation for the investment class
 *
 **********************************************************************/

#include "investment.h"
#include "utility.h"

int Investment::MAX_ID = 10;
int Investment::MAX_DAYS = 30;

void Investment::set()   // interactively sets data for host obj from keyboard
{
  setName();
  setID();
  setDate();
  setVolatility();
}

bool Investment::edit() //offers the user to edit any of the fields
{
  bool e=false;
  cout << "Investment Name: " << getName() << "\tChange(y/n)? ";
  if (yes()) {setName(); e=1; }
  cout << "Purchase Date: " << getDate() << "\tChange(y/n)? ";
  if (yes()) {setDate(); e=1; }
  cout << "Volatility: " << getVolatility() << "\tChange(y/n)? ";
  if (yes()) {setVolatility(); e=1; }
  return e;
}

void Investment::display() const  // displays the host object
{
  cout << "Investment Type: " << mInvType << endl;
  cout << "Investment ID: " << mInvID << "\tInvestment Name: " << mInvName << endl;
  cout << "Purchase Date: " << flush;
  mDate.display();
  cout << endl;
  cout << "Volatility: " << volatility <<endl;
  cout << "Current value as of ";
  lastUpdate.display();
  cout << " is: ";
  moneyDisplay(currentValue, true);
}
void Investment::write(ofstream& out) const   // writes host object to file
{
  out << mInvName << '\n' << mInvID << '\n' << volatility << '\n' << currentValue << '\n';;
  mDate.write(out);
  lastUpdate.write(out);
}
void Investment::read(ifstream& in)          // reads host object from file
{
  getline (in, mInvName);
  getline(in, mInvID);
  in >> volatility >> ws >> currentValue >> ws;
  mDate.read(in);
  lastUpdate.read(in);
}

double Investment::getRand(double v)
{
  double rn = 0;
  int k = (int) v;
  //we can change how we generate this later, right now - simplicity
  srand(time(NULL)); //otherwise ALWAYS same sequence for sam volatility
  rn = rand() % (2*k+1) - v;  //random number in the range -v..+v
  return (rn/100); //return a percentage ready for multiplication
}

//setters
void Investment::setID () 
{ 
  string temp("");

  do {
    cout << "Investment ID (max " << MAX_ID << " symbols): " << flush;
    cin >> temp;
  } while ((static_cast<int>(temp.size())) > MAX_ID && !temp.size());
  uppercaseString(temp);
  mInvID.assign(temp);
};

void Investment::setName () 
{ 
  cout << "Investment Name: " << flush;
  cin >> ws;
  getline( cin, mInvName);
};

void Investment::setDate() 
{
  Date tDate;
  int days;
  //get todays date
  tDate.setToToday();

  cout << "Purchase Date: " << flush;
  while (1) {
  cin >> mDate;
  if ((tDate - mDate < MAX_DAYS) && (tDate - mDate > 0))
    break;
  else
    cout << "Invalid date. Valid dates are from " << MAX_DAYS << " days ago until today\n";
  } //while 
  lastUpdate.setToToday(); //initaliaze last update
  //lastUpdate becomes the just entered date
  days = mDate - lastUpdate;
  lastUpdate += days;
}

void Investment::setVolatility()
{
  cout << "Volatility is the maximum percent by which the characteristic market value of an investment can change in any day of trading.\n";
  while (1) {
    cout << "Violatility rating (<=70): " << flush;
    volatility =setReal();
    if (volatility >=0 && volatility <=70)
      break;
    else
      cout << "Invalid volatility rating! Please try again." <<endl;
  }
}

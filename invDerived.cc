/**********************************************************************
 *
 *  Borce Gjorgjievski
 *  file: invDerived.cc
 *  Desc: Implementation for the Stock, Bond, MMsavings classes
 *
 **********************************************************************/

#include "utility.h"
#include "invDerived.h"

/********************** Stock class implementation ********************/

void Stock::set()   // interactively sets data for host obj from keyboard
{
  Investment::set();
  setSharePrice();
  setNumShares();
  computeCurrentValue(); // not to be 0
}

bool Stock::edit() //edits member variables
{
  Date date;
  bool e = false;

  Investment::edit();
  cout << "Original Number of shares purchased: " << getNumShares() << "\t Change(y/n)? ";
  if (yes()) { setNumShares(); e=1; }
  cout << "Initial Share Price: " << getSharePrice() << "\t Change(y/n)?";
  if (yes()) { setSharePrice(); e=1; }
  computeCurrentValue();
  //the user already entered the new opening date, now update until today
  date.setToToday();
  update(date);
  return e;
}

void Stock::display() const  // displays the host object
{
  Investment::display();
  cout << mNumShares << " shares purchased at ";
  moneyDisplay(mSharePrice);
  cout << " per share." << endl;
  cout << "Current share price as of ";
  lastUpdate.display();
  cout << " is ";
  moneyDisplay(mCurrSharePrice,true);
}
void Stock::write(ofstream& out) const   // writes host object to file
{
  Investment::write(out);
  out << mSharePrice << '\n' << mCurrSharePrice<< '\n' << mNumShares << endl;
}
void Stock::read(ifstream& in)          // reads host object from file
{
  Investment::read(in);
  in >> mSharePrice >> ws >> mCurrSharePrice >> ws >> mNumShares >> ws;
}

///////////update was re-written to always count from the start date
void Stock::update (Date when) //
{
  int days = when - getDate();
  ///no dates in the past
  if (days <= 0)
    return;

  lastUpdate += (when-lastUpdate); //lastUpdate becomes when 

  //since we always start from the original date, initialize the charac values
  mCurrSharePrice = mSharePrice;
  // now change the characteristic values randomly for each day of 'days'
  for (int i=0; i<days; ++i)
    {
      mCurrSharePrice += mCurrSharePrice*getRand(volatility);
      computeCurrentValue();
    }
}

double Stock::computeCurrentValue() 
{
  currentValue = mCurrSharePrice*mNumShares;
  return currentValue;
}
//setters
void Stock::setSharePrice () 
{ 
  do {
    cout << "Initial share Price: " << flush;
    mSharePrice = setReal();
  } while (mSharePrice <= 0);
  mCurrSharePrice = mSharePrice;
}

void Stock::setNumShares () 
{
  do {
    cout << "Number of shares purchased: " << flush;
    mNumShares = setInt();
  } while (mNumShares <=0);
}

/************************* Bond clas implementation **************************/

void Bond::set()   // interactively sets data for host obj from keyboard
{
  Investment::set();
  setPurchPrice();
  setFaceValue();
  cout << "Computing the coupon value (annual income) for this bond.\n";
  setCoupon();
  setYrs2Mature();
  setSPrating();
  computeCurrentValue();
}

bool Bond::edit() //edits member variables
{
  Date date;
  bool e = false;

  Investment::edit();
  cout << "Purchase Price: " << getPurchPrice() << "\t Change(y/n)? ";
  if (yes()) { setPurchPrice(); e=1; }
  cout << "Face Value: " << getFaceValue() << "\t Change(y/n)?";
  if (yes()) { setFaceValue(); e=1; }
  cout << "S&P Rating: " << getSPrating() << "\t Change(y/n)?";
  if (yes()) { setSPrating(); e=1; }
  cout << "Coupon: " << getCoupon() << "\t Change(y/n)?";
  if (yes()) { setCoupon(); e=1; }
  cout << "Years to Maturity: " << getYrs2Mature() << "\t Change?";
  if (yes()) { setYrs2Mature(); e=1; }
  computeCurrentValue();
  //change the characteristic values for each day from acc. opening to today
  date.setToToday();
  update(date);
  return e;
}

void Bond::display() const  // displays the host object
{
  Investment::display();
  cout << "Purchase price: ";
  moneyDisplay(mPurchPrice);
  cout << " Face value: ";
  moneyDisplay(mFaceValue);
  cout << " S&P Rating: " << mSPrating << endl;
  cout << "Coupon: " << mCoupon << "\t" << mYrs2Mature << " yrs to maturity\n";
}
void Bond::write(ofstream& out) const   // writes host object to file
{
  Investment::write(out);
  out << mPurchPrice << '\n' << mCurrPurchPrice << '\n' << mFaceValue << '\n';
  out << mCoupon << '\n' << mYrs2Mature << '\n' << mSPrating << endl;
}
void Bond::read(ifstream& in)          // reads host object from file
{
  Investment::read(in);
  in >> mPurchPrice >> ws >> mCurrPurchPrice >> ws >> mFaceValue >> ws;
  in  >> mCoupon >> ws >> mYrs2Mature >>ws;
  getline(in, mSPrating);
}

bool Bond::validRating(string r) const  //checks for valid S&P rating
{
  uppercaseString(r);
  if (!r.compare("AAA") || 
      !r.compare("AA") || 
      !r.compare("A") || 
      !r.compare("BBB") || 
      !r.compare("BB") || 
      !r.compare("B") || 
      !r.compare("CCC") || 
      !r.compare("CC") || 
      !r.compare("D"))
    return true;
  else 
    return false;
}
///////////update was re-written to always count from the start date
void Bond::update(Date when) 
{
 int days = when - getDate();
  ///no dates in the past
  if (days <= 0)
    return;

  lastUpdate += (when-lastUpdate); //lastUpdate becomes when 

  //since we always start from the purchase date, init the charact. values
  mCurrPurchPrice = mPurchPrice;

  for (int i=0; i<days; ++i)
    {
      mCurrPurchPrice += mCurrPurchPrice*getRand(volatility);
      computeCurrentValue();
    }
}

double Bond::computeCurrentValue()
{
  //this is what you'd get if you'd sell right now
  currentValue = mCurrPurchPrice;
  return currentValue;
}

 //setters
void Bond::setPurchPrice ()
{
  do {
    cout << "Enter the purchase price: " << flush;
    cin >> ws;
    mPurchPrice = setReal();
  } while (mPurchPrice<=0);
  mCurrPurchPrice = mPurchPrice;
}
void Bond::setFaceValue ()
{
  do {
    cout << "Enter the face value of this bond: " << flush;
    cin >> ws;
    mFaceValue = setReal();
  } while (mFaceValue<=0);
}
void Bond::setCoupon ()
{
  double t=0;

  while (1){
    cout << "Enter the interest rate of this bond:" << flush;
    cin >> ws;
    t = setReal();
    if (t>0 && t<1)
      break;
  else 
    cout << "Interest rate must be between zero and 1 (not inclusive).\n";
  }
  mCoupon = (t * mFaceValue) / mPurchPrice;  
}
void Bond::setYrs2Mature ()
{
  do {
    cout << "Number of years until this bond matures: " << flush;
    cin >> ws;
    mYrs2Mature = setInt();
  } while (mYrs2Mature<=0);
}
void Bond::setSPrating ()
{
  do {
    cout << "Standard & Poor's rating for this bond: " << flush;
    cin >> mSPrating;
  } while (!validRating(mSPrating));
  uppercaseString(mSPrating);
}


/********************** MMsavings class implementation ********************/

void MMsavings::set()   // interactively sets data for host obj from keyboard
{
  Investment::set();
  setSharePrice();
  setNumShares();
  setInitIRate();
  computeCurrentValue(); //avoid 0s
}

bool MMsavings::edit() //edits member variables
{
  Date date;
  bool e = false;

  Investment::edit();
  cout << "Share Price: " << getSharePrice() << "\t Change(y/n)? ";
  if (yes()) { setSharePrice(); e=1; }
  cout << "Initial Purchase: " << getNumShares() << "\t Change(y/n)?";
  if (yes()) { setNumShares(); e=1; }
  cout << "Initial Interest Rate: " << getInitIRate() << "\t Change(y/n)?";
  if (yes()) { setInitIRate(); e=1; }

  computeCurrentValue();
  //change the characteristic values for each day since last update to today
  date.setToToday();
  update(date);
  return e;
}

void MMsavings::display() const  // displays the host object
{
  Investment::display();
  cout << "Initial purchase: "<<mNumShares <<" shares\n";
  cout << "Initial interest rate: " <<mInitIRate<<endl;
  cout << "As of ";
  lastUpdate.display();
  cout << " Number of shares is: " << mCurrNumShares <<"\tInterest Rate is: "<<mCurrIRate<<endl;
}
void MMsavings::write(ofstream& out) const   // writes host object to file
{
  Investment::write(out);
  out << mSharePrice << '\n' << mNumShares << '\n' << mCurrNumShares <<'\n';
  out  << mInitIRate << '\n' << mCurrIRate << endl;;
}
void MMsavings::read(ifstream& in)          // reads host object from file
{
  Investment::read(in);
  in >> mSharePrice >> ws >>mNumShares >>ws >> mCurrNumShares ; //***** ws ?
  in >> mInitIRate >> ws >> mCurrIRate >> ws;
}
///////////update was re-written to always count from the start date
void MMsavings::update(Date when)
{
int days = when - getDate();
  ///no dates in the past
  if (days <= 0)
    return;

  lastUpdate += (when-lastUpdate); //lastUpdate becomes when 

  //since we always start from purchase date, init charact.value
  mCurrIRate = mInitIRate;
  mCurrNumShares = mNumShares;

  // now change the characteristic values randomly for each day of 'days'
  for (int i=0; i<days; ++i)
    {
      mCurrIRate += mCurrIRate*getRand(volatility);
      mCurrNumShares += mCurrNumShares*mCurrIRate;
      computeCurrentValue();
    }
}

double MMsavings::computeCurrentValue() 
{
  //allow for share price to be different than 1 (why else enter it?)
  currentValue = mCurrNumShares*mSharePrice;
  //now increase it for the interest received for that day
  currentValue += currentValue*mCurrIRate;
  return currentValue;
}

//setters
void MMsavings::setSharePrice () 
{ 
  do {
    cout << "Initial share Price: " << flush;
    mSharePrice = setReal();
  } while (mSharePrice <= 0);
}

void MMsavings::setNumShares () 
{
  do {
    cout << "Number of shares purchased: " << flush;
    mNumShares = setInt();
  } while (mNumShares <=0);
  mCurrNumShares = mNumShares;
}

void MMsavings::setInitIRate () 
{
  while (1){
    cout << "Enter the initial annual interest rate: " << flush;
    mInitIRate = setReal();
  if  (mInitIRate <=0.2 && mInitIRate >=0.01)
    break;
  else
    cout <<"Interest rate must be between 0.01 and 0.2. Please try again."<<endl;
      }
  mCurrIRate = mInitIRate;
}

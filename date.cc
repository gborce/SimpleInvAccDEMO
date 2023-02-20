/*********************************************************
 *
 *     OOP, Homework #2, Date Class 
 *     Borce Gjorgjievski
 *     file: date.cc
 *     Modified: Sept 21, 2002
 *     Desc: Date managing class implementation
 *
 *********************************************************/

#include <iostream.h>
#include <time.h>
#include "utility.h"
#include "date.h"

unsigned Date::mBaseYear = 1000;

  Date::Date()  // default constructor initializes host obj to  base date.
{
  mDsb = 1;
}
  Date::Date(unsigned m, unsigned d, unsigned y)  // constructs Date from month/day/year
{
  //default
  if ((m>12) || (m<1) || (d<1) || (d>monthdays(m,y)) || (y < mBaseYear))
      mDsb = 1;
  else
  setDsb(m,d,y);
}
  void Date::set()  // interactively sets data for host obj from keyboard, Guarantees a valid date.
{
  unsigned y(0),m(0),d(0);

  //get year
  do {
    cout << "Year: " << flush;
    y = setInt();
    if (y<mBaseYear) 
      cerr << "Invalid year! please try again" << endl;
  } while (y<mBaseYear);

  //get month
  do {
    cout << "Month (a number from 1 to 12): " << flush;
    m = setInt();
    if (m>12 || m < 1)
      cerr << "Invalid month! Please try again." << endl;
  } while (m>12 || m <1);

  //get day
  do {
    cout << "Day of the month: " << flush;
    d = setInt();

    if (d<1 || d>monthdays(m,y))
      {
	cout << "Invalid day. Please try again." << endl;
	continue;
      }
    
  } while (d<1 || d >monthdays(m,y));
  setDsb(m,d,y);
}
  void Date::set(unsigned m, unsigned d, unsigned y)
                                // sets host object from args if valid. Otherwise sets host object to base date.
{
  if (((m < 1) || (m > 12))  || (monthdays (m, y) < d) || (y < mBaseYear))
    mDsb = 1;
  else 
    setDsb(m, d, y);
}
  void Date::setToToday()            // sets host object to today's date using the system clock (see timetst.cc)
{
  struct tm *tp = new(tm);
  time_t now;

  now = time(0);
  tp = localtime(&now);
  setDsb   ((unsigned)tp->tm_mon+1,(unsigned)tp->tm_mday,(unsigned)tp->tm_year+1900);
}
 
  void Date::display(bool shortform) const  // displays the host object
{      // shortform is  mm/dd/yyyy  (e.g.,  03/22/2002
      // longform is  dayname, month dd, yyyy (e.g., Friday, Sep 13, 2002)
 unsigned m,d,y;

 getMDY(m,d,y);
 if (shortform)
   cout << m << "/" << d << "/" << y << flush;
 else
   cout << getWeekDay() << ", " << monthname(m) << " " << d << ", " << y << flush;
}

  void Date::write(ofstream& out) const  // writes a date object to file
{
  out << mDsb << endl;
}

  void Date::read(ifstream& in)          // reads a date object from file
{
  in >> mDsb >> ws;
}
  string Date::getWeekDay() const // returns the day of the week for host object
{
  //Day 1  - Jan 1st 1000 - is wednesday
  unsigned weekday = mDsb % 7;
  switch(weekday){
  case 1: return "Wednesday";
  case 2: return "Thursday";
  case 3: return "Friday";
  case 4: return "Saturday";
  case 5: return "Sunday";
  case 6: return "Monday";
  case 0: return "Tuesday";
  default: return "Err";
  }
}
  bool Date::operator<(const Date& d) const    // comparison: host < d
{
  return (mDsb < d.mDsb);
}
  bool Date::operator==(const Date& d) const // comparison: host == d
{
  return (mDsb == d.mDsb);
}
  bool Date::operator<=(const Date& d) const// comparison: host <= d
{
  return (mDsb <= d.mDsb);
}
  int  Date::operator-(const Date& d) const // computes number of days (host - d)
{
  return (mDsb - d.mDsb);
}
  Date Date::operator+(int days) const    // computes the date (host + days)
{
  if (days<0) days=0;
  Date newDate (mDsb+days);
  return newDate;
}
  void Date::operator+=(int days)           // changes host to (host + days)
{
  //days can be negative too, but mDsb cannot
  mDsb+=days;
  if (mDsb <0)
    mDsb = 0;
}

  bool Date::leapyear(unsigned year)     // tests year for leap year
{
  //leap year must be div by 4, or if century div by 400
  if ((year % 4) == 0)
    if ((year % 100) == 0)
      if ((year % 400) == 0)
	return true; //leap century year
      else 
	return false;
    else
      return true; //leap non-century year
  else
    return false;
}

 unsigned Date::yeardays(unsigned year)   // returns number of days in year
{
  if (leapyear(year))
    return (366);
  else
    return (365);
}
  unsigned Date::monthdays(unsigned month, unsigned year) // returns days in month
{
  int months [] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (month<1 || month>12)
    return 0;
  if ((month==2) && leapyear(year))
    return 29;
  else
    return months[month-1];
}
  string Date::monthname(unsigned month)     // returns name of month
{
  switch(month){
  case 1: return "Jan";
  case 2: return "Feb";
  case 3: return "Mar";
  case 4: return "Apr";
  case 5: return "May";
  case 6: return "Jun";
  case 7: return "Jul";
  case 8: return "Aug";
  case 9: return "Sep";
  case 10: return "Oct";
  case 11: return "Nov";
  case 12: return "Dec";
  default: return "ERR";
  }

}

//private functions 
 Date::Date(unsigned long dsb)      // private constructor creates Date from dsb
{
  if (dsb<=0)
    mDsb = 1;
  else
    mDsb = dsb;
}
  void Date::setDsb (unsigned month, unsigned day, unsigned year) // computes and sets mDsb
{
  mDsb=0;
  //years
  for (unsigned i=mBaseYear; i<year; i++)
    mDsb += yeardays(i);
  //months
  for (unsigned i=1;i<month;i++)
    mDsb += monthdays(i,year);
  //days
  mDsb += day;
}

void Date::getMDY (unsigned& m, unsigned& d, unsigned& y) const //computes m/d/y from mDsb
{
  unsigned ny(mBaseYear),nm(1),nd(mDsb);

  while (yeardays(ny) < nd)
    nd -= yeardays(ny++);

  while (monthdays(nm, ny) < nd)
    nd -= monthdays(nm++, ny);

  y = ny;
  m = nm;
  d = nd;
}

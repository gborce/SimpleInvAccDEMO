/**********************************************************************
 *
 *  Borce Gjorgjievski
 *  file: optfactory.cc
 *  Desc: Creates different options on request
 *
 **********************************************************************/

#include "utility.h"
#include "optfactory.h"

Option* OptFactory::create(int opt)
{
  switch(opt)
    {
    case 0: return new OptReadAcct;
    case 1: return new OptAddAcct;
    case 2: return new OptDisplayAcct;
    case 3: return new OptFindAcct;
    case 4: return new OptManageAcct;
    case 5: return new OptUpdateAcct;
    case 6: return new OptEditAcct;
    case 7: return new OptRemoveAcct;
    case 8: return new OptWriteAcct;
    case 9: return new OptQuit;
    default: //unsupported type, exit to avoid further corruption
      cerr << "Unsupported option type: " << opt << "! Aborting...\n";
      exit(1);
    }//switch
}

void OptFactory::menu()
{
  Option *o;
  int choice=OPTCOUNT;
  
  while(1)
    {
      for (int i=0; i<OPTCOUNT; i++)
	cout <<"\t\t("<<i<<")\t"<< OPTNAME[i] <<endl;
      
      cout <<"\tYour Choice: ";
      choice = setInt();
      if (choice < 0 || choice > OPTCOUNT) continue;
      o = create(choice);
      o->execute();
    }
}

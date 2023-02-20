/**********************************************************************
 *
 *  Bruce Gjorgjievski, Putting it all together
 *  file: optfactory.h
 *  Desc: Creates different options on request
 *
 **********************************************************************/

#ifndef _OPT_FACTORY_H_
#define _OPT_FACTORY_H_

#include "option.h"

class OptFactory {
 public:
  static Option* create(int opt);
  static void menu();
};

#endif

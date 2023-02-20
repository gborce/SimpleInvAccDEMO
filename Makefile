############################################################## 
#     Borce Gjorgjievski
#     file: Makefile
##############################################################

LIBS	=
CFLAGS  = -O2 -pedantic -ansi -Wall
MOD	= -c
CC	= g++

all: hw10

utility.o: utility.cc utility.h
	$(CC) $(MOD) $(CFLAGS) utility.cc

date.o: date.cc date.h utility.h
	$(CC) $(MOD) $(CFLAGS) date.cc

account.o: account.cc account.h utility.h date.h
	$(CC) $(MOD) $(CFLAGS) account.cc

investment.o: investment.cc investment.h utility.h date.h
	$(CC) $(MOD) $(CFLAGS) investment.cc

invDerived.o: invDerived.cc invDerived.h investment.h utility.h date.h
	$(CC) $(MOD) $(CFLAGS) invDerived.cc

invlist.o: invlist.cc invlist.h investment.h invDerived.h utility.h date.h
	$(CC) $(MOD) $(CFLAGS) invlist.cc

acctlist.o: acctlist.cc acctlist.h account.h utility.h invlist.h
	$(CC) $(MOD) $(CFLAGS) acctlist.cc

option.o: option.cc option.h acctlist.h account.h invlist.h 
	$(CC) $(MOD) $(CFLAGS) option.cc

optfactory.o: optfactory.cc optfactory.h option.h acctlist.h account.h
	$(CC) $(MOD) $(CFLAGS) optfactory.cc

hw10-demo.o: hw10-demo.cc optfactory.h option.h invlist.h investment.h invDerived.h utility.h date.h
	$(CC) $(MOD) $(CFLAGS) hw10-demo.cc

hw10: hw10-demo.o invlist.o investment.o invDerived.o account.o acctlist.o utility.o date.o option.o optfactory.o
	$(CC) -o hw10 hw10-demo.o invlist.o investment.o invDerived.o account.o acctlist.o utility.o date.o option.o optfactory.o $(LIBS)

clean:
	rm -f *.o core a.out hw10

xclean: 
	rm -f *.o core a.out hw10 *~
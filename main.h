#include <stdarg.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <string>
#include <squirrel3/squirrel.h>
#include <squirrel3/sqstdio.h>
#include <squirrel3/sqstdaux.h>
#include <limits>
#include <sstream>
#include <sys/stat.h>
using namespace std;

#ifdef SQUNICODE
#define scvprintf vwprintf
#else
#define scvprintf vprintf
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define ON_WIN
#endif

void printfunc(HSQUIRRELVM v, const SQChar *s, ...);
void callfunc(HSQUIRRELVM v, int n, float f, const SQChar *s);
SQInteger getInput(HSQUIRRELVM v);
SQInteger registerGlobalFunc(HSQUIRRELVM v, SQFUNCTION f, const char *fname);
SQInteger pausefunc(HSQUIRRELVM v);
SQInteger clear(HSQUIRRELVM v);
SQInteger randFloat(HSQUIRRELVM v);
SQInteger randInt(HSQUIRRELVM v);
bool getYN();
//void runfile(HSQUIRRELVM v, string* str);
bool fileExists(const char* file);
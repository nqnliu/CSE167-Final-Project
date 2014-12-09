#ifndef _XYZPARSER_H
#define _XYZPARSE_H

#include <string>
#include <vector>
#include "Vector3.h"

class XYZParser
{
public:

   // returns a pointer to two lists of floats
   static void parse(char*, std::vector<Vector3>*, std::vector<Vector3>*);
};

#endif
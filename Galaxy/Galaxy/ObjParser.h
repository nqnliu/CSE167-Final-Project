#ifndef _OBJPARSER_H
#define _OBJPARSE_H

#include <string>
#include <vector>
#include "Vector3.h"

class ObjParser
{
public:

   // returns a pointer to two lists of floats
   static void parse(char*, std::vector<Vector3>*, std::vector<Vector3>*, std::vector<Vector3>*, std::vector<Vector3>*);
   static void parse(char*, std::vector<Vector3>&, std::vector<Vector3>&); 
};

#endif
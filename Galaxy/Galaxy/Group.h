#ifndef _GROUP_H
#define _GROUP_H

#include "Node.h"
#include <list>

class Group : public Node
{
public:
   std::list<Node*> children;

   Group();

   void draw(Matrix4);
   void addChild(Node*);
   void removeChild(Node*);
};
#endif
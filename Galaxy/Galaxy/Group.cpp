#include "Group.h"
#include "main.h"
#include <algorithm>

Group::Group()
{
   children = std::list<Node*>();
}

void Group::draw(Matrix4 C)
{
   for (std::list<Node*>::iterator i = children.begin(); i != children.end(); ++i)
   {
      (*i)->draw(C);
   }
}

void Group::addChild(Node * n)
{
   children.push_back(n);
}

void Group::removeChild(Node * n)
{
   children.remove(n);
}

#ifndef IDISPLAYABLE_H
#define IDISPLAYABLE_H

#include <string>
using namespace std;

// Abstract Interface 1: anything that can display itself
class IDisplayable {
public:
    virtual void   displayProfile() = 0;
    virtual string getInfo()  const = 0;
    virtual ~IDisplayable() {}
};

#endif // IDISPLAYABLE_H

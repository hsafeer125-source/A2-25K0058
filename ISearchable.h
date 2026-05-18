#ifndef ISEARCHABLE_H
#define ISEARCHABLE_H

#include <string>
using namespace std;

// Abstract Interface 2: anything that supports searching / filtering
class ISearchable {
public:
    virtual bool   matchFilter(string brand, string model,
                               double minP, double maxP,
                               int minYear, int maxMil) const = 0;
    virtual string getSummary() const = 0;
    virtual ~ISearchable() {}
};

#endif // ISEARCHABLE_H

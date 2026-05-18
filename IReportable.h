#ifndef IREPORTABLE_H
#define IREPORTABLE_H

// Abstract Interface 4: anything that can produce a text report
class IReportable {
public:
    virtual void generateReport() const = 0;
    virtual ~IReportable() {}
};

#endif // IREPORTABLE_H

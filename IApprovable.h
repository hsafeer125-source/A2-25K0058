#ifndef IAPPROVABLE_H
#define IAPPROVABLE_H

// Forward declaration so the header doesn't need the full Listing definition
class Listing;

// Abstract Interface 3: anything that can approve / reject listings
class IApprovable {
public:
    virtual bool approveListing(Listing* lst) = 0;
    virtual bool rejectListing (Listing* lst) = 0;
    virtual ~IApprovable() {}
};

#endif // IAPPROVABLE_H

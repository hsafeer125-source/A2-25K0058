/*
===========================================================================
  OOP Assignment 02 - PakWheels Clone
  National University of Computer & Emerging Sciences, Karachi
  Subject: Object-Oriented Programming | Spring 2026

===========================================================================
*/

#include <iostream>
#include <string>
using namespace std;


// FORWARD DECLARATIONS

class Listing;
class User;
class Buyer;

// ====================================================================
// SECTION 3: ABSTRACT BASE CLASSES  (Abstraction — 4 interfaces)
// ====================================================================
#include "IDisplayable.h"
#include "ISearchable.h"
#include "IApprovable.h"
#include "IReportable.h"


// ====================================================================
// HELPER CLASSES
// ====================================================================

class Address {
private:
    string city, area, province, postalCode, country;
public:
    Address() : city("unknown"), area("unknown"),
                province("unknown"), postalCode("00000"), country("Pakistan") {}

    Address(string c, string a, string p, string pc)
        : city(c), area(a), province(p), postalCode(pc), country("Pakistan") {}

    Address(const Address& o)
        : city(o.city), area(o.area), province(o.province),
          postalCode(o.postalCode), country(o.country) {}

    void setCity(string c)     { city=c; }
    void setArea(string a)     { area=a; }
    void setProvince(string p) { province=p; }
    void setPostal(string p)   { postalCode=p; }

    string getCity()     const { return city; }
    string getArea()     const { return area; }
    string getProvince() const { return province; }
    string getPostal()   const { return postalCode; }

    void displayAddress() const {
        cout << area << ", " << city << ", " << province << " " << postalCode << endl;
    }
    bool isFromLahore()    const { return city == "Lahore"; }
    bool sameCity(string c) const { return city == c; }
    string getFullAddress() const { return area + " " + city + " " + province; }

    // Operator Overloading #1: == (same city and province)
    bool operator==(const Address& o) const {
        return city == o.city && province == o.province;
    }
    // Operator Overloading #2: << (stream)
    friend ostream& operator<<(ostream& os, const Address& a) {
        os << a.area << ", " << a.city << ", " << a.province;
        return os;
    }
};


class ContactInfo {
private:
    string phoneNum, email, whatsapp;
    bool   showPhone, showEmail;
public:
    ContactInfo() : phoneNum("N/A"), email("N/A"), whatsapp("N/A"),
                    showPhone(true), showEmail(false) {}
    ContactInfo(string p, string e, string w)
        : phoneNum(p), email(e), whatsapp(w), showPhone(true), showEmail(true) {}

    void setPhone(string p)    { phoneNum=p; }
    void setEmail(string e)    { email=e; }
    void setWhatsapp(string w) { whatsapp=w; }

    string getPhone()    const { return phoneNum; }
    string getEmail()    const { return email; }
    string getWhatsapp() const { return whatsapp; }

    void displayContact() const {
        if(showPhone)         cout << "Phone  : " << phoneNum << endl;
        if(showEmail)         cout << "Email  : " << email    << endl;
        if(whatsapp != "N/A") cout << "WA     : " << whatsapp << endl;
    }
    bool isValid()        const { return !(phoneNum=="N/A" || email=="N/A"); }
    void hidePhone()            { showPhone = false; }
    void showPhonePublic()      { showPhone = true;  }

    friend void printUserContact(const User& u);  // Friend Function #3
};


class Message {
private:
    string senderName, receiverName, msgText, date;
    bool   isRead;
public:
    Message() : senderName(""), receiverName(""), msgText(""), date(""), isRead(false) {}
    Message(string s, string r, string msg, string d)
        : senderName(s), receiverName(r), msgText(msg), date(d), isRead(false) {}

    void setSender(string s)   { senderName=s; }
    void setReceiver(string r) { receiverName=r; }
    void setText(string t)     { msgText=t; }
    void setDate(string d)     { date=d; }

    string getSender()   const { return senderName; }
    string getReceiver() const { return receiverName; }
    string getText()     const { return msgText; }
    string getDate()     const { return date; }
    bool   getIsRead()   const { return isRead; }

    void markRead() { isRead = true; }
    void displayMessage() const {
        cout << "[" << date << "] " << senderName << " -> " << receiverName << endl;
        cout << "  Msg   : " << msgText << endl;
        cout << "  Status: " << (isRead ? "Read" : "Unread") << endl;
    }
    bool checkSender  (string n) const { return senderName   == n; }
    bool checkReceiver(string n) const { return receiverName == n; }
};


class VehicleFeatures {
private:
    bool hasAC, hasSunroof, hasLeatherSeats, hasNavigation, hasRearCamera, hasPushStart;
public:
    VehicleFeatures()
        : hasAC(false), hasSunroof(false), hasLeatherSeats(false),
          hasNavigation(false), hasRearCamera(false), hasPushStart(false) {}

    VehicleFeatures(bool ac, bool sr, bool ls, bool nav, bool rc, bool ps)
        : hasAC(ac), hasSunroof(sr), hasLeatherSeats(ls),
          hasNavigation(nav), hasRearCamera(rc), hasPushStart(ps) {}

    void setAC(bool v)         { hasAC=v; }
    void setSunroof(bool v)    { hasSunroof=v; }
    void setLeather(bool v)    { hasLeatherSeats=v; }
    void setNavigation(bool v) { hasNavigation=v; }
    void setRearCamera(bool v) { hasRearCamera=v; }
    void setPushStart(bool v)  { hasPushStart=v; }

    bool getAC()         const { return hasAC; }
    bool getSunroof()    const { return hasSunroof; }
    bool getLeather()    const { return hasLeatherSeats; }
    bool getNavigation() const { return hasNavigation; }
    bool getRearCamera() const { return hasRearCamera; }
    bool getPushStart()  const { return hasPushStart; }

    void displayFeatures() const {
        cout << "Features: ";
        if(hasAC)           cout << "[AC] ";
        if(hasSunroof)      cout << "[Sunroof] ";
        if(hasLeatherSeats) cout << "[Leather] ";
        if(hasNavigation)   cout << "[Nav] ";
        if(hasRearCamera)   cout << "[RearCam] ";
        if(hasPushStart)    cout << "[PushStart] ";
        cout << endl;
    }
    int  totalFeatures() const {
        return (int)hasAC + hasSunroof + hasLeatherSeats +
               hasNavigation + hasRearCamera + hasPushStart;
    }
    bool isPremium() const { return totalFeatures() >= 4; }

    // Operator Overloading #3: + (union of features)
    VehicleFeatures operator+(const VehicleFeatures& o) const {
        return VehicleFeatures(hasAC||o.hasAC, hasSunroof||o.hasSunroof,
                               hasLeatherSeats||o.hasLeatherSeats,
                               hasNavigation||o.hasNavigation,
                               hasRearCamera||o.hasRearCamera,
                               hasPushStart||o.hasPushStart);
    }
    // Operator Overloading #4: == (identical feature sets)
    bool operator==(const VehicleFeatures& o) const {
        return hasAC==o.hasAC && hasSunroof==o.hasSunroof &&
               hasLeatherSeats==o.hasLeatherSeats &&
               hasNavigation==o.hasNavigation &&
               hasRearCamera==o.hasRearCamera &&
               hasPushStart==o.hasPushStart;
    }

    // Friend Function #2 needs private access
    friend VehicleFeatures mergeFeatures(const VehicleFeatures& a, const VehicleFeatures& b);
};

// ====================================================================
// SECTION 1 & 2: VEHICLE HIERARCHY (Inheritance + Polymorphism)
// ====================================================================

class Vehicle {
protected:
    string brand, model, transmission, fuelType;
    int    year, engineCC;
public:
    Vehicle() : brand("Unknown"), model("Unknown"), transmission("Manual"),
                fuelType("Petrol"), year(2020), engineCC(1000) {}

    Vehicle(string b, string m, int y, int ecc, string t, string f)
        : brand(b), model(m), transmission(t), fuelType(f), year(y), engineCC(ecc) {}

    Vehicle(const Vehicle& v)
        : brand(v.brand), model(v.model), transmission(v.transmission),
          fuelType(v.fuelType), year(v.year), engineCC(v.engineCC) {}

    void setBrand(string b)        { brand=b; }
    void setModel(string m)        { model=m; }
    void setYear(int y)            { year=y; }
    void setEngineCC(int e)        { engineCC=e; }
    void setTransmission(string t) { transmission=t; }
    void setFuelType(string f)     { fuelType=f; }

    string getBrand()        const { return brand; }
    string getModel()        const { return model; }
    int    getYear()         const { return year; }
    int    getEngineCC()     const { return engineCC; }
    string getTransmission() const { return transmission; }
    string getFuelType()     const { return fuelType; }

    // POLYMORPHISM: virtual - overridden in each derived class
    virtual void   displayDetails()    const {
        cout << year << " " << brand << " " << model << endl;
        cout << "  Engine: " << engineCC << "cc | " << transmission << " | " << fuelType << endl;
    }
    virtual string getVehicleType()    const { return "Vehicle"; }
    virtual string getFullName()       const {
        return to_string(year) + " " + brand + " " + model;
    }

    // keep A1-compatible name
    void displayVehicle() const { displayDetails(); }

    bool isSameBrand(string b) const { return brand == b; }
    bool isSameModel(string m) const { return model == m; }

    // Operator Overloading #5: == (same brand+model+year)
    bool operator==(const Vehicle& o) const {
        return brand==o.brand && model==o.model && year==o.year;
    }
    // Operator Overloading #6: > / < by year
    bool operator>(const Vehicle& o) const { return year > o.year; }
    bool operator<(const Vehicle& o) const { return year < o.year; }

    virtual ~Vehicle() {}
};


// Inheritance Relationship #1: Car IS-A Vehicle
class Car : public Vehicle {
private:
    int    numDoors;
    string bodyType;
public:
    Car() : Vehicle(), numDoors(4), bodyType("Sedan") {}
    Car(string b, string m, int y, int ecc, string t, string f,
        int doors, string body)
        : Vehicle(b, m, y, ecc, t, f), numDoors(doors), bodyType(body) {}

    int    getNumDoors() const { return numDoors; }
    string getBodyType() const { return bodyType; }

    // POLYMORPHISM: overrides Vehicle::displayDetails()
    void displayDetails() const override {
        cout << "[CAR] " << year << " " << brand << " " << model
             << " (" << bodyType << ")" << endl;
        cout << "  Engine : " << engineCC << "cc | " << transmission
             << " | " << fuelType << endl;
        cout << "  Doors  : " << numDoors << endl;
    }
    string getVehicleType() const override { return "Car"; }
};


// Inheritance Relationship #2: Bike IS-A Vehicle
class Bike : public Vehicle {
private:
    string bikeType;
    bool   hasFairing;
public:
    Bike() : Vehicle(), bikeType("Standard"), hasFairing(false) { fuelType="Petrol"; }
    Bike(string b, string m, int y, int ecc, string t,
         string btype, bool fairing)
        : Vehicle(b, m, y, ecc, t, "Petrol"), bikeType(btype), hasFairing(fairing) {}

    string getBikeType()   const { return bikeType; }
    bool   getHasFairing() const { return hasFairing; }

    // POLYMORPHISM: overrides Vehicle::displayDetails()
    void displayDetails() const override {
        cout << "[BIKE] " << year << " " << brand << " " << model
             << " (" << bikeType << ")" << endl;
        cout << "  Engine : " << engineCC << "cc | " << transmission << endl;
        cout << "  Fairing: " << (hasFairing ? "Yes" : "No") << endl;
    }
    string getVehicleType() const override { return "Bike"; }
};


// Inheritance Relationship #3: ElectricCar IS-A Vehicle
class ElectricCar : public Vehicle {
private:
    int    batteryKWh;
    int    rangeKm;
    string chargeType;
public:
    ElectricCar() : Vehicle(), batteryKWh(40), rangeKm(300), chargeType("AC") {
        fuelType="Electric"; transmission="Automatic";
    }
    ElectricCar(string b, string m, int y, int bat, int range, string ct)
        : Vehicle(b, m, y, 0, "Automatic", "Electric"),
          batteryKWh(bat), rangeKm(range), chargeType(ct) {}

    int    getBatteryKWh() const { return batteryKWh; }
    int    getRangeKm()    const { return rangeKm; }
    string getChargeType() const { return chargeType; }

    // POLYMORPHISM: overrides Vehicle::displayDetails()
    void displayDetails() const override {
        cout << "[ELECTRIC] " << year << " " << brand << " " << model << endl;
        cout << "  Battery: " << batteryKWh << " kWh" << endl;
        cout << "  Range  : " << rangeKm    << " km/charge" << endl;
        cout << "  Charge : " << chargeType  << endl;
    }
    string getVehicleType() const override { return "ElectricCar"; }
};


// ====================================================================
// LISTING CLASS — stores vehicle info by value (safe copying)
// Implements ISearchable (abstraction)
// ====================================================================
class Listing : public ISearchable {
private:
    int             listingID;
    double          price;
    int             mileage;
    string          condition, description, sellerName;
    bool            isApproved;
    VehicleFeatures features;

    // Store vehicle data by value inside a neutral Vehicle copy
    // plus extra data for derived types — avoids dangling pointer on copy
    Vehicle  baseVehicle;  // always set; holds brand/model/year etc.
    int      vehicleKind;  // 0=Vehicle,1=Car,2=Bike,3=Electric
    // Extra fields per type
    int    numDoors; string bodyType;           // Car
    string bikeType; bool   hasFairing;         // Bike
    int    batteryKWh, rangeKm; string chargeType; // Electric

    static int totalListings;

    void _copyFromCar(const Car& c) {
        baseVehicle = c; vehicleKind=1;
        numDoors=c.getNumDoors(); bodyType=c.getBodyType();
    }
    void _copyFromBike(const Bike& b) {
        baseVehicle = b; vehicleKind=2;
        bikeType=b.getBikeType(); hasFairing=b.getHasFairing();
    }
    void _copyFromEV(const ElectricCar& e) {
        baseVehicle = e; vehicleKind=3;
        batteryKWh=e.getBatteryKWh(); rangeKm=e.getRangeKm(); chargeType=e.getChargeType();
    }

    void _displayVehiclePart() const {
        if(vehicleKind==1){
            cout<<"[CAR] "<<baseVehicle.getYear()<<" "<<baseVehicle.getBrand()
                <<" "<<baseVehicle.getModel()<<" ("<<bodyType<<")"<<endl;
            cout<<"  Engine : "<<baseVehicle.getEngineCC()<<"cc | "
                <<baseVehicle.getTransmission()<<" | "<<baseVehicle.getFuelType()<<endl;
            cout<<"  Doors  : "<<numDoors<<endl;
        } else if(vehicleKind==2){
            cout<<"[BIKE] "<<baseVehicle.getYear()<<" "<<baseVehicle.getBrand()
                <<" "<<baseVehicle.getModel()<<" ("<<bikeType<<")"<<endl;
            cout<<"  Engine : "<<baseVehicle.getEngineCC()<<"cc | "
                <<baseVehicle.getTransmission()<<endl;
            cout<<"  Fairing: "<<(hasFairing?"Yes":"No")<<endl;
        } else if(vehicleKind==3){
            cout<<"[ELECTRIC] "<<baseVehicle.getYear()<<" "<<baseVehicle.getBrand()
                <<" "<<baseVehicle.getModel()<<endl;
            cout<<"  Battery: "<<batteryKWh<<" kWh"<<endl;
            cout<<"  Range  : "<<rangeKm<<" km/charge"<<endl;
            cout<<"  Charge : "<<chargeType<<endl;
        } else {
            baseVehicle.displayDetails();
        }
    }
    string _vehicleTypeName() const {
        if(vehicleKind==1) return "Car";
        if(vehicleKind==2) return "Bike";
        if(vehicleKind==3) return "ElectricCar";
        return "Vehicle";
    }

    void _initDefaults() {
        listingID=++totalListings; price=0; mileage=0;
        condition="Used"; description="No description";
        isApproved=false; sellerName=""; vehicleKind=0;
        numDoors=4; bodyType="Sedan";
        bikeType="Standard"; hasFairing=false;
        batteryKWh=40; rangeKm=300; chargeType="AC";
    }

public:
    Listing() { _initDefaults(); }

    // A1-compatible constructor (plain Vehicle)
    Listing(Vehicle v, VehicleFeatures f, double p, int mil,
            string cond, string desc, string seller) {
        _initDefaults();
        baseVehicle=v; features=f; price=p; mileage=mil;
        condition=cond; description=desc; sellerName=seller;
        vehicleKind=0;
    }
    // Car constructor (overloaded — function overloading)
    Listing(Car c, VehicleFeatures f, double p, int mil,
            string cond, string desc, string seller) {
        _initDefaults();
        _copyFromCar(c);
        features=f; price=p; mileage=mil;
        condition=cond; description=desc; sellerName=seller;
    }
    // Bike constructor (overloaded)
    Listing(Bike b, VehicleFeatures f, double p, int mil,
            string cond, string desc, string seller) {
        _initDefaults();
        _copyFromBike(b);
        features=f; price=p; mileage=mil;
        condition=cond; description=desc; sellerName=seller;
    }
    // ElectricCar constructor (overloaded)
    Listing(ElectricCar e, VehicleFeatures f, double p, int mil,
            string cond, string desc, string seller) {
        _initDefaults();
        _copyFromEV(e);
        features=f; price=p; mileage=mil;
        condition=cond; description=desc; sellerName=seller;
    }

    void setPrice(double p)       { price=p; }
    void setMileage(int m)        { mileage=m; }
    void setCondition(string c)   { condition=c; }
    void setDescription(string d) { description=d; }
    void setApproved(bool a)      { isApproved=a; }

    int    getListingID()  const { return listingID; }
    double getPrice()      const { return price; }
    int    getMileage()    const { return mileage; }
    string getCondition()  const { return condition; }
    bool   getIsApproved() const { return isApproved; }
    string getSellerName() const { return sellerName; }
    Vehicle getCarInfo()   const { return baseVehicle; }
    VehicleFeatures getFeatures() const { return features; }

    static int getTotalListings() { return totalListings; }

    void approve()    { isApproved = true;  }
    void disapprove() { isApproved = false; }

    void displayListing() const {
        cout << "-----------------------------------" << endl;
        cout << "Listing ID : #" << listingID << endl;
        cout << "Status     : " << (isApproved ? "Approved" : "Pending") << endl;
        cout << "Type       : " << _vehicleTypeName() << endl;
        _displayVehiclePart();
        cout << "Price      : PKR " << price     << endl;
        cout << "Mileage    : " << mileage        << " km" << endl;
        cout << "Condition  : " << condition      << endl;
        cout << "Seller     : " << sellerName     << endl;
        features.displayFeatures();
        cout << "Description: " << description    << endl;
        cout << "-----------------------------------" << endl;
    }

    // ISearchable implementations
    bool matchFilter(string brand, string model, double minP, double maxP,
                     int minYear, int maxMil) const override {
        if(brand != "" && baseVehicle.getBrand() != brand) return false;
        if(model != "" && baseVehicle.getModel() != model) return false;
        if(price < minP || price > maxP)                   return false;
        if(baseVehicle.getYear() < minYear)                return false;
        if(mileage > maxMil)                               return false;
        return true;
    }
    string getSummary() const override {
        return "Listing#" + to_string(listingID) + " " +
               baseVehicle.getFullName() + " PKR " + to_string((int)price);
    }

    // Operator Overloading #7: == (same vehicle + same price)
    bool operator==(const Listing& o) const {
        return baseVehicle == o.baseVehicle && price == o.price;
    }
    // Operator Overloading #8: > / < by price
    bool operator>(const Listing& o) const { return price > o.price; }
    bool operator<(const Listing& o) const { return price < o.price; }

    // Friend Function declarations
    friend bool            compareListing(const Listing& a, const Listing& b);
    friend VehicleFeatures mergeFeatures (const Listing& a, const Listing& b);
};
int Listing::totalListings = 0;


// ====================================================================
// FRIEND FUNCTION #1: compareListing
// Accesses private price and listingID directly
// Justification: External price-comparison utility that operates on two
//   Listing objects without belonging to either; friendship lets it
//   read private price without needing a public getter for every field.
// ====================================================================
bool compareListing(const Listing& a, const Listing& b) {
    cout << "  [Friend] Listing #" << a.listingID << " (PKR " << a.price
         << ")  vs  Listing #" << b.listingID << " (PKR " << b.price << ")" << endl;
    return a.price < b.price;   // true = a is cheaper
}

// ====================================================================
// FRIEND FUNCTION #2: mergeFeatures
// Accesses private VehicleFeatures of both Listings
// Justification: A comparison-page feature that builds a union feature
//   set from two listings needs their private features field directly.
// ====================================================================
VehicleFeatures mergeFeatures(const Listing& a, const Listing& b) {
    return a.features + b.features;   // uses VehicleFeatures::operator+
}


// ====================================================================
// SECTION 1: USER HIERARCHY (Inheritance + Polymorphism + Abstraction)
// User (abstract base) -> Buyer, Seller, Admin
// ====================================================================

class User : public IDisplayable, public IReportable {
protected:
    int         userID;
    string      username, password, role;
    ContactInfo contact;
    Address     address;
    static int  totalUsers;
public:
    User() : userID(++totalUsers), username("guest"), password("1234"), role("none") {}
    User(string uname, string pwd, string r, ContactInfo c, Address a)
        : userID(++totalUsers), username(uname), password(pwd),
          role(r), contact(c), address(a) {}
    virtual ~User() {}

    void setUsername(string u)     { username=u; }
    void setPassword(string p)     { password=p; }
    void setRole(string r)         { role=r; }
    void setContact(ContactInfo c) { contact=c; }
    void setAddress(Address a)     { address=a; }

    int         getUserID()   const { return userID; }
    string      getUsername() const { return username; }
    string      getRole()     const { return role; }
    ContactInfo getContact()  const { return contact; }

    static int getTotalUsers() { return totalUsers; }

    bool login    (string pwd)               { return password == pwd; }
    bool changePass(string old_, string new_) {
        if(password==old_){ password=new_; return true; } return false;
    }

    // IDisplayable — base version; derived classes override
    void displayProfile() override {
        cout << "UserID   : " << userID   << endl;
        cout << "Username : " << username << endl;
        cout << "Role     : " << role     << endl;
        contact.displayContact();
        address.displayAddress();
    }
    string getInfo() const override { return username + " (" + role + ")"; }

    // IReportable — base version
    void generateReport() const override {
        cout << "[REPORT] User #" << userID << " | " << username
             << " | " << role << endl;
    }

    // Operator Overloading #9: == by username
    bool operator==(const User& o) const { return username == o.username; }

    friend void printUserContact(const User& u);      // Friend Function #3
    friend double combineBudget(const Buyer& a, const Buyer& b); // #4
};
int User::totalUsers = 0;

// ====================================================================
// FRIEND FUNCTION #3: printUserContact
// Reads private ContactInfo of a User object
// Justification: An admin audit tool needs raw contact data independent
//   of the showPhone/showEmail flags; friendship bypasses those flags.
// ====================================================================
void printUserContact(const User& u) {
    cout << "[CONTACT AUDIT] " << u.username
         << " | Phone: " << u.contact.getPhone()
         << " | Email: " << u.contact.getEmail() << endl;
}


// ====================================================================
// Derived User Class 1: Buyer (Inheritance Relationship #4)
// ====================================================================
class Buyer : public User {
private:
    Listing* favorites[10];
    Message  myMessages[50];
    int      favCount, msgCount;
    double   budget;
public:
    Buyer() : favCount(0), msgCount(0), budget(0) {
        role = "Buyer";
        for(int i=0;i<10;i++) favorites[i]=NULL;
    }
    Buyer(string uname, string pwd, ContactInfo c, Address a, double b)
        : User(uname, pwd, "Buyer", c, a), favCount(0), msgCount(0), budget(b) {
        for(int i=0;i<10;i++) favorites[i]=NULL;
    }

    void   setBudget(double b) { budget=b; }
    double getBudget()   const { return budget; }
    int    getFavCount() const { return favCount; }
    int    getMsgCount() const { return msgCount; }

    bool saveFavorite(Listing* lst) {
        if(favCount>=10){ cout<<"Favorites full!"<<endl; return false; }
        for(int i=0;i<favCount;i++)
            if(favorites[i]->getListingID()==lst->getListingID())
            { cout<<"Already in favorites."<<endl; return false; }
        favorites[favCount++]=lst;
        cout<<"Saved: "<<lst->getSummary()<<endl;
        return true;
    }
    bool removeFavorite(int id) {
        for(int i=0;i<favCount;i++){
            if(favorites[i]->getListingID()==id){
                for(int j=i;j<favCount-1;j++) favorites[j]=favorites[j+1];
                favorites[--favCount]=NULL;
                cout<<"Removed from favorites."<<endl; return true;
            }
        }
        cout<<"Not found in favorites."<<endl; return false;
    }
    bool sendMessage(string toSeller, string text, string date) {
        if(msgCount>=50){ cout<<"Message limit."<<endl; return false; }
        myMessages[msgCount++]=Message(username,toSeller,text,date);
        cout<<"Message sent to "<<toSeller<<endl; return true;
    }
    void showFavorites() const {
        cout<<"=== "<<username<<"'s Favorites ==="<<endl;
        if(!favCount){ cout<<"No favorites."<<endl; return; }
        for(int i=0;i<favCount;i++) favorites[i]->displayListing();
    }
    void showMessages() const {
        cout<<"=== Messages by "<<username<<" ==="<<endl;
        if(!msgCount){ cout<<"No messages."<<endl; return; }
        for(int i=0;i<msgCount;i++) myMessages[i].displayMessage();
    }

    // POLYMORPHISM: overrides User::displayProfile()
    void displayProfile() override {
        cout<<"=== BUYER PROFILE ==="<<endl;
        User::displayProfile();
        cout<<"Budget   : PKR "<<budget<<endl;
        cout<<"Favorites: "<<favCount<<endl;
        cout<<"Messages : "<<msgCount<<endl;
    }
    // POLYMORPHISM: overrides User::getInfo()
    string getInfo() const override {
        return "Buyer: " + username + " | Budget: PKR " + to_string((int)budget);
    }
    void generateReport() const override {
        cout<<"[REPORT] Buyer "<<username<<" | Budget: PKR "<<budget
            <<" | Favs: "<<favCount<<" | Msgs: "<<msgCount<<endl;
    }

    friend double combineBudget(const Buyer& a, const Buyer& b);
};

// ====================================================================
// FRIEND FUNCTION #4: combineBudget
// Reads private budget from two Buyer objects
// Justification: A co-purchase / joint-affordability check needs to sum
//   two buyers' private budgets; friendship avoids exposing budget via
//   a public getter used only for this one special operation.
// ====================================================================
double combineBudget(const Buyer& a, const Buyer& b) {
    double total = a.budget + b.budget;
    cout<<"[Friend] Combined budget of "<<a.username<<" + "<<b.username
        <<" = PKR "<<total<<endl;
    return total;
}


// ====================================================================
// Derived User Class 2: Seller (Inheritance Relationship #5)
// ====================================================================
class Seller : public User {
private:
    Listing* myListings[20];
    int      listCount;
    double   totalEarnings;
    string   shopName;
    int      rating;
public:
    Seller() : listCount(0), totalEarnings(0), shopName("My Shop"), rating(3) {
        role="Seller";
        for(int i=0;i<20;i++) myListings[i]=NULL;
    }
    Seller(string uname, string pwd, ContactInfo c, Address a, string shop)
        : User(uname, pwd, "Seller", c, a),
          listCount(0), totalEarnings(0), shopName(shop), rating(5) {
        for(int i=0;i<20;i++) myListings[i]=NULL;
    }

    void   setShopName(string s) { shopName=s; }
    void   setRating(int r)      { rating=r; }
    string getShopName()   const { return shopName; }
    int    getRating()     const { return rating; }
    int    getListCount()  const { return listCount; }

    bool addListing(Listing* lst) {
        if(listCount>=20){ cout<<"Cannot add more listings."<<endl; return false; }
        myListings[listCount++]=lst; return true;
    }
    bool removeListing(int id) {
        for(int i=0;i<listCount;i++){
            if(myListings[i]!=NULL && myListings[i]->getListingID()==id){
                for(int j=i;j<listCount-1;j++) myListings[j]=myListings[j+1];
                myListings[--listCount]=NULL; return true;
            }
        } return false;
    }
    void showMyListings() const {
        cout<<"=== Listings by "<<shopName<<" ==="<<endl;
        if(!listCount){ cout<<"No listings."<<endl; return; }
        for(int i=0;i<listCount;i++) if(myListings[i]) myListings[i]->displayListing();
    }

    // POLYMORPHISM: overrides
    void displayProfile() override {
        cout<<"=== SELLER PROFILE ==="<<endl;
        User::displayProfile();
        cout<<"Shop     : "<<shopName<<endl;
        cout<<"Rating   : "<<rating<<"/5"<<endl;
        cout<<"Listings : "<<listCount<<endl;
    }
    string getInfo() const override {
        return "Seller: " + username + " | " + shopName;
    }
    void generateReport() const override {
        cout<<"[REPORT] Seller "<<username<<" | Shop: "<<shopName
            <<" | Listings: "<<listCount<<" | Rating: "<<rating<<"/5"<<endl;
    }
};


// ====================================================================
// Derived User Class 3: Admin (Inheritance #6; implements IApprovable)
// ====================================================================
class Admin : public User, public IApprovable {
private:
    string adminLevel, department;
    int    approvedCount, rejectedCount, removedCount;
public:
    Admin() : adminLevel("Junior"), department("Moderation"),
              approvedCount(0), rejectedCount(0), removedCount(0) { role="Admin"; }
    Admin(string uname, string pwd, ContactInfo c, Address a,
          string lvl, string dept)
        : User(uname, pwd, "Admin", c, a),
          adminLevel(lvl), department(dept),
          approvedCount(0), rejectedCount(0), removedCount(0) {}

    void   setAdminLevel(string l) { adminLevel=l; }
    void   setDepartment(string d) { department=d; }
    string getAdminLevel()   const { return adminLevel; }
    string getDepartment()   const { return department; }
    int    getApprovedCount() const { return approvedCount; }

    void reviewListing(const Listing* lst) const {
        cout<<"Admin "<<username<<" reviewing Listing #"<<lst->getListingID()<<endl;
    }

    // IApprovable pure virtual implementations
    bool approveListing(Listing* lst) override {
        if(!lst->getIsApproved()){
            lst->approve(); approvedCount++;
            cout<<"Admin "<<username<<" APPROVED Listing #"<<lst->getListingID()<<endl;
            return true;
        }
        cout<<"Already approved."<<endl; return false;
    }
    bool rejectListing(Listing* lst) override {
        if(lst->getIsApproved()){
            lst->disapprove(); rejectedCount++;
            cout<<"Admin "<<username<<" REJECTED Listing #"<<lst->getListingID()<<endl;
            return true;
        }
        cout<<"Listing already pending."<<endl; return false;
    }

    // POLYMORPHISM: overrides
    void displayProfile() override {
        cout<<"=== ADMIN PROFILE ==="<<endl;
        User::displayProfile();
        cout<<"Level    : "<<adminLevel<<endl;
        cout<<"Dept     : "<<department<<endl;
        cout<<"Approved : "<<approvedCount<<endl;
        cout<<"Rejected : "<<rejectedCount<<endl;
    }
    string getInfo() const override {
        return "Admin: " + username + " [" + adminLevel + "] | " + department;
    }
    void generateReport() const override {
        cout<<"[REPORT] Admin "<<username<<" | Level: "<<adminLevel
            <<" | Dept: "<<department
            <<" | Approved: "<<approvedCount
            <<" | Rejected: "<<rejectedCount<<endl;
    }
};


// ====================================================================
// MARKETPLACE — Controller
// ====================================================================
class Marketplace {
private:
    const string PLATFORM_NAME;
    const int    LISTING_FEE;

    Listing listings[100];
    Buyer   buyers[50];
    Seller  sellers[30];
    Admin   admins[5];
    int numListings, numBuyers, numSellers, numAdmins;

    void _linkSeller(string sellerUsername, int idx) {
        for(int i=0;i<numSellers;i++)
            if(sellers[i].getUsername()==sellerUsername)
            { sellers[i].addListing(&listings[idx]); break; }
    }

public:
    Marketplace(string name, int fee)
        : PLATFORM_NAME(name), LISTING_FEE(fee),
          numListings(0), numBuyers(0), numSellers(0), numAdmins(0) {}

    string getPlatformName() const { return PLATFORM_NAME; }
    int    getListingFee()   const { return LISTING_FEE; }

    bool registerBuyer(Buyer b) {
        if(numBuyers>=50){ cout<<"Buyer limit."<<endl; return false; }
        buyers[numBuyers++]=b;
        cout<<"Buyer registered : "<<b.getUsername()<<endl; return true;
    }
    bool registerSeller(Seller s) {
        if(numSellers>=30){ cout<<"Seller limit."<<endl; return false; }
        sellers[numSellers++]=s;
        cout<<"Seller registered: "<<s.getUsername()<<endl; return true;
    }
    bool registerAdmin(Admin a) {
        if(numAdmins>=5){ cout<<"Admin limit."<<endl; return false; }
        admins[numAdmins++]=a;
        cout<<"Admin registered : "<<a.getUsername()<<endl; return true;
    }

    // Overloaded addListing — Function Overloading (Polymorphism)
    int addListing(Vehicle v, VehicleFeatures f, double p, int mil,
                   string cond, string desc, string seller) {
        if(numListings>=100){ cout<<"Full."<<endl; return -1; }
        listings[numListings]=Listing(v,f,p,mil,cond,desc,seller);
        int id=listings[numListings].getListingID();
        _linkSeller(seller,numListings++);
        cout<<"Listing #"<<id<<" added."<<endl; return id;
    }
    int addListing(Car c, VehicleFeatures f, double p, int mil,
                   string cond, string desc, string seller) {
        if(numListings>=100){ cout<<"Full."<<endl; return -1; }
        listings[numListings]=Listing(c,f,p,mil,cond,desc,seller);
        int id=listings[numListings].getListingID();
        _linkSeller(seller,numListings++);
        cout<<"Car Listing #"<<id<<" added."<<endl; return id;
    }
    int addListing(Bike b, VehicleFeatures f, double p, int mil,
                   string cond, string desc, string seller) {
        if(numListings>=100){ cout<<"Full."<<endl; return -1; }
        listings[numListings]=Listing(b,f,p,mil,cond,desc,seller);
        int id=listings[numListings].getListingID();
        _linkSeller(seller,numListings++);
        cout<<"Bike Listing #"<<id<<" added."<<endl; return id;
    }
    int addListing(ElectricCar e, VehicleFeatures f, double p, int mil,
                   string cond, string desc, string seller) {
        if(numListings>=100){ cout<<"Full."<<endl; return -1; }
        listings[numListings]=Listing(e,f,p,mil,cond,desc,seller);
        int id=listings[numListings].getListingID();
        _linkSeller(seller,numListings++);
        cout<<"EV Listing #"<<id<<" added."<<endl; return id;
    }

    void updatePrice(int id, double newPrice) {
        Listing* l=findListing(id);
        if(l){ l->setPrice(newPrice); cout<<"Price updated for Listing #"<<id<<endl; }
        else   cout<<"Listing not found."<<endl;
    }

    bool deleteListing(int id, string uname) {
        for(int i=0;i<numListings;i++){
            if(listings[i].getListingID()==id && listings[i].getSellerName()==uname){
                for(int s=0;s<numSellers;s++) sellers[s].removeListing(id);
                for(int j=i;j<numListings-1;j++) listings[j]=listings[j+1];
                numListings--;
                cout<<uname<<" deleted Listing #"<<id<<endl; return true;
            }
        }
        cout<<"Not found or unauthorized."<<endl; return false;
    }

    void searchListings(string brand, string model,
                        double minP, double maxP, int minYear, int maxMil) const {
        cout<<"\n--- Search Results ---"<<endl;
        bool found=false;
        for(int i=0;i<numListings;i++)
            if(listings[i].getIsApproved() &&
               listings[i].matchFilter(brand,model,minP,maxP,minYear,maxMil))
            { listings[i].displayListing(); found=true; }
        if(!found) cout<<"No listings match."<<endl;
    }

    void adminApprove(string adminName, int id) {
        Admin* a=findAdmin(adminName); Listing* l=findListing(id);
        if(a&&l) a->approveListing(l); else cout<<"Not found."<<endl;
    }
    void adminReject(string adminName, int id) {
        Admin* a=findAdmin(adminName); Listing* l=findListing(id);
        if(a&&l) a->rejectListing(l); else cout<<"Not found."<<endl;
    }
    bool adminRemove(string adminName, int id) {
        Admin* a=findAdmin(adminName);
        if(!a){ cout<<"Admin not found."<<endl; return false; }
        for(int i=0;i<numListings;i++){
            if(listings[i].getListingID()==id){
                for(int s=0;s<numSellers;s++) sellers[s].removeListing(id);
                for(int j=i;j<numListings-1;j++) listings[j]=listings[j+1];
                numListings--;
                cout<<"Admin "<<adminName<<" removed Listing #"<<id<<endl; return true;
            }
        }
        cout<<"Listing not found."<<endl; return false;
    }

    void buyerSaveFav(string bname, int id) {
        Buyer* b=findBuyer(bname); Listing* l=findListing(id);
        if(b&&l) b->saveFavorite(l); else cout<<"Not found."<<endl;
    }
    void buyerRemoveFav(string bname, int id) {
        Buyer* b=findBuyer(bname);
        if(b) b->removeFavorite(id); else cout<<"Buyer not found."<<endl;
    }
    void buyerSendMsg(string bname, string sname, string text, string date) {
        Buyer* b=findBuyer(bname);
        if(b) b->sendMessage(sname,text,date); else cout<<"Buyer not found."<<endl;
    }

    void showAllListings() const {
        cout<<"\n========================================"<<endl;
        cout<<"  "<<PLATFORM_NAME<<" - All Listings"<<endl;
        cout<<"========================================"<<endl;
        if(!numListings){ cout<<"No listings."<<endl; return; }
        for(int i=0;i<numListings;i++) listings[i].displayListing();
    }

    void showStats() const {
        cout<<"\n=== Marketplace Stats ==="<<endl;
        cout<<"Platform  : "<<PLATFORM_NAME<<endl;
        cout<<"Fee       : PKR "<<LISTING_FEE<<endl;
        cout<<"Buyers    : "<<numBuyers<<endl;
        cout<<"Sellers   : "<<numSellers<<endl;
        cout<<"Admins    : "<<numAdmins<<endl;
        cout<<"Listings  : "<<numListings<<endl;
        cout<<"Total Users: "<<User::getTotalUsers()<<endl;
        cout<<"All-time listings: "<<Listing::getTotalListings()<<endl;
    }

    void showBuyerFavs    (string n){ Buyer*  b=findBuyer(n);  if(b) b->showFavorites();   else cout<<"Not found."<<endl; }
    void showBuyerMsgs    (string n){ Buyer*  b=findBuyer(n);  if(b) b->showMessages();    else cout<<"Not found."<<endl; }
    void showSellerListings(string n){ Seller* s=findSeller(n); if(s) s->showMyListings();  else cout<<"Not found."<<endl; }

    void generateAllReports() const {
        cout<<"\n=== USER REPORTS ==="<<endl;
        for(int i=0;i<numBuyers;  i++) buyers[i].generateReport();
        for(int i=0;i<numSellers; i++) sellers[i].generateReport();
        for(int i=0;i<numAdmins;  i++) admins[i].generateReport();
    }

    Buyer*   findBuyer  (string n){ for(int i=0;i<numBuyers;  i++) if(buyers[i].getUsername()==n)  return &buyers[i];  return NULL; }
    Seller*  findSeller (string n){ for(int i=0;i<numSellers; i++) if(sellers[i].getUsername()==n) return &sellers[i]; return NULL; }
    Admin*   findAdmin  (string n){ for(int i=0;i<numAdmins;  i++) if(admins[i].getUsername()==n)  return &admins[i];  return NULL; }
    Listing* findListing(int id)  { for(int i=0;i<numListings;i++) if(listings[i].getListingID()==id) return &listings[i]; return NULL; }
};


// ====================================================================
// MAIN FUNCTION
// ====================================================================
int main()
{
    cout<<"========================================"<<endl;
    cout<<"  PakWheels Clone - OOP Assignment 02  "<<endl;
    cout<<"========================================"<<endl;

    Marketplace market("PakWheels Clone", 500);

    // --- Register Users ---
    cout<<"\n--- Registering Users ---"<<endl;

    ContactInfo c1("0300-1234567","ali@gmail.com",  "0300-1234567");
    Address     a1("Lahore",  "Gulberg",  "Punjab",  "54000");
    Buyer buyer1("ali_buyer",    "pass123", c1, a1, 2500000);

    ContactInfo c2("0321-9876543","sara@gmail.com", "N/A");
    Address     a2("Karachi", "DHA",      "Sindh",   "75500");
    Buyer buyer2("sara_buyer",   "abc456",  c2, a2, 5000000);

    ContactInfo c3("0333-1111111","ahmed@gmail.com","0333-1111111");
    Address     a3("Lahore",  "Johar Town","Punjab",  "54782");
    Seller seller1("ahmed_motors","sell123", c3, a3, "Ahmed Motors");

    ContactInfo c4("0345-2222222","khan@gmail.com", "N/A");
    Address     a4("Islamabad","F-10",    "Federal", "44000");
    Seller seller2("khan_autos",  "sell456", c4, a4, "Khan Autos");

    ContactInfo ca("0311-9999999","admin@pakwheels.com","N/A");
    Address     aa("Lahore",  "Office",   "Punjab",  "54000");
    Admin  admin1("super_admin","admin999",ca, aa, "Senior","Moderation");

    market.registerBuyer(buyer1);
    market.registerBuyer(buyer2);
    market.registerSeller(seller1);
    market.registerSeller(seller2);
    market.registerAdmin(admin1);

    // --- SECTION 2: Polymorphism via Vehicle hierarchy ---
    cout<<"\n--- Vehicle Hierarchy: virtual displayDetails() ---"<<endl;
    Car car1("Toyota","Corolla",2022,1800,"Automatic","Petrol",4,"Sedan");
    Car car2("Honda", "Civic",  2023,1500,"Automatic","Petrol",4,"Sedan");
    Bike bike1("Yamaha","YZF-R15",2023,155,"Manual","Sport",false);
    ElectricCar ev1("BYD","Atto 3",2024,60,520,"DC Fast");

    // Base-class pointer array — runtime polymorphism
    Vehicle* vArr[4] = { &car1, &bike1, &ev1, &car2 };
    for(int i=0;i<4;i++){
        cout<<"Type: "<<vArr[i]->getVehicleType()<<endl;
        vArr[i]->displayDetails();   // virtual dispatch
        cout<<endl;
    }

    // --- Add Listings (overloaded addListing) ---
    cout<<"\n--- Adding Listings ---"<<endl;
    VehicleFeatures f1(true,false,false,true,true,true);
    int lid1=market.addListing(car1,f1,4500000,15000,"Used","One owner, maintained.","ahmed_motors");

    VehicleFeatures f2(true,true,true,true,true,true);
    int lid2=market.addListing(car2,f2,6800000,5000,"Used","Turbo, sunroof.","ahmed_motors");

    Vehicle v3("Suzuki","Alto",2021,660,"Manual","Petrol");
    VehicleFeatures f3(true,false,false,false,false,false);
    int lid3=market.addListing(v3,f3,1800000,35000,"Used","Good fuel average.","khan_autos");

    VehicleFeatures f4(true,true,true,true,true,true);
    int lid4=market.addListing(ev1,f4,9500000,1000,"New","Full charge 520km.","khan_autos");

    VehicleFeatures f5(false,false,false,false,false,false);
    int lid5=market.addListing(bike1,f5,550000,5000,"Used","Sport bike, excellent.","ahmed_motors");

    // --- Approvals ---
    cout<<"\n--- Admin Approvals ---"<<endl;
    market.adminApprove("super_admin",lid1);
    market.adminApprove("super_admin",lid2);
    market.adminApprove("super_admin",lid3);
    market.adminApprove("super_admin",lid4);
    market.adminApprove("super_admin",lid5);

    market.showAllListings();

    // --- Search ---
    cout<<"\n--- Search: Toyota under 5M ---"<<endl;
    market.searchListings("Toyota","",0,5000000,2018,9999999);
    cout<<"\n--- Search: All under 2M ---"<<endl;
    market.searchListings("","",0,2000000,1990,9999999);

    // --- Favorites & Messages ---
    cout<<"\n--- Buyer Favorites ---"<<endl;
    market.buyerSaveFav("ali_buyer",lid1);
    market.buyerSaveFav("ali_buyer",lid3);
    market.buyerSaveFav("sara_buyer",lid2);
    market.buyerSaveFav("sara_buyer",lid4);
    market.showBuyerFavs("ali_buyer");

    cout<<"\n--- Buyer Messages ---"<<endl;
    market.buyerSendMsg("ali_buyer","ahmed_motors","Is Corolla still available?","2026-05-01");
    market.buyerSendMsg("ali_buyer","khan_autos",  "Final price on Alto?",       "2026-05-01");
    market.buyerSendMsg("sara_buyer","ahmed_motors","Civic still under warranty?","2026-05-01");
    market.showBuyerMsgs("ali_buyer");

    // ================================================================
    // SECTION 4: OPERATOR OVERLOADING DEMO
    // ================================================================
    cout<<"\n========================================"<<endl;
    cout<<"  OPERATOR OVERLOADING DEMO"<<endl;
    cout<<"========================================"<<endl;

    // Vehicle == > <
    Vehicle va("Toyota","Corolla",2022,1800,"Automatic","Petrol");
    Vehicle vb("Toyota","Corolla",2022,1800,"Automatic","Petrol");
    Vehicle vc("Honda", "Civic",  2023,1500,"Automatic","Petrol");
    cout<<"\nVehicle == (same brand/model/year):"<<endl;
    cout<<"  va == vb : "<<(va==vb?"TRUE":"FALSE")<<endl;
    cout<<"  va == vc : "<<(va==vc?"TRUE":"FALSE")<<endl;
    cout<<"Vehicle > < (by year):"<<endl;
    cout<<"  Corolla2022 > Civic2023 : "<<(va>vc?"TRUE":"FALSE")<<endl;
    cout<<"  Corolla2022 < Civic2023 : "<<(va<vc?"TRUE":"FALSE")<<endl;

    // VehicleFeatures == +
    VehicleFeatures fa(true,true,false,false,false,false);
    VehicleFeatures fb(true,true,false,false,false,false);
    VehicleFeatures fc(false,false,true,true,true,true);
    cout<<"\nVehicleFeatures == :"<<endl;
    cout<<"  fa==fb (same): "<<(fa==fb?"TRUE":"FALSE")<<endl;
    cout<<"  fa==fc (diff): "<<(fa==fc?"TRUE":"FALSE")<<endl;
    cout<<"VehicleFeatures + (union):"<<endl;
    VehicleFeatures merged = fa + fc;
    cout<<"  fa + fc = "; merged.displayFeatures();

    // Address == <<
    Address addr1("Karachi","DHA","Sindh","75500");
    Address addr2("Karachi","Clifton","Sindh","75600");
    Address addr3("Lahore","Gulberg","Punjab","54000");
    cout<<"\nAddress << : "<<addr1<<endl;
    cout<<"Address == (same city+province): "<<endl;
    cout<<"  addr1==addr2 (both Karachi/Sindh): "<<(addr1==addr2?"TRUE":"FALSE")<<endl;
    cout<<"  addr1==addr3 (diff): "<<(addr1==addr3?"TRUE":"FALSE")<<endl;

    // User ==
    Buyer bx("ali_buyer","x",c1,a1,100);
    Buyer by("ali_buyer","y",c1,a1,200);
    Buyer bz("zara",     "z",c1,a1,300);
    cout<<"\nUser == (by username):"<<endl;
    cout<<"  bx==by (same username): "<<(bx==by?"TRUE":"FALSE")<<endl;
    cout<<"  bx==bz (diff): "<<(bx==bz?"TRUE":"FALSE")<<endl;

    // Listing > < ==
    Listing* l1ptr=market.findListing(lid1);
    Listing* l3ptr=market.findListing(lid3);
    if(l1ptr&&l3ptr){
        cout<<"\nListing > < (by price):"<<endl;
        cout<<"  lid1(4.5M) > lid3(1.8M): "<<(*l1ptr>*l3ptr?"TRUE":"FALSE")<<endl;
        cout<<"  lid1(4.5M) < lid3(1.8M): "<<(*l1ptr<*l3ptr?"TRUE":"FALSE")<<endl;
        cout<<"  lid1==lid1 (same): "<<(*l1ptr==*l1ptr?"TRUE":"FALSE")<<endl;
        cout<<"  lid1==lid3 (diff): "<<(*l1ptr==*l3ptr?"TRUE":"FALSE")<<endl;
    }

    // ================================================================
    // SECTION 5: FRIEND FUNCTIONS DEMO
    // ================================================================
    cout<<"\n========================================"<<endl;
    cout<<"  FRIEND FUNCTIONS DEMO"<<endl;
    cout<<"========================================"<<endl;

    // Friend #1: compareListing
    cout<<"\nFriend #1 - compareListing (accesses private price & listingID):"<<endl;
    if(l1ptr&&l3ptr){
        bool cheaper=compareListing(*l1ptr,*l3ptr);
        cout<<"  Is lid1 cheaper than lid3? "<<(cheaper?"Yes":"No")<<endl;
    }

    // Friend #2: mergeFeatures
    cout<<"\nFriend #2 - mergeFeatures (accesses private features):"<<endl;
    if(l1ptr&&l3ptr){
        VehicleFeatures mf=mergeFeatures(*l1ptr,*l3ptr);
        cout<<"  Union features of lid1 + lid3: "; mf.displayFeatures();
    }

    // Friend #3: printUserContact
    cout<<"\nFriend #3 - printUserContact (accesses private ContactInfo):"<<endl;
    printUserContact(buyer1);
    printUserContact(seller1);

    // Friend #4: combineBudget
    cout<<"\nFriend #4 - combineBudget (accesses private budget):"<<endl;
    Buyer* bp1=market.findBuyer("ali_buyer");
    Buyer* bp2=market.findBuyer("sara_buyer");
    if(bp1&&bp2){
        double tot=combineBudget(*bp1,*bp2);
        cout<<"  Afford EV at 9.5M together? "<<(tot>=9500000?"Yes":"No")<<endl;
    }

    // ================================================================
    // SECTION 3: ABSTRACTION DEMO — Interface pointers
    // ================================================================
    cout<<"\n========================================"<<endl;
    cout<<"  ABSTRACTION DEMO (Interface Pointers)"<<endl;
    cout<<"========================================"<<endl;

    // IDisplayable* can hold any User-derived object
    cout<<"\nIDisplayable* (polymorphic getInfo + displayProfile):"<<endl;
    IDisplayable* disp[3];
    disp[0]=&buyer1; disp[1]=&seller1; disp[2]=&admin1;
    for(int i=0;i<3;i++){
        cout<<disp[i]->getInfo()<<endl;
        disp[i]->displayProfile();
        cout<<endl;
    }

    // ISearchable* can hold Listing
    cout<<"\nISearchable* (matchFilter + getSummary on a Listing):"<<endl;
    if(l1ptr){
        ISearchable* srch=l1ptr;
        cout<<"Summary: "<<srch->getSummary()<<endl;
        cout<<"Match 'Toyota' <5M? "
            <<(srch->matchFilter("Toyota","",0,5000000,2018,99999)?"Yes":"No")<<endl;
    }

    // IApprovable* can hold Admin
    cout<<"\nIApprovable* (reject then re-approve via interface):"<<endl;
    Admin* adPtr=market.findAdmin("super_admin");
    Listing* l5ptr=market.findListing(lid5);
    if(adPtr&&l5ptr){
        IApprovable* iapp=adPtr;
        iapp->rejectListing(l5ptr);
        iapp->approveListing(l5ptr);
    }

    // IReportable* — reports
    cout<<"\nIReportable* (generateReport via interface):"<<endl;
    IReportable* reps[3];
    reps[0]=&buyer1; reps[1]=&seller1; reps[2]=&admin1;
    for(int i=0;i<3;i++) reps[i]->generateReport();

    // Generate all reports through Marketplace
    market.generateAllReports();

    // --- Misc A1 operations ---
    cout<<"\n--- Price Update ---"<<endl;
    market.updatePrice(lid1,4300000);

    cout<<"\n--- Seller Deletes Listing ---"<<endl;
    market.deleteListing(lid5,"ahmed_motors");

    cout<<"\n--- Admin Removes Suspicious Listing ---"<<endl;
    Vehicle vBad("Fake","Car",1990,500,"Manual","Petrol");
    VehicleFeatures fBad;
    int lidBad=market.addListing(vBad,fBad,100,999999,"Used","Suspicious.","khan_autos");
    market.adminApprove("super_admin",lidBad);
    market.adminRemove("super_admin",lidBad);

    cout<<"\n--- Remove from Favorites ---"<<endl;
    market.buyerRemoveFav("ali_buyer",lid3);
    market.showBuyerFavs("ali_buyer");

    cout<<"\n--- Seller Listings ---"<<endl;
    market.showSellerListings("ahmed_motors");
    market.showSellerListings("khan_autos");

    market.showStats();

    cout<<"\n--- Static Members ---"<<endl;
    cout<<"Total users    : "<<User::getTotalUsers()<<endl;
    cout<<"Total listings : "<<Listing::getTotalListings()<<endl;

    cout<<"\n========================================"<<endl;
    cout<<"       Assignment 02 Complete!          "<<endl;
    cout<<"========================================"<<endl;
    return 0;
}

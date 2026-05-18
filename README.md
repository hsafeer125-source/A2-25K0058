# PakWheels Clone — OOP Assignment 02
**Student ID:** [25K0058]  
**Course:** Object-Oriented Programming — Spring 2026  
**Instructor:** Talha Shahid  

This project is an extension of Assignment 01, implementing advanced OOP concepts
including Inheritance, Polymorphism, Abstraction, Operator Overloading, and Friend
Functions, modelled after the real PakWheels.com car marketplace.

## 1. Vehicle Listings (Car, Bike, ElectricCar)
PakWheels displays all used vehicle listings with key details like name, year, price,
mileage, and condition. We replicated this using a Listing class that stores a Vehicle
object (or its derived types Car, Bike, ElectricCar) along with price, mileage,
condition, and seller name. The displayListing() method prints all these details
exactly like a listing card on PakWheels.
<img width="1079" height="543" alt="image" src="https://github.com/user-attachments/assets/ae5b2ad1-1a05-40ab-ab1c-52790e69761e" />
## 2. Search and Filter
PakWheels lets users filter cars by brand, model, price range, year, and mileage.
We replicated this with the searchListings() method in Marketplace and the
matchFilter() method in Listing (implementing the ISearchable abstract interface).
Filters for brand, model, min/max price, minimum year, and maximum mileage are
all supported.
<img width="237" height="484" alt="image" src="https://github.com/user-attachments/assets/aebe954a-2fa4-45f6-9006-a7141129e5e4" />
<img width="236" height="609" alt="image" src="https://github.com/user-attachments/assets/f09b9f4d-4050-487a-80e1-a9abd5d7e2f4" />
<img width="234" height="608" alt="image" src="https://github.com/user-attachments/assets/30504840-506d-4b62-b7f2-240815bf272e" />
## 3. Vehicle Features Checklist
Each PakWheels listing shows a features checklist — AC, sunroof, leather seats,
navigation, rear camera, push start. We replicated this using the VehicleFeatures
class with six boolean flags. The displayFeatures() method prints only the features
that are present, matching the PakWheels listing detail page. We also extended the
vehicle hierarchy with Car (body type, doors), Bike (type, fairing), and ElectricCar
(battery, range, charge type) to match the different vehicle categories on the site.
<img width="609" height="191" alt="image" src="https://github.com/user-attachments/assets/aad5b349-27fe-4b99-a33b-e5f6eebfd6de" />
## 4. Seller and Dealer Profile
PakWheels shows dealer profiles with a shop name, contact details, and their active
listings. We replicated this with the Seller class which inherits from User and adds
shopName, rating, and a pointer array of their listings. The displayProfile() method
is overridden (runtime polymorphism) to show seller-specific information, and
showMyListings() prints all listings belonging to that dealer.
<img width="321" height="525" alt="image" src="https://github.com/user-attachments/assets/63ee5b07-f174-4574-8f7c-afc5665a860d" />
<img width="1001" height="568" alt="image" src="https://github.com/user-attachments/assets/85dbc2cf-2f28-49e0-9d87-ca16d6c99c11" />

## 5. Saved / Favourite Cars
PakWheels allows logged-in buyers to save listings to a favourites list. We replicated
this with the Buyer class which holds an array of Listing pointers (aggregation).
The saveFavorite() method adds a listing by pointer, removeFavorite() removes it by
ID, and showFavorites() displays the full saved list — mirroring the PakWheels
saved cars feature exactly.
<img width="1004" height="607" alt="image" src="https://github.com/user-attachments/assets/414f1600-9e4f-4738-8880-5911792b178c" />
## 6. Messaging System
PakWheels has a built-in messaging system where buyers can contact sellers directly
through a listing. We replicated this with the Message class storing sender, receiver,
message text, date, and read status. The Buyer class holds an array of 50 Message
objects and sendMessage() creates a new Message to a seller. The showMessages()
method displays the full inbox, including read/unread status.
<img width="303" height="170" alt="image" src="https://github.com/user-attachments/assets/6be8b53c-b1e1-4722-8a37-4f49b01444d0" />
## 7. User Registration and Profile
PakWheels requires users to register with a username, password, phone number, email,
WhatsApp number, and address. We replicated this with a User base class (abstract,
implementing IDisplayable) that holds ContactInfo and Address as composed members.
Buyer, Seller, and Admin all inherit from User and override displayProfile() and
getInfo() using runtime polymorphism. The static totalUsers counter tracks all
registered users across the platform.
<img width="450" height="510" alt="image" src="https://github.com/user-attachments/assets/56b9b82c-631a-4ca9-a640-8b399fcf59a7" />
## 8. Listing Approval and Moderation
PakWheels moderates listings before they go live and allows reporting of suspicious
ads. We replicated this with the Admin class which inherits from User and implements
the IApprovable abstract interface with approveListing() and rejectListing() pure
virtual methods. Admins can also forcibly remove any listing via adminRemove().
The Admin tracks approvedCount, rejectedCount, and department, mirroring a real
moderation system. Cann't get a screenshot of it.



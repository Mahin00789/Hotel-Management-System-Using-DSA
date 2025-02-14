#include <iostream>
 #include<vector> 
 #include<string> 
 #include<unordered_map> 
 #include<cctype> 
 using namespace std;
  
 enum RoomType { 
 Single, 
 Double, 
 Suite 
 };
 class Room
{
 public : 
 int roomNumber;
     RoomType type;
     bool isBooked;
     bool needsMaintenance;
     double price;
      
 Room(int num, RoomType t) : roomNumber(num), type(t), isBooked(false),
                               needsMaintenance(false)
    {
         switch (type)
        {
         case Single:
            price = 100.0;
            break;
         case Double:
            price = 150.0;
            break;
         case Suite:
            price = 300.0;
            break;
            
        }
        
    }
      
 string getTypeName()
    {
         switch (type)
        {
         case Single:
            return "Single";
         case Double:
            return "Double";
         case Suite:
            return "Suite";
             default : return "Unknown";
            
        }
        
    }
    
};
 class Guest
{
 public : 
 string name;
     int guestID;
     string roomBooked;
     string feedback;
      
 Guest(string n, int id, string room) : name(n), guestID(id),
                                          roomBooked(room) {}
    
};
  
 class Employee
{
 public : 
 string name;
     int employeeID;
     string shift;
      
 Employee(string n, int id, string s) : name(n), employeeID(id),
                                          shift(s) {}
    
};
  
 class Billing
{
 public : 
 void processPayment(string guestName, double amount)
    {
         cout << "Payment processed for " << guestName << ": $" << amount
               << endl;
        
    }
    
};
  
 class HotelManagementSystem
{
 private : 
 vector<Room> rooms;
     vector<Guest> guests;
     vector<Employee> employees;
     Billing billing;
     unordered_map<int, vector<string>> roomServiceRequests;
  
 public : 
 HotelManagementSystem(int numRooms)
    {
         for (int i = 1; i <= numRooms; i++)
        {
             RoomType type = (i % 3 == 1) ? Single : (i % 3 == 2) ? Double
                                                                   : Suite;
             rooms.push_back(Room(i, type));
            
        }
        
    }
      
 void bookRoom(int guestID, string guestName)
    {
         cout << "Three types of rooms are available:" << endl;
         cout << "1) Single (Room number 1,4,7,10 etc...) priced at $100" << endl;
         cout << "2) Double (Room number 2,5,8,11 etc...) priced at $150" << endl;
         cout << "3) Suite (Room number 3,6,9,12 etc...) priced at $300" << endl;
          
 int roomTypeChoice;
     cout << "Enter the type of room you want to book (1 for Single, 2 for Double, 3 for Suite): "; 
     cin >> roomTypeChoice;
  
 RoomType selectedType;
 switch (roomTypeChoice)
{
 case 1:
    selectedType = Single;
    break;
 case 2:
    selectedType = Double;
    break;
 case 3:
    selectedType = Suite;
    break;
     default : 
 cout << "Invalid room type choice!" << endl;
     return;
    
}
  
 bool isValidName = true;
 for (char c : guestName)
{
     if (!isalpha(c))
    {
         isValidName = false;
         break;
        
    }
    
}
 if (!isValidName)
{
     cout << "Enter a valid name" << endl;
     return;
    
}
  
 cout << "Available rooms of the selected type: ";
 vector<int> availableRooms;
 for (const auto &room : rooms)
{
     if (room.type == selectedType && !room.isBooked &&
          !room.needsMaintenance)
    {
         cout << room.roomNumber << " ";
         availableRooms.push_back(room.roomNumber);
        
    }
    
}
 cout << endl;
  
 if (availableRooms.empty())
{
     cout << "No available rooms of the selected type at the moment."
           << endl;
     return;
    
}
  
 int roomNumberChoice;
 cout << "Enter the specific room number you want to book from the available options : "; 
 cin >>
    roomNumberChoice;
  
 bool roomBooked = false;
 for (auto &room : rooms)
{
     if (room.roomNumber == roomNumberChoice && room.type == selectedType && !room.isBooked && !room.needsMaintenance)
    {
         room.isBooked = true;
         guests.push_back(Guest(guestName, guestID, "Room " + to_string(room.roomNumber) + " (" + room.getTypeName() + ")"));
         cout << guestName << " has successfully booked " << room.getTypeName() << " Room " << room.roomNumber << " for $" << room.price << " per night." << endl;
         roomBooked = true;
         break;
        
    }
    
}
  
 if (!roomBooked)
{
     cout << "Invalid room number or room is not available." << endl;
    
}

    }
      
 void checkIn(int guestID)
    {
         for (auto &guest : guests)
        {
             if (guest.guestID == guestID)
            {
                 cout << "Guest " << guest.name << " has checked into " << guest.roomBooked << endl;
                 return;
                
            }
            
        }
         cout << "Guest ID not found." << endl;
        
    }
      
 void checkOut(int guestID, double amount)
    {
         bool guestFound = false;
         for (int i = 0; i < guests.size(); i++)
        {
             if (guests[i].guestID == guestID)
            {
                 guestFound = true;
                 billing.processPayment(guests[i].name, amount);
                 for (auto &room : rooms)
                {
                     if (room.roomNumber ==
                          stoi(guests[i].roomBooked.substr(5)))
                    {
                         room.isBooked = false;
                        
                    }
                    
                }
                 cout << "Guest " << guests[i].name << " has checked out." << endl;
                 cout << "Would you like to leave feedback? (yes/no): ";
                 string response;
                 cin >> response;
                 if (response == "yes")
                {
                     cin.ignore();
                     cout << "Enter your feedback: ";
                     getline(cin, guests[i].feedback);
                    
                }
                 guests.erase(guests.begin() + i);
                 return;
                
            }
            
        }
         if (!guestFound)
        {
             cout << "Guest ID not found." << endl;
            
        }
        
    }
      
 void addEmployee(string name, int id, string shift)
    {
         employees.push_back(Employee(name, id, shift));
         cout << "Employee " << name << " has been added to the system." << endl;
        
    }
      
 void assignTask(int employeeID, string task)
    {
         bool found = false;
         for (auto &employee : employees)
        {
             if (employee.employeeID == employeeID)
            {
                 cout << "Assigned task: " << task << " to " << employee.name << endl;
                 found = true;
                 break;
                
            }
            
        }
         if (!found)
        {
             cout << "Employee ID not found." << endl;
            
        }
        
    }
      
 void checkRoomAvailability()
    {
         cout << "Available Rooms:" << endl;
         for (auto &room : rooms)
        {
             if (!room.isBooked && !room.needsMaintenance)
            {
                 cout << "Room " << room.roomNumber << " - " << room.getTypeName() << " ($" << room.price << " per night)" << endl;
                
            }
            
        }
        
    }
      
 void requestRoomService(int guestID, string request)
    {
         roomServiceRequests[guestID].push_back(request);
         cout << "Room service request received for Guest ID " << guestID
               << ": " << request << endl;
        
    }
      
 void markRoomForMaintenance(int roomNumber)
    {
         if (roomNumber <= rooms.size())
        {
             rooms[roomNumber - 1].needsMaintenance = true;
             cout << "Room " << roomNumber << " marked for maintenance." << endl;
            
        }
        else
        {
             cout << "Room does not exist." << endl;
            
        }
        
    }
      
 void viewEmployeeShifts()
    {
         cout << "Employee Shifts:" << endl;
         for (const auto &employee : employees)
        {
             cout << "Employee " << employee.name << " (ID: " << employee.employeeID << ") - Shift: " << employee.shift << endl;
            
        }
        
    }
    
};
  
 int main()
{
     int numRooms;
     cout << "Enter the number of rooms in the hotel: ";
     cin >> numRooms;
      
 HotelManagementSystem hotel(numRooms);
      
 int choice;
     do
    {
         cout << "\n--- Hotel Management System ---\n";
         cout << "1. Book Room\n";
         cout << "2. Check In\n";
         cout << "3. Check Out\n";
         cout << "4. Add Employee\n";
         cout << "5. Assign Task to Employee\n";
         cout << "6. Check Room Availability\n";
         cout << "7. Request Room Service\n";
         cout << "8. Mark Room for Maintenance\n";
         cout << "9. View Employee Shifts\n";
         cout << "10. Exit\n";
         cout << "Enter your choice: ";
         cin >> choice;
          
 switch (choice)
        {
         case 1:
        {
             string guestName;
             int guestID, roomNumber;
             cout << "Enter guest ID: ";
             cin >> guestID;
             cin.ignore();
             cout << "Enter guest name: ";
             getline(cin, guestName);
             hotel.bookRoom(guestID, guestName);
             break;
            
        }
         case 2:
        {
             int guestID;
             cout << "Enter guest ID to check-in: ";
             cin >> guestID;
             hotel.checkIn(guestID);
             break;
            
        }
         case 3:
        {
             int guestID;
             double amount;
             cout << "Enter guest ID to check-out: ";
             cin >> guestID;
             cout << "Enter payment amount: ";
             cin >> amount;
             hotel.checkOut(guestID, amount);
             break;
            
        }
         case 4:
        {
             string name, shift;
             int id;
             cin.ignore();
             cout << "Enter employee name: ";
             getline(cin, name);
             cout << "Enter employee ID: ";
             cin >> id;
             cout << "Enter shift: ";
             cin.ignore();
             getline(cin, shift);
             hotel.addEmployee(name, id, shift);
             break;
            
        }
         case 5:
        {
             int employeeID;
             string task;
             cout << "Enter employee ID to assign task: ";
             cin >> employeeID;
             cin.ignore();
             cout << "Enter task to assign: ";
             getline(cin, task);
             hotel.assignTask(employeeID, task);
             break;
            
        }
         case 6:
        {
             hotel.checkRoomAvailability();
             break;
            
        }
         case 7:
        {
             int guestID;
             string request;
             cout << "Enter guest ID for room service request: ";
             cin >> guestID;
             cin.ignore();
             cout << "Enter request details: ";
             getline(cin, request);
             hotel.requestRoomService(guestID, request);
             break;
            
        }
         case 8:
        {
             int roomNumber;
             cout << "Enter room number to mark for maintenance: ";
             cin >> roomNumber;
             hotel.markRoomForMaintenance(roomNumber);
             break;
            
        }
         case 9:
        {
             hotel.viewEmployeeShifts();
             break;
            
        }
         case 10:
             cout << "Exiting system.\n";
             break;
             default : 
 cout << "Invalid choice! Please try again.\n";
            
        }
        
    }
    while (choice != 10)
        ;
      
 return 0;
    
}
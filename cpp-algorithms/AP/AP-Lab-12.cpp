#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std; 

struct Plane
{
    string type;
    int numOfSeats;
};

struct Flight
{
    int number;
    string direction; 
    double ticketPrice;
};

struct Database
{
    Flight flight;
    Plane planes[10]; 
    int numPlanes;
};

void AppendData(string filename) 
{
    char flight_answer, plane_answer;
    ofstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary | ios::app);
    if (!file) 
    {
        cerr << "Error opening file!\n"; 
        return;
    }

    do
    {
        Database newFlight; 
        cout << "Flight number: "; cin >> newFlight.flight.number;
        cout << "Flight direction: "; cin >> newFlight.flight.direction; 
        cout << "Ticket price: "; cin >> newFlight.flight.ticketPrice; 
        int j = 0;
        cout << "========== Planes: ==========\n";
        do
        {
            Plane newPlane;
            cout << "Aircraft type: "; cin >> newPlane.type; 
            cout << "Number of seats: "; cin >> newPlane.numOfSeats;   
            newFlight.planes[j] = newPlane;
            j++; 
            if (j >= 10)
            {
                cout << "Cannot append more planes to the flight.\n";
                continue;
            }
            cout << "Add another aircraft to a flight? y/n "; cin >> plane_answer;
        } 
        while (plane_answer != 'n'); 
        newFlight.numPlanes = j;  
        file.write(reinterpret_cast<const char*>(&newFlight), sizeof(newFlight));   
        
        cout << "Continue input? y/n "; cin >> flight_answer;

    } 
    while (flight_answer != 'n');

    file.close();
}

void DeleteData(string filename) 
{
    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary); 
    if (!file) 
    {
        cerr << "Error opening file for reading!\n"; 
        return;
    }

    ofstream tempFile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\temp.bin", ios::binary);
    if (!tempFile) 
    {
        cerr << "Error creating temporary file!\n"; 
        return;
    }

    int flightNumber;
    cout << "Enter the flight number you want to delete: "; cin >> flightNumber; 
    getchar();

    bool flightDeleted = false;
    Database flightData;
    while (file.read(reinterpret_cast<char*>(&flightData), sizeof(flightData))) 
    {
        if (flightData.flight.number != flightNumber)  
        {
            tempFile.write(reinterpret_cast<const char*>(&flightData), sizeof(flightData));
        }
        else 
        {
            flightDeleted = true;
        }
    }

    file.close();
    tempFile.close();

    remove(("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename).c_str());
    rename(("C:\\Users\\PC\\OneDrive\\Рабочий стол\\temp.bin"), ("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename).c_str()); 
     
    if (!flightDeleted) 
    {
        cout << "Flight with number " << flightNumber << " not found.\n";
    }
    else 
    {
        cout << "Flight with number " << flightNumber << " deleted successfully.\n";
    }
    cout << "Press any key to continue..."; 
    getchar(); 
}

void ReadFromFile(string filename)
{
    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary); 
    if (!file) 
    {
        cerr << "Error opening file for reading!\n";
        return;
    }

    Database flightData; 
    while (file.read(reinterpret_cast<char*>(&flightData), sizeof(flightData))) 
    {
        cout << "Flight number: " << flightData.flight.number << endl; 
        cout << "Flight direction: " << flightData.flight.direction << endl; 
        cout << "Ticket price: " << flightData.flight.ticketPrice << endl; 
        cout << "Planes:" << endl; 
        for (int i = 0; i < flightData.numPlanes; ++i) 
        {
            cout << i + 1 << ". Type: " << flightData.planes[i].type << ", Seats: " << flightData.planes[i].numOfSeats << endl;
        }
        cout << "------------------------------------\n";
    }

    file.close(); 
    cout << "Press any key to continue..."; 
    getchar(); 
}

void FindCheapTickets(string filename)
{
    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary);
    if (!file) 
    {
        cerr << "Error opening file for reading!" << endl; 
        return;
    }

    string direction; 
    double maxPrice; 
    cout << "Enter flight direction: "; cin >> direction; 
    cout << "Enter maximum ticket price: "; cin >> maxPrice; 
    getchar();

    Database flightData; 
    bool cheapTicketsFound = false; 
    while (file.read(reinterpret_cast<char*>(&flightData), sizeof(flightData))) 
    {
        if (flightData.flight.direction == direction && flightData.flight.ticketPrice < maxPrice) 
        {
            cheapTicketsFound = true; 
            cout << "Flight number: " << flightData.flight.number << endl; 
            cout << "Ticket price: " << flightData.flight.ticketPrice << endl;  
            cout << "------------------------------------\n"; 
        }
    }

    if (!cheapTicketsFound) { 
        cout << "No cheap tickets found for the specified direction and price.\n"; 
    }

    file.close(); 
    cout << "Press any key to continue...";
    getchar(); 
}

void FindAllAircrafts(string filename)
{
    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary);
    if (!file) 
    {
        cerr << "Error opening file for reading!\n";
        return;
    }

    string direction; 
    cout << "Enter flight direction: "; cin >> direction; getchar();

    Database flightData; int totalSeatsNum = 0;
    bool planesFound = false;
    while (file.read(reinterpret_cast<char*>(&flightData), sizeof(flightData)))
    {
        if (flightData.flight.direction == direction && flightData.numPlanes > 0)
        {
            planesFound = true;
            for (int i = 0; i < flightData.numPlanes; i++)
            {
                cout << i + 1 << ". Type: " << flightData.planes[i].type << ", Seats: " << flightData.planes[i].numOfSeats << endl; 
                totalSeatsNum += flightData.planes[i].numOfSeats;
            }
        }
    }
    if (!planesFound) 
    {
        cout << "No planes found for the specified direction\n";
    }
    cout << "Total number of seats: " << totalSeatsNum << endl; 
    file.close(); 
    cout << "Press any key to continue..."; 
    getchar(); 
}

void Clear(string filename) 
{
    char choice;
    cout << "Are you sure? Delete all data? (y/n)"; cin >> choice;
    getchar();
    if (choice == 'n')
    {
        cout << "Press any key to continue...";
        getchar();
        return;
    }
    ofstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::trunc);  
    if (!file) 
    {
        cerr << "Error opening file for writing!\n";  
        return;
    }

    file.close(); 
    cout << "File cleared successfully\n"; 
    cout << "Press any key to continue...";
    getchar();
}


int main()
{
    Database scheduledFlights[3] = {
        { {101, "Paris", 400.0}, { {"Boeing_737", 150}, {"Airbus_A320", 180}, {"Boeing_787", 250} }, 3 },
        { {102, "London", 450.0}, { {"Boeing_787", 250}, {"Boeing_777", 350} }, 2 },
        { {103, "NewYork", 500.0}, { {"Airbus_A380", 500}, {"Boeing_747", 416}, {"Boeing_737", 150} }, 3 }
    };

    string filename; 
    cout << "Enter the filename with \".bin\" format: "; cin >> filename;
    ofstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary);
    if (!file) 
    {
        cerr << "Error opening file for writing!" << endl;
        return 1;
    }
    
    for (const Database &flight : scheduledFlights)  
    { 
        file.write(reinterpret_cast<const char*>(&flight), sizeof(flight)); 
    }
    
    file.close();

    int choice;
    do
    {
        system("cls"); 
        cout << "===========================MENU===========================\n\n";
        cout << "(1) Append Data\n";
        cout << "(2) Delete Data by Index\n";
        cout << "(3) Read from File\n";
        cout << "(4) Find cheaper tickets in a given direction\n";
        cout << "(5) Find all planes and total num of seats in a given direction\n";
        cout << "(6) Clear Data\n";
        cout << "(0) Exit\n\n";
        cout << "Enter menu item: "; cin >> choice;   
        getchar(); 
        system("cls");  
        switch (choice)
        {
            case 1: { AppendData(filename); break; } 
            case 2: { DeleteData(filename); break; } 
            case 3: { ReadFromFile(filename); break; }  
            case 4: { FindCheapTickets(filename); break; } 
            case 5: { FindAllAircrafts(filename); break; } 
            case 6: { Clear(filename); break; }
            case 0: { choice = 0; break; } 
            default: cout << "Invalid choice. Please try again.\n";  
        }  
    } 
    while (choice != 0);

    return 0;
}

//void Function(string filename) 
//{
//    ifstream file("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary);
//    if (!file) {
//        cerr << "Error opening file for reading and writing!" << endl;
//        return;
//    }
//
//    int flightNumber;
//    cout << "Enter the flight number you want to replace: ";
//    cin >> flightNumber;
//
//    bool flightFound = false;
//    Database flightData;
//    while (file.read(reinterpret_cast<char*>(&flightData), sizeof(flightData)))  
//    {
//        if (flightData.flight.number == flightNumber)  
//        {
//            flightFound = true;
//            break;
//        }
//    }
//
//    if (!flightFound) 
//    {
//        cout << "Flight with number " << flightNumber << " not found\n"; 
//        return;
//    }
//
//    char choice;
//    cout << "Do you want to replace (a)ll data, (f)light data only, or (p)lane data only? ";
//    cin >> choice;
//
//    if (choice == 'a' || choice == 'f') 
//    {
//        cout << "Flight number: "; cin >> flightData.flight.number;
//        cout << "Flight direction: "; cin >> flightData.flight.direction;
//        cout << "Ticket price: "; cin >> flightData.flight.ticketPrice;
//    }
//
//    if (choice == 'a' || choice == 'p') 
//    {
//        string planeChoice; 
//        do 
//        {
//            cout << "Enter plane type to replace or press 'a' to replace all: ";
//            cin >> planeChoice; 
//
//            bool planeFound = false; Plane plane;
//            for (int i = 0; i < flightData.numPlanes; i++)  
//            {
//                if (plane.type == planeChoice || planeChoice == "a") 
//                { 
//                    planeFound = true; 
//                    cout << "Aircraft type: "; cin >> plane.type;
//                    cout << "Number of seats: "; cin >> plane.numOfSeats;  
//                    flightData.planes[i] = plane;
//                    if (planeChoice != "a") break;  
//                }
//            }
//
//            if (!planeFound && planeChoice != "a") 
//            {
//                cout << "Plane with type " << planeChoice << " not found.\n"; 
//            }
//            if (planeChoice != "a")
//            {
//                cout << "Do you want to replace another plane? (y/n): "; cin >> planeChoice;  
//            }
//        } 
//        while (planeChoice != "n");  
//    }
//
//    streampos pos = file.tellg();
//    file.close();
//
//    ofstream wfile("C:\\Users\\PC\\OneDrive\\Рабочий стол\\" + filename, ios::binary);
//     
//    wfile.seekp(-static_cast<long>(sizeof(flightData)), ios::cur); 
//    wfile.write(reinterpret_cast<const char*>(&flightData), sizeof(flightData)); 
//    wfile.close(); 
//}
// Organization Transport Management System//

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define MAX_VEHICLES 500
#define MAX_DRIVERS 500
#define MAX_TRIPS 2000
#define MAX_STRING 200
#define MAX_NOTES 200

#define VEHICLE_FILE "vechile.dat"
#define DRIVER_FILE "driver.dat"
#define TRIP_FILE "trips.dat"


typedef struct
{
    int vehicleID;
    char regNumber[25];
    char type[25];
    char make[30];
    char model[30];
    int year;
    char fueltype[25];
    int seatCapacity;
    float currentOdometer;
    char insuranceExpiry[25];
    char taxExpiry[25];
    char status[25];
    char isActive;
} Vehicle;

typedef struct
{
    int driverID;
    char name[MAX_STRING];
    char licenseNumber[35];
    char licenseType[35];
    char licenseExpiry[35];
    int age;
    char contact[15];
    char address[MAX_STRING];
    char joiningDate[20];
    int totalTrip;
    float totalKmDriven;
    char status[35];
    int isActive;
} Driver;

typedef struct
{
    int tripID;
    int vehicleID;
    char vehicleReg[25];
    int driverID;
    char driverName[MAX_STRING];
    char purpose[MAX_STRING];
    char origin[MAX_STRING];
    char destination[MAX_STRING];
    char departureDate[25];
    char departureTime[25];
    char returnDate[25];
    char returnTime[25];
    int passengerCount;
    float startOdometer;
    float distanceCoverd;
    float fuelConsumed;
    float tripCost;
    char status[25];
    char approvedBy[MAX_STRING];
    char notes[MAX_NOTES];
    int isActive;
}Trips;

Vehicle vehicles[MAX_VEHICLES];
Driver drivers[MAX_DRIVERS];
Trips trips[MAX_TRIPS];

int vehicleCount = 0;
int driverCount = 0;
int tripCount = 0;

int nextVehicleID = 2001;
int nextDriverID = 3001;
int nextTripID = 4001;
// file i/o 
void loadAllData();
void saveAllData();
void loadVehicles();
void saveVehicles();
void loadDrivers();
void saveDrivers();
void loadTrips();
void saveTrips();
// vehicle management
void addVehicle();
void viewVehicle();
void updateVehicle();
void deleteVehicles();
void listAllVehicles();
// driver management
void addDriver();
void viewDriver();
void updateDriver();
void deleteDriver();
void listAllDriver();
// tripo management
void bookTrip();
void viewTrip();
void updateTrip();
void completeTrip();
void cancelTrip();
void listAllTrip();
// reports
void vehicleStatusReport();
void driverStatusReport();
void tripHistoryReport();
void costSummaryReport();
// menu hehlper
void displayMainMenu();
void displayVehicleMenu();
void displayDriverMenu();
void displayTripMenu();
void displayReportMenu();
// utilitu\y
void clearScreen();
void pauseScreen();
void clearInputBuffer();
void getCurrentDate(char* buffer);
void getCurrentTime(char* buffer);
int getValidInteger(const char* prompt, int min, int max);
float getValidFloat(const char* prompt, int min, int max);
void getValidString(const char* prompt, int min, int max);
int findVehicleByID(int id);
int findVehicleByReg(const char* reg);
int findDriverByID(int id);
void displayVehicleDetails(Vehicle v);
void displayDriverDetails(Driver d);
void displayTripDetails(Trips t);

// MAIN //
int main()
{
    printf("======================================================\n");
    printf("     Organization Transport Management Sysytem\n");
    printf("======================================================\n");
    printf("\nLoading Transport Records....\n");

    loadAllData();
    printf("System initialized successfully!\n");
    printf(" Vehicles : %d\n", vehicleCount);
    printf(" Drivers : %d\n", driverCount);
    printf(" Trips : %d\n", tripCount);
    pauseScreen();

    int choice;
    do{
        clearScreen();
        displayMainMenu();
        choice = getValidInteger("Enter your choice", 0, 5);

        switch (choice){
            case 1:
                // vehicle sub-menu
                {
                    int vc;
                    do {
                        clearScreen();
                        displayMainMenu();
                        vc = getValidInteger("Enter a choice", 0, 5);
                        switch(vc){
                            case 1: addVehicle();
                            break;
                            case 2: viewVehicle();
                            break;
                            case 3: updateVehicle();
                            break;
                            case 4: deleteVehicles();
                            break;
                            case 5: listAllVehicles();
                            break;
                            case 0: break;
                        }
                    } while (vc !=0);
                }
                break;
            case 2:
                // driver seb-menu
                {
                    int dc;
                    do {
                        clearScreen();
                        displayDriverMenu();
                        dc = getValidInteger("Enter a choice", 0, 5);
                        switch(dc) {
                            case 1: addDriver();
                            break;
                            case 2: viewDriver();
                            break;
                            case 3: updateDriver();
                            break;
                            case 4: deleteDriver();
                            break;
                            case 5: listAllDriver();
                            break;
                            case 0: break;
                        }
                    }while(dc!=0);
                }
                break;
            case 3:
                // trip sub menu
                {
                    int tc;
                    do{
                        clearScreen();
                        displayTripMenu();
                        tc = getValidInteger("Enter a choice", 0, 6);
                        switch(tc) {
                            case 1: bookTrip();
                            break;
                            case 2: viewTrip();
                            break;
                            case 3: updateTrip();
                            break;
                            case 4: completeTrip();
                            break;
                            case 5: cancelTrip();
                            break;
                            case 6: listAllTrip();
                            break;
                            case 0: break;
                        }
                    } while(tc!=0);
                }
                break;
            case 4:
                // report sub meni
                {
                    int rc;
                    do{
                        clearScreen();
                        displayReportMenu();
                        rc = getValidInteger("Enter a choice", 0, 4);
                        switch(rc) {
                            case 1 : vehicleStatusReport();
                            break;
                            case 2 : driverStatusReport();
                            break;
                            case 3 : tripHistoryReport();
                            break;
                            case 4 : costSummaryReport();
                            break;
                        }
                    }
                }

        }
    }
}
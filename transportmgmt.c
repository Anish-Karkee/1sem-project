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
    float fuelCostPerKm;
    char notes[MAX_NOTES];
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
    float endOdometer;
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
                            case 0:
                            break;
                        }
                    } while(rc!=0);
                }
                break;
            case 5:
                saveAllData();
                printf("\n All data saved successfully\n");
                pauseScreen();
                break;
            case 0:
                saveAllData();
                printf("\n================================================================\n");
                printf("        Thank you for using Transport Management System\n");
                printf("==================================================================\n");
                break;     
        }
    } while(choice!=0);
    return 0;
}

// Menu dispaly function

void displayMainMenu(){
    printf("\n=======================================================\n");
    printf("     ORGANIZATION TRANSPORT MANAGEMENT SYSTEM\n");
    printf("=======================================================\n");
    printf("  1. Vehicle Management\n");
    printf("  2. Driver Management\n");
    printf("  3. Trip / Booking Management\n");
    printf("  4. Reports & Analytics\n");
    printf("  5. Save All Data\n");
    printf("  0. Exit System\n");
    printf("=======================================================\n");
}

void displayVehicleMenu() {
    printf("\n=======================================================\n");
    printf("              VEHICLE MANAGEMENT\n");
    printf("=======================================================\n");
    printf("  1. Add New Vehicle\n");
    printf("  2. View Vehicle Details\n");
    printf("  3. Update Vehicle Record\n");
    printf("  4. Delete Vehicle Record\n");
    printf("  5. List All Vehicles\n");
    printf("  0. Back to Main Menu\n");
    printf("=======================================================\n");
}

void displayDriverMenu(){
    printf("\n=======================================================\n");
    printf("              DRIVER MANAGEMENT\n");
    printf("=======================================================\n");
    printf("  1. Add New Driver\n");
    printf("  2. View Driver Details\n");
    printf("  3. Update Driver Record\n");
    printf("  4. Delete Driver Record\n");
    printf("  5. List All Drivers\n");
    printf("  0. Back to Main Menu\n");
    printf("=======================================================\n");
}

void displayTripMenu() {
    printf("\n=======================================================\n");
    printf("              TRIP MANAGEMENT\n");
    printf("=======================================================\n");
    printf("  1. Book New Trip\n");
    printf("  2. View Trip Details\n");
    printf("  3. Update Trip Details\n");
    printf("  4. Mark Trip as Completed\n");
    printf("  5. Cancel Trip\n");
    printf("  6. List All Trips\n");
    printf("  0. Back to Main Menu\n");
    printf("=======================================================\n");
}

void displayReportMenu() {
    printf("\n=======================================================\n");
    printf("              REPORTS & ANALYTICS\n");
    printf("=======================================================\n");
    printf("  1. Vehicle Status Report\n");
    printf("  2. Driver Status Report\n");
    printf("  3. Trip History Report\n");
    printf("  4. Cost Summary Report\n");
    printf("  0. Back to Main Menu\n");
    printf("=======================================================\n");
}

// VEHICLE MANAGEMENT 

void addVehicle(){
    clearScreen();
    printf("\n=======================================================\n");
    printf("              ADD NEW VEHICLE\n");
    printf("=======================================================\n");

    if (vehicleCount>=MAX_VEHICLES){
        printf("\n Error: Maximum vehicle capacity reached!\n");
        pauseScreen();
        return;
    }

    Vehicle v;
    memset(&v, 0, sizeof(Vehicle));
    v.vehicleID = nextDriverID++;
    v.isActive = 1;
    printf("\nVehicle ID (AUTO-GENERATED): %d\n", v.vehicleID);
    getValidString("Enter REgistration Number", v.regNumber, 20);
    getValidString("Enter Vehicle Type (car/van/bus/truck/bike)", v.type, 30);
    getValidString("Enter Make (e.g. Toyota, Tata, Mahindra, hyundai)", v.make, 50);
    getValidString("Enter Model", v.model, 50);
    v.year = getValidInteger("Enter Year of Manufacture", 1980, 2026);
    getValidString("Enter Fuel Type (Petrol/Diesel/CNG/EV)", v.fueltype, 25);
    v.seatCapacity = getValidInteger("Enter Seat Capacity", 1, 60);
    v.currentOdometer = getValidFloat("Enter Current Odometer (km)", 0, 9999999);
    getValidString("Enter Insurance Expiry Date (YYYY-MM-DD)", v.insuranceExpiry, 20);
    getValidString("Enter Tax Expiry Date(YYYY-MM-DD)", v.taxExpiry, 20);
    v.fuelCostPerKm = getValidFloat("Enter Feul Cost Per Km (approx)", 0, 100);
    strcpy(v.status, "Available");
    getValidString("Enter Notes (optional)", v.notes, MAX_NOTES);

    vehicles[vehicleCount++] = v;
    saveVehicles();

    pritnf("\n Vehicle added successfully! ID: %d\n", v.vehicleID);
    pauseScreen();
}

void viewVehicle(){
    clearScreen();
    pritnf("\n=================================================\n");
    printf("              VIEW VEHICLES DETAILS\n");
    printf("=================================================\n");

    printf("\n search by:\n");
    printf("1. Vehicle ID\n");
    printf("2. Registration Number\n");
    int choice = getValidInteger("Enter a choice", 1, 2);
    int index = -1;

    if(choice == 1) {
        int id = getValidInteger("Enter Vehicle ID", 2000, 9999999);
        index = findVehicleByID(id);
    } else {
        char reg[20];
        getValidString("Enter Registration Number", reg, 20);
        index = findVehicleByReg(reg);
    }

    if(index != -1)
        displayVehicleDetails(vehicles[index]);
    else
    printf("\n Vehicle not found!\n");

    pauseScreen();
    return;
}

void updateVehicles(){
    clearScreen();
    printf("\n========================================================\n");
    printf("                UPDATE VEHICLES RECORDS\n");
    printf("=====================================================/n");

    int id = getValidInteger("Enter Vehicles ID to update", 2000, 999999);
    int index = findVehicleByID(id);

    if(index == -1) {
        printf("\n Vehicle not found!\n");
        pauseScreen();
        return;
    }

    displayVehicleDetails(vehicles[index]);
    printf("\nSelect field to update:\n");
    printf(" 1. Registration Number\n 2. Type\n 3. Make\n 4. Model\n ");
    printf(" 5. Year\n 6. Fuel Type\n 7. Seat Capacity\n 8. Odometer\n ");
    printf(" 9. Insurance Expiry\n 10. Tax Expiry\n 11. Fuel Cost Per KM\n ");
    printf(" 12. Status\n 13. Note\n 0. Cancel\n ");

    int choice = getValidInteger("Enter a choice", 0, 13);
    switch(choice) {
        case 0: printf("\nCancelled. \n"); pauseScreen(); return;
        case 1: getValidString("New Registration Number", vehicles[index].regNumber, 25); break;
        case 2: getValidString("New Type", vehicles[index].type, 30); break;
        case 3: getValidString("New Make", vehicles[index].make, 50); break;
        case 4: getValidString("New Model", vehicles[index].model, 50); break;
        case 5: vehicles[index].year = getValidInteger("New Year", 1980, 2026); break;
        case 6: getValidString("New Fuel Type", vehicles[index].fueltype, 25); break;
        case 7: vehicles[index].seatCapacity = getValidInteger("New Seat Capacity", 1, 60); break;
        case 8: vehicles[index].currentOdometer = getValidFloat("New Odometer (km)", 0, 9999999); break;
        case 9: getValidString("New Insurance Expiry (YYYY-MM-DD)",vehicles[index].insuranceExpiry, 20); break;
        case 10: getValidString("New Tax Expiry (YYYY-MM-DD)",vehicles[index].taxExpiry, 20); break;
        case 11: vehicles[index].fuelCostPerKm = getValidFloat("New Fuel Cost per Km", 0, 100); break;
        case 12: getValidString("New Status (Available/In Use/ Under Maintenance)", vehicles[index].status, 20); break;
        case 13: getValidString("New Notes", vehicles[index].notes, MAX_NOTES); break;
    }
    saveVehicles();
    printf("\n Vehicle record updated successfully\n");
    pauseScreen();
}

void deleteVehicle() {
    clearScreen();
    printf("\n===============================================\n");
    printf("            DELETE VEHICLE RECORD\n");
    printf("==============================================\n");

    int id = getValidInteger("Enter Vehicle ID to delete", 2000, 9999999);
    int index = findVehicleByID(id);
    if(index==-1) {
        printf("\n Vehicle not found\n");
        pauseScreen();
        return;
    }
    displayVehicleDetails(vehicles[index]);
    printf("\n WARNNING: This action cannot be undo!\n ");
    printf("Confirm deletion? (yes/no): ");
    char confirm[10];
    scanf("%s", confirm);
    clearInputBuffer();
    if(strcasecmp(confirm, "yes")==0){
        vehicles[index].isActive = 0;
        saveVehicles();
        printf("\n Vehicle record deleted.\n");
    }
    else {
        printf("\nDeletion cancelled.\n");
    }
    pauseScreen();
}

void listAllVehicles(){
    clearScreen();
    printf("\n=====================================================================\n");
    printf("                ALL VEHICLES\n");
    printf("=====================================================================\n");
    printf("\n%-8s %-12s %-8s %-20s %-5s %-8s %-16s", 
    "ID", "Reg No.", "Type", "Make & Model", "Year", "Cap.", "Status");
    printf("-------------------------------------------------------------------------------\n");

    int count = 0;
    for (int i = 0; i < vehicleCount; i++) {
        if(vehicles[i].isActive) {
            char makeModel[72];
            snprintf(makeModel, sizeof(makeModel), "%s %s", vehicles[i].make, vehicles[i].model);
            printf("%-8d %-12s %-8s %-20s %-5d %-8d %-16s\n",
                    vehicles[i].vehicleID,
                    vehicles[i].regNumber,
                    vehicles[i].type,
                    makeModel,
                    vehicles[i].year,
                    vehicles[i].seatCapacity,
                    vehicles[i].status);
            count++;
        }
    }

    printf("------------------------------------------------------------------------------------------------\n");
    printf("Total Active Vehicles: %d\n", count);
    pauseScreen();
    
}

//driver
void addDriver(){
    clearScreen();
    printf("\n==================================================================\n");
    printf("                ADD NEW DRIVER\n");
    printf("==================================================================\n");
    if(driverCount>=MAX_DRIVERS){
        printf("\n Error: Maximum Driver Capacity Reached!!\n");
        pauseScreen();
        return;
    }

    Driver d;
    memset(&d, 0, sizeof(Driver));
    d.driverID=nextDriverID++;
    d.isActive=1;
    d.totalTrip=0;
    d.totalKmDriven=0;

    printf("\nDriver ID (Auto-generated): %d\n", d.driverID);

    getValidString("Enter Driver Name", d.name, MAX_STRING);
    d.age=getValidInteger("Enter Age", 18, 65);
    getValidString("Enter License Number", d.licenseNumber, 35);
    getValidString("Enter License Type (INTERNATIONAL/NORMAL)", d.licenseType, 25);
    getValidString("Enter License Expiry Date (YYYY-MM-DD)", d.licenseExpiry, 25);
    getValidString("Enter Contact Number", d.contact, 20);
    getValidString("Enter Address", d.address, MAX_STRING);
    getCurrentDate(d.joiningDate);
    printf("Joining Date (Auto-set): %s\n", d.joiningDate);
    strcpy(d.status, "Available");
    drivers[driverCount++]=d;
    saveDrivers();
    printf("\n Driver added successfully! ID: %d\n", d.driverID);
    pauseScreen();
}

void viewDriver(){
    clearScreen();
    printf("\n===========================================================================\n");
    printf("                    VIEW DRIVER DETAILS\n");
    printf("===========================================================================\n");

    int id=getValidInteger("Enter Driver ID", 3000, 999999);
    int index=findDriverByID(id);
    if(index!=-1)
        displayDriverDetails(drivers[index]);
    else
        printf("\n Driver not found!\n");
    pauseScreen();
}

void updateDriver(){
    clearScreen();
    printf("\n===========================================================================\n");
    printf("                    UPDATE DRIVER RECORD\n");
    printf("===========================================================================\n");

    int id=getValidInteger("Enter Driver ID to Update", 3000, 999999);
    int index=findDriverByID(id);
    if(index==-1){
        printf("\nDriver not found!\n");
        pauseScreen();
        return;
    }

    displayDriverDetails(drivers[index]);
    printf("\nSelect field to update:\n");
    printf(" 1. Name\n 2. Age\n 3. License Number\n 4. License Type\n");
    printf(" 5. License Expiry\n 6. Contact\n 7. Address\n 8. Status\n 0. Cancel\n");

    int choice=getValidInteger("Enter a choice", 0, 8);
    switch(choice){
        case 0: printf("\nCancelled.\n"); pauseScreen(); return;
        case 1: getValidString("New Name", drivers[index].name, MAX_STRING); break;
        case 2: drivers[index].age=getValidInteger("New Age", 18, 65); break;
        case 3: getValidString("New License Number", drivers[index].licenseNumber, 30); break;
        case 4: getValidString("New License Type", drivers[index].licenseType, 30); break;
        case 5: getValidString("New License Expiry (YYYY-MM-DD)",drivers[index].licenseExpiry, 20); break;
        case 6: getValidString("New Contact", drivers[index].contact, 20); break;
        case 7: getValidString("New Address", drivers[index].address, MAX_STRING); break;
        case 8: getValidString("New Status(Available/On Duty/On Leave)", drivers[index].status, 20); break;
    }

    saveDrivers();
    printf("\nDriver record updated Successfully!\n");
    pauseScreen();
}

void deleteDriver(){
    clearScreen();
    printf("\n============================================================================\n");
    printf("                   DELETE DRIVER RECORD\n");
    printf("============================================================================\n");

    int id=getValidInteger("Enter Driver ID to delete",3000, 999999);
    int index=findDriverByID(id);

    if(index==-1) {
        printf("\n Driver not found!\n");
        pauseScreen();
        return;
    }

    displayDriverDetails(drivers[index]);
    printf("WAARNIGN: This action cannot be undo!\n");
    printf("Confirm deletio? (yes/no):");
    char confirm[10];
    scanf("%s", confirm);
    clearInputBuffer();
    if(strcasecmp(confirm, "yes")==0) {
        drivers[index].isActive=0;
        saveDrivers();
        printf("\nDriver record deleted.\n");
    }
    else {
        printf("\nDeletion cancelled.\n");
    }
    pauseScreen();
}
void listAllDrivers() {
    clearScreen();
    printf("\n========================================================\n");
    printf("                ALL DRIVERS\n");
    printf("========================================================\n");
    printf("\n%-8s %-25s %-5s %-15s %-20s %-8s %-14s\n",
            "ID", "Name", "Age", "License No.", "License Expiry", "Trips", "Starus");
    printf("-----------------------------------------------------------------------\n");

    int count=0;
    for(int i=0;i<driverCount++;i++) {
        if(drivers[i].isActive){
            printf("%-8d %-25s %-5d %-15s %-20s %-8d %-14s\n",
                    drivers[i].driverID,
                    drivers[i].name,
                    drivers[i].age,
                    drivers[i].licenseNumber,
                    drivers[i].licenseExpiry,
                    drivers[i].totalTrip,
                    drivers[i].status);
            count++;
        }
    }

    printf("-----------------------------------------------------------------------\n");
    printf("Total Active Drivers: %d\n", count);
    pauseScreen();
}

void bookTrip() {
    clearScreen();
    printf("\n=======================================================================\n");
    printf("                BOOK NEW TRIP\n");
    printf("=======================================================================\n");
    
    if(tripCount>=MAX_TRIPS) {
        printf("\n Error: Maximum trip capacity reached!\n");
        pauseScreen();
        return;
    }

    Trips t;
    memset(&t, 0, sizeof(Trips));
    t.tripID=nextTripID++;
    t.isActive=1;
    strcpy(t.status, "Scheduled");
    printf("\nTrip ID (Auto-generated): %d\n", t.tripID);

    // link vehicles
    t.vehicleID=getValidInteger("Enter Vehicle ID", 2000, 999999);
    int vi=findVehicleByID(t.vehicleID);
    if(vi==-1){
        printf("\nVehicle not found! Trip booking cancelled.\n");
        nextTripID--;
        pauseScreen();
        return;
    }
    if(strcasecmp(vehicles[vi].status, "Available")!=0){
        printf("\nWARNING: Vehicle is not marked as Available (current: %s).\n", vehicles[vi].status);
        printf("Continue anyway? (yes/no): ");
        char c[10];
        scanf("%s", c);
        clearInputBuffer();
        if(strcasecmp(c, "yes")!=0){
            nextTripID--;
            pauseScreen();
            return;
        }
    }
    strcpy(t.vehicleReg, vehicles[vi].regNumber);

    //driver linked
    t.driverID=getValidInteger("Enter Driver ID", 3000, 999999);
    int di=findDriverByID(t.driverID);
    if(di==-1) {
        printf("\nDriver not found! Trip booking cancelled.\n");
        nextDriverID--;
        pauseScreen();
        return;
    }
    strcpy(t.driverName, drivers[di].name);

    getValidString("Enter Purpose of Trip", t.purpose, MAX_STRING);
    getValidString("Enter Origin", t.origin, MAX_STRING);
    getValidString("Enter Destination", t.destination, MAX_STRING);
    getValidString("Enter Departure Date (YYYY-MM-DD)", t.departureDate, 25);
    getValidString("Enter Departure Time (HH:MM)", t.departureTime, 15);
    getValidString("Enter Expected Return Date (YYYY-MM-DD)", t.returnDate, 25);
    getValidString("Enter Expected Return Time (HH:MM)", t.returnTime, 15);
    t.passengerCount=getValidInteger("Enter Number of Passenger",0,60);
    t.startOdometer = vehicles[vi].currentOdometer;
    printf("Start Odometer (from vehicle): %.2f km\n", t.startOdometer);
    t.endOdometer = 0;
    t.distanceCoverd = 0;
    t.fuelConsumed = 0;
    t.tripCost = 0;
    getValidString("Enter Approved By", t.approvedBy, MAX_STRING);
    getValidString("Enter Notes (OPTIONAL)", t.notes, MAX_STRING);
    
    // MARK VEHICLES & DRIVER IN USE
    strcpy(vehicles[vi].status,"In Use");
    strcpy(drivers[di].status, "On Duty");

    trips[tripCount++] = t;
    saveTrips();
    saveVehicles();
    saveDrivers();
    
    printf("\nTrip booked successfully! Trip ID: %d\n", t.tripID);
    pauseScreen();
}

void viewTrip(){
    clearScreen();
    printf("\n===========================================================================\n");
    printf("                VIEW TRIP DETAILS\n");
    printf("===========================================================================\n");

    int id=getValidInteger("Enter Trip ID", 4000, 999999);

    for(int i=0;i<tripCount;i++) {
        if(trips[i].tripID==id && trips[i].isActive) {
            displayTripDetails(trips[i]);
            pauseScreen();
            return;
        }
    }

    printf("\nTrip not found!\n");
    pauseScreen();
}

void updateTrip() {
    clearScreen();
    printf("\n===========================================================================\n");
    printf("                   UPDATE TRIP DETAILS\n");
    printf("===========================================================================\n");

    int id = getValidInteger("Enter Trip ID to update", 4000, 999999);
    int index=-1;
    for(int i=0;i<tripCount;i++) { 
        if(trips[i].tripID==id && trips[i].isActive)
        { index = i; break;}
    }
    if(index==-1) {
        printf("\nTrip not found!\n");
        pauseScreen();
        return;
    }

    displayTripDetails(trips[index]);

    printf("\nSelect field to update:\n");
    printf(" 1. Purpose\n 2. Origin\n 3. Destination\n 4. Departure Date\n");
    printf(" 5. Departure Time\n 6. Return Date\n 7. Return Time\n");
    printf(" 8. Passenger Count\n 9. Approved By\n 10. Notes\n 0. Cancel\n");

    int choice = getValidInteger("Enter a Choice", 0, 10);
    switch(choice) {
        case 0: printf("\nCancelled.\n"); pauseScreen(); break;
        case 1: getValidString("New Purpose", trips[index].purpose, MAX_STRING); break;
        case 2: getValidString("New Origin", trips[index].origin, MAX_STRING); break;
        case 3: getValidString("New Destination", trips[index].destination, MAX_STRING); break;
        case 4: getValidString("New Departure Date (YYYY-MM-DD)", trips[index].departureDate, 20); break;
        case 5: getValidString("New Departure Time (HH:MM)", trips[index].departureTime, 10); break;
        case 6: getValidString("New Return Date (YYYY-MM-DD)", trips[index].returnDate, 20); break;
        case 7:getValidString("New Return Time (HH:MM)", trips[index].returnTime, 10); break;
        case 8: trips[index].passengerCount = getValidInteger("New Passenger Count", 0, 60); break;
        case 9: getValidString("New Approved By", trips[index].approvedBy, MAX_STRING); break;
        case 10: getValidString("New Notes", trips[index].notes, MAX_NOTES); break;
    }

    saveTrips();
    printf("\nTrip updated successfully!\n");
    pauseScreen();
}

852
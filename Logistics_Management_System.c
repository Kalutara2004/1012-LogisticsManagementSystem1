#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 100
#define FUEL_PRICE 310.0

//These are use as global arrays
char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];

char vehicleTypes[3][10] = {"Van", "Truck", "Lorry"};
int vehicleCapacity[3] = {1000, 5000, 10000};
int vehicleRate[3] = {30, 40, 80};
int vehicleSpeed[3] = {60, 50, 45};
int vehicleEfficiency[3] = {12, 6, 4};

int deliveryId[MAX_DELIVERIES];
char deliverySource[MAX_DELIVERIES][MAX_NAME_LENGTH];
char deliveryDestination[MAX_DELIVERIES][MAX_NAME_LENGTH];
float deliveryWeight[MAX_DELIVERIES], deliveryDistance[MAX_DELIVERIES];
int deliveryVehicle[MAX_DELIVERIES];
float deliveryCustomerCharge[MAX_DELIVERIES], deliveryEstimatedTime[MAX_DELIVERIES];
float deliveryProfit[MAX_DELIVERIES];

int cityCount = 0, deliveryCount = 0;

// Function prototypes
void initializeSystem(int* cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES], int* deliveryCount);
void displayMainMenu(void);
void cityManagement(int* cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES], int deliveryCount,
                    char deliverySource[][MAX_NAME_LENGTH],char deliveryDestination[][MAX_NAME_LENGTH]);
void distanceManagement(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]);
void vehicleManagement(void);
void deliveryRequest(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES],int* deliveryCount,
                     int deliveryId[],char deliverySource[][MAX_NAME_LENGTH],
                    char deliveryDestination[][MAX_NAME_LENGTH],float deliveryWeight[],float deliveryDistance[],int deliveryVehicle[],
                    float deliveryCustomerCharge[],
                    float deliveryEstimatedTime[],float deliveryPofit[]);
void reports(int deliveryCount,char deliverySource[][MAX_NAME_LENGTH],char deliveryDstination[][MAX_NAME_LENGTH],float deliveryDistance[],
             float deliveryEstimatedTime[],float deliveryCustomerCharge[],float deliveryProfit[]);
void fileHandling(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]);
void addCity(int* cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]);
void renameCity(int cityCount,char cities[][MAX_NAME_LENGTH],int deliveryCount,char deliverySource[][MAX_NAME_LENGTH],
                char deliveryDestination[][MAX_NAME_LENGTH]);
void removeCity(int* cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES],int deliveryCount,
                char deliverySource[][MAX_NAME_LENGTH],char deliveryDestination[][MAX_NAME_LENGTH]);
void displayCities(int cityCunt,char cities[][MAX_NAME_LENGTH]);
int inputDistance(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]);
void displayDistanceTable(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]);
float calculateDeliveryCost(int source,int destination,int vehicleType,float weight,float minDistance,int vehicleRate[],int vehicleSpeed[],
                           int vehicleEfficiency[],char cities[][MAX_NAME_LENGTH],char vehicle_types[][10]);
void saveDeliveryRecord(int source,int destination,int vehicleType,
                       float weight,float minDistance,int* deliveryCount,
                       int deliveryId[],char deliverySource[][MAX_NAME_LENGTH],
                       char deliveryDestination[][MAX_NAME_LENGTH],
                       float deliveryWeight[],float deliveryDistance[],
                       int delivery_vehicle[],float deliveryCustomerCharge[],
                       float deliveryEstimatedTime[],float deliveryProfit[],
                       char cities[][MAX_NAME_LENGTH],int vehicleRate[],
                       int vehicle_speed[]);
float findMinimumDistance(int source,int destination,int path[],int* pathLength,int cityCount,int distance[][MAX_CITIES]);
void clearInputBuffer(void);


int main(){












}

//Initialize the System
void initializeSystem(int* cityCount, char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES],int* deliveryCount) {
    for(int i = 0; i < MAX_CITIES; i++) {
        for(int j = 0; j < MAX_CITIES; j++) {
            if (i == j) {
                distance[i][j] = 0;
            } else {
                distance[i][j] = -1;
            }
        }
    }

char* dCities[] = {"Colombo", "Kandy", "Galle", "Jaffna"};
    int dDistances[4][4] = {
        {0, 120, 115, 400},
        {120, 0, 200, 350},
        {115, 200, 0, 450},
        {400, 350, 450, 0}
    };

    for(int i = 0; i < 4; i++) {
        strcpy(cities[i],dCities[i]);
        for(int j = 0; j < 4; j++) {
            distance[i][j] = dDistances[i][j];
        }
     }
    *cityCount = 4;
    *deliveryCount = 0;
    printf("Logistics Management System Initialized!\n");
}

//Display Main Menu
void displayMainMenu(void){
    printf("\n========================================\n");
    printf("    LOGISTICS MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. City Management\n 2. Distance Management\n 3. Vehicle Management\n 4. Delivery Request\n");
    printf("5. Reports\n 6. File Handling\n 7. Exit\n");
    printf("========================================\n");
}

//City Management
void cityManagement(int* cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES], int deliveryCount,
                    char deliverySource[][MAX_NAME_LENGTH],char deliveryDestination[][MAX_NAME_LENGTH]){
  int choice;
    do {
        printf("\n--- City Management ---\n");
        printf("1. Add City\n 2. Rename City\n 3. Remove City\n 4. Display Cities\n 5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearInputBuffer();

        switch(choice) {
            case 1:
                addCity(cityCount, cities, distance);
                break;
            case 2:
                renameCity(*cityCount, cities, deliveryCount, deliverySource, deliveryDestination);
                break;
            case 3:
                removeCity(cityCount, cities, distance, deliveryCount, deliverySource, deliveryDestination);
                break;
            case 4:
                displayCities(*cityCount, cities);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);
}


//Distance Management
void distanceManagement(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES]){
    int choice;
    do {
        printf("\n--- Distance Management ---\n");
        printf("1. Input Distance\n 2. Display Distance Table\n 3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        clearInputBuffer();

        if(choice == 1)
            inputDistance(cityCount, cities, distance);
        else if(choice == 2)
            displayDistanceTable(cityCount, cities, distance);
        else if(choice != 3)
            printf("Invalid choice!\n");
    } while(choice != 3);
}

//Vehicle Management
void vehicleManagement(void){
     printf("\n--- Vehicle Management ---\n");
     printf("%-10s %-12s %-15s %-12s %-15s\n","Type","Capacity(kg)","Rate/km(LKR)","Speed(km/h)","Efficiency(km)");
     printf("------------------------------------------------------------------------\n");

    for(int i = 0; i < 3; i++) {
        printf("%-10s %-12d %-15d %-12d %-15d\n",vehicleTypes[i], vehicleCapacity[i], vehicleRate[i],vehicleSpeed[i], vehicleEfficiency[i]);
    }
}

//Delivery Request
void deliveryRequest(int cityCount,char cities[][MAX_NAME_LENGTH],int distance[][MAX_CITIES],int* deliveryCount,int deliveryId[],                                                    char deliverySource[][MAX_NAME_LENGTH],
                    char deliveryDestination[][MAX_NAME_LENGTH],float deliveryWeight[],float deliveryDistance[],int deliveryVehicle[],
                    float deliveryCustomerCharge[],float deliveryEstimatedTime[],float deliveryPofit[]){
    if(city_count < 2) {
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    if(*delivery_count >= MAX_DELIVERIES) {
        printf("Delivery records are full!\n");
        return;
    }

    displayCities(cityCount, cities);

    int source, destination, vehicleType;
    float weight;

    printf("Enter source city index: ");
    scanf("%d", &source);
    printf("Enter destination city index: ");
    scanf("%d", &destination);

    if(source < 0 || source >= cityCount || destination < 0 || destination >= cityCount) {
        printf("Invalid city index! Enter correct index.\n");

        clearInputBuffer();
        return;
    }

    if(source == destination) {
        printf("Source and destination cannot be the same!\n");
        clearInputBuffer();
        return;
    }

    vehicleManagement();

    printf("Select vehicle type (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleType);
    vehicleType--;

    if(vehicleType < 0 || vehicleType > 2) {
        printf("Invalid vehicle type! Enter correct vehicle type.\n");

        clearInputBuffer();
        return;
    }

    printf("Enter package weight (kg): ");
    scanf("%f", &weight);

    clearInputBuffer();

    if(weight <= 0) {
        printf("Weight must be positive!\n");
        return;
    }
    if(weight > vehicleCapacity[vehicleType]) {
        printf("Weight exceeds vehicle capacity! Maximum is %d kg\n", vehicleCapacity[vehicleType]);
        return;
    }

    int path[MAX_CITIES];
    int pathLength = 0;
    float minDistance = findMinimumDistance(source, destination, path, &pathLength,cityCount, distance);
    if(minDistance == -1) {
        printf("No valid route found!\n");
        return;
    }
    calculateDeliveryCost(source, destination, vehicleType, weight, minDistance,vehicleRate, vehicleSpeed, vehicleEfficiency,
                          cities,vehicleTypes);
    saveDeliveryRecord(source, destination, vehicleType, weight, minDistance,deliveryCount, deliveryId, deliverySource,
                       deliveryDestination,deliveryWeight, deliveryDistance, deliveryVehicle,dliveryCustomerCharge,
                       deliveryEstimatedTime, deliveryProfit,cities, vehicleRate, vehicleSpeed);
}

//Reports
void reports(int deliveryCount,char deliverySource[][MAX_NAME_LENGTH],char deliveryDstination[][MAX_NAME_LENGTH],float deliveryDistance[],
             float deliveryEstimatedTime[],float deliveryCustomerCharge[],float deliveryProfit[]){
     if(delivery_count == 0) {
        printf("No delivery data available in system.\n");
        return;
    }

    printf("\n--- PERFORMANCE REPORTS ---\n");
    printf("a. Total Deliveries Completed: %d\n", deliveryCount);

    float totalDistance = 0;
    float totalTime = 0;
    float totalRevenue = 0;
    float totalProfit = 0;
    float longestRoute = deliveryDistance[0];
    float shortestRoute = deliveryDistance[0];
    int longestId = 0;
    int shortestId = 0;

    for(int i = 0; i < deliveryCount; i++) {
        totalDistance += deliveryDistance[i];
        totalTime += deliveryEstimatedTime[i];
        totalRevenue += deliveryCustomerCharge[i];
        totalProfit += deliveryProfit[i];

        if(longestRoute < deliveryDistance[i]) {
            longestRoute = deliveryDistance[i];
            longestId = i;
        }
        if(deliveryDistance[i] < shortestRoute) {
            shortestRoute = deliveryDistance[i];
            shortestId = i;
        }
    }

    printf("b. Total Distance Covered: %.2f km\n", totalDistance);

    float averageTime = 0;
    if (deliveryCount > 0) {
        averageTime = totalTime / deliveryCount;
    }
    printf("c. Average Delivery Time: %.2f hours\n", averageTime);

    printf("d. Total Revenue: %.2f LKR\n", totalRevenue);
    printf("   Total Profit: %.2f LKR\n", totalProfit);
    printf("e. Longest Route: %.2f km (%s to %s)\n",longestRoute,deliverySource[longestId],deliveryDestination[longestId]);
    printf("   Shortest Route: %.2f km (%s to %s)\n",shortestRoute,deliverySource[shortestId],deliveryDestination[shortestId]);
}

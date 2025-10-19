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

char* cities[] = {"Colombo", "Kandy", "Galle", "Jaffna"};
    int distancesA[4][4] = {
        {0, 120, 115, 400},
        {120, 0, 200, 350},
        {115, 200, 0, 450},
        {400, 350, 450, 0}
    };

    for(int i = 0; i < 4; i++) {
        strcpy(cities[i],cities[i]);
        for(int j = 0; j < 4; j++) {
            distance[i][j] = distancesA[i][j];
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

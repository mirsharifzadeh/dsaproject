#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

int main() {
    T_Hotel *hotel = NULL;
    int choice = 0;

    char hotel_name[100];
    char city[100];
    char last_name[100];
    char first_name[100];
    int age, num_room;

    while (1) {
        printf("\n=== HOTEL MANAGEMENT SYSTEM ===\n");
        printf("1. Create a hotel chain\n");
        printf("2. Add a location to a hotel chain\n");
        printf("3. Add a booking at a location\n");
        printf("4. Display the locations in a hotel chain\n");
        printf("5. Display the customers at a location\n");
        printf("6. Delete a booking at a location\n");
        printf("7. Delete a location\n");
        printf("8. Search for a customer by last name\n");
        printf("9. Quit\n");
        printf("Enter your choice (1-9): ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input! Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                if (hotel != NULL) {
                    printf("Hotel chain already exists: %s\n", hotel->name);
                } else {
                    printf("Enter hotel chain name: ");
                    scanf(" %[^\n]", hotel_name);
                    hotel = createHotel(hotel_name);
                    if (hotel) {
                        printf("Hotel chain '%s' created successfully.\n", hotel->name);
                    } else {
                        printf("Memory allocation failed!\n");
                    }
                }
                break;

            case 2:
                if (hotel == NULL) {
                    printf("Please create a hotel chain first (Option 1).\n");
                } else {
                    printf("Enter city name for the new location: ");
                    scanf(" %[^\n]", city);
                    T_Site *newSite = createSite(city);
                    if (addSite(hotel, newSite)) {
                        printf("Location '%s' added successfully.\n", city);
                    } else {
                        printf("Failed to add location (Duplicate city or memory error).\n");
                        if (newSite) free(newSite);
                    }
                }
                break;

            case 3:
                if (hotel == NULL || hotel->first == NULL) {
                    printf("No locations available. Add a location first.\n");
                } else {
                    printf("Enter city name: ");
                    scanf(" %[^\n]", city);

                    T_Site *curr = hotel->first;
                    while (curr != NULL && strcmp(curr->city, city) != 0) {
                        curr = curr->next;
                    }

                    if (curr == NULL) {
                        printf("Location '%s' not found!\n", city);
                    } else {
                        printf("Enter client's Last Name: ");
                        scanf(" %[^\n]", last_name);
                        printf("Enter client's First Name: ");
                        scanf(" %[^\n]", first_name);
                        printf("Enter Age: ");
                        scanf("%d", &age);
                        printf("Enter Room Number: ");
                        scanf("%d", &num_room);

                        T_Client *newClient = createClient(last_name, first_name, age, num_room);
                        if (addClient(curr, newClient)) {
                            printf("Booking added successfully to '%s'.\n", city);
                        } else {
                            printf("Failed to add booking.\n");
                            if (newClient) free(newClient);
                        }
                    }
                }
                break;

            case 4:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    displayHotel(hotel);
                }
                break;

            case 5:
                if (hotel == NULL || hotel->first == NULL) {
                    printf("No locations available.\n");
                } else {
                    printf("Enter city name: ");
                    scanf(" %[^\n]", city);

                    T_Site *curr = hotel->first;
                    while (curr != NULL && strcmp(curr->city, city) != 0) {
                        curr = curr->next;
                    }

                    if (curr == NULL) {
                        printf("Location '%s' not found!\n", city);
                    } else {
                        displaySite(curr);
                    }
                }
                break;

            case 6:
                if (hotel == NULL || hotel->first == NULL) {
                    printf("No locations available.\n");
                } else {
                    printf("Enter city name: ");
                    scanf(" %[^\n]", city);

                    T_Site *curr = hotel->first;
                    while (curr != NULL && strcmp(curr->city, city) != 0) {
                        curr = curr->next;
                    }

                    if (curr == NULL) {
                        printf("Location '%s' not found!\n", city);
                    } else {
                        printf("Enter client Last Name to delete: ");
                        scanf(" %[^\n]", last_name);
                        printf("Enter client First Name to delete: ");
                        scanf(" %[^\n]", first_name);

                        if (deleteClient(curr, last_name, first_name)) {
                            printf("Booking deleted successfully.\n");
                        } else {
                            printf("Client not found in '%s'.\n", city);
                        }
                    }
                }
                break;

            case 7:
                if (hotel == NULL || hotel->first == NULL) {
                    printf("No locations available to delete.\n");
                } else {
                    printf("Enter city name to delete: ");
                    scanf(" %[^\n]", city);

                    if (deleteSite(hotel, city)) {
                        printf("Location '%s' and all its bookings deleted.\n", city);
                    } else {
                        printf("Location '%s' not found.\n", city);
                    }
                }
                break;

            case 8:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    printf("Enter search criteria (Last Name prefix): ");
                    scanf(" %[^\n]", last_name);
                    searchClients(*hotel, last_name);
                }
                break;

            case 9:
                printf("Exiting program...\n");
                if (hotel != NULL) {
                    T_Site *currSite = hotel->first;
                    while (currSite != NULL) {
                        T_Site *tempSite = currSite;
                        currSite = currSite->next;

                        T_Client *currClient = tempSite->first;
                        while (currClient != NULL) {
                            T_Client *tempClient = currClient;
                            currClient = currClient->next;
                            free(tempClient);
                        }
                        free(tempSite);
                    }
                    free(hotel);
                }
                return 0;

            default:
                printf("Invalid option! Please select 1-9.\n");
                break;
        }
    }

    return 0;
}
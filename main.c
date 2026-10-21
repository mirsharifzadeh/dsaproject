#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

T_Site* selectSite(T_Hotel *hotel) {
    if (hotel == NULL || hotel->first == NULL) {
        printf("No locations available.\n");
        return NULL;
    }

    printf("\n--- Available Locations ---\n");
    printf("%-5s %-20s %-15s\n", "No", "City", "Clients Count");
    printf("-----------------------------------------\n");

    T_Site *curr = hotel->first;
    int index = 1;
    while (curr != NULL) {
        printf("%-5d %-20s %-15d\n", index++, curr->city, curr->number_clients);
        curr = curr->next;
    }
    printf("-----------------------------------------\n");

    int choice;
    printf("Select location (1-%d): ", index - 1);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice >= index) {
        while (getchar() != '\n');
        printf("Invalid selection!\n");
        return NULL;
    }

    curr = hotel->first;
    for (int i = 1; i < choice; i++) {
        curr = curr->next;
    }
    return curr;
}

int selectSiteIndex(T_Hotel *hotel) {
    if (hotel == NULL || hotel->first == NULL) {
        printf("No locations available.\n");
        return 0;
    }

    printf("\n--- Available Locations ---\n");
    printf("%-5s %-20s %-15s\n", "No", "City", "Clients Count");
    printf("-----------------------------------------\n");

    T_Site *curr = hotel->first;
    int index = 1;
    while (curr != NULL) {
        printf("%-5d %-20s %-15d\n", index++, curr->city, curr->number_clients);
        curr = curr->next;
    }
    printf("-----------------------------------------\n");

    int choice;
    printf("Select location to delete (1-%d): ", index - 1);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice >= index) {
        while (getchar() != '\n');
        printf("Invalid selection!\n");
        return 0;
    }
    return choice;
}

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

            case 3: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite != NULL) {
                    printf("Enter client's Last Name: ");
                    scanf(" %[^\n]", last_name);
                    printf("Enter client's First Name: ");
                    scanf(" %[^\n]", first_name);
                    printf("Enter Age: ");
                    scanf("%d", &age);
                    printf("Enter Room Number: ");
                    scanf("%d", &num_room);

                    T_Client *newClient = createClient(last_name, first_name, age, num_room);
                    if (addClient(selectedSite, newClient)) {
                        printf("Booking added successfully to '%s'.\n", selectedSite->city);
                    } else {
                        printf("Failed to add booking.\n");
                        if (newClient) free(newClient);
                    }
                }
                break;
            }

            case 4:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    displayHotel(hotel);
                }
                break;

            case 5: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite != NULL) {
                    displaySite(selectedSite);
                }
                break;
            }

            case 6: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite == NULL) break;

                if (selectedSite->first == NULL) {
                    printf("No clients found in '%s'.\n", selectedSite->city);
                } else {
                    printf("\n--- Clients in %s ---\n", selectedSite->city);
                    printf("%-5s %-15s %-15s %-8s %-10s\n", "No", "Last Name", "First Name", "Age", "Room");
                    printf("---------------------------------------------------------\n");

                    T_Client *clientCurr = selectedSite->first;
                    int clientIndex = 1;
                    while (clientCurr != NULL) {
                        printf("%-5d %-15s %-15s %-8d %-10d\n", clientIndex++, clientCurr->last_name, clientCurr->first_name, clientCurr->age, clientCurr->num_room);
                        clientCurr = clientCurr->next;
                    }
                    printf("---------------------------------------------------------\n");

                    int clientChoice;
                    printf("Enter the number of the client to delete (1-%d): ", clientIndex - 1);
                    if (scanf("%d", &clientChoice) == 1 && clientChoice >= 1 && clientChoice < clientIndex) {
                        if (deleteClient(selectedSite, clientChoice)) {
                            printf("Booking deleted successfully.\n");
                        } else {
                            printf("Failed to delete booking.\n");
                        }
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid selection!\n");
                    }
                }
                break;
            }

            case 7: {
                int siteIdx = selectSiteIndex(hotel);
                if (siteIdx > 0) {
                    if (deleteSite(hotel, siteIdx)) {
                        printf("Location and all its bookings deleted successfully.\n");
                    } else {
                        printf("Failed to delete location.\n");
                    }
                }
                break;
            }

            case 8:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    printf("Enter search criteria (Last Name prefix): ");
                    scanf(" %[^\n]", last_name);
                    searchClients(hotel, last_name);
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
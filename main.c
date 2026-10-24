#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp3.h"

Room* selectRoom(T_Site *site) {
    if (site == NULL || site->room_first == NULL) {
        printf("\nNo rooms available in '%s'! Please add a room first.\n", site->city);
        return NULL;
    }

    int free_room_exists = 0;
    Room *temp = site->room_first;
    while (temp != NULL) {
        if (!isRoomBooked(site, temp->num)) {
            free_room_exists = 1;
            break;
        }
        temp = temp->next;
    }

    if (!free_room_exists) {
        printf("\nAll rooms in '%s' are currently occupied!\n", site->city);
        return NULL;
    }

    printf("\n--- Available (Free) Rooms in %s ---\n", site->city);
    printf("%-5s %-15s\n", "No", "Room Number");
    printf("-------------------------\n");

    Room *curr = site->room_first;
    Room *freeRooms[100];
    int index = 1;

    while (curr != NULL) {
        if (!isRoomBooked(site, curr->num)) {
            printf("%-5d %-15d\n", index, curr->num);
            freeRooms[index] = curr;
            index++;
        }
        curr = curr->next;
    }
    printf("-------------------------\n");

    int choice;
    printf("Select room (1-%d): ", index - 1);
    if (scanf("%d", &choice) != 1 || choice < 1 || choice >= index) {
        while (getchar() != '\n');
        printf("Invalid room selection!\n");
        return NULL;
    }

    return freeRooms[choice];
}

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
    T_Hotel *hotel = loadData("hotel_database.txt");
    if (hotel != NULL) {
        printf("Previous data restored successfully for hotel: %s\n", hotel->name);
    }

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
        printf("4. Add a room to hotel location\n");
        printf("5. Display rooms at a location\n");
        printf("6. Delete a room at a location\n");
        printf("7. Display the locations in a hotel chain\n");
        printf("8. Display the customers at a location\n");
        printf("9. Delete a booking at a location\n");
        printf("10. Delete a location\n");
        printf("11. Search for a customer by last name\n");
        printf("12. Load Bookings from a text file\n");
        printf("13. Quit\n");
        printf("Enter your choice (1-12): ");

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
                    Room *selectedRoom = selectRoom(selectedSite);
                    if (selectedRoom == NULL) {
                        break;
                    }

                    printf("Enter client's Last Name: ");
                    scanf(" %[^\n]", last_name);
                    printf("Enter client's First Name: ");
                    scanf(" %[^\n]", first_name);
                    printf("Enter Age: ");
                    scanf("%d", &age);

                    num_room = selectedRoom->num;

                    T_Client *newClient = createClient(last_name, first_name, age, num_room);
                    if (addClient(selectedSite, newClient)) {
                        printf("Booking added successfully to Room %d in '%s'.\n", num_room, selectedSite->city);
                    } else {
                        printf("Failed to add booking.\n");
                        if (newClient) free(newClient);
                    }
                }
                break;
            }

            case 4: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite != NULL) {
                    printf("Enter Room Number: ");
                    if (scanf("%d", &num_room) == 1) {
                        Room *newRoom = createRoom(num_room);
                        if (addRoom(selectedSite, newRoom)) {
                            printf("Room %d added successfully to '%s'.\n", num_room, selectedSite->city);
                        } else {
                            printf("Failed to add room.\n");
                            if (newRoom) free(newRoom);
                        }
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid room number!\n");
                    }
                }
                break;
            }

            case 5: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite != NULL) {
                    displayRoom(selectedSite);
                }
                break;
            }

            case 6: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite == NULL) break;

                if (selectedSite->room_first == NULL) {
                    printf("No rooms found in '%s'.\n", selectedSite->city);
                } else {
                    displayRoom(selectedSite);
                    int roomChoice;
                    printf("Enter the number (index) of the room to delete: ");
                    if (scanf("%d", &roomChoice) == 1) {
                        if (deleteRoom(selectedSite, roomChoice)) {
                            printf("Room deleted successfully.\n");
                        } else {
                            printf("Failed to delete room.\n");
                        }
                    } else {
                        while (getchar() != '\n');
                        printf("Invalid selection!\n");
                    }
                }
                break;
            }

            case 7:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    displayHotel(hotel);
                }
                break;

            case 8: {
                T_Site *selectedSite = selectSite(hotel);
                if (selectedSite != NULL) {
                    displaySite(selectedSite);
                }
                break;
            }

            case 9: {
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

            case 10: {
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

            case 11:
                if (hotel == NULL) {
                    printf("No hotel chain exists.\n");
                } else {
                    printf("Enter search criteria (Last Name prefix): ");
                    scanf(" %[^\n]", last_name);
                    searchClients(hotel, last_name);
                }
                break;

            case 12:

                if (hotel == NULL) {
                    printf("Please create a hotel chain first (Option 1).\n");
                } else {
                    processingfile(hotel);
                }
                break;
                

            case 13:
                printf("Saving data and exiting program...\n");
                if (hotel != NULL) {
                    saveData(hotel, "hotel_database.txt");

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

                        Room *currRoom = tempSite->room_first;
                        while (currRoom != NULL) {
                            Room *tempRoom = currRoom;
                            currRoom = currRoom->next;
                            free(tempRoom);
                        }

                        free(tempSite);
                    }
                    free(hotel);
                }
                return 0;

            default:
                printf("Invalid option! Please select 1-12.\n");
                break;
        }
    }

    return 0;
}
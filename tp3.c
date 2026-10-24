#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_Client *createClient(char *last_name, char *first_name, int age, int num_room) {
    T_Client *newClient = (T_Client *)malloc(sizeof(T_Client));
    if (!newClient) return NULL;

    strcpy(newClient->last_name, last_name);
    strcpy(newClient->first_name, first_name);
    newClient->age = age;
    newClient->num_room = num_room;
    newClient->next = NULL;

    return newClient;
}

T_Site *createSite(char *city) {
    T_Site *newSite = (T_Site *)malloc(sizeof(T_Site));
    if (!newSite) return NULL;

    strcpy(newSite->city, city);
    newSite->number_clients = 0;
    newSite->first = NULL;
    newSite->room_first = NULL;
    newSite->next = NULL;

    return newSite;
}

T_Hotel *createHotel(char *name) {
    T_Hotel *newHotel = (T_Hotel *)malloc(sizeof(T_Hotel));
    if (!newHotel) return NULL;

    strcpy(newHotel->name, name);
    newHotel->first = NULL;

    return newHotel;
}

Room *createRoom(int num) {
    Room *newRoom = (Room*)malloc(sizeof(Room));
    if (newRoom == NULL) return NULL;

    newRoom->num = num;
    newRoom->next = NULL;

    return newRoom;
}

int addClient(T_Site *site, T_Client *client) {
    if (site == NULL || client == NULL) return 0;

    if (site->first == NULL) {
        site->first = client;
        site->number_clients++;
        return 1;
    }

    if (strcmp(client->last_name, site->first->last_name) < 0 ||
        (strcmp(client->last_name, site->first->last_name) == 0 &&
        strcmp(client->first_name, site->first->first_name) < 0)) {
        client->next = site->first;
        site->first = client;
        site->number_clients++;
        return 1;
    }

    T_Client *current = site->first;
    while (current->next != NULL &&
        (strcmp(current->next->last_name, client->last_name) < 0 ||
        (strcmp(current->next->last_name, client->last_name) == 0 &&
        strcmp(current->next->first_name, client->first_name) < 0))) {
        current = current->next;
    }
    client->next = current->next;
    current->next = client;
    site->number_clients++;
    return 1;
}

int addSite(T_Hotel *hotel, T_Site *site) {
    if (hotel == NULL || site == NULL) return 0;

    if (hotel->first == NULL) {
        hotel->first = site;
        return 1;
    }

    if (strcmp(site->city, hotel->first->city) == 0) return 0;

    if (strcmp(site->city, hotel->first->city) < 0) {
        site->next = hotel->first;
        hotel->first = site;
        return 1;
    }

    T_Site *current = hotel->first;
    while (current->next != NULL && strcmp(current->next->city, site->city) < 0) {
        current = current->next;
    }

    if (current->next != NULL && strcmp(current->next->city, site->city) == 0) return 0;

    site->next = current->next;
    current->next = site;
    return 1;
}

int addRoom(T_Site *site, Room *room) {
    if (site == NULL || room == NULL) return 0;

    if (site->room_first == NULL) {
        site->room_first = room;
        return 1;
    }

    Room *temp = site->room_first;
    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = room;
    return 1;
}

int deleteClient(T_Site *site, int index) {
    if (site == NULL || site->first == NULL || index < 1) return 0;

    if (index == 1) {
        T_Client *temp = site->first;
        site->first = site->first->next;
        free(temp);
        site->number_clients--;
        return 1;
    }

    T_Client *curr = site->first;
    int count = 1;
    while (curr->next != NULL && count < index - 1) {
        curr = curr->next;
        count++;
    }

    if (curr->next == NULL) return 0;

    T_Client *temp = curr->next;
    curr->next = temp->next;
    free(temp);
    site->number_clients--;
    return 1;
}

int deleteSite(T_Hotel *hotel, int index) {
    if (hotel == NULL || hotel->first == NULL || index < 1) return 0;

    if (index == 1) {
        T_Site *temp = hotel->first;
        hotel->first = hotel->first->next;

        // Müştəriləri təmizləmək
        T_Client *clientCurr = temp->first;
        while (clientCurr != NULL) {
            T_Client *clientTemp = clientCurr;
            clientCurr = clientCurr->next;
            free(clientTemp);
        }

        // Otaqları təmizləmək
        Room *roomCurr = temp->room_first;
        while (roomCurr != NULL) {
            Room *roomTemp = roomCurr;
            roomCurr = roomCurr->next;
            free(roomTemp);
        }

        free(temp);
        return 1;
    }

    T_Site *curr = hotel->first;
    int count = 1;
    while (curr->next != NULL && count < index - 1) {
        curr = curr->next;
        count++;
    }

    if (curr->next == NULL) return 0;

    T_Site *temp = curr->next;
    curr->next = temp->next;

    T_Client *clientCurr = temp->first;
    while (clientCurr != NULL) {
        T_Client *clientTemp = clientCurr;
        clientCurr = clientCurr->next;
        free(clientTemp);
    }

    Room *roomCurr = temp->room_first;
    while (roomCurr != NULL) {
        Room *roomTemp = roomCurr;
        roomCurr = roomCurr->next;
        free(roomTemp);
    }

    free(temp);
    return 1;
}


void displayRoom(T_Site *site) {
    if (!site || !site->room_first) {
        printf("\nThere are no rooms available in this location!\n");
        return;
    }

    Room *temp = site->room_first;
    printf("\n%-5s %-15s\n", "No", "Room Number");
    printf("-------------------------\n");
    int index = 1;
    while (temp != NULL) {
        printf("%-5d %-15d\n", index++, temp->num);
        temp = temp->next;
    }
    printf("-------------------------\n");
}

int deleteRoom(T_Site *site, int index) {
    if (site == NULL || site->room_first == NULL || index < 1) return 0;

    if (index == 1) {
        Room *temp = site->room_first;
        site->room_first = site->room_first->next;
        free(temp);
        return 1;
    }

    Room *curr = site->room_first;
    int count = 1;
    while (curr->next != NULL && count < index - 1) {
        curr = curr->next;
        count++;
    }

    if (curr->next == NULL) return 0;

    Room *temp = curr->next;
    curr->next = temp->next;
    free(temp);
    return 1;
}

void displayHotel(T_Hotel *hotel) {
    if (!hotel || !hotel->first) {
        printf("\nThere is nothing to show!\n");
        return;
    }
    T_Site *temp = hotel->first;
    printf("\n%-20s %-20s\n", "City", "Number of customers");
    printf("-----------------------------------------\n");
    while (temp != NULL) {
        printf("%-20s %-20d\n", temp->city, temp->number_clients);
        temp = temp->next;
    }
    printf("-----------------------------------------\n");
}

void displaySite(T_Site *site) {
    if (!site || !site->first) {
        printf("\nThere is nothing to show!\n");
        return;
    }
    T_Client *temp = site->first;
    printf("\n%-15s %-15s %-10s %-10s\n", "Last Name", "First Name", "Age", "Room");
    printf("--------------------------------------------------\n");
    while (temp != NULL) {
        printf("%-15s %-15s %-10d %-10d\n", temp->last_name, temp->first_name, temp->age, temp->num_room);
        temp = temp->next;
    }
    printf("--------------------------------------------------\n");
}

void processingfile(T_Hotel *hotel) {
    if (hotel == NULL) return;

    FILE *file = fopen("bookings.txt", "r");
    if (file == NULL) return;

    char last_name[100];
    char first_name[100];
    int age;
    int num_room;
    char city[100];

    while (fscanf(file, " %99[^;]; %99[^;]; %d; %d; %99[^\n]", last_name, first_name, &age, &num_room, city) == 5) {

        T_Site *targetSite = NULL;
        T_Site *currSite = hotel->first;

        while (currSite != NULL) {
            if (strcmp(currSite->city, city) == 0) {
                targetSite = currSite;
                break;
            }
            currSite = currSite->next;
        }

        if (targetSite == NULL) {
            targetSite = createSite(city);
            if (targetSite != NULL) {
                addSite(hotel, targetSite);
            }
        }

        if (targetSite != NULL) {
            T_Client *newClient = createClient(last_name, first_name, age, num_room);
            if (newClient != NULL) {
                addClient(targetSite, newClient);
            }
        }
    }
    fclose(file);
}

void searchClients(T_Hotel *hotel, char *critereaName) {
    if (!hotel || !critereaName) {
        printf("Nothing to show!\n");
        return;
    }

    T_Site *temp = hotel->first;
    size_t len = strlen(critereaName);

    printf("\n%-15s %-15s %-10s %-10s %-15s\n", "Last Name", "First Name", "Age", "Room", "City");
    printf("-------------------------------------------------------------------\n");

    while (temp != NULL) {
        T_Client *temp2 = temp->first;
        while (temp2 != NULL) {
            if (strncmp(temp2->last_name, critereaName, len) == 0) {
                printf("%-15s %-15s %-10d %-10d %-15s\n",
                       temp2->last_name, temp2->first_name, temp2->age, temp2->num_room, temp->city);
            }
            temp2 = temp2->next;
        }
        temp = temp->next;
    }
    printf("-------------------------------------------------------------------\n");
}

void saveData(T_Hotel *hotel, const char *filename) {
    if (hotel == NULL) return;

    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "HOTEL;%s\n", hotel->name);

    T_Site *siteCurr = hotel->first;
    while (siteCurr != NULL) {
        fprintf(file, "SITE;%s\n", siteCurr->city);

        Room *roomCurr = siteCurr->room_first;
        while (roomCurr != NULL) {
            fprintf(file, "ROOM;%s;%d\n", siteCurr->city, roomCurr->num);
            roomCurr = roomCurr->next;
        }

        T_Client *clientCurr = siteCurr->first;
        while (clientCurr != NULL) {
            fprintf(file, "CLIENT;%s;%s;%s;%d;%d\n",
                    siteCurr->city, clientCurr->last_name, clientCurr->first_name,
                    clientCurr->age, clientCurr->num_room);
            clientCurr = clientCurr->next;
        }

        siteCurr = siteCurr->next;
    }

    fclose(file);
}

T_Hotel* loadData(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) return NULL;

    T_Hotel *hotel = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        char type[20];
        if (sscanf(line, "%19[^;]", type) != 1) continue;

        if (strcmp(type, "HOTEL") == 0) {
            char hname[100];
            if (sscanf(line, "HOTEL;%99[^\n]", hname) == 1) {
                hotel = createHotel(hname);
            }
        } else if (strcmp(type, "SITE") == 0 && hotel != NULL) {
            char city[100];
            if (sscanf(line, "SITE;%99[^\n]", city) == 1) {
                T_Site *s = createSite(city);
                addSite(hotel, s);
            }
        } else if (strcmp(type, "ROOM") == 0 && hotel != NULL) {
            char city[100];
            int rnum;
            if (sscanf(line, "ROOM;%99[^;];%d", city, &rnum) == 2) {
                T_Site *s = hotel->first;
                while (s && strcmp(s->city, city) != 0) s = s->next;
                if (s) {
                    Room *r = createRoom(rnum);
                    addRoom(s, r);
                }
            }
        } else if (strcmp(type, "CLIENT") == 0 && hotel != NULL) {
            char city[100], last[100], first[100];
            int age, rnum;
            if (sscanf(line, "CLIENT;%99[^;];%99[^;];%99[^;];%d;%d", city, last, first, &age, &rnum) == 5) {
                T_Site *s = hotel->first;
                while (s && strcmp(s->city, city) != 0) s = s->next;
                if (s) {
                    T_Client *c = createClient(last, first, age, rnum);
                    addClient(s, c);
                }
            }
        }
    }

    fclose(file);
    return hotel;
}
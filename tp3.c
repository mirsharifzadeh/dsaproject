//
// Created by HP-UFAZ on 20/10/2026.
//

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

int addClient(T_Site *site, T_Client *client) {
    if (site == NULL || client == NULL) {
        return 0;
    }

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
    if (hotel == NULL || site == NULL) {
        return 0;
    }

    if (hotel->first == NULL) {
        hotel->first = site;
        return 1;
    }

    if (strcmp(site->city, hotel->first->city) == 0) {
        return 0;
    }

    if (strcmp(site->city, hotel->first->city) < 0) {
        site->next = hotel->first;
        hotel->first = site;
        return 1;
    }

    T_Site *current = hotel->first;
    while (current->next != NULL && strcmp(current->next->city, site->city) < 0) {
        current = current->next;
    }

    if (current->next != NULL && strcmp(current->next->city, site->city) == 0) {
        return 0;
    }

    site->next = current->next;
    current->next = site;
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

        T_Client *clientCurr = temp->first;
        while (clientCurr != NULL) {
            T_Client *clientTemp = clientCurr;
            clientCurr = clientCurr->next;
            free(clientTemp);
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
//
// Created by HP-UFAZ on 20/10/2026.
//

#include "tp3.h"

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

int addClient(T_Site *site, T_Client *client){
    if(site == NULL || client == NULL){
        return 0;
    }

    if(site->first == NULL){
        site->first = client;
        site->number_clients++;

        return 1;
    }

    if (strcmp(client->last_name, site->first->last_name) < 0 || 
        (strcmp(client->last_name, site->first->last_name) == 0 &&
        strcmp(client->first_name, site->first->first_name) < 0)){
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
int deleteClient(T_Site *site, char *last_name, char *first_name) {
    if (site == NULL && site->first == NULL) return 0;

    T_Client *curr = site->first;
    T_Client *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->last_name, last_name) == 0 && strcmp(curr->first_name, first_name) == 0) {

            if (prev == NULL) {
                site->first = curr->next;
            } else {
                prev->next = curr->next;
            }

            free(curr->last_name);
            free(curr->first_name);
            free(curr);

            site->number_clients--;
            return 1;
            }
        prev = curr;
        curr = curr->next;
    }

    return 0;
}

int deleteSite(T_Hotel *hotel, char *city) {
    if (!hotel || !hotel->first) return 0;

    T_Site *curr = hotel->first;
    T_Site *prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->city, city) == 0) {

            if (prev == NULL) {
                hotel->first = curr->next;
            } else {
                prev->next = curr->next;
            }
            
            T_Client *clientCurr = curr->first;
            while (clientCurr != NULL) {
                T_Client *temp = clientCurr;
                clientCurr = clientCurr->next;
                free(temp->last_name);
                free(temp->first_name);
                free(temp);
            }

void displayHotel(T_Hotel *hotel){
    if(!hotel || !hotel->first){
        printf("There is nothing to show!");
        return;
    }
    struct T_Site* temp = hotel->first;
    printf("%-15s %-10d","City","Number of customers")
    while (temp != NULL) {
        printf("---------------------------------------------")
        printf("%-15s %-10d", temp->city,temp->number_clients);
        temp = temp->next;
    }
}
void displaySite(T_Site *site){
    if(!site || !site->first){
        printf("There is nothing to show!");
        return;
    }
    struct T_Client* temp = site->first;
    printf("%-15s %-15s %-10d %-10d","Last Name","First Name","Age","Room")
    while (temp != NULL) {
        printf("----------------------------------------------------------")
        printf("%-15s %-15s %-10d %-10d", temp->last_name,temp->first_name,temp->age,temp->num_room);
        temp = temp->next;
    }
}
    }
}
}

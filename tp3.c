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
    if (site == NULL || site->first == NULL) return 0;

    if (strcmp(site->first->last_name, last_name) == 0 &&
        strcmp(site->first->first_name, first_name) == 0) {
        T_Client *temp = site->first;
        site->first = site->first->next;
        free(temp);
        site->number_clients--;
        return 1;
        }

    T_Client *curr = site->first;
    while (curr->next != NULL) {
        if (strcmp(curr->next->last_name, last_name) == 0 &&
            strcmp(curr->next->first_name, first_name) == 0) {
            T_Client *temp = curr->next;
            curr->next = temp->next;
            free(temp);
            site->number_clients--;
            return 1;
            }
        curr = curr->next;
    }

    return 0;
}

int deleteSite(T_Hotel *hotel, char *city) {
    if (hotel == NULL || hotel->first == NULL) return 0;

    if (strcmp(hotel->first->city, city) == 0) {
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
    while (curr->next != NULL) {
        if (strcmp(curr->next->city, city) == 0) {
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
        curr = curr->next;
    }

    return 0;
}

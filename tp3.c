//
// Created by HP-UFAZ on 20/10/2026.
//

#include "tp3.h"
#include <stddef.h>
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
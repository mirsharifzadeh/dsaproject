//
// Created by HP-UFAZ on 20/10/2026.
//

#include "tp3.h"

<<<<<<< Updated upstream
=======
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

            free(curr->city);
            free(curr);
            return 1;
        }
        prev = curr;
        curr = curr->next;
    }

    return 0;
}
>>>>>>> Stashed changes

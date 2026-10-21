//
// Created by HP-UFAZ on 20/10/2026.
//

#ifndef DSAPROJECT_TP3_H
#define DSAPROJECT_TP3_H

// Structs

typedef struct Client {
    char last_name[30];
    char first_name[30];
    int age;
    int num_room;
    struct Client *next;
} T_Client;

typedef struct Site {
    char city[20];
    int number_clients;
    T_Client *first;
    struct Site *next;
} T_Site;

typedef struct Hotel {
    char name[30];
    T_Site *first;
} T_Hotel;

// Functions

T_Client *createClient(char *last_name, char *first_name, int age, int num_room);
T_Site *createSite(char *city);
T_Hotel *createHotel(char *name);

int addClient(T_Site *site, T_Client *client); // Returns 1 if successful, otherwise 0

int addSite(T_Hotel *hotel, T_Site *site); // Returns 1 if successful, otherwise 0

void displayHotel(T_Hotel *hotel);

void displaySite(T_Site *site);

int deleteClient(T_Site *site, int index);

int deleteSite(T_Hotel *hotel, int index);

void searchClients(T_Hotel *hotel, char *critereaName);

void processingfile(T_Hotel *hotel);

#endif //DSAPROJECT_TP3_H

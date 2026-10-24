#ifndef DSAPROJECT_TP3_H
#define DSAPROJECT_TP3_H

typedef struct Client {
    char last_name[30];
    char first_name[30];
    int age;
    int num_room;
    struct Client *next;
} T_Client;

typedef struct Room {
    int num;
    T_Client cur_client;
    struct Room *next;
} Room;

typedef struct Site {
    char city[20];
    int number_clients;
    T_Client *first;
    Room *room_first;
    struct Site *next;
} T_Site;

typedef struct Hotel {
    char name[30];
    T_Site *first;
} T_Hotel;

T_Client *createClient(char *last_name, char *first_name, int age, int num_room);
T_Site *createSite(char *city);
T_Hotel *createHotel(char *name);
Room *createRoom(int num);

int addClient(T_Site *site, T_Client *client);
int addSite(T_Hotel *hotel, T_Site *site);
int addRoom(T_Site *site, Room *room);

void displayHotel(T_Hotel *hotel);
void displaySite(T_Site *site);
void displayRoom(T_Site *site);

int deleteClient(T_Site *site, int index);
int deleteSite(T_Hotel *hotel, int index);
int deleteRoom(T_Site *site, int index);

void searchClients(T_Hotel *hotel, char *critereaName);
void processingfile(T_Hotel *hotel);

void saveData(T_Hotel *hotel, const char *filename);
T_Hotel* loadData(const char *filename);

#endif //DSAPROJECT_TP3_H
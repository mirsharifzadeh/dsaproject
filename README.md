# Hotel Management System (Singly Linked List Project)

This C program manages customers and sites locations for a hotel chain using Singly Linked Lists.

## Project Structure

* **`tp3.h`**: Header file containing data structure definitions (`T_Client`, `T_Site`, `T_Hotel`), constants, and function prototypes.
* **`tp3.c`**: Implementation of linked list operations, file processing, and search algorithms.
* **`main.c`**: Interactive command-line menu interface.

## Data Structures

1. **`T_Client`**: Standard node for a customer booking (last name, first name, age, room number, pointer to next client).
2. **`T_Site`**: Standard node for a hotel location (city name, client count, pointer to first client, pointer to next site).
3. **`T_Hotel`**: Head structure for the hotel chain (hotel chain name, pointer to first site).

## Features

- **Dynamic Insertion**: Maintains sorted order by city name for sites, and alphabetically by last name and first name for clients.
- **Safe Memory Deallocation**: Cascade deletion when removing a location or terminating the program.
- **File Processing**: Parses structured text files (`bookings.txt`) to automatically construct sites and client lists.
- **Prefix Search**: Finds and prints clients matching a last name prefix across all hotel sites.

# Hotel Management System (TP3 - Singly Linked List Project)

This repository contains a C application developed for the Data Structures & Algorithms module (TP3). The program manages hotel locations and customer bookings for a hotel chain using custom **Singly Linked Lists**.

---

## Project Structure

* **`tp3.h`**: Header file containing data structure definitions (`T_Client`, `T_Site`, `T_Hotel`), function prototypes, and standard libraries.
* **`tp3.c`**: Core implementation of node allocation, sorted insertions, memory cleanup, file parsing, and searching algorithms.
* **`main.c`**: Interactive menu-driven Command Line Interface (CLI) optimized for index-based user interaction.

---

## Data Structures

The system architecture uses a hierarchical, multi-level linked list design:

1. **`T_Client`**: Represents an individual customer booking.
   * Attributes: `last_name`, `first_name`, `age`, `num_room`, pointer to `next` client.
2. **`T_Site`**: Represents a hotel location in a specific city.
   * Attributes: `city`, `number_clients`, pointer to `first` client in the list, pointer to `next` site location.
3. **`T_Hotel`**: Head structure representing the overall hotel chain.
   * Attributes: `name` of the chain, pointer to `first` site location.

---

## Key Features & Highlights

### Index-Based Navigation & Deletion System (Major Usability Upgrade)
In standard implementations, operations like deleting a client or selecting a hotel site require typing exact string inputs (e.g., matching exact city names or full client names). This approach is error-prone, sensitive to capitalization, and inefficient for CLI users. 

To overcome these constraints, we integrated a **Numeric Indexing Interface**:
* **Interactive Selection (`selectSite`)**: Locations and clients are dynamically rendered as formatted, numbered tables (`1`, `2`, `3`...).
* **Typo-Proof Operations (`deleteClientByIndex`, `deleteSiteByIndex`)**: Users select items by simply typing their list number rather than re-entering full text strings.
* **Safer Edge-Case Handling**: Index validation eliminates silent failures caused by whitespace mismatches or case-sensitivity issues.

### Automatic Sorted Insertion
* **Site Sorting**: Hotel locations are automatically inserted and maintained in alphabetical order by city name.
* **Client Sorting**: Customer records are automatically organized alphabetically by `last_name`, and secondary-sorted by `first_name` if last names match.

### Automated File Processing
* Reads structured data from `cmake-build-debug/bookings.txt` (`LastName; FirstName; Age; RoomNumber; City`).
* Dynamically instantiates new site locations and client records on the fly while preserving sorted order.

### Prefix Search Engine
* Searches across the entire hotel network to find clients whose last names start with a given prefix substring.

### Robust Memory Management
* **Cascade Cleanup**: Deleting a site automatically frees all associated client records before releasing the site node.
* **Zero-Leak Guarantee**: Exiting the program (Option 9) triggers a full traversal to free all allocated heap space safely.

---

# C Utility Library

## Setup
To setup this library for the first time run the following command in a shell
```. setup.sh```

After that is run once you can ```make``` to rebuild it

## list.c
list.c contains a generic doubly linked list along with functions that convert a double into pointer/pointer to double. The most common functions are provided below, more functions are located in list/list.h
- list\_insert(list head, void \*val) -> Inserts a node in the linked list and returns the head, if head is NULL a new list is made
- list\_delete(list head, int index, list\_free del) -> Removes the ith node from the list and free's the data if del is not NULL
- list\_remove(list head, int index, void \*\*data) -> Removes the ith node from the list and returns it's value
- list\_delete\_all(list head, list\_free del) -> applies list\_delete on all list elements
- list\_contains(list head, void \*val, list\_comparator cmp) uses cmp to compare val to elements in the list and returns 1 if the item is in the list else it returns 0

## map.c
map.c contains a generic hash table along. The most common functions are provided below, more functions are located in map/map.h
- map_create(void (\*destruct)(void \*)) -> creates a new hash table. needs to be destroyed with map_destroy(map)
- map_put(map m, char \*key, void \*val) -> assigns val to a key in the hash table
- map_contains(map m, char \*key) -> checks if a key is in the hash table
- map_destroy(map m) -> destroys a hash table
- map_delete_key(map m, char \*key) -> removes a key from the table and deletes it's contents

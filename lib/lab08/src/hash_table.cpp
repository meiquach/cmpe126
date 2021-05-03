#include "../inc/hash_table.h"
#include<iostream>
#include <math.h>
namespace lab8{
    unsigned hash_table::hash_1(std::string to_hash) {
        // hash_2 Hashing Algorithm
        unsigned int hash = 5381;
        for(char c: to_hash){
            hash = ((hash << 5) + hash) + c;
        }
        return hash;
    }

    unsigned hash_table::hash_2(std::string to_hash) {
        // Hashing Algorithm
        unsigned int seed = 131;
        unsigned int hash = 0;
        for(char c: to_hash){
            hash = (hash * seed) + c;
        }
        return hash;
    }

    void hash_table::expand() {
        // Expand the hash table by a factor of 2 every time this function is called
        // Consider the table to be full at 70% of the largest max_size
        if (max_size == PRIMES[15])
            throw "Table full";

        // Keep track of the old array and size
        auto *prevTable = hash_table_array;
        unsigned prev_current_size = current_size;

        // Get the next max_size, create a new array with the new max_size, and reset the size
        for (unsigned PRIME : PRIMES)
            if (max_size < PRIME)
                max_size = PRIME;
        hash_table_array = new key_value[max_size];
        current_size = 0;

        // Each value must be reinserted since the new max_size changes the hash index
        for (unsigned i = 0; current_size < prev_current_size; i++)
            if (!prevTable[i].key.empty()) {
                insert(prevTable[i].key, prevTable[i].value);
            }

        delete[] prevTable;

    }

    hash_table::hash_table(char type) {
        /*
         * Define the probing technique
         * 'l': Linear probing
         *          hash_1() + attempt
         * 'q': Quadratic probing
         *          hash_1() + attempt^2
         * 'd': Double Probing
         *          hash_1() + attempt * hash_2()
         *
         * Create a hash table with an initial size of 100
         * attempt = number of collisions
         */
        if(type == 'l' || type == 'q' || type == 'd')
        {
            this->probing = type;
        }
        else
        {
            throw "Unidentified type";
        }
        key_value table[100];
        max_size = 100;
        hash_table_array = new key_value[max_size];
        current_size = 0;
    }

    hash_table::~hash_table() {
        delete[] hash_table_array;
    }

    bool hash_table::insert(std::string key, int value) {
        // Insert a key according to the defined probing technique
        // If you run into an issue where you get an infinite collision loop,
        //   figure out a way to get out of the loop.
        if (key.empty())
            throw "key is empty";
        if (value == 0)
            throw "value is 0";

        unsigned hash1 = hash_1(key);
        for (unsigned attempt = 0; attempt < max_size; attempt++) {
            unsigned index;
            switch (probing) {
                case 'l':
                    index = (hash1 + attempt) % max_size;
                    break;
                case 'q':
                    index = (hash1 + unsigned(pow(attempt, 2))) % max_size;
                    break;
                case 'd':
                    index = (hash1 + attempt * hash_2(key)) % max_size;
                    break;
            }

            if (hash_table_array[index].key.empty()) {
                hash_table_array[index].key = key;
                hash_table_array[index].value = value;
                current_size++;

                if (current_size >= max_size * 0.7)
                    expand(); //table reaches 70% of the maxsize
                return true;
            }
            else if (hash_table_array[index].key == key)
                return false;
        }
        return true;
    }

    bool hash_table::in_table(std::string key){
        // Checks to see if that key is in the table.
        // Use the specified probing technique
        // Keep collisions in mind
        unsigned hash1 = hash_1(key);
        for (unsigned attempt = 0; attempt < max_size; attempt++) {
            unsigned index;
            switch (probing) {
                case 'l':
                    index = (hash1 + attempt) % max_size;
                    break;
                case 'q':
                    index = (hash1 + unsigned(pow(attempt, 2))) % max_size;
                    break;
                case 'd':
                    index = (hash1 + attempt * hash_2(key)) % max_size;
                    break;
            }

            if (hash_table_array[index].key == key) //find key
                return true;
            else if (attempt >= max_size)
                return false;
            if (key.empty())
                throw "Missing key value";
        }
    }

    int hash_table::get(std::string key) {
        // Get the int value from the node that has key
        // Use the specified probing technique
        if(current_size ==0) //check when table empty
            throw "Missing key value";

        unsigned hash1 = hash_1(key);
        for (unsigned attempt = 0; attempt < max_size; attempt++) {
            unsigned index;
            switch (probing) {
                case 'l':
                    index = (hash1 + attempt) % max_size;
                    break;
                case 'q':
                    index = (hash1 + unsigned(pow(attempt, 2))) % max_size;
                    break;
                case 'd':
                    index = (hash1 + attempt * hash_2(key)) % max_size;
                    break;
            }

            if (hash_table_array[index].key == key)
                return hash_table_array[index].value;
        }
        return 0;
    }

    void hash_table::update(std::string key, int value){
        // Update a key in the hash table.
        // Keep collisions in mind
        // Use the specified probing technique
        if (key.empty())
            throw "key is empty";
        if (value == 0)
            throw "value is 0";

        unsigned hash1 = hash_1(key);
        for (unsigned attempt = 0; attempt < max_size; attempt++) {
            unsigned index;
            switch (probing) {
                case 'l':
                    index = (hash1 + attempt) % max_size;
                    break;
                case 'q':
                    index = (hash1 + unsigned(pow(attempt, 2))) % max_size;
                    break;
                case 'd':
                    index = (hash1 + attempt * hash_2(key)) % max_size;
                    break;
            }

            if (hash_table_array[index].key == key) {
                hash_table_array[index].value = value;
                return;
            }
        }
        insert(key, value);
    }

    void hash_table::remove(std::string key){
        // Remove an item from the hash table. Keep collisions in mind
        // Use the specified probing technique
        // If the item isn't in the table, do nothing.
        if (key.empty())
            throw "key is empty";

        unsigned hash1 = hash_1(key);
        for (unsigned attempt = 0; attempt < max_size; attempt++) {
            unsigned index;
            switch (probing) {
                case 'l':
                    index = (hash1 + attempt) % max_size;
                    break;
                case 'q':
                    index = (hash1 + unsigned(pow(attempt, 2))) % max_size;
                    break;
                case 'd':
                    index = (hash1 + attempt * hash_2(key)) % max_size;
                    break;
            }

            if (hash_table_array[index].key == key) {
                hash_table_array[index].key.clear();
                hash_table_array[index].value = 0;
                current_size--;

                return;
            } else if (attempt >= max_size)
                return;
        }
    }

    std::string hash_table::to_string(){
        // Run through the entire array and create a string following this format. The {} brackets aren't part of the return
        // [{array location}]{key_value.key}:{key_value.int}
        std::string string;
        for (unsigned i = 0; i < max_size; i++)
            if (!hash_table_array[i].key.empty()) string += "[" + std::to_string(i) + "]" + hash_table_array[i].key + ":" + std::to_string(hash_table_array[i].value) + "\n";
        return string;
    }
}

#include <bits/stdc++.h>

using namespace std;

/***
 * HashTable goal: We want to perform search, insert and delete in O(1)
 * First idea:
 * Direct access table: using the key directly access an entry in the array/table
 * but what if the universe of keys is very large, a huge table will result!!!
 * Second idea:
 * Compress the universe of keys since the actual keys count are not equal to the universe count
 * Imagine an ID: 12345678911 this doesn't mean that there exists 12 Billion users
 * so we can compress this number to a smaller number that can correspond to an entry in
 * a table. The hashing reduces the needed table size.
 * Problem now what if two keys are hashed and results the same hash value?
 * A collision resolution is required.
 * Two methods:
 * - Chaining
 * - Open addressing
 * The goal of hash function is to minimize the collisions as much as possible
 * Example of hash functions:
 * - k mod m, where m has to be a prime why?
 *   because prime numbers results in distributed remainders in a good way that can reduce collisions
 * - multiplication method
 * Chaining Collision resolution:
 * The idea is to hash a key and insert the value in the entry corresponding to the key
 * what if collision:
 * Chain, which means chain the nodes in a linked list so that for each entry there exists
 * a linked list for the nodes.
 *
 * The disadvantage of this method is that if the hash function has bad distribution
 * this may result in having a single or two entries having long chain of linked list
 * which can cause costly operations of order O(n) which contradicts with the main goal
 * of hash table.
 *
 * important term "Load factor"
 * the load factor shows the number of nodes on average in an entry linked list.
 * load factor alpha = n/m where n is number of nodes and m is the table size.
 * so that the complexity of hash table operations become O(1 + alpha)
 *
 * Open addressing collision resolution:
 * No linked lists.
 * Just hash a key and insert in the corresponding entry
 * if entry is busy
 * hash again using example (iteration*key) mod m
 * and probe (test) again the other location.
 * If empty ok.
 *
 * For search:
 * Perform like insert until you find the entry with the intended key.
 * If you reached Null/Nil this means that the key is not found XD.
 *
 * For delete:
 * remove the entry and mark with a special flag to avoid
 * "If we delete an element while there are elements inserted after it, we
 *  can’t search after deletion because the element is marked as nil"
 *
 * Open addressing can have a size for the entry.
 * Which means that the entry is now a bucket that has multiple entries
 * which can help to reduce collision resolution need and improve performance.
 */
struct LinkedListNode {
    int value;
    LinkedListNode *next = NULL;

    LinkedListNode(int value) : value(value) {}
};

struct HashTableEntry {
    LinkedListNode *head = NULL;
};

class HashTable {
private:
    const int size;
    vector<HashTableEntry> table;

    int hash(int key) {
        return key % size;
    }

    bool isEmpty(int index) {
        return table[index].head == NULL;
    }

public:
    HashTable(int size) : size(size) {
        table = vector<HashTableEntry>(size);
    }

    bool isFound(int value) {
        int hashVal = hash(value);
        LinkedListNode *curr = table[hashVal].head;
        while (curr && curr->value != value) {
            curr = curr->next;
        }
        if (curr == NULL) {
            return false;
        }
        return true;
    }

    bool insert(int value) {
        int hashVal = hash(value);
        LinkedListNode *entry = new LinkedListNode(value);
        if (isEmpty(hashVal)) {
            table[hashVal].head = entry;
            return true;
        }
        LinkedListNode *curr = table[hashVal].head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = entry;
        return true;
    }

    bool remove(int value) {
        int hashVal = hash(value);

        LinkedListNode *curr = table[hashVal].head;
        LinkedListNode *prev = NULL;

        while (curr && curr->value != value) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            return false;
        }
        if(prev==NULL){
            table[hashVal].head=curr->next;
        }else{
            prev->next = curr->next;
        }
        delete curr;
        return true;
    }

    ~HashTable(){
        for(auto linkedList:table){
            LinkedListNode* curr = linkedList.head;
            while(curr){
                LinkedListNode* tmp = curr;
                curr = curr->next;
                delete tmp;
            }
        }
    }

};

//int main() {
//    HashTable table(13);
//    cout<<table.isFound(5)<<endl;
//    table.insert(5);
//    cout<<table.isFound(5)<<endl;
//    table.insert(13*5);
//    table.insert(13*13*5);
//    cout<<table.isFound(13*5)<<endl;
//    cout<<table.isFound(13*13*5)<<endl;
//    cout<<table.remove(13*5)<<endl;
//    cout<<table.isFound(13*5)<<endl;
//    cout<<table.isFound(13*13*5)<<endl;
//    return 0;
//}
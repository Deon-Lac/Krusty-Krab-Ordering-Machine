#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
using namespace std;

template <class t1, class t2>
class hashMap
{
public:
    hashMap();
    t2 &operator[](t1);

private:
    void resize(int);
    int hashFunction(string);
    struct keyVal
    {
        t1 key;
        t2 value;
    };
    static const int MAX_COLLISIONS = 5;
    int filledEntries;
    vector< list<keyVal> > table;
};

//Resize Function
template <class t1, class t2>
void hashMap<t1,t2>::resize(int resize) {
    
    
    //keeps old size of map
    int prevSize = table.size();

    //creates new size w/ resize amount
    int newSize = resize+table.size();

    //creates temp of old table
    vector<list<keyVal> > tempTable = table;

    

    //resize old map
    table.resize(newSize, list<keyVal>{});
    
    //resets filled entries
    filledEntries = 0;

    for (int i = 0 ; i < prevSize; i++)
    {   
        for (auto it = table[i].begin(); it != table[i].end(); it++)
        {
            if ((*it).value != t2())
            {
               (*this)[(*it).key] = (*it).value;
            }
        }
    }

    }


//hash function
template <class t1, class t2>
int hashMap<t1,t2>::hashFunction(string key){
    
    hash <string> result ;
    return result (key);
}

// constructor
template <class t1, class t2>
hashMap<t1, t2>::hashMap()
{
    // sets filled entries to 0 and tablesize to 5
    filledEntries = 0;
    table.resize(5);
}


// bracket operator
template <class t1, class t2>
t2 &hashMap<t1, t2>::operator[](t1 key)
{

    // checks load factor
    if (filledEntries / table.size() >= .2)
    {
        resize(table.size());
    }

    int i = hashFunction(key) % table.size();


    while (true)
    {

        for (auto it = table[i].begin(); it != table[i].end(); it++)
        {
            // checks if key is equal to passed in key
            if ((*it).key == key)
            {
                return (*it).value;
            }
        }

            table[i].push_back(keyVal{key, t2()});

            // returns the first element
            return table[i].front().value;

        // if key wasnt found
        if (table[i].size() != MAX_COLLISIONS)
        {
            auto it2 = table[i].begin();
            it2++;

            // tries to find the index where the key should belong
            while (it2 != table[i].end() && (*it2).key < key)
            {
                it2++;
            }

            // insert element at correct spot
            table[i].insert(it2, {key, t2()});
            
            // for returning purposes
            it2--;

            // checks if after the insert we made the table 5
            if (table[i].size() == MAX_COLLISIONS)
            {
                filledEntries++;
            }

            return (*it2).value;
        }
        //goes to next element
        else
        {
            i = (i + 1) % table.size();
        }
    }
}
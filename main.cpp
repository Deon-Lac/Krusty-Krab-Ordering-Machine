
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "hashmap.h"

using namespace std;

struct menuType
{
    menuType() : price(0.0), quantity(0)
    {
    }
    menuType(double p, int q) : price(p), quantity(q)
    {
    }
    // operator used in the hashMap :: resize (int ) function
    // that is used to determine if a node ’s value is not 2
    // an empty entry
    bool operator!=(const menuType &m)
    {
        return quantity != m.quantity && price != m.price;
    }
    int quantity;
    double price;
};

int main()
{

    //fstream variables
    ifstream iFile;
    string fName;
    vector<string> itemNames;
    hashMap <string, menuType> krustyKrabMenu; 

    //asks user for input
    cout << "Enter krusty krab menu:";
    cin >> fName;

    // Checks validity of input
    iFile.open(fName);
    while (!iFile.is_open())
    {
        cout << "\nEnter krusty krab menu:";
        cin >> fName;
        iFile.open(fName);
    }
    
    // temp in order to hold item name
    string temp = " ";
    double totalCost = 0;

    // Prints out top portion
    // cout << left << setw(28) << "Item Name"  << right  << setw(10) << "Price"  << setw(11) << right << "Quantity\n";

    // Reads in file, while also printing out Table
    for (unsigned int i = 0; i < 29; i++)
    {
        iFile >> temp;
        itemNames.push_back(temp);

        // converts to all lowercase
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

        //stores price and quantity
        krustyKrabMenu[temp];
        iFile >> krustyKrabMenu[temp].price >> krustyKrabMenu[temp].quantity;

    }

    //temps for user input
    string input = "  ";
    int quantity = 0;
    double runningCost = 0.0;

    do
    {
        // ouputs header
        cout << left << setw(28) << "Item Name" << right << setw(10) << "Price" << setw(11) << right << "Quantity\n";

        // outputs items only if there is more than 1 quantity
        for (unsigned int i = 0; i < 29; i++)
        {
            // checks quantity
            string temp = itemNames[i];
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            if (krustyKrabMenu[temp].quantity >= 1)
            {
                cout << fixed << setprecision(2) << left << setw(28) << itemNames[i]
                     << setw(10) << right << krustyKrabMenu[temp].price
                     << setw(10) << right << krustyKrabMenu[temp].quantity << endl;
            }
        }
        do
        {
            //asks for user input
            cout << "\nAre you going to order today, sir? ";
            cin >> input;

            // tolowers input
            transform(input.begin(), input.end(), input.begin(), ::tolower);

            // checks if item exists and its value isnt 0
            if (krustyKrabMenu[input].price == 0 || krustyKrabMenu[input].quantity == 0)
            {
                cout << "We serve food here, sir\n";
                cin.clear();
                cin.ignore(100, '\n');
            }

        } while (krustyKrabMenu[input].price == 0 || krustyKrabMenu[input].quantity == 0);

        // outputs valid promp
        cout << "Great, excellent choice\nHow many?";

        do
        {
            // asks for quantity input
            cin >> quantity;

            // checks validity of quantity
            if (krustyKrabMenu[input].quantity < quantity)
            {
                // outputs error message
                cout << "Try again: ";
                cin.clear();
                cin.ignore(100, '\n');
            }

        } while (krustyKrabMenu[input].quantity < quantity);

        // outputs well done message
        cout << " Well done, took you long enough\n";

        // subtracts the quantity
        krustyKrabMenu[input].quantity -= quantity;

        // updates running cost
        runningCost += (krustyKrabMenu[input].price * quantity);

        // checks if theres still items on the menu
        bool checker = true;
        for (unsigned int i = 0; i < itemNames.size(); i++)
        {
            string temp = itemNames[i];
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);

            //checks if the quantity is 0
            if (krustyKrabMenu[temp].quantity == 0)
            {
                continue;
            }
            //breaks out if anything else
            else {
                checker = false;
                break;
            }
        }

        // if no items are left on the menu
        if (checker == true)
        {
            cout << "Looks like you ordered everything on the menu, you know what that means\n";
            break;
        }

        // asks if the user wants
        cout << "Will this complete your order?\n";
        cin >> input;
    
    } while (input.size() == 1 && (input[0] == 'N' || input[0] == 'n'));


    //prints total
    cout << "Your order comes out to $" << runningCost << endl;
    cout << "\n\nHave a great day...barnacle head\n";
    return 0;
}

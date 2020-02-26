#include "BookStoreManagement.h"
#include <iostream>

using namespace std;

void PrintZerothMenu(bool allowOtherOptions = false)
{
    cout << "------------------------------" << endl;
    cout << "Enter Option : " << endl;
    cout << "0. Exit store" << endl;
    cout << "1. Add book to store" << endl;
    if (allowOtherOptions)
        cout << "2. Display full menu" << endl;
}

void PrintFirstMenu()
{
    cout << "------------------------------" << endl;
    cout << "Enter Option : " << endl;
    cout << "0. Exit store" << endl;
    cout << "1. Display books in store" << endl;
    cout << "2. Search book in store" << endl;
    cout << "3. Buy book in store" << endl;
}

int main()
{
    int option = 1;
    BookStore * pBookStore = BookStore::CreateInstance();
    while (option)
    {
        option = 0;
        PrintZerothMenu(!pBookStore->IsEmptyInventory());
        cin >> option;
        switch (option)
        {
        case 0:
            break;
        case 1:
            pBookStore->AddBook();
            break;
        case 2:
            if (!pBookStore->IsEmptyInventory())
                break;
        default:
            cout << "Invalid option" << endl;
        }
        if (option == 2 && !pBookStore->IsEmptyInventory())
            break;
    }
    pBookStore->FinalizeAdd(); // mem management
    while (option)
    {
        option = 0;
        PrintFirstMenu();
        cin >> option;
        switch (option)
        {
        case 0:
            break;
        case 1:
            pBookStore->DisplayBooks();
            break;
        case 2:
            pBookStore->SearchBook();
            break;
        case 3:
            pBookStore->BuyBook();
            break;
        default:
            cout << "Invalid option" << endl;
        }
    }
    pBookStore->DeleteInstance();
    cout << "Exiting..." << endl;
}

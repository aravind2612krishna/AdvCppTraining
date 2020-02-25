#include "BookStoreManagement.h"
#include <iostream>

using namespace std;

void PrintFirstMenu()
{
    cout << "------------------------------" << endl;
    cout << "Enter Option : " << endl;
    cout << "0. Exit store" << endl;
    cout << "1. Add book to store" << endl;
    cout << "2. Display books in store" << endl;
    cout << "3. Search book in store" << endl;
    cout << "4. Buy book in store" << endl;
}

int main()
{
    int option = 1;
    BookStore * pBookStore = BookStore::CreateInstance();
    while (option)
    {
        option = 0;
        PrintFirstMenu();
        cin >> option;
        switch (option)
        {
        case 1:
            pBookStore->AddBook();
            break;
        case 2:
            pBookStore->DisplayBooks();
            break;
        case 3:
            pBookStore->SearchBook();
            break;
        case 4:
            pBookStore->BuyBook();
            break;
        case 0:
            break;
        default:
            cout << "Invalid option" << endl;
        }
    }
    pBookStore->DeleteInstance();
    cout << "Exiting..." << endl;
}

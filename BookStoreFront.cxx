#include "BookStoreManagement.h"
#include <iostream>

void PrintFirstMenu()
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "Enter Option : " << std::endl;
    std::cout << "0. Exit store" << std::endl;
    std::cout << "1. Add book to store" << std::endl;
    std::cout << "2. Display books in store" << std::endl;
    std::cout << "3. Search book in store" << std::endl;
}

int main()
{
    int option = 1;
    BookStore * pBookStore = BookStore::CreateInstance();
    while (option)
    {
        option = 0;
        PrintFirstMenu();
        std::cin >> option;
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
        case 0:
            break;
        default:
            std::cout << "Invalid option" << std::endl;
        }
    }
    pBookStore->DeleteInstance();
    std::cout << "Exiting..." << std::endl;
}

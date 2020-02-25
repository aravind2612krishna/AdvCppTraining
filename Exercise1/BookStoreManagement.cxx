#include "BookStoreManagement.h"
#include <iostream>

using namespace std;

BookStore * BookStore::s_pSingleStore = nullptr;

BookStore * BookStore::CreateInstance()
{
    if (s_pSingleStore == nullptr)
        s_pSingleStore = new BookStore;
    return s_pSingleStore;
}

void BookStore::DeleteInstance() { delete s_pSingleStore; }

void BookStore::AddBook()
{
    string bookName;
    int         bookType = 1;
    unsigned    bookStock = 1;
    double      bookCost = 0.0;

    cout << "Enter name of Book :" << endl;
    cin >> bookName;
    cout << "Enter type of Book, 1. Technical, 2. Management :" << endl;
    cin >> bookType;
    cout << "Enter cost of " << bookName << endl;
    cin >> bookCost;
    cout << "Enter stock of " << bookName << " to be added :" << endl;
    cin >> bookStock;
    cout << "------------------------------" << endl << endl << endl;

    if (bookType > 2)
        bookType = 2; // TODO Print message
    if (bookType < 1)
        bookType = 1; // TODO Print message
    --bookType;

    if (bookStock > 0)
        P_AddBook(bookName, bookStock, bookCost, (Book::Type)(bookType));
    else
        cout << "0 stock book not added" << endl;
}

void BookStore::DisplayBooks() const
{
    if (p_bookInventory.size() == 0)
        cout << "No books in catalogue..." << endl;
    else
    {
        for (auto & detailedBook : p_bookInventory)
            detailedBook.Display();
    }
}

void BookStore::SearchBook() const
{
    string bookName;
    unsigned    bookStock = 1;
    if (p_bookInventory.size() == 0)
    {
        cout << "No books in catalogue" << endl;
        return;
    }

    cout << "Enter name of Book :" << endl;
    cin >> bookName;
    cout << "Enter stock of " << bookName << " needed :" << endl;
    cin >> bookStock;
    cout << "------------------------------" << endl << endl << endl;

    auto citer = p_bookInventory.cbegin();
    for (; citer != p_bookInventory.cend(); ++citer)
    {
        if (citer->GetBook()->GetName() == bookName)
            break;
    }
    if (citer == p_bookInventory.cend())
        cout << "Book " << bookName << " not found!" << endl;
    else
    {
        if (citer->GetStock() < bookStock)
            cout << "Book " << bookName << " - insufficient stock found." << endl;
        else
            cout << "Book " << bookName << " available. Price for " << bookStock << " is "
                      << citer->GetPrice(bookStock) << endl;
    }
}

void BookStore::BuyBook()
{
    string bookName;
    unsigned    bookStock = 1;
    if (p_bookInventory.size() == 0)
    {
        cout << "No books in catalogue" << endl;
        return;
    }

    cout << "Enter name of Book :" << endl;
    cin >> bookName;

    auto iter = p_bookInventory.begin();
    for (; iter != p_bookInventory.end(); ++iter)
    {
        if (iter->GetBook()->GetName() == bookName)
            break;
    }
    if (iter == p_bookInventory.end())
        cout << "Book " << bookName << " not found!" << endl;
    else
    {
        cout << "Enter stock of " << bookName << " needed :" << endl;
        cin >> bookStock;
        cout << "------------------------------" << endl << endl << endl;
        if (iter->GetStock() < bookStock)
            cout << "Book " << bookName << " - insufficient stock found." << endl;
        else
        {
            cout << "Book " << bookName << " available. Price for " << bookStock << " is "
                      << iter->GetPrice(bookStock) << endl;
            char answer = 'y';
            cout << "Buy? (y/n)" << endl;
            cin >> answer;
            if (answer == 'y')
            {
                iter->RemoveStock(bookStock);
                cout << bookStock << " " <<  bookName << " books bought" << endl;
                if (iter->GetStock() == 0)
                    p_bookInventory.erase(iter);
            }
        }
    }
}

void BookStore::P_AddBook(const string & bookName,
                          unsigned            bookStock,
                          double              bookCost,
                          Book::Type          type)
{
    auto iter = p_bookInventory.begin();
    for (; iter != p_bookInventory.end(); ++iter)
    {
        if (iter->GetBook()->GetName() == bookName)
            break;
    }
    if (iter == p_bookInventory.end())
    {
        cout << "Adding book " << bookName << endl;
        p_bookInventory.emplace_back(bookName, bookStock, bookCost, type);
    }
    else
    {
        cout << "Adding " << bookStock << " to existing book " << bookName << endl;
        iter->AddStock(bookStock);
    }
}

BookDetailed::BookDetailed(const string & bookName,
                           unsigned            bookStock,
                           double              bookPrice,
                           Book::Type          bookType)
{
    if (bookType == Book::Technical)
        p_pBook = new TechnicalBook(bookName, bookPrice);
    else // if (bookType == Book::Management)
        p_pBook = new ManagementBook(bookName, bookPrice);
    p_stock = bookStock;
}

void BookDetailed::Display() const
{
    cout << "Name : " << p_pBook->GetName() << "; Stock : " << p_stock << endl;
}

bool BookDetailed::operator==(const BookDetailed & other) const
{
    return p_pBook == other.GetBook();
}

double BookDetailed::GetPrice(unsigned quantity) const
{
    return quantity * p_pBook->GetCost();
}

double TechnicalBook::GetCost() const
{
    return (1.0 - p_discount) * Book::GetCost();
}

double ManagementBook::GetCost() const
{
    return (1.0 - p_discount) * Book::GetCost();
}

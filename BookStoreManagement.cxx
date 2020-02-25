#include "BookStoreManagement.h"
#include <iostream>

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
    std::string bookName;
    int         bookType = 1;
    unsigned    bookStock = 1;
    double      bookCost = 0.0;

    std::cout << "Enter name of Book :" << std::endl;
    std::cin >> bookName;
    std::cout << "Enter type of Book, 1. Technical, 2. Management :" << std::endl;
    std::cin >> bookType;
    std::cout << "Enter cost of " << bookName << std::endl;
    std::cin >> bookCost;
    std::cout << "Enter stock of " << bookName << " to be added :" << std::endl;
    std::cin >> bookStock;
    std::cout << "------------------------------" << std::endl << std::endl << std::endl;

    if (bookType > 2)
        bookType = 2; // TODO Print message
    if (bookType < 1)
        bookType = 1; // TODO Print message
    --bookType;

    if (bookStock > 0)
        P_AddBook(bookName, bookStock, bookCost, (Book::Type)(bookType));
    else
        std::cout << "0 stock book not added" << std::endl;
}

void BookStore::DisplayBooks() const
{
    if (p_bookInventory.size() == 0)
        std::cout << "No books in catalogue..." << std::endl;
    else
    {
        for (auto & detailedBook : p_bookInventory)
            detailedBook.Display();
    }
}

void BookStore::SearchBook() const
{
    std::string bookName;
    unsigned    bookStock = 1;

    std::cout << "Enter name of Book :" << std::endl;
    std::cin >> bookName;
    std::cout << "Enter stock of " << bookName << " needed :" << std::endl;
    std::cin >> bookStock;
    std::cout << "------------------------------" << std::endl << std::endl << std::endl;

    auto iter = p_bookInventory.begin();
    for (; iter != p_bookInventory.end(); ++iter)
    {
        if (iter->GetBook()->GetName() == bookName)
            break;
    }
    if (iter == p_bookInventory.end())
        std::cout << "Book " << bookName << " not found!" << std::endl;
    else
    {
        if (iter->GetStock() < bookStock)
            std::cout << "Book " << bookName << " - insufficient stock found." << std::endl;
        else
            std::cout << "Book " << bookName << " available. Price for " << bookStock << " is "
                      << iter->GetPrice(bookStock) << std::endl;
    }
}

void BookStore::P_AddBook(const std::string & bookName,
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
        BookDetailed bookDetailed(bookName, bookStock, bookCost, type);
        std::cout << "Adding book " << bookDetailed.GetBook()->GetName() << std::endl;
        p_bookInventory.push_back(std::move(bookDetailed));
    }
    else
    {
        std::cout << "Adding " << bookStock << " to existing book " << bookName << std::endl;
        iter->AddStock(bookStock);
    }
}

BookDetailed::BookDetailed(const std::string & bookName,
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
    std::cout << "Name : " << p_pBook->GetName() << "; Stock : " << p_stock << std::endl;
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

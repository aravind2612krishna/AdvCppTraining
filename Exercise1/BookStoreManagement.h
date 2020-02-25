#include <list>
#include <string>

class Book
{
public:
    enum Type
    {
        Technical = 0,
        Management
    };
    Book() : Book("Placeholder name", 0.0) {}
    Book(const std::string & name, const double & cost) : p_name(name), p_cost(cost) {}
    Book(const Book & otherBook) = default;

    const std::string & GetName() const { return p_name; }
    virtual double      GetCost() const { return p_cost; }

private:
    std::string p_name;
    double p_cost;
};

class TechnicalBook : public Book
{
public:
    TechnicalBook(const std::string & name, const double & cost) : Book(name, cost) {}
    virtual double GetCost() const;

private:
    static constexpr const double p_discount = 0.05;
};

class ManagementBook : public Book
{
public:
    ManagementBook(const std::string & name, const double & cost) : Book(name, cost) {}
    virtual double GetCost() const;

private:
    static constexpr const double p_discount = 0.1;
};

class BookDetailed
{
public:
    BookDetailed(const std::string & bookName,
                 unsigned            bookStock,
                 double     bookCost = 0.0, // workaround for search. Only because of enforcing list
                 Book::Type bookType = Book::Technical);
    BookDetailed(const BookDetailed & otherBookDetailed) = delete;
    BookDetailed(BookDetailed && otherBookDetailed)
    {
        p_pBook = otherBookDetailed.p_pBook;
        p_stock = otherBookDetailed.p_stock;
        otherBookDetailed.p_pBook = nullptr;
    }
    ~BookDetailed() { if (p_pBook) delete p_pBook; }
    unsigned     GetStock() const { return p_stock; }
    const Book * GetBook() const { return p_pBook; }
    // additional methods used from given design
    void   Display() const;
    bool   operator==(const BookDetailed & other) const;
    void   AddStock(unsigned stock) { p_stock += stock; }
    void   RemoveStock(unsigned stock) { p_stock -= stock; }
    double GetPrice(unsigned quantity) const;

private:
    Book *   p_pBook;
    unsigned p_stock;
};

class BookStore
{
public:
    static BookStore * CreateInstance();
    static void        DeleteInstance();
    void               AddBook();
    void               DisplayBooks() const;
    void               SearchBook() const;
    void               BuyBook();

private:
    BookStore() {}
    std::string             p_name;
    std::list<BookDetailed> p_bookInventory;
    static BookStore *      s_pSingleStore;

private:
    static BookStore * P_CreateInstance();
    void               P_AddBook(const std::string & bookName,
                                 unsigned            bookStock,
                                 double              bookCost = 0.0,
                                 Book::Type          type = Book::Technical);
    void P_SearchBook(const Book & bookDetailed);
};

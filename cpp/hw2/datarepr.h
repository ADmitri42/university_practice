//
// Created by Dima on 09.10.2019.
//

#ifndef HW2_DATAREPR_H
#define HW2_DATAREPR_H

#include <vector>
#include <string>
#include <fstream>

typedef struct {
    std::string first_name;
    std::string last_name;
    std::string patronymic;
} Name;

bool operator<(const Name&, const Name&);
bool operator>(const Name&, const Name&);
bool operator==(const Name&, const Name&);
bool operator<=(const Name&, const Name&);
bool operator>=(const Name&, const Name&);

class Book;

bool operator<(const Book& book1, const Book& book2);
bool operator>(const Book& book1, const Book& book2);
bool operator==(const Book& book1, const Book& book2);
bool operator<=(const Book& book1, const Book& book2);
bool operator>=(const Book& book1, const Book& book2);

std::ostream& operator<<(std::ostream& os, const Book& dt);

class Book{
private:
    Name author_name;
    std::string book_name;
    int pubyear;
    int n_pages;

public:
    Book(Name &author, std::string &book_name_, int year, int pages);
    friend bool operator<(const Book& book1, const Book& book2);
    friend bool operator>(const Book& book1, const Book& book2);
    friend std::ostream& operator<<(std::ostream& os, const Book& dt);
};

std::vector<Book> read_csv(std::string filename);

#endif //HW2_DATAREPR_H

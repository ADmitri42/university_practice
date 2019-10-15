//
// Created by Dima on 09.10.2019.
//
#include "datarepr.h"
#include <sstream>
//#include <iostream>


bool operator<(const Name& name1, const Name& name2){
    if(name1.last_name < name2.last_name){
        return true;
    } else if(name1.last_name == name2.last_name){
        if(name1.first_name < name2.first_name){
            return true;
        } else if(name1.first_name == name2.first_name){
            return name1.patronymic < name2.patronymic;
        }else{
            return false;
        }
    }
    return false;
}

bool operator>(const Name& name1, const Name& name2){
    if(name1.last_name > name2.last_name){
        return true;
    } else if(name1.last_name == name2.last_name){
        if(name1.first_name > name2.first_name){
            return true;
        } else if(name1.first_name == name2.first_name){
            return name1.patronymic > name2.patronymic;
        }else{
            return false;
        }
    }
    return false;
}

bool operator==(const Name& name1, const Name& name2){
    return (!(name1 > name2)&&!(name1 < name2));
}

bool operator<=(const Name& name1, const Name& name2){
    return !(name1 > name2);
}

bool operator>=(const Name& name1, const Name& name2){
    return !(name1 < name2);
}



Book::Book(Name &author, std::string &book_name_, int year, int pages){
    author_name = author;
    pubyear = year;
    n_pages = pages;
    book_name = book_name_;
}

std::ostream& operator<<(std::ostream& os, const Book& dt){
    os  << dt.book_name << " by\n\t";
    os  << dt.author_name.last_name  << " "
        << dt.author_name.first_name << " "
        << dt.author_name.patronymic << std::endl;
    return os;
}

bool operator<(const Book& book1, const Book& book2){
    if(book1.author_name < book2.author_name){
        return true;
    } else if(book1.author_name == book2.author_name){
        return book1.book_name < book2.book_name;
    }
    return false;
}

bool operator>(const Book& book1, const Book& book2){
    if(book1.author_name > book2.author_name){
        return true;
    } else if(book1.author_name == book2.author_name){
        return book1.book_name > book2.book_name;
    }
    return false;
}

bool operator==(const Book& book1, const Book& book2){
    return (!(book1 > book2)&&!(book1 < book2));
}

bool operator<=(const Book& book1, const Book& book2){
    return !(book1 > book2);
}

bool operator>=(const Book& book1, const Book& book2){
    return !(book1 < book2);
}

/***********************************
 * Reading data from CSV
 */

std::vector<Book> read_csv(std::string filename){
    std::fstream fin;
    fin.open(filename, std::ios::in);

    std::vector<Book> books;
    std::vector<std::string> row;
    std::string line, word, temp, bookname;
    int year, pages;

    while (!fin.eof()) {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line, '\n');

        // used for breaking words
        std::stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (std::getline(s, word, ';')) {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        // convert string to integer for comparision
//        std::cout << line << std::endl;
        Name author_name = {row[0], row[1], row[2]};
        bookname = row[3];
        year = stoi(row[4]);
        pages = stoi(row[5]);
        Book new_book = {author_name, bookname, year, pages};
        books.push_back(new_book);
    }
    fin.close();
    return books;
}

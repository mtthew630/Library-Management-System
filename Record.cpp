//implementation of record class

#include "Record.h"
#include <fstream>
#include <vector>

void Record::set_title(string title) {
    this->title = title;
}
void Record::set_author(string author) {
    this->author = author;
}
void Record::set_ISBN(string isbn) {
    this->ISBN = isbn;
}
void Record::set_year(string year) {
    this->year = year;
}
void Record::set_edition(string edition) {
    this->edition = edition;
}

string Record::get_title() const { return title; }
string Record::get_author() const { return author; } 
string Record::get_ISBN() const { return ISBN; }
string Record::get_year() const { return year; }
string Record::get_edition() const { return edition; }

istream& operator>>(istream& is, Record& rec) {
    //vector<Record> r;
    string title;
    string author;
    string isbn;
    string year;
    string edition;
    string emptyLine;
    getline(is, emptyLine);
    getline(is, title);
    getline(is, author);
    getline(is, isbn);
    getline(is, year);
    getline(is, edition);
    
    rec.set_title(title);
    rec.set_author(author);
    rec.set_ISBN(isbn);
    rec.set_year(year);
    rec.set_edition(edition);
    //r.push_back(rec);
    return is;
}
ostream& operator<<(ostream& os, Record& rec) {
    os << rec.get_title() << endl;
    os << rec.get_author() << endl;
    os << rec.get_ISBN() << endl;
    os << rec.get_year() << endl;
    os << rec.get_edition() << endl;
    return os;
}

// Comparison operators
bool operator==(const Record& r1, const Record& r2) {
    if (r1.get_title() == r2.get_title() && r1.get_author() == r2.get_author() && r1.get_ISBN() == r2.get_ISBN()) {
        return true;
    }
    return false;
}
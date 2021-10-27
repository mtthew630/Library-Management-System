#include "Library.h"
#include "TemplatedDLList.h"
#include <fstream>

using namespace std;

//helper function
int convert_char(char c) {
	if ('a' <= c && 'z' >= c) {// c is lowercase
		return c - 'a'; // 'a' is mapped to 0, 'b' to 1 and so on
    }
    else if ('A' <= c && 'Z' >= c) {// c is uppercase
		return c - 'A'; // 'A' is mapped to 0, 'B' to 1 and so on
	}
}

//Searches for a title in the database and returns vector of matching records
vector<Record> Library::search(string title) {
    vector<Record> rec;
    char front = title.front();
    int idx = convert_char(front);
    DLList<Record> result = book_db[idx];
    //traverse through DLL
    DLListNode<Record>* it = result.first_node();
    while (it != result.after_last_node()) {
        if (title == it->obj.get_title()) {
            rec.push_back(it->obj);
        }
        it = it->next;
    }
    return rec;
}

//Imports records from a file.  Does not import duplicates.
// Return the number of records added to the database
int Library::import_database(string filename) {
    Record rec;
    int count = 0;
    ifstream myfile(filename);
    while (myfile >> rec) {
        add_record(rec);
        count++;
    }
    return count++;
}

//Exports the current database to a file
//Return the number of records exported
int Library::export_database(string filename) {
    ofstream myfile(filename);
    DLList<Record> recList;
    int count = 0;
    for (auto x : book_db) {
        myfile << recList << endl;
    }
    return count;
}

void Library::print_database() {
    DLList<Record> recList;
    for (auto x : book_db) {
        Record rec = x.first();
        cout << rec << endl;
    }
}

//add record to database, avoid complete duplicates
bool Library::add_record(Record book) {
    /*
    vector<Record> v;
    v = search(book.get_title()); //insert location
    for (int i=0; i<v.size(); i++) {
        if (book == v[i]) {
            return false;
        }
    }
    */
    //find where to add record
    char front = book.get_title().front();
    int idx = convert_char(front);
    //DLList<Record> location = book_db[idx];
    book_db.at(idx).insert_last(book);
    return true;
}

//Deletes a record from the database
void Library::remove_record(Record book) {
    //find where to remove record
    char front = book.get_title().front();
    int idx = convert_char(front);
    //DLList<Record> location = book_db[idx];
    book_db.at(idx).remove_last();
}

//Prompts user for yes or no and returns choice Y or N
char Library::prompt_yes_no() {
    char input;
    do {
        cout << "Enter 'Y' or 'N': " << endl;
        cin >> input;
    }
    while (input != 'Y' && input != 'N');
    return input;
}

//Given a vector of menu options returns index of choice
int Library::prompt_menu(vector<string> v) {
    int input;
    for (int i=0; i<v.size(); i++) {
        cout << i+1 << ". " << v[i] << endl;
    }
    cout << "Enter a number: " << endl;
    cin >> input;
    return input-1;
}

//Prompts user for a new record
Record Library::prompt_record() {
    Record newRec;
    string newTitle;
    string newAuthor;
    string newISBN;
    string newYear;
    string newEdition;
    cout << "Enter new record data below: " << endl;
    cout << "Enter title: " << endl;
    cin >> newTitle;
    cout << "Enter author: " << endl;
    cin >> newAuthor;
    cout << "Enter ISBN: " << endl;
    cin >> newISBN;
    cout << "Enter year: " << endl;
    cin >> newYear;
    cout << "Enter edition: " << endl;
    cin >> newEdition;
    newRec.set_title(newTitle);
    newRec.set_author(newAuthor);
    newRec.set_ISBN(newISBN);
    newRec.set_year(newYear);
    newRec.set_edition(newEdition);
    return newRec;
}

//Prompt for a valid title
string Library::prompt_title() {
    string input;
    cout << "Search a title: " << endl;
    cin >> input;
    return input;
}

// Prompt for a valid string
string Library::prompt_string(string prompt) {
    string input;
    cout << prompt <<endl;
    cin >> input;
    return input;
}
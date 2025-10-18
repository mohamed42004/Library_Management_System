#include <iostream>
#include <string>
using namespace std;

// ======================================================================
//                      Library Management System
//                   Basic Version (No OOP - Arrays Only)
//                 Developed by: Mohamed Abdelmoneim Amin
// ======================================================================

const int MAX_BOOKS = 100;

// Parallel arrays to store book data
string Titles[MAX_BOOKS];
string Authors[MAX_BOOKS];
int Ids[MAX_BOOKS];
bool Status[MAX_BOOKS]; // true = available, false = borrowed

int bookCount = 0;
int lastId = 0;

// ======================================================================
//  Function: Show confirmation message and return user choice
bool Confirm() {
    int choice;
    cout << "\nDo you want to confirm? ( 1 - Yes / 2 - No ): ";
    cin >> choice;
    cin.ignore();
    return (choice == 1);
}

// ======================================================================
//  Function: Display the main menu
void MainMenu() {
    cout << "\n==============================\n";
    cout << "  Library Management System\n";
    cout << "==============================\n";
    cout << "1️ -  Display All Books\n";
    cout << "2️ -  Add New Book\n";
    cout << "3️ -  Borrow Book\n";
    cout << "4️ -  Return Book\n";
    cout << "5️ -  Update Book\n";
    cout << "6️ -  Delete Book\n";
    cout << "7️ -  Exit\n";
    cout << "------------------------------\n";
    cout << "Enter your choice: ";
}

// ======================================================================
//  Function: Display details of a single book
void DisplayBook(string title, string author, int id, bool status) {
    string bookStatus = status ? " Available" : " Borrowed";
    cout << "\n-----------------------------------\n";
    cout << " Title: " << title << endl;
    cout << " Author: " << author << endl;
    cout << " ID: " << id << endl;
    cout << " Status: " << bookStatus << endl;
}

// ======================================================================
//  Function: Display all books in the library
void DisplayAllBooks() {
    if (bookCount == 0) {
        cout << "\n  No books found in the library.\n";
        return;
    }

    cout << "\n=======  Library Books =======\n";
    for (int i = 0; i < bookCount; i++) {
        DisplayBook(Titles[i], Authors[i], Ids[i], Status[i]);
    }
}

// ======================================================================
//  Function: Add a new book to the library
void AddBook() {
    if (bookCount == MAX_BOOKS) {
        cout << "\n⚠  Cannot add more books. Maximum limit reached.\n";
        return;
    }

    string title, author;
    cin.ignore();
    cout << "\nEnter book title: ";
    getline(cin, title);
    cout << "Enter book author: ";
    getline(cin, author);

    Titles[bookCount] = title;
    Authors[bookCount] = author;
    Ids[bookCount] = ++lastId;
    Status[bookCount] = true;
    bookCount++;

    cout << "\n Book added successfully!\n";
    cout << "   → Title: " << title << endl;
    cout << "   → Author: " << author << endl;
    cout << "   → ID: " << lastId << endl;
}

// ======================================================================
//  Function: Search for a book by ID (returns index or -1)
int Search(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (Ids[i] == id)
            return i;
    }
    return -1;
}

// ======================================================================
//  Function: Borrow a book
void BorrowBook() {
    int id;
    cout << "\nEnter the Book ID to borrow: ";
    cin >> id;

    int index = Search(id);
    if (index == -1) {
        cout << " Book not found.\n";
        return;
    }

    if (!Status[index]) {
        cout << "  This book is already borrowed.\n";
        return;
    }

    DisplayBook(Titles[index], Authors[index], Ids[index], Status[index]);
    if (Confirm()) {
        Status[index] = false;
        cout << "\n Book borrowed successfully!\n";
    }
    else {
        cout << "\n Operation cancelled.\n";
    }
}

// ======================================================================
//  Function: Return a borrowed book
void ReturnBook() {
    int id;
    cout << "\nEnter the Book ID to return: ";
    cin >> id;

    int index = Search(id);
    if (index == -1) {
        cout << " Book not found.\n";
        return;
    }

    if (Status[index]) {
        cout << "  This book is already available.\n";
        return;
    }

    DisplayBook(Titles[index], Authors[index], Ids[index], Status[index]);
    if (Confirm()) {
        Status[index] = true;
        cout << "\n Book returned successfully!\n";
    }
    else {
        cout << "\n Operation cancelled.\n";
    }
}

// ======================================================================
//  Function: Update book title or author
void UpdateBook() {
    int id, choice;
    cout << "\nEnter the Book ID to update: ";
    cin >> id;

    int index = Search(id);
    if (index == -1) {
        cout << " Book not found.\n";
        return;
    }

    DisplayBook(Titles[index], Authors[index], Ids[index], Status[index]);
    if (!Confirm()) {
        cout << "\n Operation cancelled.\n";
        return;
    }

    cout << "\nWhat do you want to update?\n";
    cout << "1️ -  Title\n";
    cout << "2️ - Author\n";
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore();

    string newValue;
    if (choice == 1) {
        cout << "Enter new title: ";
        getline(cin, newValue);
        Titles[index] = newValue;
    }
    else if (choice == 2) {
        cout << "Enter new author: ";
        getline(cin, newValue);
        Authors[index] = newValue;
    }
    else {
        cout << " Invalid choice.\n";
        return;
    }

    cout << "\n Book updated successfully!\n";
}

// ======================================================================
//  Function: Delete a book
void DeleteBook() {
    int id;
    cout << "\nEnter the Book ID to delete: ";
    cin >> id;

    int index = Search(id);
    if (index == -1) {
        cout << " Book not found.\n";
        return;
    }

    DisplayBook(Titles[index], Authors[index], Ids[index], Status[index]);
    if (!Confirm()) {
        cout << "\n Operation cancelled.\n";
        return;
    }

    // Shift all elements to fill the deleted position
    for (int i = index; i < bookCount - 1; i++) {
        Titles[i] = Titles[i + 1];
        Authors[i] = Authors[i + 1];
        Ids[i] = Ids[i + 1];
        Status[i] = Status[i + 1];
    }

    bookCount--;
    cout << "\n  Book deleted successfully!\n";
}

// ======================================================================
// Main Function
int main() {
    int choice;

    while (true) {
        MainMenu();
        cin >> choice;

        switch (choice) {
        case 1: DisplayAllBooks(); break;
        case 2: AddBook(); break;
        case 3: BorrowBook(); break;
        case 4: ReturnBook(); break;
        case 5: UpdateBook(); break;
        case 6: DeleteBook(); break;
        case 7:
            cout << "\n Exiting the program. Goodbye!\n";
            return 0;
        default:
            cout << "\n Invalid choice. Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get(); // pause for user to see results
        system("clear || cls"); // works on Windows and Linux
    }
}

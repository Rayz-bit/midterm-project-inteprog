    #include <iostream>
    #include <iomanip>
    #include <string>
    #include <cctype>

    using namespace std;

    #define MAX_BOOKS 100

    class Book {
    private:
        string id;
        string isbn;
        string title;
        string author;
        string edition;
        string publication;
        string category;

        string truncate(const string& str, size_t width) const {
            if (str.length() > width) {
                return str.substr(0, width - 3) + "...";
            }
            return str;
        }

    public:
        Book() : id(""), isbn(""), title(""), author(""), edition(""), publication(""), category("") {}

        // Setters
        void setID(const string& _id) { id = _id; }
        void setISBN(const string& _isbn) { isbn = _isbn; }
        void setTitle(const string& _title) { title = _title; }
        void setAuthor(const string& _author) { author = _author; }
        void setEdition(const string& _edition) { edition = _edition; }
        void setPublication(const string& _publication) { publication = _publication; }
        void setCategory(const string& _category) { category = _category; }

        // Getters
        string getID() const { return id.empty() ? "-" : id; }
        string getISBN() const { return isbn.empty() ? "-" : isbn; }
        string getTitle() const { return title.empty() ? "-" : truncate(title, 22); }
        string getAuthor() const { return author.empty() ? "-" : truncate(author, 17); }
        string getEdition() const { return edition.empty() ? "-" : edition; }
        string getPublication() const { return publication.empty() ? "-" : truncate(publication, 17); }
        string getCategory() const { return category.empty() ? "-" : category; }

        void displayBook() const {
            cout << left 
                << setw(10) << getID()
                << setw(15) << getISBN()
                << setw(25) << getTitle()
                << setw(20) << getAuthor()
                << setw(10) << getEdition()
                << setw(20) << getPublication()
                << setw(15) << getCategory()
                << endl;
        }
        
    };

    class Library {
    private:
        Book books[MAX_BOOKS];
        int bookCount;

        void pressToContinue() {
            cout << "\nPress any key to continue...";
            cin.ignore();
            cin.get();
        }

        bool isDuplicateID(const string& id) {
            for (int i = 0; i < bookCount; i++) {
                if (books[i].getID() == id)
                    return true;
            }
            return false;
        }

        int findBookIndex(const string& id) {
            for (int i = 0; i < bookCount; i++) {
                if (books[i].getID() == id)
                    return i;
            }
            return -1;
        }

        bool isAlphanumeric(const string& str) {
            if (str.empty()) return false;
            for (char c : str) {
                if (!isalnum(c)) return false;
            }
            return true;
        }

        bool isNonEmpty(const string& str) {
            return !str.empty();
        }

        bool isValidISBN(const string& isbn) {
            if (isbn.length() < 10 || isbn.length() > 13) return false;
            for (char c : isbn) {
                if (!isdigit(c) && c != '-') return false;
            }
            return true;
        }

        bool isValidName(const string& str) {
            if (str.empty()) return false;
            for (char c : str) {
                if (!isalpha(c) && c != ' ' && c != '.' && c != '-') {
                    return false;
                }
            }
            return true;
        }

        bool isValidEdition(const string& str) {
            if (str.empty()) return false;
            for (char c : str) {
                if (!isdigit(c) && !isalpha(c)) {
                    return false;
                }
            }
            return true;
        }

        void displayTableHeader() {
            cout << left 
                << setw(10) << "ID"
                << setw(15) << "ISBN"
                << setw(25) << "Title"
                << setw(20) << "Author"
                << setw(10) << "Edition"
                << setw(20) << "Publication"
                << setw(15) << "Category"
                << endl;
        
            cout << string(115, '-') << endl;
        }
        
        

    public:
        Library() : bookCount(0) {}

        void addBook() {
            cout << "=== ADD NEW BOOK ===\n";
            
            if (bookCount >= MAX_BOOKS) {
                cout << "\nLibrary is full! Cannot add more books.\n";
                pressToContinue();
                return;
            }

            string id, isbn, title, author, edition, publication, category;

            // Category validation
            do {
                cout << "Enter Book Category (Fiction/Non-fiction): ";
                cin >> category;
                if (category != "Fiction" && category != "Non-fiction") {
                    cout << "Invalid category. Please enter either 'Fiction' or 'Non-fiction'.\n";
                }
            } while (category != "Fiction" && category != "Non-fiction");

            // ID validation
            do {
                cout << "Enter Book ID (alphanumeric, 3-10 characters): ";
                cin >> id;
                if (!isAlphanumeric(id)) {
                    cout << "ID must be alphanumeric only! Try again.\n";
                } else if (id.length() < 3 || id.length() > 10) {
                    cout << "ID must be between 3-10 characters! Try again.\n";
                } else if (isDuplicateID(id)) {
                    cout << "Duplicate ID! This ID already exists. Try again.\n";
                }
            } while (!isAlphanumeric(id) || isDuplicateID(id) || id.length() < 3 || id.length() > 10);

            // ISBN validation
            do {
                cout << "Enter ISBN (10-13 digits, hyphens allowed): ";
                cin >> isbn;
                if (!isValidISBN(isbn)) {
                    cout << "Invalid ISBN format! Must be 10-13 digits with optional hyphens.\n";
                }
            } while (!isValidISBN(isbn));

            // Title validation
            do {
                cout << "Enter Title: ";
                cin.ignore();
                getline(cin, title);
                if (!isNonEmpty(title)) {
                    cout << "Title cannot be empty. Try again.\n";
                } else if (title.length() > 100) {
                    cout << "Title too long! Maximum 100 characters allowed.\n";
                }
            } while (!isNonEmpty(title) || title.length() > 100);

            // Author validation
            do {
                cout << "Enter Author: ";
                getline(cin, author);
                if (!isNonEmpty(author)) {
                    cout << "Author cannot be empty. Try again.\n";
                } else if (!isValidName(author)) {
                    cout << "Author name can only contain letters, spaces, dots and hyphens.\n";
                } else if (author.length() > 50) {
                    cout << "Author name too long! Maximum 50 characters allowed.\n";
                }
            } while (!isNonEmpty(author) || !isValidName(author) || author.length() > 50);

            // Edition validation
            do {
                cout << "Enter Edition: ";
                cin >> edition;
                if (!isNonEmpty(edition)) {
                    cout << "Edition cannot be empty. Try again.\n";
                } else if (!isValidEdition(edition)) {
                    cout << "Edition can only contain letters and numbers.\n";
                } else if (edition.length() > 10) {
                    cout << "Edition too long! Maximum 10 characters allowed.\n";
                }
            } while (!isNonEmpty(edition) || !isValidEdition(edition) || edition.length() > 10);

            // Publication validation
            do {
                cout << "Enter Publication: ";
                cin.ignore();
                getline(cin, publication);
                if (!isNonEmpty(publication)) {
                    cout << "Publication cannot be empty. Try again.\n";
                } else if (publication.length() > 50) {
                    cout << "Publication name too long! Maximum 50 characters allowed.\n";
                }
            } while (!isNonEmpty(publication) || publication.length() > 50);

            books[bookCount].setID(id);
            books[bookCount].setISBN(isbn);
            books[bookCount].setTitle(title);
            books[bookCount].setAuthor(author);
            books[bookCount].setEdition(edition);
            books[bookCount].setPublication(publication);
            books[bookCount].setCategory(category);

            bookCount++;
            cout << "\nBook added successfully!\n";
            pressToContinue();
        }

        void editBook() {
            cout << "=== EDIT BOOK ===\n";
            
            string id;
            cout << "Enter the Book ID to edit: ";
            cin >> id;

            int index = findBookIndex(id);
            if (index == -1) {
                cout << "\nBook not found!\n";
                pressToContinue();
                return;
            }

            cout << "\nCurrent book details:\n";
            displayTableHeader();
            books[index].displayBook();
            cout << endl;

            string isbn, title, author, edition, publication, category;

            // ISBN validation
            do {
                cout << "Enter new ISBN (10-13 digits, hyphens allowed) [" << books[index].getISBN() << "]: ";
                cin >> isbn;
                if (isbn.empty()) {
                    isbn = books[index].getISBN();
                    break;
                }
                if (!isValidISBN(isbn)) {
                    cout << "Invalid ISBN format! Must be 10-13 digits with optional hyphens.\n";
                }
            } while (!isValidISBN(isbn) && !isbn.empty());

            // Title validation
            do {
                cout << "Enter new Title [" << books[index].getTitle() << "]: ";
                cin.ignore();
                getline(cin, title);
                if (title.empty()) {
                    title = books[index].getTitle();
                    break;
                }
                if (title.length() > 100) {
                    cout << "Title too long! Maximum 100 characters allowed.\n";
                }
            } while (title.length() > 100 && !title.empty());

            // Author validation
            do {
                cout << "Enter new Author [" << books[index].getAuthor() << "]: ";
                getline(cin, author);
                if (author.empty()) {
                    author = books[index].getAuthor();
                    break;
                }
                if (!isValidName(author)) {
                    cout << "Author name can only contain letters, spaces, dots and hyphens.\n";
                } else if (author.length() > 50) {
                    cout << "Author name too long! Maximum 50 characters allowed.\n";
                }
            } while ((!isValidName(author) || author.length() > 50) && !author.empty());

            // Edition validation
            do {
                cout << "Enter new Edition [" << books[index].getEdition() << "]: ";
                cin >> edition;
                if (edition.empty()) {
                    edition = books[index].getEdition();
                    break;
                }
                if (!isValidEdition(edition)) {
                    cout << "Edition can only contain letters and numbers.\n";
                } else if (edition.length() > 10) {
                    cout << "Edition too long! Maximum 10 characters allowed.\n";
                }
            } while ((!isValidEdition(edition) || edition.length() > 10) && !edition.empty());

            // Publication validation
            do {
                cout << "Enter new Publication [" << books[index].getPublication() << "]: ";
                cin.ignore();
                getline(cin, publication);
                if (publication.empty()) {
                    publication = books[index].getPublication();
                    break;
                }
                if (publication.length() > 50) {
                    cout << "Publication name too long! Maximum 50 characters allowed.\n";
                }
            } while (publication.length() > 50 && !publication.empty());

            // Category validation
            do {
                cout << "Enter new Category (Fiction/Non-fiction) [" << books[index].getCategory() << "]: ";
                cin >> category;
                if (category.empty()) {
                    category = books[index].getCategory();
                    break;
                }
                if (category != "Fiction" && category != "Non-fiction") {
                    cout << "Invalid category. Please enter either 'Fiction' or 'Non-fiction'.\n";
                }
            } while (category != "Fiction" && category != "Non-fiction" && !category.empty());

            books[index].setISBN(isbn);
            books[index].setTitle(title);
            books[index].setAuthor(author);
            books[index].setEdition(edition);
            books[index].setPublication(publication);
            books[index].setCategory(category);

            cout << "\nBook edited successfully!\n";
            pressToContinue();
        }

        void searchBook() {
            cout << "=== SEARCH BOOK ===\n";
            
            string id;
            cout << "Enter the Book ID to search: ";
            cin >> id;

            int index = findBookIndex(id);
            if (index == -1) {
                cout << "\nBook not found!\n";
                pressToContinue();
                return;
            }

            cout << "\nBook found:\n";
            displayTableHeader();
            books[index].displayBook();
            pressToContinue();
        }

        void deleteBook() {
            cout << "=== DELETE BOOK ===\n";
            
            string id;
            cout << "Enter the Book ID to delete: ";
            cin >> id;

            int index = findBookIndex(id);
            if (index == -1) {
                cout << "\nBook not found!\n";
                pressToContinue();
                return;
            }

            cout << "\nBook to delete:\n";
            displayTableHeader();
            books[index].displayBook();

            char choice;
            cout << "\nAre you sure you want to delete this book? (y/n): ";
            cin >> choice;

            if (tolower(choice) == 'y') {
                for (int i = index; i < bookCount - 1; i++) {
                    books[i] = books[i + 1];
                }
                bookCount--;
                cout << "\nBook deleted successfully!\n";
            } else {
                cout << "\nDeletion canceled.\n";
            }
            pressToContinue();
        }

        void viewBooksByCategory() {
            cout << "=== VIEW BOOKS BY CATEGORY ===\n";
            
            string category;
            bool found = false;

            do {
                cout << "Enter category to view (Fiction/Non-fiction): ";
                cin >> category;
                
                if (category != "Fiction" && category != "Non-fiction") {
                    cout << "Invalid category. Please try again.\n";
                    continue;
                }

                cout << "\nBooks in category '" << category << "':\n";
                displayTableHeader();
                
                for (int i = 0; i < bookCount; ++i) {
                    if (books[i].getCategory() == category) {
                        books[i].displayBook();
                        found = true;
                    }
                }

                if (!found) {
                    cout << "Category not found!\n";
                }
            } while (!found && (category != "Fiction" && category != "Non-fiction"));

            pressToContinue();
        }

        void viewAllBooks() {
            cout << "=== VIEW ALL BOOKS ===\n";
            
            if (bookCount == 0) {
                cout << "\nNo books available in the library.\n";
            } else {
                cout << "\nAll Books (" << bookCount << "):\n";
                displayTableHeader();
                for (int i = 0; i < bookCount; i++) {
                    books[i].displayBook();
                }
            }
            
            pressToContinue();
        }
    };

    void displayMainMenu() {
        cout << "\n=== LIBRARY MANAGEMENT SYSTEM ===" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Edit Book" << endl;
        cout << "3. Search Book" << endl;
        cout << "4. Delete Book" << endl;
        cout << "5. View Books by Category" << endl;
        cout << "6. View All Books" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice (1-7): ";
    }

    bool isValidChoice(const string& input, int& choice) {
        if (input.length() != 1 || !isdigit(input[0])) {
            return false;
        }
        choice = input[0] - '0';
        return (choice >= 1 && choice <= 7);
    }

    int main() {
        Library lib;
        string input;
        int choice;

        do {
            displayMainMenu();

            while (true) {
                cin >> input;
                if (!isValidChoice(input, choice)) {
                    cout << "Invalid choice! Please enter a number between 1 and 7: ";
                } else {
                    break;
                }
            }

            switch (choice) {
                case 1: lib.addBook(); break;
                case 2: lib.editBook(); break;
                case 3: lib.searchBook(); break;
                case 4: lib.deleteBook(); break;
                case 5: lib.viewBooksByCategory(); break;
                case 6: lib.viewAllBooks(); break;
                case 7: cout << "\nThank you for using Library Management System. Goodbye!\n"; break;
                default: cout << "Unexpected error.\n"; break;
            }

        } while (choice != 7);

        return 0;
    }
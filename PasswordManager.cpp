#include <iostream>
#include <string>

using namespace std;

class Node {
public:
    string website;
    string username;
    string password;
    Node* next;

    Node(string web, string user, string pass) : website(web), username(user), password(pass), next(nullptr) {}
};

class PasswordManager {
private:
    Node* head;

public:
    PasswordManager() : head(nullptr) {}

    ~PasswordManager() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void addPassword(string web, string user, string pass) {
        Node* newNode = new Node(web, user, pass);
        newNode->next = head;
        head = newNode;
        cout << "Password added successfully." << endl;
    }

    void editPassword(string web, string user, string oldPass, string newPass) {
        Node* current = head;
        bool found = false;
        while (current) {
            if (current->website == web && current->username == user && current->password == oldPass) {
                current->password = newPass;
                found = true;
                cout << "Password edited successfully." << endl;
                break;
            }
            current = current->next;
        }
        if (!found) {
            cout << "Password not found for editing or incorrect existing password." << endl;
        }
    }

    void deletePassword(string web, string user, string pass) {
        Node* current = head;
        Node* prev = nullptr;
        bool found = false;
        while (current) {
            if (current->website == web && current->username == user && current->password == pass) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                delete current;
                found = true;
                cout << "Password deleted successfully." << endl;
                break;
            }
            prev = current;
            current = current->next;
        }
        if (!found) {
            cout << "Password not found for deletion or incorrect password." << endl;
        }
    }

    bool searchPassword(string web) {
        Node* current = head;
        bool found = false;
        while (current) {
            if (current->website == web) {
                found = true;
                cout << "Passwords for website '" << web << "':" << endl;
                while (current && current->website == web) {
                    cout << "Username: " << current->username << ", Password: " << current->password << endl;
                    current = current->next;
                }
                break;
            }
            current = current->next;
        }
        return found;
    }

    void displayPasswords() {
        if (!head) {
            cout << "No passwords stored." << endl;
        } else {
            cout << "List of stored passwords:" << endl;
            Node* current = head;
            int count = 1;
            while (current) {
                cout << count << ". Website: " << current->website << ", Username: " << current->username << endl;
                current = current->next;
                count++;
            }
        }
    }
};

void displayMenu(PasswordManager& manager) {
    int choice;
    string web, user, pass, oldPass, newPass;

    do {
        cout << "\nPassword Manager Menu:" << endl;
        cout << "1. Add Password" << endl;
        cout << "2. Edit Password" << endl;
        cout << "3. Delete Password" << endl;
        cout << "4. Search Password" << endl;
        cout << "5. Display All Passwords" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter website: ";
                cin >> web;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                manager.addPassword(web, user, pass);
                break;
            case 2:
                cout << "Enter website: ";
                cin >> web;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter existing password: ";
                cin >> oldPass;
                cout << "Enter new password: ";
                cin >> newPass;
                manager.editPassword(web, user, oldPass, newPass);
                break;
            case 3:
                cout << "Enter website: ";
                cin >> web;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                manager.deletePassword(web, user, pass);
                break;
            case 4:
                cout << "Enter website: ";
                cin >> web;
                if (!manager.searchPassword(web)) {
                    cout << "No passwords found for website '" << web << "'." << endl;
                }
                break;
            case 5:
                manager.displayPasswords();
                break;
            case 6:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
    } while (choice != 6);
}

int main() {
    PasswordManager manager;
    displayMenu(manager);
    return 0;
}

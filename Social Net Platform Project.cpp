#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base class User
class User {
protected:
    string username;
    string password;
public:
    User(string u, string p) : username(u), password(p) {}
    
    bool login(string u, string p) {
        return (username == u && password == p);
    }

    virtual void showProfile() = 0; // pure virtual for polymorphism

    string getUsername() {
        return username;
    }
};

// Profile class inherits User
class Profile : public User {
private:
    string fullName;
    vector<string> friends;
    vector<string> updates;
public:
    Profile(string u, string p, string name) : User(u, p), fullName(name) {}

    void addFriend(const string& friendName) {
        friends.push_back(friendName);
        cout << friendName << " added as a friend.\n";
    }

    void shareUpdate(const string& update) {
        updates.push_back(update);
        cout << "Update shared: " << update << endl;
    }

    void showFriends() {
        cout << "Friends of " << fullName << ": ";
        if(friends.empty()) {
            cout << "No friends yet." << endl;
            return;
        }
        for (const auto& f : friends) cout << f << ", ";
        cout << endl;
    }

    void showUpdates() {
        cout << "Updates by " << fullName << ":\n";
        if(updates.empty()) {
            cout << "No updates yet.\n";
            return;
        }
        for (const auto& u : updates) {
            cout << "- " << u << endl;
        }
    }

    void showProfile() override {
        cout << "Profile of " << fullName << " (username: " << username << ")\n";
        showFriends();
        showUpdates();
    }
};

// Abstract base class for interactions
class Interaction {
public:
    virtual void display() = 0;  // pure virtual
    virtual ~Interaction() {}
};

// Post class inherits Interaction
class Post : public Interaction {
protected:
    string content;
public:
    Post(const string& c) : content(c) {}
    void display() override {
        cout << "Post: " << content << endl;
    }
};

// Comment class inherits Interaction
class Comment : public Interaction {
private:
    string commentText;
public:
    Comment(const string& c) : commentText(c) {}
    void display() override {
        cout << "Comment: " << commentText << endl;
    }
};

// Message class inherits Interaction
class Message : public Interaction {
private:
    string messageText;
public:
    Message(const string& m) : messageText(m) {}
    void display() override {
        cout << "Message: " << messageText << endl;
    }
};

int main() {
    // Create some user profiles (simulating a database)
    vector<Profile> users;
    users.emplace_back("hamza", "12345", "Hamza Farooq");
    users.emplace_back("ali", "54321", "Ali Khan");

    string inputUsername, inputPassword;

    cout << "=== Social Networking Platform Login ===\n";
    cout << "Enter username: ";
    cin >> inputUsername;
    cout << "Enter password: ";
    cin >> inputPassword;

    Profile* loggedInUser = nullptr;

    // Login check
    for (auto &user : users) {
        if (user.login(inputUsername, inputPassword)) {
            loggedInUser = &user;
            break;
        }
    }

    if (loggedInUser == nullptr) {
        cout << "Login failed! Invalid username or password.\n";
        return 0;
    }

    cout << "Login successful! Welcome, " << loggedInUser->getUsername() << endl;

    // Simple menu for demonstration
    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Show Profile\n";
        cout << "2. Add Friend\n";
        cout << "3. Share Update\n";
        cout << "4. Show Updates\n";
        cout << "5. Interact (Post, Comment, Message)\n";
        cout << "0. Logout\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear newline after int input

        if (choice == 1) {
            loggedInUser->showProfile();
        }
        else if (choice == 2) {
            string friendName;
            cout << "Enter friend's username to add: ";
            getline(cin, friendName);
            loggedInUser->addFriend(friendName);
        }
        else if (choice == 3) {
            string updateText;
            cout << "Write your update: ";
            getline(cin, updateText);
            loggedInUser->shareUpdate(updateText);
        }
        else if (choice == 4) {
            loggedInUser->showUpdates();
        }
        else if (choice == 5) {
            cout << "Choose interaction type:\n";
            cout << "1. Post\n2. Comment\n3. Message\nChoice: ";
            int interChoice; cin >> interChoice; cin.ignore();
            Interaction* interaction = nullptr;
            string text;
            cout << "Enter content: ";
            getline(cin, text);

            switch (interChoice) {
                case 1: interaction = new Post(text); break;
                case 2: interaction = new Comment(text); break;
                case 3: interaction = new Message(text); break;
                default: cout << "Invalid choice\n"; continue;
            }
            interaction->display();
            delete interaction;
        }
        else if (choice == 0) {
            cout << "Logging out...\n";
        }
        else {
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}

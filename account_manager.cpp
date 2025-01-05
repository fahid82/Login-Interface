#include <iostream>
#include <limits>
#include <cctype>
#include <vector>
#include <regex>
#include <random>
#include <set>
using namespace std;

struct Register
{
    string email;
    string password;
    string name;
    int ID;
    string security_question; // Stores the security question
    string security_answer;
};

bool is_valid_email(const string &email)
{
    // Basic regex pattern for email validation
    regex pattern("^[a-zA-Z0-9_+&*-]+(?:\\.[a-zA-Z0-9_+&*-]+)*@(?:[a-zA-Z0-9-]+\\.)+[a-zA-Z]{2,7}$");
    return regex_match(email, pattern); // Returns true if it matches the pattern
}

std::set<int> used_ids;

int generate_unique_id()
{
    std::random_device rd;                                      // Seed
    std::mt19937 gen(rd());                                     // Random number generator
    std::uniform_int_distribution<> dist(100000000, 999999999); // 9-digit range

    int new_id;
    do
    {
        new_id = dist(gen);
    } while (used_ids.find(new_id) != used_ids.end()); // Ensure uniqueness

    used_ids.insert(new_id);
    return new_id;
}

std::vector<Register> accounts;

void register_account()
{
    system("clear"); // Use "clear" for macOS/Linux

    cout << "\n ";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << " REGISTER ACCOUNT ";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << "\n ";

    Register newAccount;

    cout << "\n " << "ENTER USER NAME: ";
    cin >> newAccount.name;

    cout << "\n " << "ENTER USER EMAIL: ";
    cin >> newAccount.email;

    if (!is_valid_email(newAccount.email))
    {
        cout << "\n Invalid email address. Press ENTER to return to Main Menu.\n";
        getchar();
        return; // Exit the function if the email is invalid
    }

    // Clear the input buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "\n " << "ENTER USER PASSWORD: ";
    getline(cin, newAccount.password); // Use getline to capture the full password

    // Set up the security question
    cout << "\n " << "SETUP A SECURITY QUESTION FOR PASSWORD RECOVERY: ";
    getline(cin, newAccount.security_question);

    cout << "\n " << "ENTER THE ANSWER TO YOUR SECURITY QUESTION (CASE SENSITIVE): ";
    getline(cin, newAccount.security_answer);

    // Assign the ID before pushing to the vector
    newAccount.ID = generate_unique_id();
    accounts.push_back(newAccount); // Add the new account to the vector

    cout << "\n\nAccount successfully registered!\n";
    cout << "\nYour Unique User ID is: " << newAccount.ID << "\n"; // Display the assigned ID
    cout << "\nMake sure to keep it safe and do NOT share with anyone!\n";
    cout << "\n\nPress ENTER to Continue\n";
}

void login_account()
{
    system("clear");

    if (accounts.empty())
    {
        cout << "\n\nNO ACCOUNT REGISTERED YET!\n";
        cout << "\nWOULD YOU LIKE TO REGISTER?\n";
        char choice;
        cout << "\nY/N: ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            register_account();
            return; // Exit the function after successful registration
        }
        else if (choice == 'n' || choice == 'N')
        {
            return;
        }
        return; // Exit the function if no accounts are registered
    }

    int found = 0;
    string t_email, t_password;
    int attempts = 0;           // Counter for the number of attempts
    const int max_attempts = 3; // Maximum number of attempts

    while (attempts < max_attempts)
    {
        cout << "\n ";
        for (int i = 0; i < 10; i++)
            cout << "*";
        cout << " LOGIN ACCOUNT ";
        for (int i = 0; i < 10; i++)
            cout << "*";
        cout << "\n ";

        cout << "\n " << "ENTER USER EMAIL: ";
        cin >> t_email;

        // Clear the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n " << "ENTER USER PASSWORD: ";
        getline(cin, t_password);

        for (size_t i = 0; i < accounts.size(); i++)
        {
            if (t_email == accounts[i].email && t_password == accounts[i].password)
            {
                found++;
                cout << "\n\nLOGIN SUCCESSFUL. Press ENTER to continue.\n";
                return; // Exit after a successful login
            }
        }

        // Increment the number of attempts
        attempts++;

        // Check if max attempts have been reached
        if (attempts < max_attempts)
        {
            cout << "\nInvalid credentials. You have " << max_attempts - attempts << " attempts left.\n";
        }
    }

    // If the loop ends, that means max attempts were reached
    cout << "\nMax login attempts reached. Exiting...\n";
    cout << "\n Press enter to continue\n";
}

void forgot_email()
{
    system("clear");

    if (accounts.empty())
    {
        cout << "\n\nNo accounts registered yet!\n";
        return;
    }

    int t_id; // Declare t_id as an int
    bool found = false;

    cout << "\n";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << " FORGOT EMAIL ";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << "\n\n";

    // Ask the user to provide their user ID
    cout << "Enter your User ID: ";
    cin >> t_id; // Directly read the input as an integer

    // Debugging output to check user input
    cout << "\nUser entered ID: " << t_id << "\n";

    // Iterate through the accounts vector to find the email by ID
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].ID == t_id)
        { // Compare the input ID directly with the stored IDs
            cout << "\nYour registered email is: " << accounts[i].email << "\n";
            found = true;
            break; // Exit the loop when a match is found
        }
    }

    if (!found)
    {
        cout << "\nNo account found with that ID.\n";
    }

    // Add this to ensure the user has time to read the message
    cout << "\nPress Enter to return to the main menu.";
    // cin.ignore();  // To clear the buffer before calling getchar()
    getchar(); // Wait for the user to press Enter
}

void forgot_password()
{
    system("clear");

    if (accounts.empty())
    {
        cout << "\n\nNo accounts registered yet!\n";
        return;
    }

    int t_id;
    bool found = false;

    cout << "\n";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << " FORGOT PASSWORD ";
    for (int i = 0; i < 10; i++)
        cout << "*";
    cout << "\n\n";

    // Ask the user for their ID
    cout << "Enter your User ID: ";
    cin >> t_id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].ID == t_id)
        {
            found = true;
            cout << "\nAnswer the security question to reset your password:\n\n";
            cout << accounts[i].security_question << "\n";

            string answer;
            getline(cin, answer);

            if (answer == accounts[i].security_answer)
            {
                cout << "\nCorrect! Enter your new password: ";

                string new_password;
                do
                {
                    getline(cin, new_password);
                    if (new_password.empty())
                    {
                        cout << "\nPassword cannot be blank. Please enter a valid password: ";
                    }
                } while (new_password.empty());

                accounts[i].password = new_password;
                cout << "\nPassword successfully updated! Press ENTER 2X to return to the Main Menu.\n";

                // Use cin.ignore() instead of getchar()
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            else
            {
                cout << "\nIncorrect answer. Password reset failed. Press ENTER 2X to return to the Main Menu.\n";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            break;
        }
    }

    if (!found)
    {
        cout << "\nNo account found with that ID. Press ENTER 2X to return to the Main Menu.\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main()
{
    int choice;
    while (true)
    {
        system("clear");
        cout << "\n ";
        for (int i = 0; i < 10; i++)
            cout << "*";
        cout << " MAIN MENU ";
        for (int i = 0; i < 10; i++)
            cout << "*";
        cout << "\n ";
        cout << "\n\n " << '*' << '*' << " 1. REGISTER ACCOUNT ->";
        cout << "\n\n " << '*' << '*' << " 2. LOGIN ACCOUNT ->";
        cout << "\n\n " << '*' << '*' << " 3. FORGOT EMAIL ->";
        cout << "\n\n " << '*' << '*' << " 4. FORGOT PASSWORD ->";
        cout << "\n\n " << '*' << '*' << " 5. EXIT ->";
        cout << "\n ";
        cout << "\n ";
        for (int i = 0; i < 31; i++)
            cout << "*";
        cout << "\n\n\n " << "ENTER YOUR CHOICE: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            register_account();
            break;
        case 2:
            login_account();
            break;
        case 3:
            forgot_email();
            break;
        case 4:
            forgot_password();
            break;
        case 5:
            exit(0);
        default:
            cout << "\n\n";
            cout << "INVALID CHOICE. Press Enter to try again.";
            getchar();
            break;
        }
        getchar();
    }
}
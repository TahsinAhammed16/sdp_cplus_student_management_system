#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Forward declarations
void login();
void registration();
void forgotPassword();
void showPassword();
void recoverByEmail();
void recoverBySecurityQuestion();

int main()
{
    int choice;
    // Loop to continuously display the menu until the user exits
    while (true)
    {
        // Display the menu
        cout << "__________________________________________________________________\n";
        cout << "|                                                                |\n";
        cout << "|                   Welcome to the Login Page                    |\n";
        cout << "|________________________________________________________________|\n\n";

        cout << "                         ~~~ MENU ~~~                            \n\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  1. LOGIN                                        |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  2. REGISTER                                     |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  3. FORGOT PASSWORD                              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  4. EXIT                                         |\n";
        cout << "\t|--------------------------------------------------|\n";

        // Ask for the user's choice
        cout << "\nPlease enter your choice: ";
        cin >> choice;
        cout << endl;

        // Handle the menu choice
        switch (choice)
        {
        case 1:
            system("cls"); // Clear screen
            login();
            break;
        case 2:
            system("cls");
            registration();
            break;
        case 3:
            system("cls");
            forgotPassword();
            break;
        case 4:
            system("cls");

            cout << "|******************************************************************|\n";
            cout << "|          Thank you for using the system. Exiting...              |\n";
            cout << "|******************************************************************|\n\n\n";
            return 0; // Exit the program
        default:
            system("cls");
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "!    Invalid choice. Please select from the options given below.   !\n";
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        }
    }

    return 0;
}

void login()
{
    int count;
    string userId, userPassword, id, pass;
    cout << "__________________________________________________________________\n";
    cout << "|                           Login Page                            |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t USERNAME: ";
    cin >> userId;
    cout << "\t\t PASSWORD: ";
    cin >> userPassword;

    // Open the file where credentials are stored
    ifstream read("credentials.txt");
    // Check the file for matching username and password
    while (read >> id >> pass)
    {
        if (id == userId && pass == userPassword)
        {
            count = 1; // Successful login
            break;
        }
    }
    read.close();
    system("cls");

    // Output result based on the success or failure of the login attempt
    if (count == 1)
    {
        cout << "|******************************************************************|\n";
        cout << "|               Login successful! Welcome " << userId << "!        \n";
        cout << "|******************************************************************|\n\n";
    }
    else
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Login failed! Invalid username or password.             !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void registration()
{
    string userId, userPassword, userEmail, securityQuestion, securityAnswer;
    cout << "__________________________________________________________________\n";
    cout << "|                       Registration Page                         |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t Enter the username: ";
    cin >> userId;
    cout << "\t\t Enter the password: ";
    cin >> userPassword;
    cout << "\t\t Enter your email: ";
    cin >> userEmail;

    cout << "\t\t Enter a security question (e.g., Your pet's name?): ";
    // cin >> securityQuestion;
    cin.ignore();                   // Clear the input buffer
    getline(cin, securityQuestion); // Use getline to take the full input, including spaces

    cout << "\t\t Enter the answer to your security question: ";
    cin >> securityAnswer;

    ofstream write("credentials.txt", ios::app);
    write << userId << ' ' << userPassword << ' ' << userEmail << ' ' << securityQuestion << ' ' << securityAnswer << endl;
    write.close();
    system("cls");

    cout << "|******************************************************************|\n";
    cout << "|                  Registration is successful!                     |\n";
    cout << "|******************************************************************|\n\n\n";
}

/* Forgotton password previous
void forgotPassword()
{
    int option;
    cout << "__________________________________________________________________\n";
    cout << "|             You forgot the password? No worries..               |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t 1. Search your ID by username. " << endl;
    cout << "\t 2. Go back to the main menu. \n\n";
    cout << "\t Please enter your choice: ";
    cin >> option;

    switch (option)
    {
    case 1:
    {
        int count;
        string userId, id, pass;
        cout << "\t Enter the username you remembered:";
        cin >> userId;
        cout << "\n";

        ifstream search("credentials.txt");
        while (search >> id >> pass)
        {
            if (id == userId)
            {
                count = 1; // User ID found
                break;
            }
        }
        search.close();

        if (count == 1)
        {
            cout << "|*****************************************************************|\n";
            cout << "|                   Your account is found!                        |\n";
            cout << "|                  Your password is: " << pass << "               \n";
            cout << "|*****************************************************************|\n\n\n";
            main();
        }
        else
        {
            cout << "\n\t Sorry! Your account is not found! \n";
            main();
        }
        break;
    }
    case 2:
        main();
        break;
    default:
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Invalid option. Please try again.                       !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        forgotPassword();
    }
}
*/

void forgotPassword()
{
    int option;
    cout << "__________________________________________________________________\n";
    cout << "|                  Forgot Password Recovery                       |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t 1. Recover by email." << endl;
    cout << "\t 2. Recover by answering security question." << endl;
    cout << "\n\t Please enter your choice: ";
    cin >> option;

    switch (option)
    {
    case 1:
        recoverByEmail();
        break;
    case 2:
        recoverBySecurityQuestion();
        break;
    default:
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Invalid option. Please try again.                       !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        forgotPassword();
    }
}

void showPassword()
{
}

void recoverByEmail()
{
    string userId, userEmail, storedEmail, id, pass, secQuestion, secAnswer;
    cout << "\n\t\t Enter your username: ";
    cin >> userId;
    cout << "\t\t Enter your registered email: ";
    cin >> userEmail;

    ifstream read("credentials.txt");
    int count = 0;

    while (read >> id >> pass >> storedEmail >> secQuestion >> secAnswer)
    {
        if (id == userId && userEmail == storedEmail)
        {
            count = 1;

            cout << "|*****************************************************************|\n";
            cout << "|               Your account is found!                            |\n";
            cout << "|               Your password is: " << pass << "                  \n";
            cout << "|               Would you like to change your password? (Y/N)     |\n";
            cout << "|*****************************************************************|\n\n";

            char choice;
            cout << "\t\t Enter 'Y' for Yes or 'N' for No: ";
            cin >> choice;

            if (choice == 'Y' || choice == 'y')
            {
                string newPassword;
                cout << "\t\t Enter your new password: ";
                cin >> newPassword;

                // Write the new password to a temporary file
                ofstream tempFile("temp.txt");  
                ifstream inFile("credentials.txt");
                string tempId, tempPass, tempEmail, tempSecQ, tempSecA;
                while (inFile >> tempId >> tempPass >> tempEmail >> tempSecQ >> tempSecA)
                {
                    if (tempId == userId)
                    {
                        tempFile << tempId << ' ' << newPassword << ' ' << tempEmail << ' ' << tempSecQ << ' ' << tempSecA << endl;
                    }
                    else
                    {
                        tempFile << tempId << ' ' << tempPass << ' ' << tempEmail << ' ' << tempSecQ << ' ' << tempSecA << endl;
                    }
                }
                inFile.close();
                tempFile.close();

                // Rename temp file to replace the original file
                remove("credentials.txt");
                rename("temp.txt", "credentials.txt");

                cout << "|******************************************************************|\n";
                cout << "|               Password reset successfully!                       |\n";
                cout << "|******************************************************************|\n\n";
            }
            else if (choice == 'N' || choice == 'n')
            {
                cout << "|******************************************************************|\n";
                cout << "|                     No changes made.                             |\n";
                cout << "|******************************************************************|\n\n";
            }
            else
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout << "!          Invalid option. Please select either Y or N.            !\n";
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
            }
            break;
        }
    }
    read.close();

    if (count != 1)
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Error! Username or email not found.                     !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void recoverBySecurityQuestion()
{
    string userId, secAnswer, storedSecAnswer, id, pass, secQuestion, email;
    cout << "\t\t Enter your username: ";
    cin >> userId;

    ifstream read("credentials.txt");
    bool userFound = false;

    while (read >> id >> pass >> email >> secQuestion >> storedSecAnswer)
    {
        if (id == userId)
        {
            userFound = true;
            cout << "\t\t Security Question: " << secQuestion << endl;
            cout << "\t\t Enter the answer: ";
            cin >> secAnswer;

            if (secAnswer == storedSecAnswer)
            {
                cout << "|*****************************************************************|\n";
                cout << "|               Your account is found!                            |\n";
                cout << "|               Your password is: " << pass << "                  \n";
                cout << "|               Would you like to change your password? (Y/N)     |\n";
                cout << "|*****************************************************************|\n\n";

                char choice;
                cout << "\t\t Enter 'Y' for Yes or 'N' for No: ";
                cin >> choice;

                if (choice == 'Y' || choice == 'y')
                {
                    cout << "\t\t Enter your new password: ";
                    string newPassword;
                    cin >> newPassword;

                    // Write the new password to a temporary file
                    ofstream tempFile("temp.txt");
                    ifstream inFile("credentials.txt");
                    string tempId, tempPass, tempEmail, tempSecQ, tempSecA;
                    while (inFile >> tempId >> tempPass >> tempEmail >> tempSecQ >> tempSecA)
                    {
                        if (tempId == userId)
                        {
                            tempFile << tempId << ' ' << newPassword << ' ' << tempEmail << ' ' << tempSecQ << ' ' << tempSecA << endl;
                        }
                        else
                        {
                            tempFile << tempId << ' ' << tempPass << ' ' << tempEmail << ' ' << tempSecQ << ' ' << tempSecA << endl;
                        }
                    }
                    inFile.close();
                    tempFile.close();

                    // Rename temp file to replace the original file
                    remove("credentials.txt");
                    rename("temp.txt", "credentials.txt");

                    cout << "|******************************************************************|\n";
                    cout << "|               Password reset successfully!                       |\n";
                    cout << "|******************************************************************|\n\n";
                }
                else if (choice == 'N' || choice == 'n')
                {
                    cout << "|******************************************************************|\n";
                    cout << "|               No changes made.                                   |\n";
                    cout << "|******************************************************************|\n\n";
                }
                else
                {
                    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                    cout << "!          Invalid option. Please select either Y or N.            !\n";
                    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
                }
                break; // Exit the while loop after processing the answer
            }
            else
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout << "!          Error! Incorrect answer to the security question.       !\n";
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
            }
        }
    }
    read.close();

    if (!userFound)
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Error! Username not found.                              !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

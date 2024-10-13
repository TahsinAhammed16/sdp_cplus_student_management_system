#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function Declarations
void login();
void registration();
void forgotPassword();
void recoverByEmail();
void recoverBySecurityQuestion();
void manageStudents();
void addStudent();
void displayStudents();
void modifyStudent();
void deleteStudent();
void calculateCGPA();

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
    int count = 0;
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
        // Call manageStudents function after successful login
        manageStudents();
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
    string userId, securityQuestion, userAnswer, id, pass, storedQuestion, storedAnswer;
    cout << "\n\t\t Enter your username: ";
    cin >> userId;

    ifstream read("credentials.txt");
    int count = 0;

    while (read >> id >> pass >> storedQuestion >> storedAnswer)
    {
        if (id == userId)
        {
            count = 1;
            cout << "|*****************************************************************|\n";
            cout << "|               Security Question: " << storedQuestion << "         \n";
            cout << "|*****************************************************************|\n\n";

            cout << "\t\t Enter your answer: ";
            cin >> userAnswer;

            if (userAnswer == storedAnswer)
            {
                cout << "|*****************************************************************|\n";
                cout << "|               Your password is: " << pass << "                   |\n";
                cout << "|*****************************************************************|\n\n";
            }
            else
            {
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
                cout << "!          Error! Incorrect answer.                               !\n";
                cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
            }
            break;
        }
    }
    read.close();

    if (count != 1)
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!          Error! Username not found.                             !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void manageStudents()
{
    int choice;
    while (true)
    {
        cout << "__________________________________________________________________\n";
        cout << "|                     Student Management System                   |\n";
        cout << "|_________________________________________________________________|\n\n";

        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  1. Add Student                                 |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  2. Display Students                            |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  3. Modify Student                              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  4. Delete Student                              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  5. Calculate CGPA                              |\n";
        cout << "\t|--------------------------------------------------|\n";
        cout << "\t|  6. Logout                                       |\n";
        cout << "\t|--------------------------------------------------|\n";

        cout << "\nPlease enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            addStudent();
            break;
        case 2:
            system("cls");
            displayStudents();
            break;
        case 3:
            system("cls");
            modifyStudent();
            break;
        case 4:
            system("cls");
            deleteStudent();
            break;
        case 5:
            system("cls");
            calculateCGPA();
            break;
        case 6:
            system("cls");
            cout << "|******************************************************************|\n";
            cout << "|                     Logging out...                               |\n";
            cout << "|******************************************************************|\n\n";
            return; // Return to the main menu
        default:
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
            cout << "!          Invalid choice. Please try again.                       !\n";
            cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        }
    }
}

void addStudent()
{
    // Function to add student data
    string name, rollNumber;
    int semester;
    cout << "__________________________________________________________________\n";
    cout << "|                     Add Student Record                          |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t Enter student name: ";
    cin.ignore(); // Clear the input buffer
    getline(cin, name); // Get the full name
    cout << "\t\t Enter roll number: ";
    cin >> rollNumber;
    cout << "\t\t Enter semester: ";
    cin >> semester;

    // Write student data to a file
    ofstream write("students.txt", ios::app);
    write << name << ' ' << rollNumber << ' ' << semester << endl;
    write.close();

    cout << "|******************************************************************|\n";
    cout << "|                   Student record added!                          |\n";
    cout << "|******************************************************************|\n\n";
}

void displayStudents()
{
    // Function to display all student records
    cout << "__________________________________________________________________\n";
    cout << "|                      Student Records                             |\n";
    cout << "|_________________________________________________________________|\n\n";

    ifstream read("students.txt");
    string name, rollNumber;
    int semester;

    // Check if the file is empty
    if (read.peek() == ifstream::traits_type::eof())
    {
        cout << "|            No records found!                                    |\n";
    }
    else
    {
        while (read >> name >> rollNumber >> semester)
        {
            cout << "|  Name: " << name << ", Roll Number: " << rollNumber << ", Semester: " << semester << " |\n";
        }
    }
    read.close();
    cout << "|_________________________________________________________________|\n\n";
}

void modifyStudent()
{
    // Function to modify existing student record
    string rollNumber, name;
    cout << "__________________________________________________________________\n";
    cout << "|                     Modify Student Record                       |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t Enter roll number of the student to modify: ";
    cin >> rollNumber;

    ifstream read("students.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    while (read >> name >> rollNumber)
    {
        if (name == rollNumber) // Assuming name as unique identifier
        {
            found = true;
            cout << "\t\t Current details - Name: " << name << ", Roll Number: " << rollNumber << endl;
            cout << "\t\t Enter new name: ";
            cin >> name; // Get new name
            cout << "\t\t Enter new roll number: ";
            cin >> rollNumber; // Get new roll number
        }
        tempFile << name << ' ' << rollNumber << endl; // Write back to temp file
    }
    read.close();
    tempFile.close();

    if (found)
    {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "|******************************************************************|\n";
        cout << "|                  Student record modified!                       |\n";
        cout << "|******************************************************************|\n\n";
    }
    else
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!         Student not found. No changes made.                     !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void deleteStudent()
{
    // Function to delete a student record
    string rollNumber;
    cout << "__________________________________________________________________\n";
    cout << "|                     Delete Student Record                       |\n";
    cout << "|_________________________________________________________________|\n\n";

    cout << "\t\t Enter roll number of the student to delete: ";
    cin >> rollNumber;

    ifstream read("students.txt");
    ofstream tempFile("temp.txt");
    bool found = false;

    while (read >> rollNumber)
    {
        if (rollNumber != rollNumber) // Skip the student to delete
        {
            tempFile << rollNumber << endl;
        }
        else
        {
            found = true; // Student found
        }
    }
    read.close();
    tempFile.close();

    if (found)
    {
        remove("students.txt");
        rename("temp.txt", "students.txt");
        cout << "|******************************************************************|\n";
        cout << "|                  Student record deleted!                        |\n";
        cout << "|******************************************************************|\n\n";
    }
    else
    {
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
        cout << "!         Student not found. No changes made.                     !\n";
        cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    }
}

void calculateCGPA()
{
    // Function to calculate CGPA from student records
    cout << "__________________________________________________________________\n";
    cout << "|                     Calculate CGPA                              |\n";
    cout << "|_________________________________________________________________|\n\n";

    // Logic to calculate CGPA would go here
    cout << "CGPA calculation is currently not implemented.\n";
}

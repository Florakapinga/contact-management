#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>

using namespace std;

class contact
{
private:
    char fName[50], lName[50], address[50], email[50];
    long long phNo;

public:
    void createContact()
    {
        cout << "Enter your first name: ";
        cin.ignore(); // Clear the input buffer
        cin.getline(fName, 50);

        cout << "Enter your last name: ";
        cin.getline(lName, 50);

        cout << "Enter your phone number: ";
        cin >> phNo;

        cout << "Enter your address: ";
        cin.ignore(); // Clear the input buffer
        cin.getline(address, 50);

        cout << "Enter your email: ";
        cin.ignore(); // Clear the input buffer
        cin.getline(email, 50);
    }

    void showContact()
    {
        cout << "Name: " << fName << " " << lName << endl;
        cout << "Phone: " << phNo << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
    }

    void writeOnFile()
    {
        char ch;
        ofstream f1("CMS.dat", ios::binary | ios::app);
        do
        {
            createContact();
            f1.write(reinterpret_cast<char *>(this), sizeof(*this));
            cout << "Do you have next data? (y/n): ";
            cin >> ch;
        } while (ch == 'y');
        cout << "Contact has been successfully created...";
        f1.close();
    }

    void readFromFile()
    {
        ifstream f2("CMS.dat", ios::binary);
        cout << "\n=========================\n";
        cout << "LIST OF CONTACTS";
        cout << "\n=============================\n";
        while (f2.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            showContact();
            cout << "\n=============================\n";
        }
        f2.close();
    }

    void searchOnFile()
    {
        ifstream f3("CMS.dat", ios::binary);
        long long phone;
        cout << "Enter phone number: ";
        cin >> phone;
        while (f3.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (phone == phNo)
            {
                showContact();
                return;
            }
        }
        cout << "\n\nNo record found";
        f3.close();
    }

    void deleteFromFile()
    {
        long long phone;
        int flag = 0;
        ofstream f4("temp.dat", ios::binary);
        ifstream f5("CMS.dat", ios::binary);

        cout << "Enter phone number to delete: ";
        cin >> phone;
        while (f5.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (phNo != phone)
            {
                f4.write(reinterpret_cast<char *>(this), sizeof(*this));
            }
            else
            {
                flag = 1;
            }
        }
        f5.close();
        f4.close();
        remove("CMS.dat");
        rename("temp.dat", "CMS.dat");

        flag != 1 ? cout << "\tContact Deleted..." : cout << "\tContact Not Found...";
    }

    void editContact()
    {
        long long phone;
        fstream f6("CMS.dat", ios::binary | ios::in | ios::out);
        cout << "Edit Contact";
        cout << "\n===============================\n";
        cout << "Enter the phone number to be edited: ";
        cin >> phone;

        while (f6.read(reinterpret_cast<char *>(this), sizeof(*this)))
        {
            if (phone == phNo)
            {
                cout << "Enter new record\n";
                createContact();
                f6.seekp(-static_cast<int>(sizeof(*this)), ios::cur);
                f6.write(reinterpret_cast<char *>(this), sizeof(*this));
                cout << "\n\tContact Successfully updated...";
                return;
            }
        }
        cout << "\n\nNo Record found";
        f6.close();
    }
};

int main()
{
    system("cls");
    system("color 3F");

    cout << "\n\n\n\n\n\n\n\n\n\n\n\t\t * WELCOME TO THE CONTACT MANAGEMENT SYSTEM *";
    getch();

    while (true)
    {
        contact c1;
        int choice;

        system("cls");
        system("color 03");
        cout << "\nCONTACT MANAGEMENT SYSTEM";
        cout << "\n\nMAIN MENU";
        cout << "\n==================================\n";
        cout << "[1] Add a new contact\n";
        cout << "[2] List all contacts\n";
        cout << "[3] Search for contacts\n";
        cout << "[4] Delete a contact\n";
        cout << "[5] Edit a contact\n";
        cout << "[0] Exit";
        cout << "\n===================================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system("cls");
            c1.writeOnFile();
            break;

        case 2:
            system("cls");
            c1.readFromFile();
            break;

        case 3:
            system("cls");
            c1.searchOnFile();
            break;

        case 4:
            system("cls");
            c1.deleteFromFile();
            break;

        case 5:
            system("cls");
            c1.editContact();
            break;

        case 0:
            system("cls");
            cout << "\n\n\n\n\t\t\t\t\tThank you for using CMS." << endl
                 << endl;
            exit(0);
            break;

        default:
            continue;
        }

        int opt;
        cout << "\n\n..::Enter the Choice:\n[1] Main Menu\t[0] Exit\n";
        cin >> opt;

        switch (opt)
        {
        case 0:
            system("cls");
            cout << "\n\n\n\t\t\t THANK YOU FOR USING CMS." << endl
                 << endl;
            exit(0);
            break;
        default:
            continue;
        }
    }
    return 0;
}

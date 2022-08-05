#include<iostream>
#include<string.h>
#include<fstream>

#define LENGTH 31

using namespace std;

struct User_Details
{
    char Password[LENGTH];
    char name[51];
    char RegdNo[7];
    char Username[LENGTH];
    char DOB[11];

    void Register();

    void SignIn();

    void Display_Profile();

    void Edit_Profile();

    User_Details operator=(User_Details a);
};

//member function

void User_Details :: Register()
{
    cout << "Please enter your Institute Registration Number : ";
    cin>>ws;
    cin.getline(this->RegdNo,7);
    cout << "Please enter your Name : ";
    cin>>ws;
    cin.getline(this->name, LENGTH);   
    cout << "Please enter your User_Name : ";
    cin>>ws;
    cin.getline(this->Username, LENGTH);
    cout << "Please enter your Password : ";
    system("stty -echo");
    cin>>ws;
    system("stty -echo");
    cin.getline(this->Password, LENGTH);
    system("stty echo");
    cout << "\nPlease enter your Date Of Birth (DD/MM/YYYY) : ";
    cin>>ws;
    cin.getline(this->DOB, LENGTH);
    system("clear");
}

void User_Details :: SignIn()
{
    char psd[LENGTH];
    int i= 0;
    do
    {
            cout << "Please enter your Password : ";
            system("stty -echo");
            cin>>ws;
            cin.getline(psd, LENGTH);
            system("stty echo");

            if(strcmp(psd,this->Password) == 0)
            {
                system("clear");
                cout<< "You are Good to go ...\n";
                break;
            }
            else
            {
                i++;
                cout<< "Wrong Password.\nPlease try again.\n\n";
                if(i == 3)
                {
                    cout<< "Try after some time...";
                    exit(1);
                }
            }

    }while(1);

    return;
}

void User_Details :: Display_Profile()
{
    system("clear");
    cout<< "Registration Number : "<< RegdNo << endl;
    cout<< "My name is "<< name << endl;
    cout<< "User_name @ "<< Username << endl;
    cout<< "Wish me on "<< DOB << endl;
}

User_Details User_Details :: operator=(User_Details a)
{
    strncpy(this->RegdNo, a.RegdNo, 7);
    strncpy(this->Username, a.Username, LENGTH);
    strncpy(this->DOB, a.DOB, 11);
    strncpy(this->name, a.name, 51);
    strncpy(this->Password, a.Password, LENGTH);
}

void User_Details :: Edit_Profile()
{
    int ch;
    char psd[LENGTH] = {};
    char un[LENGTH] = {};

    do
    {
    system("clear");
    cout<< "You can only edit your Name, User_name and Password.\nSo, What do u wanna change???\n";
    cout<< "For Name, Press 1\nFor User_name, Press 2\nFor Password, Press 3\n";
    cin >> ch;
        switch(ch)
        {
            case 2:
            cout<< "Enter the New User_Name : ";
            cin >> ws;
            cin.getline(un,LENGTH);
            strncpy(this->Username, un, LENGTH);
            system("clear");
            cout<< "Done! Your new User_name is "<< this->Username << endl;
            break;

        case 1:
            cout<< "Enter the New Name : ";
            cin >> ws;
            cin.getline(un,LENGTH);
            strncpy(this->name, un, LENGTH);
            system("clear");
            cout<< "Done! Your new name is "<< this->name << endl;
            break;

        case 3:
            cout<< "Enter Current Password : ";
            system("stty -echo");
            cin>>ws;
            cin.getline(psd, LENGTH);
            system("stty echo");
            cout << "\nEnter your New Password : ";
            system("stty -echo");
            cin>>ws;
            cin.getline(psd, LENGTH);
            system("stty echo");
            cout << "\nRe-Enter your New Password : ";
            system("stty -echo");
            cin>>ws;
            cin.getline(psd, LENGTH);
            system("stty echo");
            system("clear");
            strncpy(this->Password, psd, LENGTH);
            cout<< "\nDone! Your password has been changed successfully changed.\n";
        break;

        default:
            cout<< "Wrong Choice...\nTry again.\n";
            continue;
        }
        break;

    }while(1);

    return;
}
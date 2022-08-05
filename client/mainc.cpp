#include<fstream>
#include"client_alpha(1.0).cpp"
#include"Sock.cpp"

using namespace Xtras;

int main()
{
    signal(SIGINT, Client :: Ctrl_C_handler);

    int ch;
    char reg[7] = {};
    User_Details info;
    
    int sock = CreateSock();

    fstream fobj;
    system("clear");
    cout<< "\t\t\t\t\t\tWelcome to The MDH Chat Portal\n\n";
    do
    {
        cout<< "NEW User ??? Sign-Up (1) OR EXISTING User ??? Sign-In (2)\n"; 
        cout<< "Enter your choice : ";
        cin>> ch;

        switch(ch)
        {
            case 1:
                info.Register();
                fobj.open(info.RegdNo, ios::out);
                fobj.write((char *)&info,sizeof(info));
                fobj.close();
                break;

            case 2: 
                cout<< "Please enter your Registration Number : ";
                cin>> ws;
                cin.getline(reg,7);
                fobj.open(reg, ios::in);
                if(!fobj)
                {
                    cout<< "Sorry, There is no account on this Registration Number.\nPlease Sign Up.\n\n";
                    info.Register();
                    fobj.open(info.RegdNo, ios::out);
                    fobj.write((char *)&info,sizeof(info));
                    fobj.close();
                    break;
                }
                fobj.read((char *)&info,sizeof(info));
                info.SignIn();
	            fobj.close();
                break;

            default:
                cout<< "Wrong Choice...\n";
                continue;
        }
        break;
    }while(1);

    prin(info.name);// nameless obj

    Client c(info, sock);
    
    do
    {
        cout<< "\nHere's what we have on the menu today :-\n";
        cout<<"1 - Enter the MDH chatroom.\n2 - Display Profile.\n3 - Edit Profile.\n4 - Exit.\n";
        cout<< "Enter your choice : ";
        cin>> ch;
        switch(ch)
        {
            case 1:
                
                c.Set_IP();
                c.Estd_connect();
                c.Init_chat();
                c.~Client();
                break;
            case 2:
                info.Display_Profile();
                break;
            case 3:
                info.Edit_Profile();
                fobj.open(info.RegdNo, ios::out);
                fobj.write((char *)&info,sizeof(info));
                fobj.close();
                break;
            case 4:
                //cout<< "The windows of the MDH Chatroom will always be open for you.\n";
                cout<< "Bye ! See yaa\n";
                exit(1); 
            default:
                cout<< "Wrong choice...\nTry again.\n";
        }

    }while(1);

    return 0;
}

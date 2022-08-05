#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<bits/stdc++.h>
#include"str.cpp"
#include"User_details.cpp"
#define LENGTH 31
#define LENGTH_MSG 101

using namespace std;

class Msg_pass
{
private:
	static int sock_id;
	static int flag;

public:

	Msg_pass() // default ctor
	{
		cout<< "Error : No socket passed.";
        exit(1);
	}

	Msg_pass(int s) // ctor for sockid init (-1 for error)
	{
		if (s == -1)
        {
            cout<< "Error : Invalid socket passed.\n";
            exit(1);
        }

		sock_id = s;
	
		flag = 0;
	}

	static void Ctrl_C_handler(int sig)// catch CTRL+C
	{
		cout<< "\rChat Quitted.\n";
		exit(1);
	}

	static void Recv_msg_handler();

	static void Send_msg_handler();

	virtual ~Msg_pass(){};

};
// Static variables

int Msg_pass :: sock_id;
int Msg_pass :: flag;

// Member functions

void Msg_pass :: Recv_msg_handler()
{
	char RecvMsg[LENGTH_MSG];
	int receive;
	while(!flag)
	{
		receive = recv(sock_id, RecvMsg, LENGTH_MSG, 0);
		if (receive > 0)
       	{
			if(strcmp(RecvMsg,"U_exit")==0)
			{
				flag = 1;
				cout<< "Chat Quitted\n";	
				break;
			}
			if(strcmp(RecvMsg,"I_Quit")==0)
			{
				flag = 1;
				cout<< "Server Down due to Maintenence.\n";
				cout<< "We are sorry for the inconvinence.\n";
				cout<< "Try again later.\nPress any key followed by enter to continue...\n";	
				break;
			}
       		cout<<"\r"<< RecvMsg<<"\n";
			cout<<"\r> ";
			fflush(stdout);
		}
		else if(receive == 0)
		{
			break;
		}
	}
};

void Msg_pass :: Send_msg_handler()
{
	char SendMsg[LENGTH_MSG];
	while(!flag)
	{
		while(fgets(SendMsg, LENGTH_MSG, stdin) != NULL)
		{
			str_trim(SendMsg, LENGTH_MSG);
			if(strlen(SendMsg) == 0)
			{
				cout<<"\r> ";
				fflush(stdout);
			}
			else
			{
				break;
			}
		} 
		if(strcmp(SendMsg,"exit") == 0)
		{
			flag = 1;
		}
		send(sock_id, SendMsg, LENGTH_MSG, 0);
	}
}
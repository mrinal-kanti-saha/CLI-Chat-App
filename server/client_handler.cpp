#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<signal.h>
#include"client_node.cpp"
#include"User_details.cpp"

using namespace std;

class Client_Handler : public ClientList<User_Details>
{
public:

    static ClientList<User_Details> *root, *now;

    Client_Handler()
    {
        *root = *now = NULL;
    }

    static void Remove_Clients(int sig); // removes all the clients and shuts program

    static void Send_to_all_clients(ClientList<User_Details> *np, char tmp_buffer[LENGTH_MSG]); // send to all clients

    static void handler(void *p_client);

    virtual ~Client_Handler(){};

};

//Static variables

ClientList<User_Details>* Client_Handler :: root = NULL;
ClientList<User_Details>* Client_Handler :: now = NULL;

//member functions

    void Client_Handler :: Send_to_all_clients(ClientList<User_Details> *np, char tmp_buffer[LENGTH_MSG]) // send to all clients
    {
        ClientList<User_Details> *tmp = root->link;
        while (tmp != NULL) 
        {
            if (np->data != tmp->data) 
            { // all clients except itself.
                send(tmp->data, tmp_buffer, LENGTH_MSG, 0);
            }
            tmp = tmp->link;
        }
    }

    void Client_Handler :: Remove_Clients(int sig) // removes all the clients and shuts program // signal function
    {
        ClientList<User_Details> *tmp;
        int i = 0;
        cout<< "\nClosing all sockets...\n";

        cout<< "\n";
        while (root != NULL) 
        {   
            if(i)
            {
                send(root->data, "I_Quit", LENGTH_MSG, 0);
                cout << "Close socket : "<< root->data << endl << root->info.Username << " was removed from the Chat.\n";
            }
        
            close(root->data); // close all socket include server_sock_id
            i = 1;
            tmp = root;
            root = root->link;
            delete(tmp);
        }
        cout << "Chat Server Quitted.\n";
        exit(1);
    }

    void Client_Handler :: handler(void *p_client) 
    {
        int leave_flag = 0;
        User_Details *temp;
        char recv_buffer[LENGTH_MSG];
        char send_buffer[LENGTH_MSG];
        char tempBlock[sizeof(User_Details)];
        strcpy(recv_buffer, "\0");
        strcpy(send_buffer, "\0");

        ClientList<User_Details> *np = (ClientList<User_Details> *)p_client;

        // Naming
        if (recv(np->data, tempBlock, sizeof(User_Details), 0) <= 0 )//|| strlen(name) < 2 || strlen(name) >= LENGTH-1) 
        {
            cout << "Error : "<< np->ip <<" didn't input name.\n";
            leave_flag = 1;
        } 
        else 
        {
            temp = (User_Details *)tempBlock;
            strncpy(np->info.Username, temp->Username, LENGTH);
            strncpy(np->info.name, temp->name, 51);
            strncpy(np->info.Password, temp->Password, LENGTH);
            strncpy(np->info.RegdNo, temp->RegdNo, 7);
            strncpy(np->info.DOB, temp->DOB, 11);


            cout <<"\r"<< np->info.Username << "(" << np->info.RegdNo <<") at ("<< np->ip <<") joined the Chat.\n" << "Active Now : "<< ClientList<User_Details> :: active<< "\n";
            sprintf(send_buffer, "%s(%s) at (%s) joined the Chat.\nActive Now : %d ", np->info.Username, np->info.RegdNo, np->ip, ClientList<User_Details> :: active);
            Send_to_all_clients(np, send_buffer);
        }
        int receive = 0;
        // Conversation
        while (1) 
        {
            receive = recv(np->data, recv_buffer, LENGTH_MSG, 0);
            if (leave_flag) 
            {
                break;
            }
            if (receive == 0 || strcmp(recv_buffer,"exit") == 0) // error in recvry client exit warrant
            {
                send(np->data, "U_exit", LENGTH_MSG, 0);
                break;
            }
            if (receive > 0) // recieved msg
            {
                if (strlen(recv_buffer) == 0) // empty msg
                {
                    continue;
                }
                
                cout <<"\r" << np->info.Username << " : " << recv_buffer << endl;
                sprintf(send_buffer, "%s：%s", np->info.Username, recv_buffer);  // some msg received
            }   
            else // error in recv
            {
                cout << "Error : Recovery error.\n";
                break;
            }
            Send_to_all_clients(np, send_buffer); //name of func is sufficient
        }

        // Remove Node
        close(np->data);
        if (np == now) 
        { // remove an edge node
            now = np->prev;
            now->link = NULL;
        } 
        else 
        { // remove a middle node
            np->prev->link = np->link;
            np->link->prev = np->prev;
        }

        delete(np);
        cout << "\r" << np->info.Username << " left the Chat.\nActive Now : "<< ClientList<User_Details> :: active<< "\n";
        sprintf(send_buffer, "%s left the Chat.\nActive Now : %d", np->info.Username, ClientList<User_Details> :: active);
        Send_to_all_clients(np, send_buffer); //name of func is sufficient
    }

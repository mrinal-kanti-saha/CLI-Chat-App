#include<thread>
#include"client_handler.cpp"
#include"chatcs.cpp"
#define MAXQSIZE 25

using namespace std;

class Server : public ChatCS, public Client_Handler
{
private:
    int server_sock_id, client_sock_id;
    struct sockaddr_in server_info, client_info;
    int size_server, size_client;

public:
    Server(int sock = -1) : Client_Handler()
    {
        server_sock_id = sock;
        size_client = size_server = sizeof(sockaddr_in);
        memset(&server_info,0,size_server);
        memset(&client_info,0,size_client);
    }

    void Set_IP();

    void Estd_connect();

	void Init_chat();

    ~Server(){};

};

// member functions

void Server :: Set_IP() // setting the server_info (virtual)
{   

    server_info.sin_family = AF_INET; // protocol family PF_INET
    server_info.sin_addr.s_addr = inet_addr("192.168.34.58"); // IP address
    server_info.sin_port = htons(3100); // port no

    return;
}

void Server :: Estd_connect()
{
    bind(server_sock_id, (struct sockaddr *)&server_info, size_server);
    listen(server_sock_id, MAXQSIZE);

    // Print Server IP
    getsockname(server_sock_id, (struct sockaddr*) &server_info, (socklen_t*) &size_server);

    cout << "Hosted Chat on : "<< inet_ntoa(server_info.sin_addr) << " : "<< ntohs(server_info.sin_port)<< endl;

    return;
}

void Server :: Init_chat()
{
    // Initial linked list for clients
    root = newNode(server_sock_id, inet_ntoa(server_info.sin_addr));
    now = root;

    while (1) 
    {
        client_sock_id = accept(server_sock_id, (struct sockaddr*) &client_info, (socklen_t*) &size_client);

        // Print Client IP
        getpeername(client_sock_id, (struct sockaddr*) &client_info, (socklen_t*) &size_client);
        //cout << "Client " << inet_ntoa(client_info.sin_addr) << " : " << ntohs(client_info.sin_port) <<"joined the Chat.\n";

        // Append linked list for clients
        ClientList<User_Details> *c = newNode(client_sock_id, inet_ntoa(client_info.sin_addr));
        c->prev = now;
        now->link = c;
        now = c;

        thread client_h(handler,c);
        client_h.detach();
    }
    
    return;
}

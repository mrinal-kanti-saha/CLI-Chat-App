#include"Message_chat.cpp"
#include"chatcs.cpp"

using namespace std;

class Client : public ChatCS, public Message
{
private:
    int error = 1;
    User_Details info; // user_details obj
    int sock_id;
    struct sockaddr_in server_info, client_info;
    int size_server, size_client;

public:
    Client(User_Details sm, int sock = -1): Message(sock)
    {
        info = sm;
        sock_id = sock;
        size_client = size_server = sizeof(sockaddr_in);
        memset(&server_info,0,size_server);
        memset(&client_info,0,size_client);
    };

    void Set_IP(); 

    void Estd_connect();

	void Init_chat(); 

    ~Client(){}
};

// member functions

void Client :: Set_IP() // setting the server_info (virtual)
{
    char ip_addr[16];
    int port_no;

    server_info.sin_family = PF_INET; // protocol family PF_INET
    server_info.sin_addr.s_addr = inet_addr("192.168.34.58"); // IP address
    server_info.sin_port = htons(3100); // port no

    return;
}

void Client :: Estd_connect() // conn estd and user details sent to server (virtual)
{
    int err; 
    try
    {
        if(sock_id == -1)
            throw sock_id;
    }
    catch(int a)
    {
        cout << "Please create the socket first.\n";
        return;
    }

    system("clear");

    err = connect(sock_id, (struct sockaddr *)&server_info, size_server);// establish connection through the created socket
    try
    {
        if (err != 0) 
            throw err;
    }
    catch(int a)
    {
        cout << "Server Down due to Maintenence.\nWe are sorry for the inconvinence.\nTry again later.\n" ; // failure case
        error = 1;
        return;
    }
    
    getsockname(sock_id, (struct sockaddr*) &client_info, (socklen_t*) &size_client);
    getpeername(sock_id, (struct sockaddr*) &server_info, (socklen_t*) &size_server);

    cout << "You are Now Connected to the Chat Server.\n\n"; //<< inet_ntoa(server_info.sin_addr) <<" at Port Number : "<< ntohs(server_info.sin_port) << endl;
    
    error = 0;

    return;
}

void Client :: Init_chat() // otherwise just call Chats directly anyways available in the class client
{
    if(error)
    {
        cout<< "Chat option not available at this moment.\nPlease check your connection with the server\n";
        return;
    }   

    char *temp = NULL;
    temp = (char *)&info;
    send(sock_id, temp, sizeof(User_Details), 0); // sending nickname // send user details

    Chat();
    close(sock_id);
    return; 
}

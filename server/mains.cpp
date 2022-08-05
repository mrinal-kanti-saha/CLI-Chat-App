#include"server_alpha(1.0).cpp"
#include"Sock.cpp"

using namespace Xtras;

int main()
{
    signal(SIGINT, Server::Remove_Clients);

    int sock = CreateSock();

    Server s(sock);
    s.Set_IP();
    s.Estd_connect();
    s.Init_chat(); 

    return 0;
}
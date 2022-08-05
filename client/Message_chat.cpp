#include<thread>
#include"Msg_pass.cpp"

using namespace std;

class Message : public Msg_pass
{
public:
	Message(int sock): Msg_pass(sock){};

    void Chat();

    virtual ~Message(){};
};

// Member function

void Message :: Chat()
{
	thread send_thread(Send_msg_handler);
    thread recv_thread(Recv_msg_handler);

    send_thread.join();
    recv_thread.join();

    return;
}

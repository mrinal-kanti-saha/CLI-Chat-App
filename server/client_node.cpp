#include<iostream>
#include<stdlib.h>
#include<string.h>
#include"str.cpp"
#define LENGTH 31
#define LENGTH_MSG 101

using namespace std;

template <class T>
class ClientList
{
public:
	static int active;
    int data;
    class ClientList<T>* prev;
    class ClientList<T>* link;
    char ip[16];
    T info;

    void* operator new(size_t size);

    void operator delete(void  *p);

	ClientList<T>* operator=(ClientList<T> *p);

    ClientList<T> *newNode(int sockfd, char ip[16]);

};
template <class T>
int ClientList<T>:: active = -1;

template <class T>
void * ClientList<T>:: operator new(size_t size)
{
    void *p = ::new ClientList();
    active++;
    return p;
}

template <class T>
void ClientList<T>:: operator delete(void *p)
{
    free(p);
    active--;
    return;
}

template <class T>
ClientList<T>* ClientList<T>:: operator=(ClientList *p)
{
	return(p);
}

template <class T>
ClientList<T>* ClientList<T>:: newNode(int sock_id, char ip[16]) 
{
    ClientList *np =  new ClientList();

    np->data = sock_id;
    np->prev = NULL;
    np->link = NULL;
    strncpy(np->ip, ip, 16);
    memset(&info, 0, sizeof(T));

    return np;
}

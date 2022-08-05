namespace Xtras
{
	class prin
	{
		public:
		prin(char a[51])
		{
			cout << "Welcome, " << a << endl;
		}
		~prin()
		{

		}
	};

	int CreateSock()
	{
		 int sock = socket(AF_INET , SOCK_STREAM , 0);
    	         try
    		{
    		    if (sock == -1)
    		        throw sock;
   		 }
   		 catch(int a)
    		{
		        printf("Fail to create a socket.\n");// failure to create a socket
		        exit(1);
	   	 }
		return(sock);
	}
}

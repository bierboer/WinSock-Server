#include "Network.h"

int main()
{
	Network network;
	network.StartServer();
	
	while (true)
	{
		network.WaitForClientData();
		if (network.CheckData() == "hello")
		{
			network.SendData("hi, how are you?");
		}
	}

	network.StopServer();
	return 0;
}
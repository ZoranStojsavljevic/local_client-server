/****************** CLIENT CODE ****************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(){
	int clientSocket;
	char buffer[1024];
	struct sockaddr_in serverAddr;
	socklen_t addr_size;

	bzero(&buffer, sizeof(buffer));

	/*---- Create the socket. The three arguments are: ----*/
	/* 1) Internet domain 2) Stream socket 3) Default protocol IPPROTO_IP (IP in this case) */
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	/* 1) Internet domain 2) Stream socket 3) IPPROTO_TCP (TCP in this case) */
	//	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	/* 1) Internet domain 2) Stream socket 3) IPPROTO_UDP (UDP in this case) */
	//	clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_UDP);

	/*---- Configure settings of the server address struct ----*/
	/* Address family = Internet */
	serverAddr.sin_family = AF_INET;
	/* Set port number, using htons function to use proper byte order */
	serverAddr.sin_port = htons(7891);
	/* Set IP address to localhost */
	//	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	/* Set IP address to distant server */
	serverAddr.sin_addr.s_addr = inet_addr("192.168.178.28");
	/* Set all bits of the padding field to 0 */
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);

	/*---- Connect the socket to the server using the address struct ----*/
	addr_size = sizeof serverAddr;
	connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size);

	/*---- Read the message from the server into the buffer ----*/
	recv(clientSocket, buffer, 1024, 0);

	/*---- Print the received message ----*/
	printf("Data received: %s\n", buffer);

	return 0;
}

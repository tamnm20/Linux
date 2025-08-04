#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>  // Cho InetPton
#pragma comment(lib, "ws2_32.lib")

#define BUFF_SIZE 256

void chat_func(SOCKET server_fd) {
    int numb_write, numb_read;
    char recvbuff[BUFF_SIZE];
    char sendbuff[BUFF_SIZE];

    while (1) {
        memset(sendbuff, 0, BUFF_SIZE);
        memset(recvbuff, 0, BUFF_SIZE);
        printf("Please enter the message: ");
        fgets(sendbuff, BUFF_SIZE, stdin);

        //numb_write = send(server_fd, sendbuff, (int)strlen(sendbuff), 0);
        numb_write = send(server_fd, sendbuff, sizeof(sendbuff), 0);
        if (numb_write == SOCKET_ERROR) {
            perror("send()");
            break;
        }

        if (strncmp("exit", sendbuff, 4) == 0) {
            printf("Client exit ...\n");
            break;
        }

        numb_read = recv(server_fd, recvbuff, BUFF_SIZE, 0);
        if (numb_read <= 0) {
            perror("recv()");
            break;
        }

        if (strncmp("exit", recvbuff, 4) == 0) {
            printf("Server exit ...\n");
            break;
        }

        printf("\nMessage from Server: %s\n", recvbuff);
    }

    closesocket(server_fd);
}

int main(int argc, char *argv[]) {
    WSADATA wsa;
    SOCKET server_fd;
    struct sockaddr_in serv_addr;
    int portno;

    if (argc < 3) {
        printf("Usage: %s <server address> <port number>\n", argv[0]);
        return 1;
    }

    portno = atoi(argv[2]);

    // Khởi động Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    // Tạo socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == INVALID_SOCKET) {
        printf("Could not create socket. Error Code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);  // dùng thay inet_pton

    // Kết nối tới server
    if (connect(server_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed. Error Code: %d\n", WSAGetLastError());
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    chat_func(server_fd);

    WSACleanup();
    return 0;
}

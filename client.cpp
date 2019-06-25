#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <thread>

int main() {
    int m_socket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "client socket: " << m_socket << std::endl;

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(2001);

    // connect
    int connect_status = connect(m_socket, (sockaddr*)(&addr), sizeof(addr));
    std::cout << "client connection status: " << connect_status << std::endl; 

    // work loop

    int buffsize = 256;
    char buff[buffsize];
    buff[0] = 'a', buff[1] = 'b', buff[2] = '\n'; 
    send(m_socket, buff, buffsize, NULL);

    std::cout << "client send: " << buff << std::endl;

    recv(m_socket, buff, buffsize, NULL);
    std::cout << "client recive: " << buff << std::endl;

    close(m_socket);

    return 0;
}
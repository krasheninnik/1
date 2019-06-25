#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <thread>

void cli_process(int socket) {
    int buffSize = 256;
    char buff[buffSize];
    char resultbuff[buffSize];

    recv(socket, buff, buffSize, NULL);
    std::cout << "server recive: " << buff << std::endl;
    // processing
   // memcpy(resultbuff, buff, buffSize);
    resultbuff[0] = 'c', resultbuff[1] = 'd', resultbuff[2] = '\n'; 

    std::cout << "server send: " << resultbuff << std::endl;
    send(socket, resultbuff, buffSize, NULL);

    close(socket);
}

int main() {
    int m_socket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "server socket: " << m_socket << std::endl;

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY; ////
    addr.sin_port = htons(2001);


    int bind_status = bind(m_socket, (sockaddr *)(& addr), sizeof(addr));
    std::cout << "server bind status: " << bind_status << std::endl;

    int listen_status = listen(m_socket, 1);
     std::cout << "server listen_status: " << listen_status << std::endl;

    sockaddr_in cli = {};
    socklen_t cli_len = sizeof(cli); ////

    while(true) {
        int cli_socket = accept(m_socket, (sockaddr*)(&cli), &cli_len); ///
        std::cout << "server cli socket: " << cli_socket << std::endl;

        std::thread thr = std::thread(cli_process, cli_socket);
        thr.detach();
    }

    return 0;
}
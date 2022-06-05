#include "server.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "varint.h"

int main(int argc, const char* argv[]) {
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);
    
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!server_fd) {
        perror("!! Failed to create socket");
        return 1;
    }

    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("!! Failed to set socket option");
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(25565);

    if (bind(server_fd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("!! Failed to bind to port 25565");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("!! Failed to listen to socket");
        return 1;
    }

    printf("Waiting for connections...\n");

    while (1) {
        int accepted = accept(server_fd, (struct sockaddr*) &addr, (socklen_t*) &addrlen);
        if (accepted < 0) {
            perror("!! Failed to accept incoming connection");
            return 1;
        }

        char buffer[4096] = { 0 };
        int valread = read(accepted, buffer, 4096);
        if (valread < 0) {
            perror("!! Failed to read data from connection");
            continue;
        }

        printf("Received a packet %d bytes long...Inspecting...\n", valread);
        unsigned char* bytes_read = {0};
        long long length = read_varint(buffer, bytes_read);
        printf(">> Length field is %llu\n", length);
        unsigned long long offset = sizeof(bytes_read);
        printf(">> Read %llu bytes...\n", offset);
        long long packet_id = read_varint(buffer + offset, bytes_read);
        printf(">> Packet ID is %llu\n", packet_id);
        offset = sizeof(bytes_read);
        printf(">> Read %llu bytes...\n", offset);

        close(accepted);
    }
    
    shutdown(server_fd, SHUT_RDWR);
    return 0;
}
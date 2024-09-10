#include <stdio.h>
#include <stdlib.h>

void tcp_server();
void udp_server();
void tcp_client();
void udp_client();

int main() {
    int choice;
    
    printf("Select an option:\n");
    printf("1. Run TCP server\n");
    printf("2. Run UDP server\n");
    printf("3. Run TCP client\n");
    printf("4. Run UDP client\n");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            tcp_server();
            break;
        case 2:
            udp_server();
            break;
        case 3:
            tcp_client();
            break;
        case 4:
            udp_client();
            break;
        default:
            printf("Invalid option.\n");
            break;
    }
    
    return 0;
}

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);

    // Enlazar el socket
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    std::cout << "Esperando mensajes..." << std::endl;

    int num1, num2, sum;
    recvfrom(serverSocket, (char*)&num1, sizeof(num1), 0, (sockaddr*)&clientAddr, &clientAddrSize);
    recvfrom(serverSocket, (char*)&num2, sizeof(num2), 0, (sockaddr*)&clientAddr, &clientAddrSize);

    sum = num1 + num2;
    sendto(serverSocket, (char*)&sum, sizeof(sum), 0, (sockaddr*)&clientAddr, clientAddrSize);

    // Cerrar el socket
    closesocket(serverSocket);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}

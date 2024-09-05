#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(54000);

    // Enlazar el socket
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Escuchar conexiones entrantes
    listen(serverSocket, SOMAXCONN);

    std::cout << "Esperando conexiones..." << std::endl;

    // Aceptar una conexión
    clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);

    int num1, num2, sum;
    recv(clientSocket, (char*)&num1, sizeof(num1), 0);
    recv(clientSocket, (char*)&num2, sizeof(num2), 0);

    sum = num1 + num2;
    send(clientSocket, (char*)&sum, sizeof(sum), 0);

    // Cerrar sockets
    closesocket(clientSocket);
    closesocket(serverSocket);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}

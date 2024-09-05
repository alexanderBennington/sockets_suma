#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    SOCKET clientSocket;
    sockaddr_in serverAddr;

    // Inicializar Winsock
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Crear el socket del cliente
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Configurar la dirección del servidor
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddr.sin_port = htons(54000);

    // Conectar al servidor
    connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    int num1 = 5, num2 = 10, sum;
    send(clientSocket, (char*)&num1, sizeof(num1), 0);
    send(clientSocket, (char*)&num2, sizeof(num2), 0);

    recv(clientSocket, (char*)&sum, sizeof(sum), 0);
    std::cout << "La suma es: " << sum << std::endl;

    // Cerrar el socket
    closesocket(clientSocket);

    // Limpiar Winsock
    WSACleanup();

    return 0;
}

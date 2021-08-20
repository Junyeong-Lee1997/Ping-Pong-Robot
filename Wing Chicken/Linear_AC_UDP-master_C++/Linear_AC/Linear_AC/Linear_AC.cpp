// Linear_AC.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*

#include <stdio.h>
#include <winsock2.h> // 윈속 헤더 포함 
#include <windows.h> 
#include <iostream>
#include <stdlib.h>
#include "CLinear_actu.h"
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#define BUFFER_SIZE 8 // 버퍼 사이즈

using namespace std;

int main(void)
{
    std::string dir = "C:\\Users\\admin\\Desktop\\ajin20190628.mot";
    CLinear_actu Acc_Ptr(dir);

    WSADATA wsaData; // 윈속 데이터 구조체.(WSAStartup() 사용할꺼!)
    SOCKET ServerSocket; // 소켓 선언
    SOCKADDR_IN ServerInfo; // 서버 주소정보 구조체
    SOCKADDR_IN FromClient; // 클라이언트에서 받는 주소정보 구조체

    int FromClient_Size; // 클라이언트로부터 받는 메시지 크기
    int Recv_Size; // 받는 사이즈
    int Send_Size; // 보내는 사이즈
    int Count;

    char Buffer[BUFFER_SIZE];
    short ServerPort = 7777; // 서버 포트번호

    //WSAStartup은 WS2_32.DLL을 초기화 하는 함수
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup 설정에서 문제 발생하면
    {
        cout << "WinSock 초기화부분에서 문제 발생 " << endl;
        WSACleanup(); // WS2_32.DLL의 사용 끝냄
    }

    // memset : 사용자가 정한 메모리 크기만큼 메모리 영역을 특정한 값으로 채움
    memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0으로 초기화
    memset(&FromClient, 0, sizeof(FromClient));
    memset(Buffer, 0, BUFFER_SIZE);

    ServerInfo.sin_family = AF_INET; // IPv4 주소체계 사용 
    ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1"); // 루프백 IP. 즉 혼자놀이용..
    ServerInfo.sin_port = htons(ServerPort); // 포트번호

    // 소켓 생성
    ServerSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // udp용 소켓 생성. SOCK_DGRAM : UDP 사용
    if (ServerSocket == INVALID_SOCKET) // 에러 발생시
    {
        cout << "소켓을 생성할수 없습니다." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(0);
    }

    // bind() - 새로 오는 클라이언트를 받을 welcome 소켓
    // 전달만 할꺼면 필요없음
    if (bind(ServerSocket, (struct sockaddr*)&ServerInfo, //바인드 소켓에 서버정보 부여
        sizeof(ServerInfo)) == SOCKET_ERROR)
    {
        cout << "바인드를 할 수 없습니다." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(0);
    }

    int bf = 0;
    int x = 0;  // vision x 좌표
    int y = 0;  // vision y 좌표

    while (1)
    {
        FromClient_Size = sizeof(FromClient);
        // recvfrom : UDP통신 비연결형.  패킷수신
        Buffer[0] = '\0';
        Buffer[1] = '\0';
        Buffer[2] = '\0';
        Buffer[3] = '\0';
        Recv_Size = recvfrom(ServerSocket, Buffer, BUFFER_SIZE, 0,
            (struct sockaddr*)&FromClient, &FromClient_Size);

        if (Recv_Size < 0)
        {
            cout << "recvfrom() error!" << endl;
            exit(0);
        }
        
        x = atoi(Buffer) / 1000 - 1000;
        y = atoi(Buffer) % 1000 - 100;

        // int bf = atoi(Buffer); // atoi 함수 양수는 제대로 안됨
        if (abs(bf - y) > 1 && x < 100) {
            bf = y;
        }
        else continue;

        // Acc_Ptr.move_actu(bf, 700, 200);        // linear 제어
        //cout << "패킷수신됨! 패킷을 보낸 클라이언트는 " << inet_ntoa(FromClient.sin_addr) << endl;
        cout << "패킷의 데이터는 " << bf << endl;

        //  패킷송신
        Send_Size = sendto(ServerSocket, Buffer, Recv_Size, 0,
            (struct sockaddr*)&FromClient, sizeof(FromClient));
        cout << "send!" << endl;
        if (Send_Size != Recv_Size)
        {
            cout << "sendto() error!" << endl;
            exit(0);
        }
    }
    cout << "off" << endl;
    closesocket(ServerSocket); // 소켓을 닫습니다.
    WSACleanup();
    Acc_Ptr.~CLinear_actu();

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
*/

// Linear_AC.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//



#include <stdio.h>
#include <winsock2.h> // 윈속 헤더 포함 
#include <windows.h> 
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <ws2tcpip.h>
#include "CLinear_actu.h"
#pragma comment (lib,"ws2_32.lib") // 윈속 라이브러리 링크
#define BUFFER_SIZE 256 // 버퍼 사이즈

using namespace std;

void ErrorHandling(char* message);

int main(void)
{
    //std::string dir = "C:\\Users\\admin\\Desktop\\ajin20190628.mot";
    std::string dir = "C://Users//WingC//source//repos//ajin20190628.mot";
    CLinear_actu Acc_Ptr(dir);

    WSADATA wsaData; // 윈속 데이터 구조체.(WSAStartup() 사용할꺼!)
    SOCKET ServerSocket; // 소켓 선언
    SOCKADDR_IN ServerInfo; // 서버 주소정보 구조체
    SOCKADDR_IN FromClient; // 클라이언트에서 받는 주소정보 구조체

    int FromClient_Size; // 클라이언트로부터 받는 메시지 크기
    int Recv_Size; // 받는 사이즈
    int Send_Size; // 보내는 사이즈
    int Count;
    int state, strLen;

    char Buffer[BUFFER_SIZE];
    short ServerPort = 8888; // 서버 포트번호

    struct ip_mreq joinAddr;

    //WSAStartup은 WS2_32.DLL을 초기화 하는 함수
    if (WSAStartup(0x202, &wsaData) == SOCKET_ERROR) // WSAStartup 설정에서 문제 발생하면
    {
        cout << "WinSock 초기화부분에서 문제 발생 " << endl;
        WSACleanup(); // WS2_32.DLL의 사용 끝냄
    }

    // memset : 사용자가 정한 메모리 크기만큼 메모리 영역을 특정한 값으로 채움
    memset(&ServerInfo, 0, sizeof(ServerInfo)); // 0으로 초기화
    memset(&FromClient, 0, sizeof(FromClient));
    memset(Buffer, 0, BUFFER_SIZE);

    ServerInfo.sin_family = AF_INET; // IPv4 주소체계 사용 
    ServerInfo.sin_addr.s_addr = inet_addr("127.0.0.1");
    ServerInfo.sin_port = htons(ServerPort); // 포트번호

    // 소켓 생성
    ServerSocket = socket(PF_INET, SOCK_DGRAM, 0); // udp용 소켓 생성. SOCK_DGRAM : UDP 사용
    if (ServerSocket == INVALID_SOCKET) // 에러 발생시
    {
        cout << "소켓을 생성할수 없습니다." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(0);
    }

    // bind() - 새로 오는 클라이언트를 받을 welcome 소켓
    // 전달만 할꺼면 필요없음
    if (bind(ServerSocket, (struct sockaddr*)&ServerInfo, //바인드 소켓에 서버정보 부여
        sizeof(ServerInfo)) == SOCKET_ERROR)
    {
        cout << "바인드를 할 수 없습니다." << endl;
        closesocket(ServerSocket);
        WSACleanup();
        exit(0);
    }
    joinAddr.imr_multiaddr.s_addr = inet_addr("127.0.0.1");
    joinAddr.imr_interface.s_addr = htonl(INADDR_ANY);
    state = setsockopt(ServerSocket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&joinAddr, sizeof(joinAddr));
    // if (state == SOCKET_ERROR) ErrorHandling("setsockopt error");

    int bf = 0;
    int temp = 0;
    int bff = 0;
    int acc = 0;
    /*
    int x = 0;
    int y = 0;  // 리니어 y 좌표
    */

    while (1)
    {
        FromClient_Size = sizeof(FromClient);
        // recvfrom : UDP통신 비연결형.  패킷수신
        Buffer[0] = '\0';
        Buffer[1] = '\0';
        Buffer[2] = '\0';
        Buffer[3] = '\0';
        Recv_Size = recvfrom(ServerSocket, Buffer, BUFFER_SIZE, 0,
            (struct sockaddr*)&FromClient, &FromClient_Size);

        if (Recv_Size < 0)
        {
            cout << "recvfrom() error!" << endl;
            exit(0);
        }

        // x = atoi(Buffer) / 1000 - 1000;
        temp = bf/0.0943;
        bf = -0.0943 * atoi(Buffer);
        bff = bf/0.0943;
        if (abs(bff - temp) > 200)
            acc = 1000;
        else
            acc =  abs(bff - temp) + 800;

        // int bf = atoi(Buffer); // atoi 함수 양수는 제대로 안됨
        /* if (abs(bf - y) > 1 && x < 100) {
            bf = y;
        }
        else continue;
        */
        //(bf-temp)/1000+800


        Acc_Ptr.move_actu(bf, 800, acc);        // linear 제어
        //cout << "패킷수신됨! 패킷을 보낸 클라이언트는 " << inet_ntoa(FromClient.sin_addr) << endl;
        cout << "UDP data:" << bf << endl;

        //  패킷송신
        Send_Size = sendto(ServerSocket, Buffer, Recv_Size, 0,
            (struct sockaddr*)&FromClient, sizeof(FromClient));
        if (Send_Size != Recv_Size)
        {
            cout << "sendto() error!" << endl;
            exit(0);
        }
    }
    cout << "off" << endl;
    closesocket(ServerSocket); // 소켓을 닫습니다.
    WSACleanup();
    Acc_Ptr.~CLinear_actu();

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.



/*


####################


2021-07-10 22:51 결론 : 25000 unit = 10.42
맨 오른쪽으로 처박아서 0 unit 이 되게 설정 (EzMotion 에서 Command Position 하고 Actual Position 이 같도록 clear 해주기)
이상태에서 진행하는데, labview 에 0 이나 -200 넣으면 끝단에 박아서 멈추니까 조심 (각각 0 unit 과 500000 unit 에 해당)
비교적으로 정확한 값이 측정되는 부분은
5000 unit = 28.2cm
130000 unit = 80.3cm
255000 unit = 132.4cm
380000 unit = 184.5cm
이 부분들을 활용하여 계산해보니
25000 unit = 10.42cm에 해당되는걸 알수있음

참고로 0 unit 은 26.116cm 로 측정됨
측정방식은 줄자를 유리문쪽 끝단위에 올려두고 후크를 철판왼쪽끝에 거는것으로 설정하였음

그리고 이거 실행안되면 project1 한번 실행하고 이거 실행하면 잘됨 ㅋㅋ

*/ 


// 결론 = 250 unit 은 1.04mm 
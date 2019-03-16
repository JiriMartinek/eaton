/*
The problem to solve is following:
    You monitor devices, which are sending data to you.
    Each device have a unique name.
    Each device produces measurements.

Challenge is:
    Compute number of messages you got or read from the devices.
*/
#include "common.h"
#include <unordered_map>
#include <string>
#include <pthread.h>

#define MESSAGE(type, message) messageHandler("Server", type, message)

//<! storage of the number of messages
std::unordered_map<std::string, size_t> messagesCounterMap;

/** handle socket data
 * @param socketfd socket descriptor
*/
void handleData(int socketfd)
{
    T_Packet data;
    size_t receivedBytes = read(socketfd, &data, sizeof(T_Packet));
    assert(receivedBytes == sizeof(T_Packet));
    std::string key = std::string(data.deviceName);
    //TODO handle received measurement
    //std::string measurement = std::string(data.deviceMeasurement);
    size_t value = 0;
    if (messagesCounterMap.find(key) != messagesCounterMap.end()) {
        value = messagesCounterMap[key];
    }
    messagesCounterMap[key] = ++value;

#if DEBUG_
    char dbgMessage[BUFSIZE];
    sprintf(dbgMessage, "handleData() received %d bytes", receivedBytes);
    MESSAGE(MSG_INFO, dbgMessage);
    sprintf(dbgMessage, "handleData() %s:%s", data.deviceName, data.deviceMeasurement);
    MESSAGE(MSG_INFO, dbgMessage);
    sprintf(dbgMessage, "handleData()-map %s:%d", data.deviceName, value);
    MESSAGE(MSG_INFO, dbgMessage);
#endif
}

/** show information about the count of received messages each 5 seconds
 * @param argument nothing is expected
*/
void* statisticLoop(void *argument){
    char message[BUFSIZE];
    while(true)
    {
        size_t sum = 0;
        for ( const auto &pair : messagesCounterMap ) {
            sprintf(message, "Number of messages per device %s:%d", pair.first.c_str(), pair.second);
            sum += pair.second;
            MESSAGE(MSG_INFO, message);
        }
        sprintf(message, "Number of all messages: %d\n------\n", sum);
        MESSAGE(MSG_INFO, message);
        sleep(5);
    }
}

/** tcp loop
 * @param argument nothing is expected
*/
void* tcpLoop(void *argument)
{
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // create TCP socket
    if ((sockfd) < 0)
    {
        MESSAGE(MSG_ERROR, "creating socket");
        exit(1);
    }

    struct sockaddr_un serverAddress; //!< server address structure
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, IP_PORT);

    if (bind(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        MESSAGE(MSG_ERROR, "binding socket");
        exit(1);
    }

    listen(sockfd, MAX_NUM_OF_CLIENTS);
    struct sockaddr_un clientAddress; //!< client address structure
    socklen_t clientAddrLen = sizeof(clientAddress);
    /*endless loop*/
    while(true)
    {
        int newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddrLen);
        if (newsockfd < 0)
        {
            MESSAGE(MSG_ERROR, "accepting client");
        }
        else
        {
            handleData(newsockfd);
            close(newsockfd);
        }
    }
    close(sockfd);
}

/** the main function
 * @param argc number of parameters - nothing is expected
 * @param argv array of parameters
*/
int main(int argc, char* argv[])
{
    pthread_t threadTcp;
    int rv1 = pthread_create( &threadTcp, NULL, tcpLoop, (void*)"threadTcp");

    pthread_t threadStatistic;
    int rv2 = pthread_create( &threadStatistic, NULL, statisticLoop, (void*)"threadStatistic");

    if (rv1 || rv2)
    {
        MESSAGE(MSG_ERROR, "create thread(s)");
    }
    else
    {
        pthread_join(threadStatistic, NULL);
        pthread_join(threadTcp, NULL);
    }

    return 0;
}

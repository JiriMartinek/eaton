/* a client simulation a device */
#include "common.h"

#define MESSAGE(type, message) messageHandler("Client", type, message)

/** the main function
 * @param argc number of parameters - expected 2 parameters
 * @param argv array of parameters - "device name" "measurement value"
*/
int main(int argc, char *argv[])
{
    assert(argc == 3); //expected 2 parameters
    int sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // create TCP socket
    if ((sockfd) < 0)
    {
        MESSAGE(MSG_ERROR, "creating socket");
        exit(1);
    }

//connect to the server
    struct sockaddr_un serverAddress; //!< server address structure
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sun_family = AF_UNIX;
    strcpy(serverAddress.sun_path, IP_PORT);

    if (connect(sockfd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0)
    {
        MESSAGE(MSG_ERROR, "Connecting");
        exit(1);
    }

//create and send data packet
    T_Packet packet;
    memset(&packet, 0, sizeof(packet));
    strcpy(packet.deviceName, argv[1]);
    strcpy(packet.deviceMeasurement, argv[2]);
    write(sockfd, &packet, sizeof(packet));

    close(sockfd);
    return 0;
}

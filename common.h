#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/un.h>
#include <stdio.h>
#include <assert.h>

//<! communication buffer length
#define BUFSIZE 1024

//<! communication TCP/IP port
#define IP_PORT "12345"

//<! maximum number of clients
#define MAX_NUM_OF_CLIENTS 64

#define MSG_ERROR "Error"
#define MSG_WARNING "Warning"
#define MSG_INFO "Info"

/** handle message, used by the macro(s) MESSAGE
 * @param sender identification of the sender
 * @param type message type - ERROR, WARNING, INFO, ...
 * @param message given message
*/
void messageHandler(const char* sender, const char* type, const char* message)
{
    printf("%s reports: %s: %s\n",  sender, type, message); //FIX-ME use some logging system
}

struct T_Packet
{
    char deviceName[32];
    char deviceMeasurement[128];
} T_Packet_;


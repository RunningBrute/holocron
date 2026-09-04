#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "holocron/message/Message.h"

#define MAX_MESSAGE_SIZE 256

typedef struct Message
{
    int senderId;
    int receiverId;
    char payload[MAX_MESSAGE_SIZE];
} Message;

Message* createMessage(const int senderId, const int receiverId, const char* payloadToSend, const int payloadSize)
{
    Message* message = malloc(sizeof(*message));

    message->senderId = senderId;
    message->receiverId = receiverId;
    memcpy(message->payload, payloadToSend, payloadSize);

    printf("Message! %s \n", message->payload);

    return message;
}

void destroyMessage(Message* message)
{
    free(message);
}
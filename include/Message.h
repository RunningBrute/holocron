#ifndef MESSAGE_H
#define MESSAGE_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Message Message;

Message* createMessage(const int senderId, const int receiverId, const char* payloadToSend, const int payloadSize);
void destroyMessage(Message* message);

#ifdef __cplusplus
}
#endif


#endif
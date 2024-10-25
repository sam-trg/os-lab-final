// time receiver message queue
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    int users;
    int hours;
    int minutes;
} message;

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    int hour_users[24] = {0};
    int hour_count[24] = {0};

    while (1) {
        msgrcv(msgid, &message, sizeof(message) - sizeof(long), 1, 0);

        hour_users[message.hours] += message.users;
        hour_count[message.hours]++;

        float avg = (float)hour_users[message.hours] / hour_count[message.hours];
        printf("Average users at hour %02d: %.2f\n", message.hours, avg);
    }

    return 0;
}

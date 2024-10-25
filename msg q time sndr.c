// time sender message queue
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

struct msg_buffer {
    long msg_type;
    int users;
    int hours;
    int minutes;
} message;

int get_users() {
    return rand() % 10; // Simulate number of users (0 to 9)
}

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);

    while (1) {
        time_t t = time(NULL);
        struct tm *tm_info = localtime(&t);

        message.msg_type = 1;
        message.users = get_users();
        message.hours = tm_info->tm_hour;
        message.minutes = tm_info->tm_min;

        msgsnd(msgid, &message, sizeof(message) - sizeof(long), 0);
        printf("Sent: %d users at %02d:%02d\n", message.users, message.hours, message.minutes);
        sleep(600); // Wait 10 minutes
    }

    return 0;
}

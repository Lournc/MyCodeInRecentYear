#include <sys/socket.h>
#include <sys/types.h>

int main() { auto clientfd = socket(AF_INET, SOCK_STREAM, 0); }
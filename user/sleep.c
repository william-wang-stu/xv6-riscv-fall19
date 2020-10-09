#include <kernel/types.h>
#include <user/user.h>

int main(int argc, char *argv[]){
	if (argc != 2)
		write(2, "Error Message!\n", strlen("Error Message!\n"));

	int x = atoi(argv[1]);

	sleep(x);

	exit();
}

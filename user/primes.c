#include "kernel/types.h"
#include "user/user.h"

// Reference: Sieve of Eratosthenes
// Pseudocode:
//	p = get a number from left neighbour
//	print p
//	loop:
//	  n = get a number from left neighbour
//	  if (n % p != 0)
//	     send n to right neighbour

int main(int argc, char* argv[]){
	
	int fd[2];
	int iter_cnt = 0;	// cnt of primes per iteration
	int buffer[34];	// maximum storage of 2 to 35
	
	for(int i=2;i<=35;i++){
		buffer[iter_cnt++] = i;
	}
	
	while(iter_cnt > 0){
		pipe(fd);
		if (fork() == 0){
			close(fd[1]);
			
			// Reset iter_cnt
			iter_cnt = 0;
			
			// Applying the Algorithm above
			int p, n;
			if (read(fd[0], &p, sizeof(p)) != 0){
				printf("prime %d\n", p);
				while(read(fd[0], &n, sizeof(n)) != 0){
					if (n % p != 0){
						buffer[iter_cnt++] = n;
					}
				}
			}
			
			close(fd[0]);
		}
		else{
			close(fd[0]);
			for(int i=0; i<iter_cnt; i++){
				write(fd[1], &buffer[i], sizeof(buffer[i]));
			}
			close(fd[1]);
			wait();
			
			// parent process only provides numbers for the first time
			break;
		}
	}
	
	exit();
}

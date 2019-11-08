/*------------------------------------------------------*/
/* Skeleton for the synchronization Lab .   assignment */
/*------------------------------------------------------*/
/* Note:	                       */
/* -----	                       */
/* 1. E = Elephant	                   */
/* 2. D = Dog	                   */
/* 3. C = Cat	                   	*/
/* 4. M = Mouse	                   */
/* 5. P = Parrot	                   */
/*------------------------------------------------------*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define  CHILD	0       /* Return value of child proc from fork call */

int main()
{
    sem_t * elephant_mouse; /* my semaphores */
    sem_t * mouse_parrot;
    sem_t * cat_dog;
    sem_t * parrot_cat;
    int pid;	/* Process id after fork call */
    int i;	/* Loop index. */
    int N;	/* Number of requests to process */
    int status;  	/* Exit status of child process. */
    int type;           /* Type of animal */


    /*   Initialization of the semaphores   */
      if ((elephant_mouse = sem_open("elephant_mouse", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }
  if (( cat_dog = sem_open("cat_dog", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }
  if ((parrot_cat = sem_open("parrot_cat", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }
  if ((mouse_parrot = sem_open("mouse_parrot", O_CREAT, 0644, 1)) == SEM_FAILED) {
    perror("semaphore initilization");
    exit(1);
  }
  
  
     
    printf("How many requests to be processed: \n");
    scanf("%d",&N);

    for (i=1; i<=N; i++) {
        printf("Who wants in (E=1)(D=2)(C=3)(M=4)(P=5): \n");
        fflush(stdout);
        scanf("%d",&type);
        if ((pid = fork()) == -1) {
   	       /* Fork failed! */
       perror("fork");
       exit(1);
        }
        
        
        if (pid == 0) {
       pid = getpid();
            switch (type) {

   case 1: /* Elephant code*/
                    printf("     Elephant process with pid %d wants in.\n",pid);
                   fflush(stdout);
                   sem_wait(elephant_mouse);
           
                    printf("     Elephant process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Elephant process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(elephant_mouse);
                    break;

   case 2:  /*Dog code*/
                    printf("     Dog process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(cat_dog);
                  
                    printf("     Dog process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Dog process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(cat_dog);
           break;

   case 3: /*Cat Code*/
                    printf("     Cat process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(parrot_cat);
                    sem_wait(cat_dog);
                    printf("     Cat process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Cat process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(parrot_cat);
                    sem_post(cat_dog);
           break;

   case 4: /*Mouse code*/
                    printf("     Mouse process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(elephant_mouse);
                    sem_wait(mouse_parrot);
                    printf("     Mouse process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Mouse process with pid %d is out.\n",pid);
                    fflush(stdout); 
                    sem_post(elephant_mouse);
                    sem_post(mouse_parrot);
           break;

   case 5: /*Parrot  Code*/
                    printf("     Parrot process with pid %d wants in.\n",pid);
                    fflush(stdout);
                    sem_wait(parrot_cat);
                    sem_wait(mouse_parrot);
                    printf("     Parrot process with pid %d is in.\n",pid);
                    fflush(stdout);
                    sleep(rand()%10);
                    printf("     Parrot process with pid %d is out.\n",pid);
                    fflush(stdout);
                    sem_post(parrot_cat);
                    sem_post(mouse_parrot);
           break;
            }
            exit(0);
        }
    }
    
    /* Now wait for the child processes to finish */
    for (i=1; i<=N; i++) {
        pid = wait(&status);
        printf("Child (pid = %d) exited with status %d.\n", pid, status);
        fflush(stdout);
    }
}

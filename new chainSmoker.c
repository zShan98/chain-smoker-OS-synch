#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <semaphore.h>
#include <sys/syscall.h>
#include <linux/kernel.h>

sem_t stick;

sem_t card;

sem_t powder;



void *brooker()
{
int iteration=0, smoked=0,paper=0,match=0;

sleep(2);

printf("ciggerete Smoked: 0");

 while (true)

{

      int number = rand() % 3;

     

if(iteration == 12){

printf( "\nsmoker with the Tobacco: %d\n", smoked);

printf( "smoker with the papers: %d\n", paper);

printf( "smoker with the Match Sticks: %d\n", match);

exit(0);



}



sleep(1);



    if(number == 0){

sem_post (&stick);

sem_post (&card);

printf("\nAgent has put Match sticks and papers on the table\n");

printf("ciggerete Smoked: %d\n", iteration + 1);

smoked++;

}

else if(number == 1){

sem_post (&stick);

sem_post (&powder);

printf("\nAgent has put Match sticks and tobacco powder on the table\n");

printf( "ciggerete Smoked: %d\n", iteration + 1);

paper++;

}

else{

sem_post (&card);

sem_post (&powder);

printf("\nAgent has put papers and tobacco on the table\n");
printf( "ciggerete Smoked: %d\n", iteration + 1);

match++;



}



iteration++;



    }

 

   



}







void *powderGuy ()

{



  while (true){

 

    sem_wait (&stick);

    if (sem_trywait (&card) == 0)

    {

printf("Match sticks and papers feched");

    }

else sem_post (&stick);



    }



}





void *stickGuy (){
	
  while (true){
      sem_wait (&card);
      if (sem_trywait(&powder) == 0){
		printf("Tobacco powder and ciggreate paper taken");
        }
      else
  		sem_post (&card);

    }
}







void *cardGuy ()
{
  while (true){
      sem_wait (&powder);

 if (sem_trywait (&stick) == 0) {
printf("Match sticks and paper taken");
        }
      else
  sem_post (&powder);
    }



}





int main() {

pthread_t pt1, pt2, pt3, pt4;

sem_init(&stick,0,0);

sem_init(&card,0,0);

sem_init(&powder,0,0);


pthread_create(&pt1,NULL, brooker,NULL);
pthread_create(&pt2,NULL, powderGuy ,NULL);
pthread_create(&pt3,NULL, cardGuy ,NULL);
pthread_create(&pt4,NULL, stickGuy ,NULL);


    pthread_join(pt1,NULL);
    pthread_join(pt2,NULL);
    pthread_join(pt3,NULL);
    pthread_join(pt4,NULL);

   
// Kernel replica

    sema_init(&stick, 0);
    sema_init(&card, 0);
    sema_init(&powder, 0);

kthread_create(brooker, NULL, "Brooker");
kthread_create(powderGuy, NULL, "powderGuy");
kthread_create(cardGuy, NULL, "cardGuy");
kthread_create(stickGuy, NULL, "stickGuy");


return 0;



}
	


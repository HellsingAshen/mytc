#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define CHAR_ARR_LEN_MAX 1024
#define TC_BIE(ret) \
	if (0 != ret) { break;}

int g_iNum = 0;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
/*
 *@des： 线程的执行函数,不使用条件量，让三个线程依次执行，ABCABC...
 *@caution: 
 */
void *
Th_Printf (void *in)
{
  int iRet = 0;
  int iIn = (int *) in;
  do
    {
      printf (" in id = [%d]\n", (int *) in);
      while (0 == pthread_mutex_trylock (&mutex))
	{
	  if (g_iNum != (((int *) in)))
	    {
	      printf ("selfid =[%x] donothing.\n", pthread_self ());
	      pthread_mutex_unlock (&mutex);
	      sleep (1);
	    }
	  else
	    {

	      printf ("thread_tag = [%s]  th_id = [%x] id = [%d]\n",
		      (iIn == 0) ? "A" : ((iIn == 1) ? "B" : "C"),
		      pthread_self (), (int *) in);
	      g_iNum = (g_iNum + 1) % 3;
	      pthread_mutex_unlock (&mutex);
	    }
	}
    }
  while (0);

}

void *
ThCond_Printf (void *in)
{
  int iRet = 0;
  int iIn = (int *) in;
  do
    {
      //printf(" in id = [%d]\n",  (int*)in);
      while (1)
	{
	  printf (" In Loopin id = [%d]\n", (int *) in);
	  while (0 == pthread_mutex_trylock (&mutex))
	    {
	      /*这里纠结了下 */
	      while (g_iNum != (((int *) in)))
		{
		  printf ("selfid =[%x] g= [%d] in = [%d] start waiting...\n",
			  pthread_self (), g_iNum, (int *) in);
		  pthread_mutex_unlock (&mutex);
		  pthread_cond_wait (&cond, &mutex);
		}


	      printf ("thread_tag = [%s]  th_id = [%x] id = [%d] g= [%d]\n",
		      (iIn == 0) ? "A" : ((iIn == 1) ? "B" : "C"),
		      pthread_self (), (int *) in, g_iNum);
	      g_iNum = (g_iNum + 1) % 3;
	      pthread_cond_broadcast (&cond);
	      pthread_mutex_unlock (&mutex);
	    }
	  sleep (1);
	}
    }
  while (0);

}
#pragma pack(1)
    struct tagAAA
    {
        unsigned char a : 1;
        unsigned char b : 2;
        unsigned char c : 6;
        unsigned char d : 4;
        unsigned char e;
        unsigned char f : 4;
        unsigned char g;
    }AAA_s;
#pragma pack()
int
main (char* args[], int argc)
{
		printf("%d\t\n", sizeof(AAA_s));
	
#if 0
  pthread_t t_id[3];
  int i = 0;
  int iRet = 0;
  char sPara[CHAR_ARR_LEN_MAX] = {0};
  while (i < argc)
    {
  	if (0 == memcmp(args[i], "-c", strlen("-c")))
	{
		printf("%s\t\n", args[i+1]);
	    
	}
	i++;
    }
  int *apiArr[3] = { 0, 1, 2 };
  for (i = 0; i < 3; i++)
    {
      //iRet = pthread_create(&t_id[i], NULL, Th_Printf, apiArr[i]); 
      iRet = pthread_create (&t_id[i], NULL, ThCond_Printf, apiArr[i]);
      TC_BIE (iRet);
    }
  for (i = 0; i < 3; i++)
    {
      iRet = pthread_join (t_id[i], NULL);
      TC_BIE (iRet);
    }
#endif

  return 0;
}

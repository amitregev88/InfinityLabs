
/****************************************************************************/
/*	Project:	multi threaded counting sort        						*/
/*	Date: 		07/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:	            												*/
/*	Version: 	1.00														*/
/****************************************************************************/
/****************************************************************************/
/*                     includes                                             */
/****************************************************************************/
#include <stdio.h> /*printf*/
#include <stdlib.h> /* malloc */
#include <assert.h> /* assert  */
#include <sys/mman.h> /* mmap */
#include <fcntl.h> /*open*/
#include <sys/stat.h> /*fstat*/
#include <pthread.h> /* pthread_create*/
#include <unistd.h> /* sysconf */
#include <sys/stat.h> /*struct statbuf */
#include <string.h> /* memcpy */
#include "utility.h"
/***************************************************************************/
/*                                             macros                      */
/***************************************************************************/
#define DICTIONARY_PATH "/usr/share/dict/words" /*/etc/dictionaries-common/words*/
#define NUM_OF_THREADS 5
#define NUM_OF_COPIES 5000
#define ASCII_SIZE 256
/****************************************************************************/
/*                          enums                                           */
/****************************************************************************/
enum {SUCCESS, FAILURE};
/******************************************************************************/
/*                    forward declaration                                     */
/******************************************************************************/
typedef struct
{
    char *dict_iter;
    size_t letters_total;
}dict_info_ty;

typedef struct
{
    int *histogram;
    char *from;
    size_t num_of_letters;
    long cache_line_size;
}dict_thread_ty;

typedef void* (*func_dict_ty)(void*);
/******************************************************************************/
/*                    functions  declaration                                 */
/******************************************************************************/
static int AllocGetDictData(dict_info_ty *_data);
static pthread_t *CreateThreads(dict_thread_ty *data_for_thread, int *total_histogram);
static void InitDataForEachThread(dict_info_ty *data, dict_thread_ty *data_for_thread);
static int CountLetters(dict_info_ty *data);
static void *ThreadCount(void *data_for_thread);
static void SumHistograms(int *histogram_total, int *histogram_from_thread);
/******************************************************************************/
/*                    function  definitions                                   */
/******************************************************************************/
int main()
{
    
    clock_t start = 0;
    clock_t end = 0;
    dict_info_ty data = {0};
 
    AllocGetDictData(&data); 
    /*check if fail*/

    start = clock();
    CountLetters(&data);
    /*check if fail*/

    end = clock(); 
    
    printf("The runtime to count dictonaty letters by %d threads %d copies took  %f sec\n", NUM_OF_THREADS, NUM_OF_COPIES, ((double)(end - start))/CLOCKS_PER_SEC);
    
    return SUCCESS;
}
/******************************************************************************/
/*                   AllocGetDictData function                                */
/******************************************************************************/
static int AllocGetDictData(dict_info_ty *_data)
{
    struct stat statbuf = {0};
    int file_descriptor = 0;
    char *dict_on_mem = NULL;
    size_t i = 0;
    
    file_descriptor  = open(DICTIONARY_PATH, O_RDONLY);
    ReturnErnoIfFail(file_descriptor >= 0, )
    /*check if fail*/
   
    /* checks the length of char in file and more info..  */
    fstat(file_descriptor, &statbuf);
    /*check if fail*/

    _data->letters_total = statbuf.st_size;

    dict_on_mem = (char *) mmap(NULL,_data->letters_total, PROT_READ, MAP_PRIVATE, file_descriptor, 0);
     /*check if fail*/

    close(file_descriptor);
    /*check if fail*/

    _data->dict_iter = (char *)malloc(_data->letters_total * sizeof(char) * NUM_OF_COPIES);
	/*check if fail*/

	for (i = 0; i < NUM_OF_COPIES; ++i)
	{
		memcpy(_data->dict_iter + (i * _data->letters_total), dict_on_mem, _data->letters_total);
	}

    munmap(dict_on_mem, _data->letters_total);
	/*check if fail*/

    return SUCCESS;
}
/******************************************************************************/
/*                   CreateThreads function                                   */
/******************************************************************************/
static pthread_t *CreateThreads(dict_thread_ty *data_for_thread, int *total_histogram)
{
    size_t i = 0;
    pthread_t *threads;
    int status = 0;

    threads = (pthread_t *)malloc(sizeof(pthread_t) * NUM_OF_THREADS);
    /*check if fail*/

    for (; i < NUM_OF_THREADS; ++i)
    {
        pthread_create(&threads[i], NULL, (func_dict_ty)ThreadCount,data_for_thread);
        RETURN_IF_FAIL(status == 0, "pthread_create() failed", NULL);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
    {
        status = pthread_join(threads[i], NULL);
        RETURN_IF_FAIL(status == 0, "pthread_join() failed", NULL);
        
        SumHistograms(total_histogram, data_for_thread->histogram);
    }

    return threads;
}
/******************************************************************************/
/*                   InitDataForEachThread function                           */
/******************************************************************************/
static void InitDataForEachThread(dict_info_ty *data, dict_thread_ty *data_for_thread)
{
    size_t i = 0;

    dict_thread_ty task_thread[NUM_OF_THREADS] = {0};

    size_t rest = data->letters_total % NUM_OF_THREADS;
    size_t prev_len = 0;
    size_t thread_letters = data->letters_total / NUM_OF_THREADS;
    

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        task_thread[i].from = data->dict_iter + (thread_letters * i) + prev_len;

        task_thread[i].num_of_letters = thread_letters + (rest > 0) ? 1 : 0;

        prev_len = task_thread[i].num_of_letters;
        --rest;
        task_thread[i].histogram = data_for_thread->histogram + i * (ASCII_SIZE +
                            data_for_thread->cache_line_size / sizeof(int));

    }
}
/******************************************************************************/
/*                   CountLetters function                                    */
/******************************************************************************/
static int CountLetters(dict_info_ty *data)
{
    int *cout_lut = NULL;
    dict_thread_ty *data_for_threads = NULL;
    pthread_t *threads = NULL;

    /* 	Initiallize an iter pointer, length of letters and histogram for each thread.	*/
	data_for_threads = (dict_thread_ty *)malloc(sizeof(dict_thread_ty) * NUM_OF_THREADS);
	/*check if fail*/


    /*checks the size of the Level 1 data cache.  */
	data_for_threads->cache_line_size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
	/*check if fail*/
    
    cout_lut = (int *)calloc(ASCII_SIZE, sizeof(int));
    /*check if fail*/

    /*	Initiallize a histogram for each thread with CACHE_LINE padding		*/	
	data_for_threads->histogram = (int *)calloc((sizeof(int) * ASCII_SIZE + 
                                data_for_threads->cache_line_size), NUM_OF_THREADS);
	/*check if fail*/

    InitDataForEachThread(data, data_for_threads);

    threads = CreateThreads(data_for_threads, cout_lut);
    /*check if fail*/
    
    free(threads);
	free(data_for_threads->histogram);
	free(data_for_threads);
    free(data->dict_iter);
    free(cout_lut);

    return SUCCESS;

}
/******************************************************************************/
/*                   ThreadCount function                                     */
/******************************************************************************/
static void *ThreadCount(void *data_for_thread)
{
	size_t i = 0;
	dict_thread_ty *args = NULL;
	unsigned char letter = 0;

	args = (dict_thread_ty *)data_for_thread;

	/* 	For each letter in the subarray - count occurence.*/
	for (i = 0; i < args->num_of_letters; ++i)
	{
		letter = args->from[i];
        ++args->from;
		++args->histogram[letter];
	}

	return args->histogram;
}
/******************************************************************************/
/*                   SumHistograms function                                   */
/******************************************************************************/
static void SumHistograms(int *histogram_total, int *histogram_from_thread)
{
	size_t i = 0;

	for (i = 0; i < ASCII_SIZE; ++i)
	{
		histogram_total[i] += histogram_from_thread[i];
	}
}
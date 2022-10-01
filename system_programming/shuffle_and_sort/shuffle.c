/****************************************************************************/
/*	Project:    Multi threaded count	    						        */
/*	Date: 		6/09/2022					    							*/
/*	Name: 		Amit Regev						    						*/
/*	Reviewer:		    		    	    							*/
/****************************************************************************/

#include <stdio.h>                  /* printf                             */
#include <stdlib.h>                 /* malloc, free, qsort                */
#include <string.h>                 /* memcpy                             */
#include <fcntl.h>                  /* open                               */
#include <time.h>                   /* clock_gettime                      */
#include <assert.h>                 /* assert                             */
#include <pthread.h>                /*pthread join, pthread create        */
#include <sys/mman.h>               /* mmap                               */
#include <unistd.h>                 /* sysconf                            */
#include <sys/stat.h>               /* stat                               */

#include "utility.h"

enum {SUCCESS = 0};
enum {NUM_OF_COPIES = 2};
enum {THREADS_NUM = 4};

typedef struct 
{
    char **start_data_arr;     /* beggin arr to calculate from */
    size_t num_of_elem;        /* num_of_elements in start data arr */
}thread_info_ty;

typedef struct
{
    char *dict_content_arr;
    size_t num_of_elem;
}dict_memo_info_ty;

/****************************************************************************/
static int ShuffleNSortDict(void);

/* function mapping english dictionary and init the mem_info param with data
   caller must use destroymemup. return 0 on success, 1 on failure */
static int CreateMemomap(dict_memo_info_ty *mem_info);

/* destroy memup acording to dict_memo_info_ty argument.
   return 0 on success, otherwise 1 */
static int DestroyMemap(dict_memo_info_ty *mem_info);

/* malloc large amount of data base acording to arguments. return handler to the
   data or null if fails. user must free */
char **CreateBigData(char **ptr_to_dict, size_t num_of_elem);

/* free the resources allocated at CreateBigData */
static void DestroyBigData(char **data_base);

/* malloc and init arr of pointers and return handler to it.return null if fails
   user must free  */
static char **CreateNInitPtr2Dict(char *privte_dict, size_t num_of_words);

/* free the resources allocated at CreateNInitPtr2Dict */
static void DestroyPtr2Dict(char **ptrs_to_dict);

/* func allocate memory and return handler to the copied data.
   the caller must free. return null if fails*/
static char *CopyDictIMP(dict_memo_info_ty *dict_mem_map);

/* destroy the allocated memory from CopyDictImp */
static void DestroyCopyDictIMP(char *copy_dict);

static void *ThreadSortingDataIMP(void *info_to_calc);
static size_t CountDictWordsIMP(const char *dict);
static int ShuffleFuncImp(const void *str1, const void *str2);
static int CmpFuncSortImp(const void *str1, const void *str2);
static void PrintTime(const struct timespec *start_time,
                                               const struct timespec *stop_time);
/****************************************************************************/

int main()
{
    return ShuffleNSortDict();
}
/****************************************************************************/

static int ShuffleNSortDict(void)
{
    int ret_status = 0;
    size_t i = 0;
    size_t res = 0;
    size_t num_of_words = 0;
    size_t work_amount = 0;
    struct timespec start_time = {0};
    struct timespec stop_time = {0};
    
    dict_memo_info_ty dict_mem_map = {0};
    thread_info_ty thread_info[THREADS_NUM] = {0};
    pthread_t thread_id[THREADS_NUM] = {0};
    
    char *privte_dict = NULL;
    char **ptrs_to_dict = NULL;
    char **database = NULL;

    /* CreateMemomap() with english dict*/
    ret_status = CreateMemomap(&dict_mem_map);
    RETURN_IF_BAD_ERNO(0 == ret_status, "memo map creation failed", 1);

    assert(dict_mem_map.dict_content_arr);

    /* copy file to heap */
    privte_dict = CopyDictIMP(&dict_mem_map);
    RETURN_IF_BAD(privte_dict, "copy dict fail", 1);
    /* destroy Memomap */
    ret_status = DestroyMemap(&dict_mem_map);
    RETURN_IF_BAD(0 == ret_status, "destroy memmup fail", 1);

    /* count number of words in dictionary */
    num_of_words = CountDictWordsIMP(privte_dict);
    
    /* malloc array of pointers to every word and init it */
    ptrs_to_dict = CreateNInitPtr2Dict(privte_dict, num_of_words);
    RETURN_IF_BAD(ptrs_to_dict, "malloc & init fail", 1);

    /* CreateBigData() */
    database = CreateBigData(ptrs_to_dict, num_of_words);
    RETURN_IF_BAD(database, "create big data fail", 1);

    /* shuffle the big data arr using qsort with rand*/
    qsort(database, num_of_words * NUM_OF_COPIES, sizeof(char*), ShuffleFuncImp);
    
    /* devide work according to num of threads */
    work_amount = num_of_words * NUM_OF_COPIES / THREADS_NUM;
    res = (num_of_words * NUM_OF_COPIES) % THREADS_NUM;

    /* init array of structs with thread info */
    for (i = 0; THREADS_NUM > i; ++i)
    {
        thread_info[i].start_data_arr = database + (work_amount * i);
        if (i == 0)
        {
            thread_info[i].num_of_elem = work_amount + res;
        }
        else
        {
            thread_info[i].num_of_elem = work_amount;
        }
    }

    /* clock_gettime */
    ret_status = clock_gettime(CLOCK_REALTIME, &start_time);
    RETURN_IF_BAD(0 == ret_status, "clock gettime fail", 1);

    /* create threads */
    for (i = 0; THREADS_NUM > i; ++i)
    {
        ret_status = pthread_create(&thread_id[i], NULL, ThreadSortingDataIMP, 
                                                                &thread_info[i]);
        RETURN_IF_BAD(0 == ret_status,"pthread create fail", 1);
    }

    /* join */
    for (i = 0; THREADS_NUM > i; ++i)
    {
        ret_status = pthread_join(thread_id[i], NULL);
        RETURN_IF_BAD(0 == ret_status, "join thread fail", 1);
    }    

    work_amount = num_of_words * NUM_OF_COPIES;

    /* merge arr - sort the arr after threads finished */
    qsort(database, work_amount, sizeof(char*), CmpFuncSortImp);

    /* check if sorted */
    for(i = 1; i < work_amount; ++i)
    {
        if (0 > strcmp(database[i],database[i - 1]))
        {
            puts("database isnt sorted at:");
            printf("%s \n",*(database + i));
            fflush(stdout);
        }
    }

    /* measure time */
    ret_status = clock_gettime(CLOCK_REALTIME, &stop_time);
    RETURN_IF_BAD(0 == ret_status, "clock gettime fail", 1);

    /* print time */
    PrintTime(&start_time, &stop_time);

    /* destroy  */
    DestroyCopyDictIMP(privte_dict);
    DestroyBigData(database);
    DestroyPtr2Dict(ptrs_to_dict);

    /* return 0 */
    return SUCCESS;
}
/****************************************************************************/

static int CreateMemomap(dict_memo_info_ty *mem_info)
{
    /* prep for memap */
    int ret_status = 0;
    struct stat file_info = {0};
    long size_of_file = 0;
    int fd = 0;
    char *ret_mmap = NULL;
    
    /* memmap english dictionary */
    ret_status = stat("/usr/share/dict/american-english", &file_info);
    RETURN_IF_BAD_ERNO(0 == ret_status, "stat func fail", 1);
    
    size_of_file = file_info.st_size;

    fd = open("/usr/share/dict/american-english", O_RDONLY);
    RETURN_IF_BAD_ERNO(-1 != fd, "open dictionary fail", 1);

    ret_mmap = mmap(NULL, size_of_file, PROT_READ, MAP_PRIVATE, fd, 0);

    close(fd);

    /* init struct */
    mem_info->dict_content_arr = ret_mmap;
    mem_info->num_of_elem = size_of_file;

    /* return 0 */
    return 0;
}
/****************************************************************************/
static char *CopyDictIMP(dict_memo_info_ty *dict_mem_map)
{
    char *dict = (char*)malloc(dict_mem_map->num_of_elem * sizeof(char) + 1);
    RETURN_IF_BAD(dict, "malloc fail allocate dict", NULL);

    dict[dict_mem_map->num_of_elem] = '\0';

    memcpy(dict, dict_mem_map->dict_content_arr, dict_mem_map->num_of_elem);

    return dict;
}
/****************************************************************************/
static void DestroyCopyDictIMP(char *copy_dict)
{
    free(copy_dict);
    copy_dict = NULL;
}
/****************************************************************************/

static size_t CountDictWordsIMP(const char *dict)
{
    size_t num_of_words = 0;

    assert(dict);

    while ('\0' != *dict)
    {
        if ('\n' == *dict)
        {
            ++num_of_words;
        }

        ++dict;
    }

    return num_of_words;
}
/****************************************************************************/

static char **CreateNInitPtr2Dict(char *privte_dict, size_t num_of_words)
{
    size_t i = 1;
    char *delimit = "\n";
    char **ptrs_to_dict = NULL;

    assert(privte_dict);
    
    /* malloc arr of ptrs */
    ptrs_to_dict = (char**)malloc(sizeof(char*) * num_of_words);
    RETURN_IF_BAD(ptrs_to_dict, "malloc ptrs to dicts fail", NULL);

    /* use strtok to init ptrs arr */
    *(ptrs_to_dict) = strtok(privte_dict, delimit);

    while (num_of_words > i)
    {
        *(ptrs_to_dict + i) = strtok(NULL, delimit);
        ++i;
    }

    return ptrs_to_dict;
}
/****************************************************************************/
static void DestroyPtr2Dict(char **ptrs_to_dict)
{
    free(ptrs_to_dict);
    ptrs_to_dict = NULL;
}
/****************************************************************************/

char **CreateBigData(char **ptr_to_dict, size_t num_of_elem)
{
    char **big_data = NULL;
    char **database = NULL;
    size_t num_to_multiply = NUM_OF_COPIES;

    assert(ptr_to_dict);

    /* malloc **big data in amount of NUM_TO_MULTIPLY_DATA 2 */
    big_data = (char**)malloc(num_of_elem * NUM_OF_COPIES * sizeof(char*));
    RETURN_IF_BAD(big_data, "malloc big data fail", NULL);

    /* save adderss */
    database = big_data;
    
    while (num_to_multiply > 0)
    {
        /* memcpy from the dictionary to the big data */
        memcpy(big_data, ptr_to_dict, num_of_elem * sizeof(char*));

        --num_to_multiply;
        big_data += num_of_elem;
    }
    
    /*return the saved address*/
    return database;
}
/****************************************************************************/
static void DestroyBigData(char **data_base)
{
    free(data_base);
    data_base = NULL;
}
/****************************************************************************/

static void *ThreadSortingDataIMP(void *info_to_sort)
{
    thread_info_ty *sort_info = (thread_info_ty*)info_to_sort;
    
    /* call qsort (with CmpFuncSortImp) */
    qsort(sort_info->start_data_arr, sort_info->num_of_elem, sizeof(char*),
                                                                 CmpFuncSortImp);
    /* return null */
    return NULL;
}
/****************************************************************************/

static int DestroyMemap(dict_memo_info_ty *mem_info)
{
    int ret_status = 0;

    assert(mem_info);
    /* munmap */
    ret_status = munmap(mem_info->dict_content_arr ,mem_info->num_of_elem);
    RETURN_IF_BAD_ERNO(0 == ret_status, "munmap failed", 1);

    /* return 0 */
    return SUCCESS;
}
/****************************************************************************/

static int CmpFuncSortImp(const void *str1, const void *str2)
{
    /* return what strcmp returns */
    return (strcmp (*(char **)str1, *(char **)str2)) ;
}
/****************************************************************************/

static int ShuffleFuncImp(const void *str1, const void *str2)
{
    (void)str1;
    (void)str2;

    /* return random number - random number */
    return (rand() - rand());
}
/****************************************************************************/

static void PrintTime(const struct timespec *start_time, 
                                               const struct timespec *stop_time)
{
    double measured_time = 0;

    assert(start_time);
    assert(stop_time);

    measured_time = (stop_time->tv_sec - start_time->tv_sec) + 
                    (double)(stop_time->tv_nsec - start_time->tv_nsec) /
                    1000000000;
    printf("measured time is: %f\n", measured_time);
}

/****************************************************************************/


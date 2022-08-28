/*

1. create FSQ (Fixed Size Queue)
1.1 check if FSQ fail

2. sem_init ready_to_read
2.1    check if sem_init fail

3. sem_init ready_to_write
3.1 check if sem_init fail

4. pthread_mutex_init - read lock
4.1 check if pthread_mutex_init fail

5. pthread_mutex_init - write lock
5.1 check if pthread_mutex_init fail

6. for 0-> NUM_OF_PRODUCERS
    pthread_create producers
    check if pthread_create fail

7. for 0-> NUM_OF_CONSUMERS
    pthread_create consumer
    check if pthread_create fail

8. for 0-> NUM_OF_PRODUCERS

    pthread_join producers
    check of pthread_join fail

9. for 0-> NUM_OF_CONSUMERS

    pthread_join concumers
    check of pthread_join fail
 
10. pthread_mutex_destroy(read lock)
    cheack if faild

11. pthread_mutex_destroy (write lock)
    cheack if faild


12. sem_destroy(ready to write)
    cheack if faild


13. sem_destroy(ready to read)
    cheack if faild


14. FSQ destroy


Producer Routine:

 while ( num of iterations )

    num of iterations --

    data = produce() // func that input num to alloc array

    1. sem_wait (semaphore ready to write)
    check if sem wait fail

    2. pthread_mutex_lock (write lock)
        check if pthread_mutex fail

    3.  BufferWrite (data)
        check if fail

    4. buffer mutex_unlock (write lock)
        check if fail

    5. sem_post (ready to read)
        check if fail


Consumer Routine:


 while ( num of iterations )

    num of iterations --

    sem_wait (ready_to_read)

    mutex lock  (read)

    data = bufferread()

    mutex unlock

    sum_array(data)

    sem_post(reay to write)

    free (data)



















































*/


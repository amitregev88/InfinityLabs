int main()
{
    MAKE_ME_IMMORTAL()


    DNR();


}






Product.out :

    thread 1-> main_thread - app running
   
     MAKE_ME_IMMORTAL(interval time, counter_time, argv)
     
        0. get watchdogpid
        
        1. create thread 2 (func_ping_pong watchdog_thread (interval , num_of_fail))

        2. check status of pthread_create 

        3. check watchdog_thread func status

            if first signal from whtchdog app accept - > sucess else faild. 

            
    func_ping_pong watchdog_thread(num_of_fail, interval, arg -file_name to fork)
    {

        
        1. add task to scheduler (interval) - (sends signal and atomic_increase the g_counter)


        while (1)    
        {
            2. if (!WD_PID)- /*if watchdog proccess is not exist  - create it .*/

                2.1 fork ()

                2.2 if child
                
                    2.2.1 exec (watchdog.out)


                2.3 run scheduler /*as parent process */

           
            3. if (flag_hanler_func == 1 ) /*signal arrived*/

                    g_counter_fail = 0;
            
            4.  if (g_counter_fail == num_of_fail)

                    stop sched 
                    SIGKILL
        }


    }
                 

                
                
        






    
           
        



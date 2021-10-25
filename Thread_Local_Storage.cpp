// Thread_Local_Storage.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
//      When you declare a variable thread_local then each thread is going to have it's own distinct object The 
// storage duration = the entire duration of the thread in which it was created, and the value stored in the obect
// is initialized when the thread is started
// 
// 
//

#include <iostream>
#include<thread>
#include<atomic>    //https://en.cppreference.com/w/cpp/atomic/atomic
#include<chrono>

//1. create a global atomic int
//4a. append thread_local before declaration
//thread_local 
std::atomic<int> i = 0;

//1a. this atomic int is similar to a normal int, EXCEPT if one thread writes a value to it, that value
// will be visible to all other threads in this context


void second()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}


//2. create the function
//
void foo()
{   //2a. all this does is increment the above defined integer varaible and launch it's value
    ++i;
    std::cout << i;

}
int main()
{
    //3. launch three threads
    std::thread thread1(foo);
    std::thread thread2(foo);
    std::thread thread3(foo);

    thread1.join();
    thread2.join();
    thread3.join();

    // output:
    //  123
    // 
    //      these are not the only results we can get, but this is a standard output.
    // these values can be changed in two operation in the foo function, there can be 
    // some non harmful conditions.
    // 
    //4. if you change the atomic int to thread_local, it's output is instead going to read 
    // as 111
    //
    // 4b. this is because each thread is going to have it's OWN DISTINC OBJECTS, which are
    // only visible to that thread, therefore each join will not be able to access the atomic 
    // variable as if it were sharing it
    // 
    //
}

// c++ reader-writer program by Moon Lee 06/12/2015
// compile: g++ -std=c++11 readerwriter.cpp -pthread
// then ./a.out

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <random>
#include <chrono>
#include <atomic>

using namespace std;

random_device rd; // uniformly-distributed integer random number generator that produces non-deterministic random numbers.
mt19937_64 mt(rd()); // Non-deterministic 64-bit seed. Random number engine based on Mersenne Twister algorithm.
uniform_int_distribution<int> prefix_dist(0, 1000); // Produces random integer values i, uniformly distributed on the closed interval [a, b]
uniform_int_distribution<int> access_dist(0, 10000);

mutex mtx; // reader writer mutex for condition variable
mutex ready_mtx; // ready mutex for concurrent start execution
mutex print_mtx; // guarantee only one is printed at a time
condition_variable readwrite_cv;
condition_variable ready_cv;
atomic<bool> ready(false);
atomic<int> rw_flag(0); // global variable. reader writer flag

int suffix_time; // global variable. sleep time for suffix.
auto start_time = chrono::high_resolution_clock::now(); // the time when program starts

// generate random number between [0, 1000] and return
int generate_random_prefix_time()
{
    return prefix_dist(mt);
}
// generate random number between [0, 10000] and return
int generate_random_access_time()
{
    return access_dist(mt);
}
void print_message(string message)
{
    lock_guard<mutex> lck (print_mtx); // this lock guarantees following instructions can be executed atomically
    
    // current time
    auto current_time = chrono::high_resolution_clock::now();
    
    // print "current time - start time"
    cout << "(" << chrono::duration_cast<chrono::nanoseconds>(current_time - start_time).count() << "ns) ";
    cout << message << endl;
}
/**
 * Reader
 * Readers can not access file while one writer accessing file
 * Multiple readers can access file simultaneously
 * @param wait_time int waiting time before accessing file
 * @param access_time int file accessing time
 * @param id int thread id
 */
void reader(int wait_time, int access_time, int id)
{
    // threads will wait until all threads are ready to run
    while (!ready) {
        unique_lock<mutex> ready_lck(ready_mtx);
        ready_cv.wait(ready_lck);
    }
    
    while(1) {
        this_thread::sleep_for(chrono::milliseconds(wait_time)); // sleep for prefix
        
        while (rw_flag < 0) {
            print_message("R" + to_string(id) + " try to access file");
            unique_lock<mutex> lck(mtx);
            readwrite_cv.wait(lck);
        }
        
        rw_flag++; // acquire shared
        
        print_message("R" + to_string(id) + " start accessing file"); // it will be deleted in final version
        
        this_thread::sleep_for(chrono::milliseconds(access_time)); // sleep for access
        
        print_message("R" + to_string(id) + " finish accessing file");
        
        rw_flag--; // release shared
        
        readwrite_cv.notify_all(); // signal all waiting threads
        print_message("R" + to_string(id) +" notify all");
        
        this_thread::sleep_for(chrono::milliseconds(suffix_time)); // sleep for suffix
        print_message("R" + to_string(id) + " terminated");
    }
}
/**
 * Writer
 * If one or more readers or one writer are accessing file, writer has to wait until no other readers or writer access file
 * Only one writer can access file
 * @param wait_time int waiting time before accessing file
 * @param access_time int file accessing time
 * @param id int thread id
 */
void writer(int wait_time, int access_time, int id)
{
    // threads will wait until all threads are ready to run
    while (!ready) {
        unique_lock<mutex> ready_lck(ready_mtx);
        ready_cv.wait(ready_lck);
    }
    
    while(1) {
        this_thread::sleep_for(chrono::milliseconds(wait_time)); // sleep for prefix
        
        while (rw_flag) {
            print_message("W" + to_string(id) + " try to access file");
            unique_lock<mutex> lck(mtx);
            readwrite_cv.wait(lck);
        }
        
        rw_flag = -1; // acquire exclusive
        
        print_message("W" + to_string(id) + " start accessing file"); // it will be deleted in final version
        
        this_thread::sleep_for(chrono::milliseconds(access_time)); // sleep for access
        
        print_message("W" + to_string(id) + " finish accessing file");
        
        rw_flag = 0; // release exclusive
        
        readwrite_cv.notify_all(); // signal all waiting threads
        print_message("W" + to_string(id) +" notify all");
        
        this_thread::sleep_for(chrono::milliseconds(suffix_time)); // sleep for suffix
        print_message("W" + to_string(id) + " terminated");
    }
}

// starts all threads concurrently
void start_running() {
    unique_lock<std::mutex> ready_lck(ready_mtx); // this lock guarantees following instructions can be executed atomically
    ready = true;
    ready_cv.notify_all(); // signal all waiting threads
}
int main() {
    int number_writer, number_reader;
    
    cout << "Enter the number of reader threads: ";
    cin >> number_reader;
    cout << "Enter the number of writer threads: ";
    cin >> number_writer;
    cout << "Enter the term of sleep before terminating(milliseconds): ";
    cin >> suffix_time;
    cout << endl;
    
    vector<thread> readers;
    vector<thread> writers;
    
    for (int i = 0; i < number_reader; ++i) {
        readers.push_back(thread(reader, generate_random_prefix_time(), generate_random_access_time(), i));
    }
    for (int i = 0; i < number_writer; ++i) {
        writers.push_back(thread(writer, generate_random_prefix_time(), generate_random_access_time(), i));
    }
    
    // starts all threads concurrently
    start_running();
    
    for (auto& th : writers) th.join();
    for (auto& th : readers) th.join();
    return 0;
}

/**
 * Two hungry threads, anxiously waiting for their turn to take soup
 */
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cstdio>

using std::mutex, std::condition_variable, std::unique_lock, std::thread;

int soup_servings = 10;
int num_hungry_people = 15;
mutex slow_cooker_lid;
condition_variable soup_taken;

void hungry_person(int id) {
    int put_lid_back = 0;
    while (soup_servings > 0) {
        unique_lock<mutex> lid_lock(slow_cooker_lid); // pick up the slow cooker lid
        while ((id != soup_servings % num_hungry_people) && (soup_servings > 0)) { // is it your turn to take soup?
            put_lid_back++; // it's not your turn; put the lid back...
            soup_taken.wait(lid_lock); // ...and wait...
        }
        if (soup_servings > 0) {
            soup_servings--; // it's your turn; take some soup!
            lid_lock.unlock(); // put back the lid
            soup_taken.notify_all(); // notify another thread to take their turn
        }
    }
    printf("Person %d put the lid back %u times.\n", id, put_lid_back);
}

int main() {
    thread hungry_threads[num_hungry_people];
    for (int i=0; i<num_hungry_people; i++) {
        hungry_threads[i] = thread(hungry_person, i);
    }
    for (auto& ht : hungry_threads) {
        ht.join();
    }
}
/**
 * Deciding how many bags of chips to buy for the party
 */
#include <thread>
#include <mutex>
#include <cstdio>
#include <barrier>

unsigned int bags_of_chips = 1; // start with one on the list
using std::mutex, std::barrier, std::scoped_lock, std::thread;
mutex pencil;
void olivia_shopper();
barrier fist_bump(10);

void cpu_work(unsigned long workUnits) {
    unsigned long x = 0;
    for (unsigned long i=0; i<workUnits*1000000; i++) {
        x++;
    }
    //std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void barron_shopper() {
    cpu_work(1); // do a bit of work first
    fist_bump.arrive_and_wait();
    {
        scoped_lock<mutex> lock(pencil);
        bags_of_chips *= 2;
    }
    printf("Barron DOUBLED the bags of chips.\n");
}

void olivia_shopper() {
    cpu_work(1); // do a bit of work first
    {
        scoped_lock<mutex> lock(pencil);
        bags_of_chips += 3;
    }
    printf("Olivia ADDED 3 bags of chips.\n");
    fist_bump.arrive_and_wait();
}


int main() {
    thread shoppers[10];
    for (int i=0; i<10; i+=2) {
        shoppers[i] = thread(barron_shopper);
        shoppers[i+1] = thread(olivia_shopper);
    }
    for (auto& s : shoppers) {
        s.join();
    }
    printf("We need to buy %u bags_of_chips.\n", bags_of_chips);
}
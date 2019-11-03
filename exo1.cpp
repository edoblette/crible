
#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>  
#include <chrono>

#define SetTo1(n) (*(list+(n>>3)) |=(1<<(n&7)))
#define GetBit(n) (*(list+(n>>3)) & (1<<(n&7)))  
#define LIMIT 10000000000
#define THREAD 4
unsigned char list[LIMIT];

//Protos
void crible(long );
void prime(int, int, int id );

std::mutex block_mutex; 


int main() {  

  int SQRT_MAXN = sqrt(LIMIT) ;
  unsigned long   count;
  
  std::vector<std::thread> process; 

  int start = 3 , end;
  for(int i = 0; i < THREAD; i++){
    end = SQRT_MAXN * ((double)(i+1)/(THREAD*(THREAD-i)));
    //prime(start, end );
    std::cout << start <<" "<< end << std::endl;
    process.push_back(std::thread(prime, start, end, i ));
    start = end + 1;
  }
  //join
  for(int nbThread = 0; nbThread < THREAD; process[nbThread++].join());

  // Result 
  count=1;
  for (unsigned long i = 3; i < LIMIT; i += 2) {
    if(!GetBit(i)){
      //std::cout << i << std::endl;
      ++count;
    }
  }
  printf("Count    : %lu\n", count);
 
  return 0;
}


void prime(int  start, int end, int id){
  clock_t begin = clock();
  unsigned long  i, j;
  for ( i = start; i < end; i+=2){
    block_mutex.lock();
    if(!GetBit(i))
      for(j = pow(i,2); j < LIMIT; j += i<<1)
        SetTo1(j);
      
    block_mutex.unlock();
  }
  clock_t stop = clock();
  double elapsed_secs = double(stop - begin) / CLOCKS_PER_SEC;
  std::cout << id << "stop  working - "<< elapsed_secs << std::endl;
}


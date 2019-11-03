
#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <bitset>
#include <math.h>  
#include <chrono>
#include <string>
#include <fstream>


#define SetTo1(n) (*(list+(n>>3)) |=(1<<(n&7)))
#define GetBit(n) (*(list+(n>>3)) & (1<<(n&7)))  
#define LIMIT 1000000000
#define THREAD 6
static unsigned char list[LIMIT/8];

//Protos
void prime(int, int, int id );
void result(int );

std::mutex block_mutex; 


int main() {  

  int sqrt_limit = sqrt(LIMIT) ;
  unsigned long   count;
  std::vector<std::thread> process; 

  int start = 3 , end;
  for(int i = 0; i < THREAD; i++){
    end = sqrt_limit * ((double)(i+1)/(THREAD*(THREAD-i)));
    //prime(start, end );
    std::cout << start <<" "<< end << std::endl;
    process.push_back(std::thread(prime, start, end, i ));
    start = end + 1;
  }

  //join
  for(int nbThread = 0; nbThread < THREAD; process[nbThread++].join());
 
  result(sqrt_limit);
  // Result 
  count=1;
  for (unsigned long i = 3; i < LIMIT; i += 2) {
    if(!GetBit(i)){
     // std::cout << i << std::endl;
      ++count;
    }
  }
  printf("Count    : %lu\n", count);
 
  return 0;
}


void prime(int  start, int end, int id){
  clock_t begin = clock();
  unsigned long  i, j, count=0;
  for ( i = start; i < end; i+=2){
    if(!GetBit(i))
      for(j = i*i; j < LIMIT; j += i<<1){
        ++count;
        SetTo1(j);
      }
      
  }
  clock_t stop = clock();
  double elapsed_secs = double(stop - begin) / CLOCKS_PER_SEC;
  std::cout << id << "stop  working - " << count << " - " << elapsed_secs << std::endl;
}

void result(int sqrt_limit){
  prime(3, sqrt_limit, 0);
  
  std::string buffer;
  buffer.reserve(LIMIT);
  for (unsigned long i = 3; i < LIMIT; i += 2) 
      if(!GetBit(i))
        buffer.append(std::to_string(i) + '\n');

  
  std::ofstream myfile ("result.txt");
  if (myfile.is_open()){
    myfile.write(buffer.data(), buffer.size());
    myfile.close();
  }
  else std::cout << "Unable to open file";
}


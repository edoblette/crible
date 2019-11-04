
#include <iostream>
#include <unistd.h>
#include <thread>
#include <vector>
#include <math.h>  
#include <fstream>
#include <mutex>


std::mutex block_mutex; 
std::vector<bool> list(1,1); 

//Protos
void crible(unsigned long limit, int THREAD);
void prime(int, int, unsigned long LIMIT, int THREAD);
void result(unsigned long LIMIT);



int main(int argc, char ** argv) {  
  if(argc != 3){
    std::cout << "usage : THREAD LIMIT" << std::endl;
    exit(0);
  }

  int THREAD = atoi(argv[1]);
  unsigned long LIMIT = atoi(argv[2]);
  list.reserve(LIMIT);
  std::fill(list.begin(), list.end()+ LIMIT, 1);

  crible(LIMIT, THREAD);
  result(LIMIT);

  return 0;
}

void crible(unsigned long LIMIT, int THREAD){

  int start , end = sqrt(LIMIT);
  std::vector<std::thread> process; 

  for(int i = 0; i < THREAD; i++){
      //end = sqrt_limit * ((double)(i+1)/THREAD);
      //end = sqrt_limit * ((double)(i+1)/(THREAD*(THREAD-i)));
      start = 3 + (2 * i);
      process.push_back(std::thread(prime, start, end, LIMIT, THREAD ));
  }
  for(int nbThread = 0; nbThread < THREAD; process[nbThread++].join());


}

void prime(int  start, int end, unsigned long LIMIT, int THREAD){
  unsigned long  i, j;
  int offset = (2 * THREAD);
  for ( i = start; i < end; i += offset){
    block_mutex.lock();
    if(list[i])
      for(j = i*i; j < LIMIT; j += i)
        list[j] = 0;  
      
    block_mutex.unlock();  
  }

 
}

void result(unsigned long LIMIT){

  std::cout << "Writing on buffer" << std::endl;
  std::string buffer;
  buffer.reserve(LIMIT);
  unsigned long i, count = 1;
  for ( i = 3; i < LIMIT; i += 2)
    if(list[i]){
      //printf("i= %d\n", i);
      buffer.append(std::to_string(i) + '\n');
      ++count;
    }
  

  std::cout << "Writing " << count << " numbers on file" << std::endl;
  
  std::ofstream myfile ("result.txt");
  if (myfile.is_open()){
    myfile.write(buffer.data(), buffer.size());
    myfile.close();
  }
  else std::cout << "Unable to open file";
}


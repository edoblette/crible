
#include <iostream>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>

//Protos
void crible(int);

std::mutex block_mutex; 


int main() {  
  
  crible(5000000);

  return 0;
}

void crible(int limit){
  
  unsigned long  i, j;
  int* list = new int[limit];
  for (i = 0; i < limit; ++i)
    list[i] = i;

  for ( i = 3; i < limit; i+=2){
    for(j = i+i; j < limit; j += i) 
      list[j] = 0;
    
  }

  // Result 
  for ( i = 2; i < limit; ++i)
    if(list[i])
      std::cout << list[i] << std::endl;
 
}

#include <iostream>
#include <thread>
#include <vector>
#include <math.h>  
#include <fstream>

std::vector<char> list(1,true); 

//Protos
void crible(size_t limit, int THREAD);
void prime(int, size_t LIMIT, int THREAD);
void result(size_t LIMIT);



int main(int argc, char ** argv) {  
  if(argc != 3){
    std::cout << "usage : ./crible [limit] [thread]" << std::endl;
    exit(0);
  }

  //initialise les variables
  size_t LIMIT = atoi(argv[1]);
  int THREAD = atoi(argv[2]);


  //agrandit le vecteur 
  list.reserve(LIMIT);
  std::fill(list.begin(), list.end()+ LIMIT, true);

  //lance les calculs
  crible(LIMIT, THREAD);
  result(LIMIT);

  return 0;
}

// distribue les taches au thread 
void crible(size_t LIMIT, int THREAD){

  int start;
  std::vector<std::thread> process; 

  for(int i = 0; i < THREAD; i++){
      start = 3 + (2 * i);  //on fait un decalage de 3 pour chaque thread, calcul par canaux 
      process.push_back(std::thread(prime, start, LIMIT, THREAD ));
  }
  for(int nbThread = 0; nbThread < THREAD; process[nbThread++].join());

}

void prime(int  start, size_t LIMIT, int THREAD){
  int offset = (2 * THREAD); //on faut un offset pour conserver le decalage et donc rester son canal de calcul
  for ( size_t i = start; i*i < LIMIT; i += offset) //on calcul jusqu'a la racine de notre limite
    if(list[i]) //si nombre est possiblement premier
      for(size_t j = i*i; j < LIMIT; j += i<<1) //ici on fait un decalage binaire, c'est plus rapide qu'un X2
          list[j] = false; //si nombre n'est pas premier
}

void result(size_t LIMIT){

  std::cout << "Writing on buffer" << std::endl;

  //on cree notre buffer pour stocker les chiffres
  std::string buffer;
  buffer.reserve(LIMIT);

  size_t count = 1;
  for ( size_t i = 3; i < LIMIT; i += 2)
    //on recupere tout les chiffre premier
    if(list[i]){
      buffer.append(std::to_string(i) + '\n'); //cree une ligne par nombre
      ++count;
    }
  

  std::cout << "Writing " << count << " numbers on file" << std::endl;
  
  std::ofstream myfile ("result.txt");
  if (myfile.is_open()){

    //on remplit notre fichier avec notre buffer
    myfile.write(buffer.data(), buffer.size());
    myfile.close();
  }
  else std::cout << "Unable to open file";
}


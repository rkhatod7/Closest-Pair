// Radhika Khatod
// CS 130B
// Prog 1 RandData file

#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc, char** argv){

  srand(time(NULL));

  int max = 10000;
  int min = -10000;
  double one, two;
  //argv[1] holds the number of random points that they want to generate

  for(int i = 0; i < atoi(argv[1]); i++){
    one = min + (max - min) *(double)rand()/RAND_MAX;
    two = min +(max - min) *(double)rand()/RAND_MAX;
    cout << one << " " << two << endl;
  }
}

#include <iostream>
#include <thread>
#include <chrono>
#include "Model.hpp"

using namespace std;

int main() {

  srand(time(0));

  Model test;

  // test.readTXT(); // tesing 

  cout << "Welcome to this generative program, how many words would you like to generate?" << endl;
  cout << "Please enter a positive integer:" << endl;

  int numWords;
  cin >> numWords;
  bool valid = true;

  while (valid) {
    while (cin.fail()) {
      cout << "Invalid input, please type a positive integer:" << endl;
      cin.clear(); 
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear the input buffer
      cin >> numWords;
    }

    if (numWords < 1) {
      cout << "Invalid input, please type a positive integer:" << endl;
      cin.clear(); 
      cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear the input buffer
      cin >> numWords;
    } else {
      valid = false; // escape loop
    }
  }
  // test
  // cout << numWords;

  cout << "Generating " << numWords << " words..." << endl;
  this_thread::sleep_for(chrono::milliseconds(1000)); 

  test.generate(numWords);
  // test.generate(10);

  return 0;
}
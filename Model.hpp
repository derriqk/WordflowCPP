#ifndef MODEL_HPP
#define MODEL_HPP

#include <unordered_map>
#include <string>
#include "Words.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class Model {
  public:
    unordered_map<string, WordItem> data;
    vector<string> wordsUsed;

    Model() {
      readTXT(); // perform the reading and storing into data
    }

    void generate(int n) { 
      // given a number, generate n amount of words

      // test
      // cout << n << endl << endl;

      string word = getRandomWord();

      // test
      // cout << word << endl << endl;

      // do this n times
      for (int i = 0; i < n; i++) {
        if (i % 10 == 0) {
          cout << endl; // every 10 words make new line
        }
        if ((i < n) && (data[word].wordList.size() == 0)) {// empty but still need words, so get random
          word = getRandomWord();
        }
        cout << word << " ";
        word = data[word].getFollowing();

        // test
        // cout << word << endl << endl;
      }
    }

    // use this to start the generation, get a random word first
    string getRandomWord() {
      int randIndex = rand() % wordsUsed.size();
      return wordsUsed[randIndex];
    }

    void readTXT() {
      // reads a file (currently im hardcoding the file type and contents, it is a .txt file)
      ifstream file;
      file.open("words.txt"); // hardcoding the text file
      if (!file.is_open()) return; // failed to open

      string current; // tracking two words at a time
      string following;
      int first = 0;

      while (file >> following) {
        // cout << current << endl; // testing if it reads correctly
        
        if (first != 0) { // current word has been tracked

          if (data.find(current) != data.end()) { // word exists on the hash
            data[current].insert(following);
          } else { // word doesnt exist yet
            WordItem newWord(current); // create a new Item and add it to the data table
            data.insert({newWord.word, newWord});
            data[newWord.word].insert(following);
            wordsUsed.push_back(current);
          }
          // update trackers
          current = following;
        } else {
          current = following; // start tracking following and current

          first++;
        }
      }
    }
  
};

#endif
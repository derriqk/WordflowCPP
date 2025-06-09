#ifndef WORDS_HPP
#define WORDS_HPP

// this file is for the two word classes that use each other for this project

#include <vector>
#include <string>

using namespace std;

class FollowingWord {
  public:
    int frequency;
    string word;

    FollowingWord(int n, string word) {
      this->frequency = n;
      this->word = word;
    }

    void increaseFreq() {
      this->frequency++;
    }
};

class WordItem {
  public:
    vector<FollowingWord> wordList;
    string word;
    int totalWords; // used to calculate probability, example if totalWords = 100 and a word has a frequency of 50, it has a 50% chance

    WordItem(string s) {
      this->word = s;
    }

    WordItem() {
      this->word = "";
      this->totalWords = 0;
    }

    void sort(int position) {
      for (int i = position; i > 0; i--) {
        if (wordList[i].frequency > wordList[i-1].frequency) { // swap iteratively
          // swap
          FollowingWord temp = wordList[i-1];
          wordList[i-1] = wordList[i];
          wordList[i] = temp;
        } 
        else {
          i = 0; // stop the loop early
        }
      }
    }

    void insert(string word) { 
      // checks if the word exist in its list already
      bool exist = false;
      for (int i = 0; i < wordList.size(); i++) {
        if (word == wordList[i].word) {
          wordList[i].increaseFreq();

          // since frequency was updated, re-sort it
          sort(i);

          exist = true;
          totalWords++; // increase total words
        }
      }

      // new word so just push it back because invariant is that the very back is the least frequent
      // and new words are always freq = 1
      if (!exist) {
        FollowingWord temp(1, word);
        wordList.push_back(temp);
        totalWords++; // increase total words
      }
    }

    string getFollowing() {
      string result;

      if (wordList.size() == 0) {
        result = ""; // empty list so theres no following word
      } else {
        // otherwise use a random number to get a word based on its frequency
        int freqTotal = 0;
        int randNum = rand() % totalWords; // get a random number between 0 and totalWords - 1

        for (int i = 0; i < wordList.size(); i++) {
          freqTotal += wordList[i].frequency;
          if (randNum < freqTotal) { // example: frequency of a word is 10 and randumNum chose 50 from (1...100) it would ignore this word
            result = wordList[i].word;
            i = wordList.size(); // end loop early
          }
        }
      }

      return result;
    }
};


#endif
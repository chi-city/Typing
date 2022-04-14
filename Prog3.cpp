/*
    Zaid Awaidah
    CS-141
    Program 3 - Typing
    Visual Studio 2019
*/

#include <iostream>
#include <cassert>
#include <cctype>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

const int TIME_LIMIT = 15;
void wordsIntoDictionaryVctr(vector <string>& dictionary);                                                                                                  // Function to read words into the dictionary vector
void misspelledWordsVctr(vector <string>& misspelledwords);                                                                                                 //  Function to read words into the misspelled words vector
void menuOptions(int bestScore, int& wordLength, int& score, int menuOption, vector <string> misspelledWords, vector<string> dictionaryWords);              // Menu Options
void calcScoreMenuOpt1(int& score, int elapsedTime, int correctWordsCounter, int incorrectWordsCounter);                                                    // Function to calculate the score for menuOpt 1
void calcScoreMenuOpt2(int& score, int wordLength, int elapsedTime, int correctWordsCounter, int incorrectWordsCounter);                                    // Function to calculate the score for menuOpt 2
void menuOpt1(int& score, vector <string> misspelledWords);                                                                                                 //Type words from misspelled.txt within time limit
void menuOpt2(int& score, int& wordLength, vector<string> dictionaryWords);                                                                                 //Type dictionary words within time limit
void menuOpt3(vector <string> misspelledWords, vector<string> dictionaryWords);                                                                             // Displays a list of words from the dictionary,
void menuOpt4(vector<string> dictionaryWords);                                                                                                              // Searches through the dictionary using binary search to find a word
void menuOpt5(int& newWordLength);                                                                                                                          // Sets a new word length to use with dictionary.
void menuOpt6(int finalScore);                                                                                                                              // Exits Program

int main() {
    srand(1);
    int score = 0;                                                                                                                                          // Initial Score
    int highScore = 0;                                                                                                                                      // High Score value
    int wordLength = 5;                                                                                                                                     // Initial Word Length
    bool readingWords = true;
    vector<string> dictionaryWords;
    vector<string> misspelledWords;

    //Read words into respective vectors
    wordsIntoDictionaryVctr(dictionaryWords);
    misspelledWordsVctr(misspelledWords);

    cout << "There are " << dictionaryWords.size() << " words in the full dictionary." << endl;
    cout << "There are " << misspelledWords.size() / 2 << " commonly misspelled words.\n" << endl;

    while (readingWords) {
        //Selecting menu option
        cout << "\nSelect a menu option: \n";
        cout << "   1. Spell commonly misspelled words (timed)" << endl;
        cout << "   2. Type random words from full dictionary (timed)" << endl;
        cout << "   3. Display some words from one of the lists" << endl;
        cout << "   4. Use binary search to lookup a word in full dictionary" << endl;
        cout << "   5. Set word length to use with full dictionary" << endl;
        cout << "   6. Exit the program" << endl;

        int menuOption;
        cout << "Your choice --> ";
        cin >> menuOption;
        menuOptions(highScore, wordLength, score, menuOption, misspelledWords, dictionaryWords);

        if (highScore < score) {
            highScore = score;
        }
    }
    return 0;
}

void wordsIntoDictionaryVctr(vector <string>& dictionary) {
    //Reading in:
    ifstream streamObj;
    streamObj.open("dictionary.txt");      //Opens file
    assert(streamObj.fail() == false);     //Ensures file opened

    //clear dictionary vector if it was used before
    dictionary.clear();

    string wordInput;
    while (streamObj >> wordInput) {
        //Push word to end of vector(increases size)
        dictionary.push_back(wordInput);
    }
    streamObj.close();      //close file
}

void misspelledWordsVctr(vector <string>& misspelledwords) {
    //Reading in:
    ifstream streamObj;
    streamObj.open("misspelledWords.txt");      //Opens file
    assert(streamObj.fail() == false);     //Ensures file opened

    //clear vector if it was used before
    misspelledwords.clear();

    string wordInput;
    while (streamObj >> wordInput) {
        //Push word to end of vector(increases size)
        misspelledwords.push_back(wordInput);
    }
    streamObj.close();      //close file
}

void menuOptions(int bestScore, int& wordLength, int& score, int menuOption, vector <string> misspelledWords, vector<string> dictionaryWords) {
    switch (menuOption) {
    case 1:
        menuOpt1(score, misspelledWords);
        break;

    case 2:
        menuOpt2(score, wordLength, dictionaryWords);
        break;

    case 3:
        cout << "   Displaying word list entries.\n"
            << "   Which words do you want to display?\n"
            << "      A. Dictionary of all words\n"
            << "      B. Wrongly spelled common misspelled words\n"
            << "      C. Correctly spelled common misspelled words\n"
            << endl;
        menuOpt3(misspelledWords, dictionaryWords);
        break;

    case 4:
        menuOpt4(dictionaryWords);
        break;

    case 5:
        menuOpt5(wordLength);
        break;
    case 6:
        menuOpt6(bestScore);
        break;
    }
}

void menuOpt1(int& score, vector <string> misspelledWords) {
    cout << "Using commonly misspelled words\n";
    int correctWordsCounter = 0;
    int incorrectWordsCounter = 0;
    vector<string> correctWords;                                                                                                                                     // All the correct words in MisspelledWords.txt
    vector<string>incorrectWords;                                                                                                                                    // All incorrect words in MisspelledWords.txt
    vector<string>randomIncorrectWords;                                                                                                                              // Stores random incorrect words from misspelledwords.txt
    vector<string> correctlySpelledWords;                                                                                                                            // Stores corresponding correct words for incorrect words chosen at random
    vector<string> incorrectlySpelledWords;                                                                                                                          //user spelled incorrect words
    vector<string> trackWords;                                                                                                                                       //tracks correct words in misspelledwords.txt

    for (unsigned int i = 0; i < misspelledWords.size(); i++) {
        if (i % 2 == 1) {
            correctWords.push_back(misspelledWords.at(i));                                                                                                           //Storing all correct words
        }
        if (i % 2 == 0) {
            incorrectWords.push_back(misspelledWords.at(i));                                                                                                         //Storing all incorrect words
        }
    }

    for (int i = 0; i < 5; i++) {                                                                                                                                    //Getting a random word and its corresponding correct word
        int wordIndex = rand() % incorrectWords.size();
        randomIncorrectWords.push_back(incorrectWords.at(wordIndex));
        correctlySpelledWords.push_back(correctWords.at(wordIndex));
    }

    for (int j = 0; j < 5; j++) {
        cout << randomIncorrectWords.at(j) << " ";
    }cout << endl;

    //Ask for user input and begin timing  
    int elapsedTime = 0;
    bool misspellWords{};
    string userWord1, userWord2, userWord3, userWord4, userWord5;
    cout << "Type in those words within goal of 15 seconds:\n";
    time_t startTime = time(NULL);
    cin >> userWord1 >> userWord2 >> userWord3 >> userWord4 >> userWord5;
    elapsedTime = difftime(time(NULL), startTime);


    //Comparing User words with correct words
    if (userWord1.compare(correctlySpelledWords.at(0)) != 0) {
        incorrectWordsCounter++;
        incorrectlySpelledWords.push_back(userWord1);
        trackWords.push_back(correctlySpelledWords.at(0));
        misspellWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (userWord2.compare(correctlySpelledWords.at(1)) != 0) {
        incorrectWordsCounter++;
        incorrectlySpelledWords.push_back(userWord2);
        trackWords.push_back(correctlySpelledWords.at(1));
        misspellWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (userWord3.compare(correctlySpelledWords.at(2)) != 0) {
        incorrectWordsCounter++;
        incorrectlySpelledWords.push_back(userWord3);
        trackWords.push_back(correctlySpelledWords.at(2));
        misspellWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (userWord4.compare(correctlySpelledWords.at(3)) != 0) {
        incorrectWordsCounter++;
        incorrectlySpelledWords.push_back(userWord4);
        trackWords.push_back(correctlySpelledWords.at(3));
        misspellWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (userWord5.compare(correctlySpelledWords.at(4)) != 0) {
        incorrectWordsCounter++;
        incorrectlySpelledWords.push_back(userWord5);
        trackWords.push_back(correctlySpelledWords.at(4));
        misspellWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (misspellWords == true) {
        cout << "   Misspelled words: \n";
        for (int currIndex = 0; currIndex < incorrectlySpelledWords.size(); currIndex++) {
            if (incorrectlySpelledWords.at(currIndex) != trackWords.at(currIndex)) {
                cout << "       " << incorrectlySpelledWords.at(currIndex) << " should be: " << trackWords.at(currIndex) << endl;
            }
        }
    }
    else {
        cout << "   No misspelled words!\n";
    }
    calcScoreMenuOpt1(score, elapsedTime, correctWordsCounter, incorrectWordsCounter);                                                                          //Finally calculate score
}

void menuOpt2(int& score, int& wordLength, vector<string> dictionaryWords) {
    int correctWordsCounter = 0;
    int incorrectWordsCounter = 0;
    bool misspelledWords{};
    vector<string>randWrdsFromDict;                                                                                                                             // Stores Words that were chosen at random  
    vector<string>incorrectSpelledWrds;                                                                                                                         // Stores the words the user spelled incorrectly
    vector<string>correctSpelledWrds;                                                                                                                           // Stores the corresponding correct word for previous vector

    cout << "Using full dictionary\n";
    while (randWrdsFromDict.size() < 5) {
        int wordIndex = rand() % dictionaryWords.size();

        if (dictionaryWords[wordIndex].length() == wordLength) {
            cout << dictionaryWords[wordIndex] << " ";
            randWrdsFromDict.push_back(dictionaryWords.at(wordIndex));
        }
    }cout << endl;

    //Ask for user input and begin timing  
    int elapsedTime = 0;
    string userWord1, userWord2, userWord3, userWord4, userWord5;
    cout << "Type in those words within goal of 15 seconds:\n";
    time_t startTime = time(NULL);
    cin >> userWord1 >> userWord2 >> userWord3 >> userWord4 >> userWord5;
    elapsedTime = difftime(time(NULL), startTime);

    //Comparing User words with correct words
    if (userWord1.compare(randWrdsFromDict.at(0)) != 0) {
        incorrectWordsCounter++;
        incorrectSpelledWrds.push_back(userWord1);
        correctSpelledWrds.push_back(randWrdsFromDict.at(0));
        misspelledWords = true;
    }
    else {
        correctWordsCounter++;
    }
    if (userWord2.compare(randWrdsFromDict.at(1)) != 0) {
        incorrectWordsCounter++;
        incorrectSpelledWrds.push_back(userWord2);
        correctSpelledWrds.push_back(randWrdsFromDict.at(1));
        misspelledWords = true;
    }
    else {
        correctWordsCounter++;
    }
    if (userWord3.compare(randWrdsFromDict.at(2)) != 0) {
        incorrectWordsCounter++;
        incorrectSpelledWrds.push_back(userWord3);
        correctSpelledWrds.push_back(randWrdsFromDict.at(2));
        misspelledWords = true;
    }
    else {
        correctWordsCounter++;
    }
    if (userWord4.compare(randWrdsFromDict.at(3)) != 0) {
        incorrectWordsCounter++;
        incorrectSpelledWrds.push_back(userWord4);
        correctSpelledWrds.push_back(randWrdsFromDict.at(3));
        misspelledWords = true;
    }
    else {
        correctWordsCounter++;
    }
    if (userWord5.compare(randWrdsFromDict.at(4)) != 0) {
        incorrectWordsCounter++;
        incorrectSpelledWrds.push_back(userWord5);
        correctSpelledWrds.push_back(randWrdsFromDict.at(4));
        misspelledWords = true;
    }
    else {
        correctWordsCounter++;
    }

    if (misspelledWords == true) {
        cout << "   Misspelled words: \n";
        for (int currIndex = 0; currIndex < incorrectSpelledWrds.size(); currIndex++) {
            if (incorrectSpelledWrds.at(currIndex) != correctSpelledWrds.at(currIndex)) {
                cout << "       " << incorrectSpelledWrds.at(currIndex) << " should be: " << correctSpelledWrds.at(currIndex) << endl;
            }
        }
    }
    else {
        cout << "   No misspelled words!\n";
    }
    calcScoreMenuOpt2(score, wordLength, elapsedTime, correctWordsCounter, incorrectWordsCounter);                                                             //Finally calculate score
    wordLength++;
}


void menuOpt3(vector <string> misspelledWords, vector<string> dictionaryWords) {
    char userSubChoice;
    cout << "   Your choice --> ";
    cin >> userSubChoice;
    userSubChoice = tolower(userSubChoice);

    if (userSubChoice == 'a') {
        int startInd, endInd;
        cout << "   Enter the start and end indices between 0 and 263532: ";
        cin >> startInd >> endInd;

        for (int index = startInd; index <= endInd; ++index) {
            cout << "     " << index << ". " << dictionaryWords.at(index) << endl;
        }
    }

    if (userSubChoice == 'b') {
        int startInd, endInd;
        cout << "   Enter the start and end indices between 0 and 113: ";
        cin >> startInd >> endInd;

        for (int index = startInd; index <= endInd; index++) {
            cout << "     " << index << ". " << misspelledWords.at(index * 2) << endl;
        }
    }

    if (userSubChoice == 'c') {
        int startInd, endInd;
        cout << "   Enter the start and end indices between 0 and 113: ";
        cin >> startInd >> endInd;

        for (int index = startInd; index <= endInd; ++index) {
            cout << "     " << index << ". " << misspelledWords.at((index * 2) + 1) << endl;
        }
    }
}

void menuOpt4(vector<string> dictionaryWords) {
    int counter = 1;
    string wordToLookUp;
    bool wordIsFound = false;
    cout << "Enter the word to lookup: ";
    cin >> wordToLookUp;

    int midWord;
    int firstWord = 0;
    int lastWord = dictionaryWords.size() - 1;

    while (firstWord <= lastWord) {
        midWord = (lastWord + firstWord) / 2;

        cout << "     " << counter << ". Comparing to: " << dictionaryWords.at(midWord) << endl;
        counter++;

        if ((dictionaryWords.at(midWord).compare(wordToLookUp)) == 0) {
            counter = 1;
            wordIsFound = true;
            break;
        }
        else if ((dictionaryWords.at(midWord).compare(wordToLookUp)) > 0) {
            lastWord = midWord - 1;
        }
        else if ((dictionaryWords.at(midWord).compare(wordToLookUp)) < 0) {
            firstWord = midWord + 1;
        }
    }

    if (wordIsFound == true) {
        cout << wordToLookUp << " was found.\n" << endl;
    }
    else {
        cout << wordToLookUp << " was NOT found.\n" << endl;
    }
}

void menuOpt5(int& newWordLength) {
    int newLength;
    cout << "Enter new wordLength: ";
    cin >> newLength;

    newWordLength = newLength;
}

void menuOpt6(int finalScore) {
    cout << "\nExiting program\n";
    cout << "Best score was " << finalScore;
    exit(0);
}

void calcScoreMenuOpt1(int& score, int elapsedTime, int correctWordsCounter, int incorrectWordsCounter) {
    int currentScore = 0;
    int ptsnumberOfSecondsUnder15 = (TIME_LIMIT - elapsedTime) * 2;
    int ptsnumberOfSecondsOver15 = (TIME_LIMIT - elapsedTime) * 3;
    int pointsForCorrectWords = correctWordsCounter * 3;
    int pointsForIncorrectWords = incorrectWordsCounter * 6;

    if (elapsedTime < TIME_LIMIT) {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << ptsnumberOfSecondsUnder15 << " point bonus for finishing " << TIME_LIMIT << " seconds early.\n";
        cout << "   " << pointsForCorrectWords << " points: " << correctWordsCounter << " spelled correctly x 3 points each\n";

        if (incorrectWordsCounter > 0) {
            cout << "   " << pointsForIncorrectWords << " point penalty: " << incorrectWordsCounter << " spelled incorrectly x 6 points each\n";
        }

        currentScore = (ptsnumberOfSecondsUnder15 + pointsForCorrectWords) - pointsForIncorrectWords;
        cout << "Score: " << currentScore << endl;
    }
    else {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << ptsnumberOfSecondsOver15 << " points for finishing " << TIME_LIMIT - elapsedTime << " seconds late.\n";
        cout << "   " << pointsForCorrectWords << " points: " << correctWordsCounter << " spelled correctly x 3 points each\n";

        if (incorrectWordsCounter > 0) {
            cout << "   " << pointsForIncorrectWords << " point penalty: " << incorrectWordsCounter << " spelled incorrectly x 6 points each\n";
        }

        currentScore = (ptsnumberOfSecondsOver15 + pointsForCorrectWords) - pointsForIncorrectWords;
        cout << "Score: " << currentScore << endl;
    }
    score = currentScore;
}

void calcScoreMenuOpt2(int& score, int wordLength, int elapsedTime, int correctWordsCounter, int incorrectWordsCounter) {
    int currentScore = 0;
    int ptsFornumberOfSecondsUnder15 = (TIME_LIMIT - elapsedTime) * 2;
    int ptsFornumberOfSecondsOver15 = (TIME_LIMIT - elapsedTime) * 3;
    int numberOfPointsPerWord = wordLength - 4;
    int pointsForCorrectWords = correctWordsCounter * numberOfPointsPerWord;
    int pointsForIncorrectWords = incorrectWordsCounter * (numberOfPointsPerWord * 2);
    int totalPtsForWrongWords = pointsForIncorrectWords * incorrectWordsCounter;

    if (elapsedTime < TIME_LIMIT) {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << ptsFornumberOfSecondsUnder15 << " point bonus for finishing " << TIME_LIMIT << " seconds early.\n";
        cout << "   " << pointsForCorrectWords << " points: " << correctWordsCounter << " spelled correctly x " << numberOfPointsPerWord << " points each\n";

        if (incorrectWordsCounter > 0) {
            cout << "   " << pointsForIncorrectWords << " point penalty: " << incorrectWordsCounter << " spelled incorrectly x " << (numberOfPointsPerWord * 2) << " points each\n";
        }

        currentScore = (ptsFornumberOfSecondsUnder15 + pointsForCorrectWords) - pointsForIncorrectWords;
        cout << "Score: " << currentScore << endl;
    }
    else {
        cout << "   Elapsed time: " << elapsedTime << " seconds. " << ptsFornumberOfSecondsOver15 << " points for finishing " << (elapsedTime - TIME_LIMIT) << " seconds late.\n";
        cout << "   " << pointsForCorrectWords << " points: " << correctWordsCounter << " spelled correctly x " << numberOfPointsPerWord << " points each\n";

        if (incorrectWordsCounter > 0) {
            cout << "   " << totalPtsForWrongWords << " point penalty: " << incorrectWordsCounter << " spelled incorrectly x " << pointsForIncorrectWords << " points each\n";
        }

        currentScore = (ptsFornumberOfSecondsOver15 + pointsForCorrectWords) - totalPtsForWrongWords;
        cout << "Score: " << currentScore << endl;
    }
    score = currentScore;
}
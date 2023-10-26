#include <exception>
#include <iostream>
#include <typeinfo>
using namespace std;

class GameEntry {
 public:
  GameEntry(const string &n = "", int s = 0);
  string getName() const;
  int getScore() const;
  void setScore(const int newScore);

 private:
  string name;
  int score;
};

GameEntry::GameEntry(const string &n, int s) : name(n), score(s) {}

string GameEntry::getName() const { return name; }

int GameEntry::getScore() const { return score; }

void GameEntry::setScore(const int newScore) { score = newScore; }

class Scores {
 public:
  Scores(int maxEnt = 10);
  ~Scores();
  void add(const GameEntry &e);
  GameEntry remove(int i);
  void printAllScores();
  void printPlayersCount();
  void printPlayersInScoreRange(int min, int max);

 private:
  int maxEntries;      // maximum number of entries
  int numEntries;      // actual number of entries
  GameEntry *entries;  // array of game entries
  bool isEqual(string a, string b);
  int search(string name);
};

Scores::Scores(int maxEnt) {            // constructor
  maxEntries = maxEnt;                  // save the max size
  entries = new GameEntry[maxEntries];  // allocate array storage
  numEntries = 0;                       // initially no elements
}

Scores::~Scores() { delete[] entries; }

int Scores::search(string name) {
  for (int k = 0; k < numEntries; k++) {
    if (isEqual(entries[k].getName(), name)) return k;
  }
  return -1;
}

void Scores::add(const GameEntry &e) {
  string name = e.getName();
  int newScore = e.getScore();  // score to add

  int index = search(name);

  if (index != -1) {
    // player exists
    if (newScore < entries[index].getScore()) return;

    entries[index].setScore(newScore);

    for (int i = index; i > 0; i--) {
      // compare the entry to the left

      // if this entry is not high enough to be swapped,
      // break out of the loop
      if (entries[i].getScore() <= entries[i - 1].getScore()) break;

      // swap with the entry to the left
      // WRITE YOUR CODE HERE...
      GameEntry t = entries[i];
      entries[i] = entries[i - 1];
      entries[i - 1] = t;
    }
  } else {
    if (numEntries == maxEntries) {  // the array is full
      if (newScore <= entries[maxEntries - 1].getScore())
        return;  // not high enough - ignore
    } else
      numEntries++;          // if not full, one more entry
    int i = numEntries - 2;  // start with the next to last
    while (i >= 0 && newScore > entries[i].getScore()) {
      entries[i + 1] = entries[i];  // shift right if smaller
      i--;
    }
    entries[i + 1] = e;  // put e in the empty spot
  }
}

GameEntry Scores::remove(int i) {
  if ((i < 0) || (i >= numEntries))  // invalid index
    throw("IndexOutOfBounds - Invalid index");
  GameEntry e = entries[i];  // save the removed object
  for (int j = i + 1; j < numEntries; j++)
    entries[j - 1] = entries[j];  // shift entries left
  numEntries--;                   // one fewer entry
  return e;                       // return the removed object
}

void Scores::printAllScores() {
  for (int i = 0; i < numEntries; i++) {
    cout << entries[i].getName() << " : " << entries[i].getScore() << "\n";
  }
}

void Scores::printPlayersCount() {
  bool isPicked[numEntries]{false};

  for (int k = 0; k < numEntries; k++) {
    if (isPicked[k]) continue;

    string playerName = entries[k].getName();
    int playerCount = 1;

    for (int j = k + 1; j < numEntries; j++) {
      if (isPicked[j]) continue;
      if (isEqual(playerName, entries[j].getName())) {
        isPicked[j] = true;
        playerCount++;
      }
    }

    isPicked[k] = true;
    cout << playerName << ": " << playerCount << endl;
  }
}

void Scores::printPlayersInScoreRange(int min, int max) {
  // isPicked is a table that helps us record whether a player was already
  // considered for calculating his/her count.
  bool isPicked[numEntries]{false};

  for (int k = 0; k < numEntries; k++) {
    if (isPicked[k]) continue;

    string playerName = entries[k].getName();
    int playerTotalScore = entries[k].getScore();

    for (int j = k + 1; j < numEntries; j++) {
      if (isPicked[j]) continue;
      if (isEqual(playerName, entries[j].getName())) {
        isPicked[j] = true;
        playerTotalScore += entries[j].getScore();
      }
    }

    isPicked[k] = true;
    if (playerTotalScore >= min && playerTotalScore <= max)
      cout << playerName << ": " << playerTotalScore << endl;
  }
}

bool Scores::isEqual(string a, string b) {
  if (a.length() != b.length()) return false;
  for (int k = 0; k < a.length(); k++) {
    if (a[k] != b[k]) return false;
  }
  return true;
}

void showOptions() {
  cout << "1:	Add Player\n"
       << "2:	Remove Player By Index\n"
       << "3:	Print Scores\n"
       << "4:	Print Players With Score in Range\n"
       << "5:   Exit\n";
}
int main() {
  Scores scoresObj;
  int option;
  string playerName;
  int score;

  while (1) {
    showOptions();
    cin >> option;
    switch (option) {
      case 1:
        cout << "Enter Player Name and Score\n";
        cin >> playerName >> score;
        scoresObj.add(GameEntry(playerName, score));
        break;
      case 2:
        int index;
        cout << "Enter the index\n";
        cin >> index;
        scoresObj.remove(index);
        break;
      case 3:
        scoresObj.printAllScores();
        break;
      case 4:
        int maxValue, minValue;
        cout << "Enter max value and min value\n";
        cin >> maxValue >> minValue;
        scoresObj.printPlayersInScoreRange(minValue, maxValue);
        break;
      case 5:
        return EXIT_SUCCESS;
    }
  }
}

// 1
// Rohit 85
// 1
// Virat 95
// 1
// Gill 120
// 3
// 1
// Gill 200
// 3
// 4 200 90
// 5
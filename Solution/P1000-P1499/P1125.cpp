#include <iostream>
#include <vector>

using namespace std;

struct Letter {
  char _value;
  int _times;
};

bool _isPrime = false;
int _res;

string _word;

vector<Letter> _timeList;

void ParseIn () {
  cin >> _word;
}

bool CheckIn (char solo, vector<Letter> theList)  {
  for (int i = 0; i < theList.size(); i++)  {
    if (solo == theList[i]._value) {
      return true;
    }
  }
  return false;
}

int CheckIndex (char solo, vector<Letter> theList)  {
  for (int i = 0; i < theList.size(); i++)  {
    if (solo == theList[i]._value) {
      return i;
    }
  }
  return -578432;
}

void GenList (string str)  {
  Letter lSolo;
  for (int i = 0; i < str.length(); i++)  {
    if(CheckIn(str[i],_timeList)) {
      _timeList[CheckIndex(str[i],_timeList)]._times++;
      continue;
    }
    lSolo._value = str[i];
    lSolo._times = 0;
    _timeList.push_back(lSolo);
  }
}

int CalcMax (vector<Letter> theList)  {
  int times = -1;
  
  for(int i = 0; i < theList.size(); i++)  {
    if(times < theList[i]._times)  {
      times = theList[i]._times;
    }
  }
  return times;
}

int CalcMin (vector<Letter> theList)  {
  int times = 1000;
  
  for(int i = 0; i < theList.size(); i++)  {
    if(times > theList[i]._times)  {
      times = theList[i]._times;
    }
  }
  return times;
}

bool IsPrime (int num)  {
  if (num < 2)  {
    return false;
  }

  for (int i = 2; i < num; i++)  {
    if(num%i==0) {
      return false;
    }
  }
  return true;
}

void Core () {
  GenList(_word);
  _res = CalcMax(_timeList)-CalcMin(_timeList);
  _isPrime = IsPrime(_res);
}

void WriteOut () {
  if (_isPrime) {
    cout << "Lucky Word" << endl;
    cout << _res << endl;
    return;
  }
  cout << "No Answer" << endl;
  cout << 0 << endl;
}

int main () {
  ParseIn();
  Core();
  WriteOut();
  return 0;
}

#include <bits/stdc++.h>
#define ERROR cout << "error\n"
using namespace std;

list<tuple<string, int, int>> myDisk;
list<tuple<string, int, int>>::iterator pre, nxt;
map<string, bool> fileExist;
int V;

void setting() {
  myDisk.push_front({"FILE_START", 0, 0});
  myDisk.push_back({"FILE_END", V, V});
  pre = myDisk.begin();
  nxt = myDisk.begin();
  nxt++;
}

void writeFile(string fileName, int fileSize) {
  if (fileExist.find(fileName) == fileExist.end()) {
    int leftDiskSize = 0, diskSize;
    setting();
    fileExist[fileName] = true;

    for (nxt; nxt != myDisk.end(); nxt++) {
      diskSize = get<1>(*nxt) - get<2>(*pre);
      if (diskSize > 0 && diskSize >= fileSize) {
        myDisk.insert(nxt, {fileName, get<2>(*pre), get<2>(*pre) + fileSize});
        myDisk.pop_front();
        myDisk.pop_back();
        return;
      }
      leftDiskSize += diskSize;
      pre++;
    }

    if (leftDiskSize < fileSize) {
      cout << "diskfull\n";
      fileExist.erase(fileName);
    } else {
      pre = myDisk.begin();
      nxt = myDisk.begin();
      nxt++;

      for (nxt; nxt != myDisk.end(); nxt++) {
        diskSize = get<1>(*nxt) - get<2>(*pre);
        if (diskSize > 0) {
          if (diskSize >= fileSize) {
            myDisk.insert(nxt,
                          {fileName, get<2>(*pre), get<2>(*pre) + fileSize});
            break;
          } else {
            fileSize -= diskSize;
            nxt = myDisk.insert(
                nxt, {fileName, get<2>(*pre), get<2>(*pre) + diskSize});
          }
        }
        pre++;
      }
    }
    myDisk.pop_front();
    myDisk.pop_back();
  } else
    ERROR;
}

void deleteFile(string fileName) {
  if (fileExist.find(fileName) != fileExist.end()) {
    fileExist.erase(fileName);
    myDisk.remove_if([fileName](tuple<string, int, int> f) -> bool {
      return get<0>(f) == fileName;
    });
  } else
    ERROR;
}

void showFile(string fileName) {
  if (fileExist.find(fileName) != fileExist.end()) {
    for (auto i : myDisk)
      if (get<0>(i) == fileName) cout << get<1>(i) << " ";
    cout << "\n";
  } else
    ERROR;
}

void compactFiles() {
  int preLast, nxtFirst, gap, fileFirst, fileLast;
  string fileName;
  setting();

  for (nxt; nxt != myDisk.end(); nxt++) {
    preLast = get<2>(*pre);
    nxtFirst = get<1>(*nxt);
    if (preLast != nxtFirst) {
      gap = nxtFirst - preLast;
      tie(fileName, fileFirst, fileLast) = *nxt;
      nxt = myDisk.erase(nxt);
      if (get<0>(*pre) == fileName) {
        fileFirst = get<1>(*pre) + gap;
        pre = myDisk.erase(pre);
        pre--;
      }
      nxt = myDisk.insert(nxt, {fileName, fileFirst - gap, fileLast - gap});
    }
    pre++;
  }
  myDisk.pop_front();
  myDisk.pop_back();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  int sa;
  string command = "start", fa;

  cin >> V;
  while (command != "end") {
    cin >> command;
    if (command == "end") break;
    if (command == "compact")
      compactFiles();
    else
      cin >> fa;
    if (command == "write") {
      cin >> sa;
      writeFile(fa, sa);
    }
    if (command == "delete") deleteFile(fa);
    if (command == "show") showFile(fa);
  }
}
#pragma once
#include <string>
#include <fstream>
using namespace std;

class CLibdialog {
public:
    string GetPathName() { return ""; }
    string GetFileName() { return ""; }
    int DoModal() { return 0; }
};

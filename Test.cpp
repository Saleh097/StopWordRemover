#include <iostream>
#include "StopWordRMV.h"
#include<fstream>
#include<string>

using namespace std;

int main()
{
    string que = "this is my sentence that should be cleaned";
    StopWordManager stp(14);
    stp.removeStopWords(que);
    cout<<que<<endl;
    return 0;
}
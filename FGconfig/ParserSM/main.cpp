//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <sstream>
//#include <regex>
//#include <bits/stdc++.h>
#include "fgconfig.h"


#define PATH "C:/Users/DINH TUYEN/Desktop/gittest/config/gittest/FGconfig/DemoConfig - Copy.cfg" // dummy value
#define PATH_OUTPUT "C:/Users/DINH TUYEN/Desktop/gittest/config/gittest/FGconfig/DemoConfig_Out.cfg"
using namespace std;
int main()
{
    // support comment
    // fix bug execute list
    // show error line
    vector<FGStartupInfo> mFGStartupInfoList = getFGConfig(PATH);
    for(uint i = 0 ; i < mFGStartupInfoList.size(); i++){
        cout << "FG "<< i +1 << endl;
        mFGStartupInfoList[i].toString();
    }
    exportFile(mFGStartupInfoList,PATH_OUTPUT);
}

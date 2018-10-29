#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <bits/stdc++.h>

using namespace std;
#define PATH "C:/Users/DINH TUYEN/Desktop/gittest/new git/gittest/parse config/DemoConfig.cfg"
enum SyncPointType : uint16_t {
    kFGActivated =0,
    kAllComponentRegistered,
    kAllComponentReachedFirstState,
    kFreeDefined
};
struct DependencyFG {
    DependencyFG(){};
    std::string FGname;
    SyncPointType type;
};
class FGStartupInfo{

public:
    FGStartupInfo(){};
    virtual         ~FGStartupInfo(){};
    std::string name;
    //Internal FG info
    std::string state;
    std::vector <std::string> exeName;
    bool bHasTriggeredActivate;
    //Sync Points related to FG
    bool bActivatedSync;
    bool bAllComponentOfFGRegisteredSync;
    bool bAllComponentOfFGReachedFirstStateSync;
    //FG dependencies
    std::vector <DependencyFG> listDependFG;
    void toString(){
        cout << "name = " << name << endl;
        cout << "state = " << state <<endl;
        cout << "execute list : " << endl;
        for(unsigned int i = 0 ; i < exeName.size(); i++){
            cout << "exeName " << i << "= "<<exeName[i] << endl;
        }
        cout << "dependency list : " << endl;
        for(unsigned int i = 0 ; i < listDependFG.size(); i++){
            cout << "dependency " << i+1 << endl;
            cout << "name = " << listDependFG[i].FGname<< endl;
            cout << "type = " << (int)listDependFG[i].type<< endl;
        }
    }

protected:

};

string trim(string input){
    string ret = "";
    smatch match;
    regex charRegex("\\S+");
      if (regex_search(input, match, charRegex) == true) {
        ret = match.str();
    }
    return ret;
}


FGStartupInfo  getFGConfig(std::string input){




}
int main()
{
    string fileName  = PATH;
    ifstream file(fileName);
    if(!file){
        cout << "Invalid file !" << endl;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    string str = buffer.str();

    DependencyFG mDependencyFG;
    vector<FGStartupInfo> mFGStartupInfoList ;

try {

  std::regex testRegex("\\s*\\{[\\w\\s\\/\\d]*Name\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*State\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*ExecuteList\\s*:\\s*\\[\\/\\/ array(\\s*[^\\s,\\]]*,\\s*)+\\],\\s*DependencyFGList\\s*:\\s*\\[(\\s*[\\S]*\\s*:\\s*\\{\\s*[^,]*,\\s*[\\w]*\\s*\\},?\\s*)+\\]\\s*\\}\\s*");
  vector<int> index_matches;
  for(auto it = std::sregex_iterator(str.begin(), str.end(), testRegex);it != std::sregex_iterator();++it)
    {
        cout << "it->position() :  = "<<it->position() << endl;
        index_matches.push_back(it->position());
    }
  smatch match;
    cout << "index_matches.size() = " << index_matches.size() << endl;



    // define regex
    std::regex nameRegex("Name\\s*:\\s*[^\\s,]*,");
    std::regex stateRegex("\\s*State\\s*:\\s*[^\\s,]*,");
    std::regex executeRegex("\\s*ExecuteList\\s*:\\s*\\[\\/\\/ array(\\s*[^\\s,\\]]*,\\s*)+\\],");
    std::regex executeItemRegex("\\s*[^\\s,\\]]+,\\s*");
    std::regex dependencyRegex("\\s*DependencyFGList\\s*:\\s*\\[(\\s*[\\S]*\\s*:\\s*\\{\\s*[^,]*,\\s*[\\w]*\\s*\\},?\\s*)+\\]\\s*");
    std::regex dependencyItemRegex("\\{\\s*[^,]*,\\s*[\\w]*\\s*\\}");

    for(unsigned int t = 0 ; t < index_matches.size(); t++){
        FGStartupInfo mFGStartupInfo;
            cout << "t ======= " << t << endl;
          if (regex_search(str, match, testRegex) == true) {
            string result = str.substr(index_matches[t],match.length()) ;
            cout << result << endl;
                    // parse name
                  if (regex_search(result, match, nameRegex) == true) {
                        string nameStr = match.str();
                        string name = nameStr.substr(nameStr.find(":")+1,nameStr.find(",")- nameStr.find(":") -1) ;
                        cout << "Name = " <<name << endl;
                        mFGStartupInfo.name = trim(name);
                    }
                    // parse state
                  if (regex_search(result, match, stateRegex) == true) {
                        string stateStr = match.str();
                        string state = stateStr.substr(stateStr.find(":")+1,stateStr.find(",")- stateStr.find(":") -1) ;
                        cout << "State = "<< state << endl;
                        mFGStartupInfo.state = trim(state);
                    }
                    // parse execute list
                  if (regex_search(result, match, executeRegex) == true) {
                        cout << "Execute : = " << match.str() << endl;
                        string executeListStr = match.str();
                        vector<int> exe_index_matches;
                          for(auto it = std::sregex_iterator(executeListStr.begin(), executeListStr.end(), executeItemRegex);it != std::sregex_iterator();++it)
                            {
                                cout << "it->position1() :  = "<<it->position() << endl;
                                exe_index_matches.push_back(it->position());
                                string exeSubString = executeListStr.substr(it->position());
                                string exeName = trim(exeSubString.substr(0,exeSubString.find(",")));
                                cout << "exeSubString = " << exeName << endl;
                                mFGStartupInfo.exeName.push_back(exeName);
                            }

                    }
                    // parse FG dependency list
                  if (regex_search(result, match, dependencyRegex) == true) {
                                cout << "Dependency : = " << match.str() << endl;
                        string dependencyListStr = match.str();
                        vector<int> depen_index_matches;
                          for(auto it = std::sregex_iterator(dependencyListStr.begin(), dependencyListStr.end(), dependencyItemRegex);it != std::sregex_iterator();++it)
                            {
                                cout << "it->position2() :  = "<<it->position() << endl;
                                depen_index_matches.push_back(it->position());
                                string depenSubString = dependencyListStr.substr(it->position());
                                string depName = trim(depenSubString.substr(1,depenSubString.find(",")-1));
                                string depType = trim(depenSubString.substr(depenSubString.find(",")+1,depenSubString.find("}") - depenSubString.find(",") -1));
                                cout << "dependencyName= " << depName << endl;
                                cout << "dependencyType= " << depType << endl;
                                mDependencyFG.FGname = trim(depName);
                                mDependencyFG.type = (SyncPointType)1;//(SyncPointType)std::stoi(depType); dummy
                                mFGStartupInfo.listDependFG.push_back(mDependencyFG);

                            }
                    }
                    mFGStartupInfoList.push_back(mFGStartupInfo);
          }
    }
} catch (std::regex_error& e) {
    cout << "Error !" << e.what() << endl;
  // Syntax error in the regular expression
}
    cout << "result" << endl;
    for(unsigned int i = 0 ; i < mFGStartupInfoList.size(); i++){
            cout << "FG "<< i +1 << endl;
        mFGStartupInfoList[i].toString();
    }
    return 0;
}

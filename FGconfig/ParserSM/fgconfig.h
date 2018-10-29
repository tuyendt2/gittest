#ifndef FG_CONFIG
#define FG_CONFIG

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

#define uint unsigned int

#define NAME_REGEX "\\s*Name\\s*\\:\\s*[^,#]+\\s*,"
#define STATE_REGEX  "\\s*State\\s*\\:\\s*[^,#]+\\s*,"
#define EXECUTE_REGEX "\\s*ExecuteList\\s*\\:\\s*\\[(\\s*[^,#\\s\\]]+\\s*,)*\\s*[^,#\\s\\]]+\\s*\\]\\s*,"
#define EXECUTE_ITEM_REGEX "\\s*[^\\s,\\]]+\\s*,\\s*"
//#define DEPENDENCY_ITEM_REGEX "(\\{\\s*[\\w\\d]+\\s*,\\s*[0-3]\\s*\\})"
//#define DEPENDENCY_REGEX (std::string)"DependencyFGList\\s*\\:\\s*\\[(" + DEPENDENCY_ITEM_REGEX + (std::string)"\\s*,)*(" + DEPENDENCY_ITEM_REGEX + (std::string)")\\s*\\]\\s*"
#define DEPENDENCY_REGEX "\\s*DependencyFGList\\s*\\:\\s*\\[(\\s*[\\w\\d]+\\s*\\:\\s*\\{\\s*[\\w\\d]+\\s*,\\s*[0-3]\\s*\\},)*\\s*[\\w\\d]+\\s*\\:\\s*\\{\\s*[\\w\\d]+\\s*,\\s*[0-3]\\s*\\}\\s*\\]\\s*"
#define DEPENDENCY_ITEM_REGEX "\\{\\s*[^,]*,\\s*[\\w]*\\s*\\}"
#define FG_REGEX  (std::string)"\\{("+ NAME_REGEX +(std::string)")("+ STATE_REGEX + (std::string)")("+ EXECUTE_REGEX +(std::string)")(" + DEPENDENCY_REGEX+ (std::string)")\\}\\s*"
#define FILE_REGEX  (std::string)"\\s*FG:\\s*\\[\\s*(" + FG_REGEX + (std::string)",\\s*)*" + FG_REGEX + (std::string)"\\]\\s*"
//#define FG_REGEX "(\\{(\\s*Name\\s*\\:\\s*[^,#]+\\s*,)(\\s*State\\s*\\:\\s*[^,#]+\\s*,)(\\s*ExecuteList\\s*\\:\\s*\\[(\\s*[^,#\\s\\]]+\\s*,)*\\s*[^,#\\s\\]]+\\s*\\]\\s*,)(\\s*DependencyFGList\\s*\\:\\s*\\[(\\s*[\\w\\d]+\\s*\\:\\s*\\{\\s*[\\w\\d]+\\s*,\\s*[0-3]\\s*\\},)*\\s*[\\w\\d]+\\s*\\:\\s*\\{\\s*[\\w\\d]+\\s*,\\s*[0-3]\\s*\\}\\s*\\]\\s*)\\}\\s*)"

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
    void toString();// just for test, will be removed

protected:
};
void exportFile(std::vector<FGStartupInfo> fGList,std::string path);// for generating configuration file

std::string trim(std::string input);

std::vector<FGStartupInfo>  getFGConfig(std::string path);

std::string readConfigFile(std::string fileName);

bool validateFile(std::string path);

#endif // FG_CONFIG

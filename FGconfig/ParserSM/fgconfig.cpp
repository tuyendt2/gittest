#include "fgconfig.h"
using namespace std;

vector<FGStartupInfo>  getFGConfig(std::string path){
    vector<FGStartupInfo> mFGStartupInfoList ;
    DependencyFG mDependencyFG;
    string str = readConfigFile(path);

    try {
       // cout << "Start! " << endl;
    std::regex nameRegex(NAME_REGEX);

    std::regex stateRegex(STATE_REGEX);
    std::regex executeRegex(EXECUTE_REGEX);
    std::regex executeItemRegex(EXECUTE_ITEM_REGEX);
    std::regex dependencyRegex(DEPENDENCY_REGEX);
    std::regex dependencyItemRegex(DEPENDENCY_ITEM_REGEX);
    //cout << "FG regex before "<< endl << FG_REGEX << endl;
    std::regex testRegex(FG_REGEX) ;
    //cout << "FG regex after"<< endl << FILE_REGEX << endl;
    std::regex fileRegex(FILE_REGEX) ;
    //cout << "file regex " << endl << FILE_REGEX << endl;

    //cout << "Not exception! " << endl;
      std::smatch m_smatch;
      cout << "start" << endl;
      //std::regex fileRegex("\\s*FG\\s*:\\s*\\[\\s*(\\{[\\w\\s\\/\\d]*Name\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*State\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*ExecuteList\\s*:\\s*\\[(\\s*[^\\s,\\]]*\\s*,\\s*)+\\],\\s*DependencyFGList\\s*:\\s*\\[(\\s*[\\S]*\\s*:\\s*\\{\\s*[^,]*,\\s*[\\w]*\\s*\\},?\\s*)+\\]\\s*\\}\\s*(,)?\\s*)+\\]\\s*");
      regex_search(str,m_smatch,fileRegex);
      if((uint)m_smatch.length() == str.size() ){
        cout << "Valid file" << endl;
      }else{
        cout << "Invalid file!" << m_smatch.length() << endl;
      }

      if(regex_match(str,fileRegex) == true ){
      //std::regex testRegex("\\s*\\{[\\w\\s\\/\\d]*Name\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*State\\s*:\\s*[^\\s,]*,\\s*(\\/\\/\\s*[^\\n]*)*\\s*ExecuteList\\s*:\\s*\\[(\\s*[^\\s,\\]]*\\s*,\\s*)+\\],\\s*DependencyFGList\\s*:\\s*\\[(\\s*[\\S]*\\s*:\\s*\\{\\s*[^,]*,\\s*[\\w]*\\s*\\},?\\s*)+\\]\\s*\\}\\s*");

      vector<int> index_matches;
      for(auto it = std::sregex_iterator(str.begin(), str.end(), testRegex);it != std::sregex_iterator();++it)
        {
            //cout << "it->position() :  = "<<it->position() << endl;
            index_matches.push_back(it->position());
        }
      smatch match;
        //cout << "index_matches.size() = " << index_matches.size() << endl;

        // define regex
        /*std::regex nameRegex("Name\\s*:\\s*[^\\s,]*,");
        std::regex stateRegex("\\s*State\\s*:\\s*[^\\s,]*,");
        std::regex executeRegex("\\s*ExecuteList\\s*:\\s*\\[\\/\\/ array(\\s*[^\\s,\\]]*,\\s*)+\\],");
        std::regex executeItemRegex("\\s*[^\\s,\\]]+,\\s*");
        std::regex dependencyRegex("\\s*DependencyFGList\\s*:\\s*\\[(\\s*[\\S]*\\s*:\\s*\\{\\s*[^,]*,\\s*[\\w]*\\s*\\},?\\s*)+\\]\\s*");
        std::regex dependencyItemRegex("\\{\\s*[^,]*,\\s*[\\w]*\\s*\\}");*/



        for(uint t = 0 ; t < index_matches.size(); t++){
            FGStartupInfo mFGStartupInfo;
                //cout << "t ======= " << t << endl;
              if (regex_search(str, match, testRegex) == true) {
                    string result = str.substr(index_matches[t],match.length()) ;
                    //cout << result << endl;
                            // parse name
                          if (regex_search(result, match, nameRegex) == true) {
                                string nameStr = match.str();
                                string name = nameStr.substr(nameStr.find(":")+1,nameStr.find(",")- nameStr.find(":") -1) ;
                                //cout << "Name = " <<name << endl;
                                mFGStartupInfo.name = trim(name);
                            }
                            // parse state
                          if (regex_search(result, match, stateRegex) == true) {
                                string stateStr = match.str();
                                string state = stateStr.substr(stateStr.find(":")+1,stateStr.find(",")- stateStr.find(":") -1) ;
                                //cout << "State = "<< state << endl;
                                mFGStartupInfo.state = trim(state);
                            }
                            // parse execute list
                          if (regex_search(result, match, executeRegex) == true) {
                                //cout << "Execute : = " << match.str() << endl;
                                string executeListStr = match.str();
                                vector<int> exe_index_matches;
                                  for(auto it = std::sregex_iterator(executeListStr.begin(), executeListStr.end(), executeItemRegex);it != std::sregex_iterator();++it)
                                    {
                                        //cout << "it->position1() :  = "<<it->position() << endl;
                                        exe_index_matches.push_back(it->position());
                                        string exeSubString = executeListStr.substr(it->position());
                                        string exeName = trim(exeSubString.substr(0,exeSubString.find(",")));
                                        //cout << "exeSubString = " << exeName << endl;
                                        mFGStartupInfo.exeName.push_back(exeName);
                                    }
                            }
                            // parse FG dependency list
                          if (regex_search(result, match, dependencyRegex) == true) {
                                //cout << "Dependency : = " << match.str() << endl;
                                string dependencyListStr = match.str();
                                vector<int> depen_index_matches;
                                  for(auto it = std::sregex_iterator(dependencyListStr.begin(), dependencyListStr.end(), dependencyItemRegex);it != std::sregex_iterator();++it)
                                    {
                                        //cout << "it->position2() :  = "<<it->position() << endl;
                                        depen_index_matches.push_back(it->position());
                                        string depenSubString = dependencyListStr.substr(it->position());
                                        cout << "depenSubString : " << depenSubString << endl;
                                        string depName = trim(depenSubString.substr(1,depenSubString.find(",")-1));
                                        string depType = trim(depenSubString.substr(depenSubString.find(",")+1,depenSubString.find("}") - depenSubString.find(",") -1));
                                        cout << "dependencyName = " << depName << endl;
                                        //cout << "dependencyType= " << depType << endl;
                                        mDependencyFG.FGname = trim(depName);
                                        mDependencyFG.type = (SyncPointType)std::stoi(depType);
                                        mFGStartupInfo.listDependFG.push_back(mDependencyFG);

                                    }
                           }
                            mFGStartupInfoList.push_back(mFGStartupInfo);
                  }
            }
        }
    } catch (std::regex_error& e) {
        cout << "Error !" << e.what() << endl;
      // Syntax error in the regular expression
    } catch (exception &e){
            cout << "Exception !" << e.what() << endl;
    }
    return mFGStartupInfoList;
}

void FGStartupInfo::toString(){
        cout << "name = " << name << endl;
        cout << "state = " << state <<endl;
        cout << "execute list : " << endl;
        for(uint i = 0 ; i < exeName.size(); i++){
            cout << "exeName " << i << "= "<< exeName[i] << endl;
        }
        cout << "dependency list : " << endl;
        for(uint i = 0 ; i < listDependFG.size(); i++){
            cout << "dependency " << i+1 << endl;
            cout << "name = " << listDependFG[i].FGname<< endl;
            cout << "type = " << (int)listDependFG[i].type<< endl;
        }
}

void exportFile(vector<FGStartupInfo> fGList,std::string path){
    ofstream out(path,std::ofstream::out);
    out << "FG:\n\t\t[" << endl;
    for(uint i =0 ; i < fGList.size(); i++){
        out << "\t\t {" << endl;
        out << "\t\t\t Name : " << fGList[i].name << "," << endl;
        out << "\t\t\t State : " << fGList[i].state << "," << endl;
        // ExecuteList
        out << "\t\t\t ExecuteList : [" << endl;
        for(uint j = 0 ; j < fGList[i].exeName.size(); j++){
            if(j != (fGList[i].exeName.size() -1 )) {
                out << "\t\t\t\t\t\t\t" << fGList[i].exeName[j] << "," << endl;
            } else {
                out << "\t\t\t\t\t\t\t" << fGList[i].exeName[j] << endl;
            }
        }
        out << "\t\t\t ]," << endl;
        // ExecuteList end

        //DependencyFGList
        out << "\t\t\t DependencyFGList : [" << endl;
        for(uint t = 0 ; t < fGList[i].listDependFG.size(); t++){
            out << "\t\t\t\t\t\t\t FG_" << ( t + 1 ) << " : {" << endl;
            out << "\t\t\t\t\t\t\t\t " <<  fGList[i].listDependFG[t].FGname << "," << endl;
            out << "\t\t\t\t\t\t\t\t " <<  (uint)fGList[i].listDependFG[t].type << endl;
            if(t != (fGList[i].listDependFG.size() -1 )){
                out << "\t\t\t\t\t\t\t }," << endl;
            } else {
                out << "\t\t\t\t\t\t\t }" << endl;
            }
        }
        out << "\t\t\t\t ]" << endl;
        // DependencyFGList end
        if(i != (fGList.size() -1)){
            out << "\t\t }," << endl;
        }else {
            out << "\t\t }" << endl;
        }
    }
    out << "\t ]";
    out.close();
}

string trim(std::string input){
    string ret = "";
    smatch match;
    std::regex charRegex("\\S+");
      if (regex_search(input, match, charRegex) == true) {
        ret = match.str();
    }
    return ret;
}


std::string readConfigFile(std::string fileName){
    std::string fileContent = "";
    ifstream file(fileName);
    if(!file){
        cout << "Invalid file !" << endl;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    fileContent = buffer.str();
    file.close();
    return fileContent;
}

bool validateFile(std::string path){
    bool ret = true;
    string str = readConfigFile(path);
    return ret;
}

#include "PluginManager.hh"
#include <iostream>
#include <dlfcn.h>
#include <fstream>
#include <iomanip>
#include <sstream>

#include <stdio.h>

using namespace std;

const int LINE_LEN = 100;

PluginManager::~PluginManager(){
  for(const auto &x : plugins){
    
    /* delete x.second->interpreter;
       dlclose(x.second->libHandler);*/
    delete x.second;
  }
}

bool PluginManager::loadAndExecuteCommandFile(const string &name){
  string systemCommand = "cpp -P " + name;
  FILE* inFile = popen(systemCommand.c_str(),"r");
  char line[LINE_LEN];
  visualization.Draw(&pose);
  string commandName;
  bool correctFlag = true;
  
  while(fgets(line,sizeof(line),inFile) != NULL){
    string linestr(line);
    istringstream stream(linestr);
    stream >> commandName;
    if(stream.fail()){
      cerr << "Blad przy zczytywaniu nazwy komendy!\n";
      correctFlag = false;
      break;
    }
    auto it = plugins.find(commandName);
    if(it == plugins.end()){
      cerr << "Nieznana komenda: " << commandName << endl;
      correctFlag = false;
      break;
    }
    if(it->second->interpreter->ReadParams(stream) == false){
      correctFlag = false;
      break;
    }
    if(it->second->interpreter->ExecCmd(&pose,&visualization) == false){
      correctFlag = false;
      break;
    }
    if(visualization.fail()){  // gdy nastąpi kolizja
      visualization.clear();
      pclose(inFile);
      return true;
    }
  }
  pclose(inFile);
  return correctFlag;
}



void PluginManager::listCommands(const string &name){
  string systemCommand = "cpp -P " + name;
  FILE* inFile = popen(systemCommand.c_str(),"r");
  char line[LINE_LEN];
  string commandName;
  
  while(fgets(line,sizeof(line),inFile) != NULL){
    string linestr(line);
    istringstream stream(linestr);
    stream >> commandName;
    auto it = plugins.find(commandName);
    if(it == plugins.end())
      continue;
    it->second->interpreter->ReadParams(stream);
    it->second->interpreter->PrintCmd();
  }
  pclose(inFile);
  
}


void PluginManager::listPlugins(){
  for(const auto &x : plugins){
    x.second->interpreter->PrintSyntax();
  }
}



bool PluginManager::addPlugin(const char *name){
  Plugin* plug = new Plugin();
  plug->libHandler = dlopen(name,RTLD_LAZY);
  Interp4Command *(*pCreateCmd_Move)(void);
  void *pFun;

  if (!plug->libHandler) {
    cerr << "Brak biblioteki " << name << endl;
    return false;
  }

  pFun = dlsym(plug->libHandler,"CreateCmd");
  if (!pFun) {
    cerr << "Nie znaleziono funkcji CreateCmd" << endl;
    return false;
  }

  pCreateCmd_Move = reinterpret_cast<Interp4Command* (*)(void)>(pFun);
  plug->interpreter = pCreateCmd_Move();
  plugins.insert(make_pair(plug->interpreter->GetCmdName(),plug));
  return true;
}


bool PluginManager::deletePlugin(const string &name){
  auto it = plugins.find(name);
  if(it != plugins.end()){
    /*delete it->second->interpreter;
      dlclose(it->second->libHandler);*/
    delete it->second;
    plugins.erase(it);
    return false;
  }
  return true;
}

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <readline/readline.h>
#include <readline/history.h>
#include "PluginManager.hh"

#include <stdio.h>

#define PLUGIN1 "libs/Interp4Fly.so"
#define PLUGIN2 "libs/Interp4Turn.so"
#define PLUGIN3 "libs/Interp4Rotate.so"
#define PLUGIN4 "libs/Interp4ReadScene.so"
#define PLUGIN5 "libs/Interp4Pause.so"

using namespace std;

void displayMenu();

int main(int argc, char * argv[])
{
  PluginManager manager;
  manager.addPlugin(PLUGIN1);
  manager.addPlugin(PLUGIN2);
  manager.addPlugin(PLUGIN3);
  manager.addPlugin(PLUGIN4);
  manager.addPlugin(PLUGIN5);
  
  if(argc == 2){ // program w trybie wykonania pojedynczego pliku komend
    if(!manager.loadAndExecuteCommandFile(string(argv[1])))
      return -1;
    cout << "Aby zakonczyc nacisnij klawisz ENTER" << endl;
    cin >> skipws;
    cin.ignore(100000,'\n');
    return 0;
  }
  
  char choice = '?', *line;
  const char *prompt = "Twoj wybor (? - menu)> ";
  istringstream input;
  string name;

  rl_bind_key('\t', rl_complete);
  do{
    switch(choice){
    case 'w':
      line = readline("Podaj nazwe pliku: ");
      if(!line)
	return 0;
      add_history(line);
      if(manager.loadAndExecuteCommandFile(string(line)))
	cout << "Plik z instrukcjami wczytany i wykonany poprawnie.\n";
      else
	return -1;
      
      free(line);     
      break;
    case 'p':
      line = readline("Podaj nazwe pliku: ");
      if(!line)
	return 0;
      add_history(line);
      manager.listCommands(string(line));
      free(line);
      break;
    case 'i':
      manager.listPlugins();
      break;
    case 'a':
      line = readline("Podaj nazwe pliku z biblioteka: ");
      if(!line)
	return 0;
      add_history(line);
      line[strlen(line)-1] = '\0'; // usuniecie spacji z konca linii
      if(manager.addPlugin(line))
	cout << "Poprawnie dodano wtyczkę.\n";
      free(line);
      break;
    case 'd':
      line = readline("Podaj nazwe komendy: ");
      if(!line)
	return 0;
      add_history(line);
      if(manager.deletePlugin(string(line)))
	cout << "Poprawnie usunieto wtyczke.\n";
      free(line);
      break;
    case '?':
      displayMenu();
      break;
    default:
      cerr << "Nieznana opcja menu\n";
      break;
    }
    line = readline(prompt);
    if(!line)
      return 0;
    add_history(line);
    input.str(line);
    free(line);
  }while(input >> choice, choice != 'k');
  cout << "Koniec dzialania programu\n";
}


void displayMenu(){
  cout << "\nw - wczytaj i wykonaj plik z komendami\n"
       << "p - pokaz sekwencje instrukcji dla podanego pliku\n"
       << "i - pokaz dostepne instrukcje/wtyczki\n"
       << "a - dodaj nowa wtyczke\n"
       << "d - usun wtyczke\n"
       << "? - wyswietl ponownie menu\n\n"
       << "k - koniec dzialania program\n\n";
}

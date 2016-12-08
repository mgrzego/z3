#ifndef PLUGIN_MANAGER_HH
#define PLUGIN_MANAGER_HH

#include "Interp4Command.hh"
#include "DronPose.hh"
#include "GnuplotVisualizer.hh"
#include "Plugin.hh"
#include <map>
#include <string>

/*!
 * \file
 * \brief Definicja klasy menadżera wtyczek
 *
 * Plik zawiera definicję klasy odpowiedzialnej za zarządzanie wtyczkami, 
 * oraz wykonywanie związanych z nimi czynności
 */

/*!
 * \brief Klasa menadżera wtyczek
 *
 * Klasa przechowująca uchwyty do wszystkich otwartych bibliotek 
 * współdzielonych, oraz obiekty klas odpowiedzialnych za wizualizację ruchu
 * robota i obliczanie jego położenia. Klasa posiada metody
 * pozwalające na dodawanie i usuwanie wtyczek, wczytywanie plików z komendami
 * , wykonywanie tych komend, itp. Ogólnie rzecz biorąc realizuje całą 
 * funkcjonalnośc aplikacji, poza wyświetlaniem i obsługą tekstowego menu. 
 */

class PluginManager{
  /*! 
   * \brief Mapa wtyczek wraz z nazwami
   *
   * Mapa w której kluczem jest string przechowujący nazwę komendy, 
   * natomiast elementem jest obiekt reprezentujący wtyczkę Kontener ten
   * przechowuje  wszystkie altualnie załadowane wtyczki, pozwala na wygodny 
   * dostęp do nich podczas wczytywania listy komend, które muszą zostać 
   * zinterpretowane przez odpowiednie wtyczki, jak również podczas procesu
   * dodawania/usuwania wtyczek. 
   */
  std::map<std::string,Plugin*> plugins;
  /*!
   * \brief Obiekt odpowiedzialny za wizualizację
   *
   * Instancja klasy GNUPlotVisualizer pozwalającej na wizualizację ruchu
   * drona za pomocą programu GNUPlot. 
   */
  GnuplotVisualizer visualization;
  /*!
   * \brief Obiekt przechowujący położenie i orientację robota
   *
   * W tym obiekcie przechowywane są aktualne parametry, dotyczące pozycji
   * drona. Po wykonaniu każdej listy poleceń, położenie drona jest nie wraca
   * do punktu startowego, tylko jest zapamiętywane. Dzięki temu przy 
   * wykonywaniu następnych poleceń, dron może rozpocząć swoją ścieżkę tam, 
   * gdzie zakończył poprzednią. 
   */
  DronPose pose;
public:
  ~PluginManager();
  /*!
   * \brief Wczytuje plik z komendami, które na bieżąco wykounuje
   *
   * Funkcja otwiera plik z komendami, odczytując z niego wszystkie 
   * przeznaczone dla robota instrukcje. Odczytane dane program natychmiast
   * wykonuje. Na koniec plik jest zamykany. 
   * \post zmienna pose zostaje zaktualizowana o nowe przemieszczenia
   * \param[in] name - nazwa pliku z komendami.
   * \retval true - działanie funkcji przebiegło pomyślnie
   * \retval false - działanie funkcji zakończone niepowodzeniem.  
   */
  bool loadAndExecuteCommandFile(const std::string &name);
  /*!
   * \brief Wypisuje wczytane polecenia
   *
   * Funkcja wypisuje na standardowe wyjście programu wszystkie polecenia
   * wczytane z pliku z komendami. 
   * \param[in] name - nazwa pliku z komendami.
   */
  void listCommands(const std::string &name);
  /*!
   * \brief Wypisuje dostępne wtyczki
   *
   * Funkcja wypisuje na standardowe wyjście programu wszystkie wczytane 
   * wtyczki, będące jednocześnie listą komend, które program jest w danej 
   * chwili w stanie wykonać. 
   */
  void listPlugins();
  /*!
   * \brief Dodaje wtyczkę
   *
   * Funkcja otwiera bibliotekę współdzieloną zawierająca wtyczkę oraz dodaje
   * ją do mapy plugins. 
   * \post Do mapy plugins zostaje dodana nowa wtyczka, o ile wczytywanie
   *       przebiegło poprawnie. 
   * \param[in] name - nazwa pliku biblioteki współdzielonej, z którego ma 
   *                   zostać wczytana wtyczka.
   * \retval true - dodawanie wtyczki przebiegło pomyślnie.
   * \retval false - błąd podczas dodawania wtyczki.
   */
  bool addPlugin(const char *name);
  /*!
   * \brief Usuwa wtyczkę
   * 
   * Funkcja usuwa wtyczkę o nazwie przekazanej jako parametr name. Nie jest 
   * to nazwa pliku biblioteki współdzielonej jak w przypadku dodawania 
   * wtyczki, tylko podstawowa nazwa komendy. 
   * \post Z mapy plugins usunięty zostaje element o kluczu name (jeśli taki
   *       istniał.
   * \param[in] name - nazwa usuwanej wtyczki.
   * \retval true - Wtyczka poprawnie usunięta.
   * \retval false - Błąd! Brak elementu o podanym kluczu.
   */
  bool deletePlugin(const std::string &name);

};

#endif

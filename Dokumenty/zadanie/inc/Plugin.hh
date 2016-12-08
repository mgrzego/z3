#ifndef PLUGIN_HH
#define PLUGIN_HH

#include "Interp4Command.hh"
#include <dlfcn.h>

/*!
 * \file
 * \brief Definicja struktury wtyczki
 *
 * Plik zawiera definicję prostej struktury modelującej pojęcie wtyczki
 */

/*!
 * \brief Struktura wtyczki
 *
 * Prosta struktura łącząca uchwyt do biblioteki współdzielonej, z instancją
 * klasy odpowiedzialnej za interpretację i wykonywanie komendy, której
 * dotyczy ta biblioteka. Oba te obiekty scalone razem mozna określić mianem
 * wtyczki.
 */

struct Plugin{
  /*!
   * \brief Destruktor klasy Plugin.
   *
   * Destruktor zapewnia poprawne zniszczenie obiektu. Jest on bardzo ważny, 
   * gdyż w tym przypadku zasoby muszą zostać zwalniane w odpowiedniej 
   * kolejności, inaczej program spowoduje błąd ochrony pamięci.
   */ 
  ~Plugin(){
    delete interpreter;
    dlclose(libHandler);
  }
  /*!
   * \brief Uchwyt do biblioteki współdzielonej
   *
   * Po otwarciu biblioteki, wskaźnik do niej zostaje zapisany w tym obiekcie.
   * Jest on niezbędny do poprawnego zamknięcia biblioteki pod koniec działania
   * programu.
   */
  void* libHandler;
  /*!
   * \brief Instancja klasy interpretera
   *
   * Wskaźnik polimorficzny na klasę pochodną od Interp4Command. Obiekt tej
   * klasy używany jest do wykonywania poleceń ruchu drona, oraz do kilku 
   * pomniejszych zadań, takich jak np. wypisywanie składni polecenia. 
   */
  Interp4Command* interpreter;
  
};

#endif

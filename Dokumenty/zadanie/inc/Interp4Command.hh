#ifndef  INTERP4COMMAND_HH
#define  INTERP4COMMAND_HH

#include <iostream>
#include "DronPose.hh"
#include "Visualization.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Command
 *
 * Plik zawiera definicję klasy Interp4Command, stanowiącej bazę dla wszystkich
 * klas obsługujących poszczególne polecenia dla drona. Klasy te kompilowane są
 * osobno, i dołączane do głównego programu w formie bibliotek dzielonych. 
 */

/*!
 * \brief Precyzja odtwarzania animacji
 *
 * Liczba sekund, co którą pojawi się nowa klatka w animacji ruchu drona
 */
const double TIME_PRECISION = 0.03;

/*!
 * \brief Modeluje abstrakcyjne polecenie dla robota mobilnego
 *
 * Klasa abstrakcyjna, stanowiąca interfejs, za pomocą którego możemy
 * wykonywać konkretne polecenie. 
 */
 class Interp4Command {
  public:
   /*!
    * \brief Destruktor wirtualny ze wzgledu na klasy pochodne
    *
    * 
    */
   virtual ~Interp4Command() {}
   /*!
    * \brief Wypisuje wartości parametrów
    *
    * W klasach pochodnych metoda ta używana jest to wypisywania nazwy
    * polecenia oraz aktualnych wartości parametrów na standardowe wyjście.
    */
   virtual void PrintCmd() const = 0;
   /*!
    * \brief Wypisuje składnię polecenia
    *
    * W klasach pochodnych metoda ta uzywana jest do wypisywania składni 
    * polecenia na standardowe wyjście.
    */
   virtual void PrintSyntax() const = 0;
   /*!
    * \brief Zwraca nazwę komendy
    *
    * W klasach pochodnych metoda ta używana jest do uzyskania z obiektu
    * nazwy komendy, która dany obiekt obsługuje. 
    */
   virtual const char* GetCmdName() const = 0;
   /*!
    * \brief Wykonuje komendę
    *
    * W klasach pochodnych metoda ta używana jest do wykonania odpowiedniej
    * komendy.
    */
   virtual bool ExecCmd(  DronPose  *pRobPose,  Visualization *pVis  ) const = 0;
   /*!
    * \brief Odczytuje parametry
    *
    * W klasach pochodnych metoda ta używana jest to wczytania parametrów
    * z przekazanego strumienia. 
    */
   virtual bool ReadParams(std::istream& Strm_CmdsList) = 0;
 };

#endif

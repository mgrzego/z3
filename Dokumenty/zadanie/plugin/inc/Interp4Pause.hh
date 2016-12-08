#ifndef  COMMAND4PAUSE_HH
#define  COMMAND4PAUSE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Pause
 *
 * Plik zawiera definicję klasy Interp4Pause, obsługującej polecenie 
 * zatrzymania wykonywania komend przez określoną liczbę milisekund. 
 */

/*!
 * \brief Modeluje polecenie dla sceny, które wymusza pauzę
 *
 * Klasa modeluje polecenie dla sceny, które zatrzymuje wykonywanie kolejnych
 * poleceń przez liczbę milisekund podaną jako argument.  
 */
class Interp4Pause: public Interp4Command {
  /*!
   * \brief liczba milisekund którą ma trwać pauza
   */
  double time_ms;
 public:
  /*!
   * \brief Konstruktor klasy
   *
   * Konstruktor inicjalizuje wszystkie parametry polecenia zerami
   */
  Interp4Pause();  
  /*!
   * \brief Wypisuje wartości parametrów
   *
   * Metoda ta używana jest to wypisywania nazwy polecenia oraz aktualnych
   * wartości parametrów na standardowe wyjście.
   */
  virtual void PrintCmd() const;
  /*!
   * \brief Wypisuje składnię polecenia
   *
   * Metoda ta uzywana jest do wypisywania składni polecenia na standardowe
   * wyjście.
   */
  virtual void PrintSyntax() const;
  /*!
   * \brief Zwraca nazwę komendy
   *
   * Metoda ta używana jest do uzyskania z obiektu nazwy komendy, która dany
   * obiekt obsługuje. W tym przypadku jest to słowo 'Pause'. Jest przydatna
   * przy tworzeniu mapy, w której kluczem jest nazwa komendy, lub przy 
   * wypisywaniu parametrów polecenia. 
   * \return Metoda zwraca nazwę komendy jako łańcuch w stylu C
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje komendę
   *
   * Metoda ta używana jest do wykonania polecenia pauzy. 
   * \param[out] pRobPose - aktualna pozycja drona
   * \param[out] pVis - wskaźnik na obiekt odpowiedzialny za wizualizację
   * \retval true - wykonywanie komendy przebiegło poprawnie
   * \retval false - wystąpił błąd podczas wykonywania komendy
   */
  virtual bool ExecCmd( DronPose  *pRobPose,   Visualization *pVis) const;
  /*!
   * \brief Odczytuje parametry komendy
   *
   * Metoda odczytuje parametry komendy z przekazanego strumienia, i zapisuje 
   * je w swoich zmiennych prywatnych. 
   * \param[in] Strm_CmdsList - strumień, z którego mają zostać odczytane dane
   * \retval true - dane zczytane poprawnie
   * \retval false - błąd przy zczytywaniu danych
   */
  virtual bool ReadParams(std::istream& Strm_CmdsList);
  /*!
   * \brief Tworzy nowy obiekt klasy Interp4Pause
   *
   * Metoda tworzy na stercie nowy obiekt typu Interp4Pause i zwraca wskaźnik
   * do niego. Typem zwracanym jest wskaźnik na klasę bazową, następuje więc
   * niejawne rzutowanie w górę. 
   * \return Metoda zwraca wskaźnik na obiekt typu Interp4Pause 
   */
  static Interp4Command* CreateCmd();
 };

#endif

#ifndef  COMMAND4MOVE_HH
#define  COMMAND4MOVE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Fly
 *
 * Plik zawiera definicję klasy Interp4Fly, obsługującej polecenie lotu po 
 * lini prostej. 
 */

/*!
 * \brief Modeluje polecenie dla drona, które wymusza jego ruch po lini prostej
 *
 * Klasa modeluje polecenie dla drona, w którym porusza się on po lini
 * prostej z zadaną predkością horyzontalną i wertykalną. 
 */
class Interp4Fly: public Interp4Command {
  /*!
   * \brief predkość horyzontalna
   */
  double horizontalSpeed;
  /*!
   * \brief prędkość wertykalna
   */
  double verticalSpeed;
  /*!
   * \brief długość drogi
   */
  double distance;
 public:
  /*!
   * \brief Konstruktor klasy
   *
   * Konstruktor inicjalizuje wszystkie parametry polecenia zerami
   */
  Interp4Fly();  
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
   * obiekt obsługuje. W tym przypadku jest to słowo 'Fly'. Jest przydatna
   * przy tworzeniu mapy, w której kluczem jest nazwa komendy, lub przy 
   * wypisywaniu parametrów polecenia. 
   * \return Metoda zwraca nazwę komendy jako łańcuch w stylu C
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje komendę
   *
   * Metoda ta używana jest do wykonania polecenia ruchu robota po prostej
   * lini. Na podstawie przekazanych wcześniej do klasy parametrów oraz 
   * aktualnej pozycji drona, wyliczane jest jego nowe położenie. Pozycja 
   * zostaje zaktualizowana, a klasa odpowiedzialna za wizualizację otrzymuje
   * kolejny punkt stanowiący fragment ścieżki robota. 
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
   * \brief Tworzy nowy obiekt klasy Interp4Fly
   *
   * Metoda tworzy na stercie nowy obiekt typu Interp4Fly i zwraca wskaźnik
   * do niego. Typem zwracanym jest wskaźnik na klasę bazową, następuje więc
   * niejawne rzutowanie w górę. 
   * \return Metoda zwraca wskaźnik na obiekt typu Interp4Fly 
   */
  static Interp4Command* CreateCmd();
 };

#endif

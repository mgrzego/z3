#ifndef  COMMAND4ROTATE_HH
#define  COMMAND4ROTATE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Rotate
 *
 * Plik zawiera definicję klasy Interp4Rotate, obsługującej polecenie obrotu
 * drona wokół własnej osi.  
 */

/*!
 * \brief Modeluje polecenie dla drona, które wymusza jego obrót
 *
 * Klasa modeluje polecenie dla drona, w którym obraca się on wokół własnej 
 * osi z zadaną prędkością kątową 
 */
class Interp4Rotate: public Interp4Command {
  /*!
   * \brief prędkość kątowa
   */
  double speed;
  /*!
   * \brief kąt obrotu
   */
  double angle;
 public:
 /*!
   * \brief Konstruktor klasy
   *
   * Konstruktor inicjalizuje wszystkie parametry polecenia zerami
   */
  Interp4Rotate();  
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
   * obiekt obsługuje. W tym przypadku jest to słowo 'Rotate'. Jest przydatna
   * przy tworzeniu mapy, w której kluczem jest nazwa komendy, lub przy 
   * wypisywaniu parametrów polecenia. 
   * \return Metoda zwraca nazwę komendy jako łańcuch w stylu C
   */
  virtual const char* GetCmdName() const;
 /*!
   * \brief Wykonuje komendę
   *
   * Metoda ta używana jest do wykonania polecenia obrotu drona wokół własnej
   * osi. Na podstawie przekazanych wcześniej do klasy parametrów oraz 
   * aktualnej pozycji drona, wyliczana jest jego nowa orientacja. Pozycja 
   * zostaje zaktualizowana o nowy kąt robota.  
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
   * \brief Tworzy nowy obiekt klasy Interp4Rotate
   *
   * Metoda tworzy na stercie nowy obiekt typu Interp4Rotate i zwraca wskaźnik
   * do niego. Typem zwracanym jest wskaźnik na klasę bazową, następuje więc
   * niejawne rzutowanie w górę. 
   * \return Metoda zwraca wskaźnik na obiekt typu Interp4Rotate
   */
  static Interp4Command* CreateCmd();
 };

#endif

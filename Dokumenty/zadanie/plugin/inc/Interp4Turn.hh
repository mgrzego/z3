#ifndef  COMMAND4TURN_HH
#define  COMMAND4TURN_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"

/*!
 * \file
 * \brief Definicja klasy Interp4Turn
 *
 * Plik zawiera definicję klasy Interp4Turn, obsługującej polecenie lotu po 
 * łuku. 
 */

/*!
 * \brief Dokładność rysowania łuku
 *
 * Stała określa dokładność, z jaką łuk skrętu przybliżany jest za pomocą
 * wierzchołka. Jej wartość jest równa ilości wierzchołków, które przypadną
 * na każde 180 stopni rysowanego łuku. Jest wykorzystywana w obliczeniach 
 * zmiennoprzecinkowych, stąd typ double. Dopuszczalna jest więc wartość nie
 * będąca liczbą całkowitą. 
 */
const double PRECISION = 16.0;

/*!
 * \brief Modeluje polecenie dla drona, które wymusza jego ruch po łuku
 *
 * Klasa modeluje polecenie dla drona, w którym porusza się on po łuku o 
 * zadanym promieniu krzywizny, z zadaną prędkością. Określony jest również
 * dystans, który dron ma przebyć. 
 */
class Interp4Turn: public Interp4Command {
  /*!
   * \brief predkośc drona
   */
  double speed;
  /*!
   * \brief dystans do przebycia
   */
  double distance;
  /*!
   * \brief promień krzywizny ścieżki
   */
  double radius;
 public:
  /*!
   * \brief Konstruktor klasy
   *
   * Konstruktor inicjalizuje wszystkie parametry polecenia zerami
   */
  Interp4Turn();  
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
   * obiekt obsługuje. W tym przypadku jest to słowo 'Turn'. Jest przydatna
   * przy tworzeniu mapy, w której kluczem jest nazwa komendy, lub przy 
   * wypisywaniu parametrów polecenia. 
   * \return Metoda zwraca nazwę komendy jako łańcuch w stylu C
   */
  virtual const char* GetCmdName() const;
  /*!
   * \brief Wykonuje komendę
   *
   * Metoda ta używana jest do wykonania polecenia ruchu robota po łuku.
   * Na podstawie przekazanych wcześniej do klasy parametrów oraz 
   * aktualnej pozycji drona, wyliczane jest jego nowe położenie. Pozycja 
   * zostaje zaktualizowana, a klasa odpowiedzialna za wizualizację otrzymuje
   * serię punktów, które przybliżają wycinek koła po którym poruszał się dron.
   * Dokładnośc tego przybliżenia może zostać ustawiona poprzez modyfikację
   * stałej PRECISION. 
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
   * \brief Tworzy nowy obiekt klasy Interp4Turn
   *
   * Metoda tworzy na stercie nowy obiekt typu Interp4Turn i zwraca wskaźnik
   * do niego. Typem zwracanym jest wskaźnik na klasę bazową, następuje więc
   * niejawne rzutowanie w górę. 
   * \return Metoda zwraca wskaźnik na obiekt typu Interp4Turn 
   */
  static Interp4Command* CreateCmd();
 };

#endif

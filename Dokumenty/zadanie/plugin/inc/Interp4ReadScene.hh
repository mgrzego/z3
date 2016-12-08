#ifndef  COMMAND4READSCENE_HH
#define  COMMAND4READSCENE_HH

#ifndef __GNUG__
# pragma interface
# pragma implementation
#endif

#include "Interp4Command.hh"
#include <string>

/*!
 * \file
 * \brief Definicja klasy Interp4ReadScene
 *
 * Plik zawiera definicję klasy Interp4ReadScene, obsługującej polecenie 
 * wczytania sceny z pliku. 
 */

/*!
 * \brief Modeluje polecenie dla sceny, które wymusza jej wczytanie z pliku
 *
 * Klasa modeluje polecenie dla sceny, polegające na otwarciu pliku XML i 
 * odczytaniu z niego informacji na temat przeszkód znajdujących się na scenie 
 */
class Interp4ReadScene: public Interp4Command {
  /*!
   * \brief nazwa pliku XML
   */
  std::string fileName;
public:
  /*!
   * \brief Konstruktor klasy
   *
   * Konstruktor inicjalizuje wszystkie parametry polecenia zerami
   */
  Interp4ReadScene();  
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
   * Metoda ta używana jest do wykonania polecenia wczytania sceny z pliku
   * XML. Sama wtyczka stanowi jedynie opakowanie dla właściwej funkcji, która
   * znajduje się w klasie GnuplotVisualizer, dziedziczącej po Visualization.  
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
   * \brief Tworzy nowy obiekt klasy Interp4ReadScene
   *
   * Metoda tworzy na stercie nowy obiekt typu Interp4ReadScene i zwraca 
   * wskaźnik do niego. Typem zwracanym jest wskaźnik na klasę bazową, 
   * następuje więc niejawne rzutowanie w górę. 
   * \return Metoda zwraca wskaźnik na obiekt typu Interp4ReadScene 
   */
  static Interp4Command* CreateCmd();
 };

#endif

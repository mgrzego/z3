#ifndef GNUPLOTVISULIZER_HH
#define GNUPLOTVISULIZER_HH



#include "Visualization.hh"
#include "lacze_do_gnuplota.hh"
#include "scene.hh"

/*!
 * \file
 * \brief Definicja klasy wizualizacji
 *
 * Plik zawiera definicję klasy odpowiedzialnej za wizualizację przelotu
 * drona za pomocą programu GNUPlot. 
 */

/*!
 * \brief Nazwa pliku zawierającego współrzędne trajektorii drona
 *
 * Symbol definiuje nazwę pliku, do którego dopisywane są współrzędne
 * kolejnych punktów trajektrii. Na podstawie zawartości tego pliku
 * rysowana jest łamana reprezentująca trajektorię drona.
 */
#define FILE_NAME__TRAJECTORY         "trajektoria_drona.dat"
/*!
 * \brief Nazwa pliku zawierającego współrzędne korpusu drona
 *
 * Symbol definiuje nazwę pliku, do którego wpisywane są współrzędne
 * wierzchołków korpusu drona po każdorazowej zmianie jego pozycji.
 * Plik ten jest wykorzystywany do odczytu przez program gnuplot.
 * Na podstawi danych w nim zawartych.
 */
#define FILE_NAME__DRON_BODY_VIEW     "widok_drona.dat"
/*!
 * \brief Nazwa pliku z opisem były wzorcowej modelującej korpus drona
 *
 * Symbol definiuje nazwę pliku, w którym zapisane są współrzędne
 * wierzchołków bryły wzorcowej, która modeluje korpus drona.
 * Współrzędne są podane względem lokalnego układu współrzędnych,
 * w którym współrzędne środka to (0,0,0). Aby więc otrzymać obrys
 * bryły w aktualnej pozycji należy je rotować o kąt odpowiadający
 * aktualnej orientacji drona, a następnie dodać do współrzędnych
 * poszczególnych wierzchołków, współrzędne akutalne pozycji.
 */
#define FILE_NAME__DRON_BODY_TEMPLATE "elementarny_szescian.dat"


/*!
 * \brief Klasa odpowiedzialna za wizualizację
 *
 * Umożliwia wykorzystanie programu \p gnuplot do wizualizacji
 * ruchu drona.
 */
class GnuplotVisualizer: public Visualization {
  /*!
   * \brief Instancja klasy przechowującej przeszkody
   *
   * Instancja klasy scene, przechowującej informacje o przeszkodach na scenie.
   * Jest uzywana do wykrywania kolizji. 
   */
  Scene scene;
  /*!
   * \brief Zmienna określająca stan obiektu
   *
   * Zmienna określa, czy obiekt znajduje się w prawidłowym stanie. 
   * Nieprawidłowy stan oznacza wystąpienie kolizji. W takim przypadku dalszy 
   * ruch drona nie powinien mieć miejsca, jednak funkcja 
   * Interp4Command::ExecCmd nie jest w stanie powiadomić o kolizji wywołującej
   * jej funkcji. Jedynym sposobem jest więc ustawienie tej flagi w klasie 
   * wizualizacji. 
   */
  bool isValid;
  /*!
   * \brief Instancja klasy "Łącze do GNUPlota". 
   *
   *Pośredniczy w uruchomieniu i przekazywaniu poleceń
   *        do programu \p gnuplot
   */
  PzG::LaczeDoGNUPlota   Plotter;

  /*!
   * \brief Dodaje nazwy plików opisów obiektów reprezentujących drona
   */
  void AddDronFileNames4Gnuplot();
  /*!
   * \brief Tworzy i uruchamia obiekt parsera
   *
   * Funkcja tworzy obiekt klasy SAX2XMLReader, ustawia w nim odpowiednie opcje
   * , łączy go ze sceną a następnie uruchamia parser. 
   * \param[in] fileName - nazwa pliku XML. 
   * \retval true - parsowanie przebiegło pomyślnie.
   * \retval false - funkcja zakończyła się błędem.
   */
  bool readFile(const char* fileName);
public:
  /*!
   * \brief Kasuje zawartość plików danych i dodaje je do łącza do gnuplota
   */ 
  GnuplotVisualizer();
  /*! 
   * \brief Zwraca informacje o stanie obiektu
   *
   * Funkcja zwraca informacje o tym, czy obiekt znajduje się w poprawnym 
   * stanie. Niepoprawny stan oznacza wystąpienie kolizji. 
   * \retval true - obiekt znajduje się w niepoprawnym stanie.
   * \retval false - obiekt znajduje się w poprawnym stanie.
   */
  bool fail(){ return !isValid; }
  /*!
   * \brief Czyści flagę stanu
   *
   * Funkcja resetuję flagę stanu, ustawiając stan obiektu na poprawny. 
   */
  void clear() {isValid = true; }
  /*!
   * \brief Rysuje punkt i sprawdza kolizję
   *
   * Funkcja dodaje pliku nowy punkt trajektorii drona przekazany jako 
   * argument. Jednocześnie sprawdza, czy nowe położenie drona nie powoduje
   * kolizji z którąś z przeszkód. 
   * \param[in] pPose - nowa pozycja drona
   */
  virtual void Draw( const DronPose *pPose );
  /*!
   * \brief Metoda czyta opis sceny z pliku XML
   */
  virtual bool ReadScene(const char* FileName_XML); 
};


#endif

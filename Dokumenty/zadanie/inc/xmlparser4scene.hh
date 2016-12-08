#ifndef XMLPARSER4SCENE_HH
#define XMLPARSER4SCENE_HH


#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax/Locator.hpp>

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <string>

#include "Cuboid.hh"
#include "scene.hh"

/*!
 * \brief Implementuje reakcje na napotkane elementu opisu akcji
 *
 * Klasa zawiera zestaw metod, które wywoływane są w trakcie czytania i analizy
 * pliku XML.
 */
class XMLParser4Scene : public xercesc::DefaultHandler {
  public:
   /*!
    * \brief Inicjalizuje obiekt i kojarzy go ze sceną
    */
  XMLParser4Scene(Scene &Scn);


   /*!
    * \brief Wywoływana jest po napotkaniu nowego elementu XML
    */
    virtual void startElement(
                    const XMLCh *const pURI, 
                    const XMLCh *const pLocalName, 
                    const XMLCh *const pQNname,
                    const   xercesc::Attributes&     attrs
                  );

   /*!
    * \brief Wywoływana jest po dojściu do końca elementu XML
    */
    virtual  void endElement(
                    const XMLCh *const pURI, 
                    const XMLCh *const pLocalName, 
                    const XMLCh *const pQNname
                   );
   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd fatalny
    */
    void fatalError(const xercesc::SAXParseException&);

   /*!
    * \brief Wywoływana jest gdy napotkany zostanie błąd
    */
    void error(const xercesc::SAXParseException &exc);

   /*!
    * \brief Wywoływana jest gdy parser sygnalizuje ostrzeżenie
    */
    void warning(const xercesc::SAXParseException &exc);


  private:
  /*!
   * \brief Czyści tablicę flag
   *
   * Ustawia wszystkie wartości w tablicy 'flags' na 'false'. 
   */
  void clearFlags();
  /*!
   * \brief Sprawdza czy przeszkoda jest kompletna
   *
   * Metoda sprawdza, czy wszystkie elementy tablicy 'flags' mają wartość
   * 'true'. Jeśli tak, przeszkoda jest kompletna. 
   * \retval true Przeszkoda jest kompletna
   * \retval false Nie wszystkie parametry wszytane
   */
  bool isObstacleComplete();
  /*!
   * \brief Tablica flag przeszkody
   *
   * Tablica flag, która zapełniana jest wraz z wczytywaniem kolejnych
   * parametrów przeszkody. Jeśli pod koniec czytania przeszkody wszystkie 
   * wartości są równe 'true', przeszkoda została wczytana poprawnie. Jeśli
   * nie, wystąpił błąd.
   */
  bool flags[6];
    /*!
   * \brief Przetwarza atrybuty parametrów przeszkody
   *
   * Metoda prywatna wywoływana przez funkcję startElement po napotkaniu na
   * element będący parametrem prostopadłościanu. Jest odpowiedzialna za
   * wyłuskanie danych obiektu i zapisanie ich w odpowiedniej zmiennej.
   * \param[in] Attrs - obiekt przechowujący atrybuty parametru
   * \post Zmienna tmpSize lub tmpCenter powinna zostać zaktualizowana o nową
   * wartość. 
   */
  void processParameterAttrs(const xercesc::Attributes &Attrs);
   /*!
   * \brief Tymczasowa przeszkoda
   *
   * Obiekt uzupełniany w trakcie parsowania pliku XML, przy napotkaniu na 
   * koniec elementu Obstacle zostaje on umieszczony w kontenerze obstacles.
   */
  Cuboid tmpObstacle;
  /*!
   * \brief Tymczasowy wektor rozmiaru
   *
   * Obiekt uzupełniany w trakcie parsowania pliku XML, przy napotkaniu na 
   * koniec elementu Obstacle zostaje on włączony do obiektu tmpObstacle.
   */
  Wektor3D tmpSize;
  /*!
   * \brief Tymczasowy punkt centralny
   *
   * Obiekt uzupełniany w trakcie parsowania pliku XML, przy napotkaniu na 
   * koniec elementu Obstacle zostaje on włączony do obiektu tmpObstacle.
   */
  Wektor3D tmpCenter;
  /*!
   *  \brief Zawiera wskaźnik do modyfikowanej sceny
   *
   *  Zawiera wskaźnik na obiekt, do którego mają zostać wpisane
   *  informacje z wczytywanego pliku.
   */
   Scene  *_pScn;
};

/*!
 * \brief Funkcja zamieniająca string na double
 *
 * Prosta funkcja podobna do atof, dokonująca ekstrakcji liczby 
 * zmiennoprzecinkowej zawartej w stałej łańcuchowej, do zmiennej typu double.
 * \param[in] sNum - napis przechowujący liczbę.
 * \param[out] rVal - zmienna, do której zostanie zapisana odczytana liczba
 * \retval true - pomyślnie odczytano liczbę.
 * \retval false - wykonanie funkcji nie powiodło się.
 */
bool string2double(const char * sNum, double &rVal);

#endif

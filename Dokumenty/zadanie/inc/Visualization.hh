#ifndef VISUALIZATION_HH
#define VISUALIZATION_HH


#include "DronPose.hh"
#include "Cuboid.hh"

/*!
 * \brief
 */
class Visualization {

  public:
  /*!
   * \brief Destruktor wirtualny, aby zapewnić poprawną destrukcję
   *        obiektu klasy pochodnej
   */
   virtual ~Visualization() {}
  /*!
   * \brief Powoduje odrysowanie aktualnej sceny z uwzglęnieniem bieżącej
   *        pozycji drona
   */
  virtual bool fail() = 0;
  virtual void Draw( const DronPose *pPose ) {}
  /*!
   * \brief Metoda ma czytać opis sceny z pliku XML
   *
   *  Metoda ma czytać opis sceny z pliku XML, który zawiera informację
   *  o rozmieszczeniu przeszkód. Każda z przeszkód reprezentowana jest
   *  poprzez prostopadłościan. Dla ułatwienia przyjmujemy, że 
   *  ścianki prostopadłościanów są albo prostopadle, albo też równoległe
   *  do płaszczyzn OXY, OXZ oraz OYZ.
   *
   *  \param[in] FileName_XML - nazwa pliku w formacie XML, w którym zawarty
   *                            jest opis rozmieszczenia przeszkód na scenie.
   *
   *  \retval true - gdy operacja zakończyła się powodzeniem,
   *  \retval false - w przypadku przeciwnym.
   *
   *  \post  Jeżeli operacja zakończyła się powodzeniem, to zostają usunięte
   *         stare przeszkody, zaś na ich miejsce wstawiane są nowe.
   */
  virtual bool ReadScene(const char* FileName_XML) = 0;
};






#endif

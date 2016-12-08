#ifndef CUBOID_HH
#define CUBOID_HH


#include "Wektor3D.hh"
#include <string>

/*!
 * \file
 * \brief Definicja klasy prostopadłościanu
 *
 * Plik zawiera definicję klasy prostopadłościanu modelującego przeszkodę, 
 * z którą może zderzyć się dron.
 */

/*!
 * \brief Klasa przeszkody - prostopadłościanu
 *
 * Klasa modeluje prostopadłościan, którego ściany są równoległe do osi x,y i 
 * z. Prostopadłościan reprezentowany jest za pomocą wektora długości boków, 
 * oraz punktu wyznaczającego jego geometryczny środek. Obiekt ten stanowi
 * przeszkodę, z którą dron może się zderzyć podczas lotu. 
 */
class Cuboid {
  /*!
   * \brief Środek geometryczny 
   *
   * Punkt w przestrzeni 3D wyznaczający geometryczny środek przeszkody.
   */
  Wektor3D center;
    /*!
   * \brief Długości ścian 
   *
   * Trojelementowy wektor, definiujący rozmiar prostopadłościanu.
   */
  Wektor3D size;
  /*!
   * \brief Nazwa przeszkody
   *
   * Nazwa przeszkody odczytana z pliku XML. Używana jest do wyświetlania
   * nazwy przeszkody, z którą nastąpiła kolizja. 
   */
  std::string name;
public:
  /*!
   * \brief Konstruktor klasy Cuboid
   *
   * Konstruktor klasy inicjalizujący zmienną przechowującą nazwę przeszkody
   * \param[in] n - nazwa przeszkody
   */
  Cuboid(const char* n = ""): name(std::string(n)) {}
  /*!
   * \brief Wykrywa przecięcie z dronem
   *
   * Funkcja przyjmuje jako argument punkt wyznaczający położenie drona w
   * przestrzeni. 
   * \param[in] pos - punkt określający położenie drona na scenie.
   * \pre Wektory center i size muszą być poprawnie zainicjalizowane.
   * \retval true - dron koliduje z przeszkodą.
   * \retval false - dron nie koliduje z przeszkodą.
   */
  bool intersects(const Wektor3D& pos) const;
  /*!
   * \brief Zwraca nazwę przeszkody
   *
   * Funkcja zwraca nazwę przeszkody odczytaną z pliku XML. Dzięki niej 
   * użytkowik może otrzymać informację o tym, z jaką przeszkoda zderzył się 
   * dron.
   * \return Nazwa przeszkody
   */ 
  const std::string& getName() const {return name; } ;
  /*!
   * \brief Udostępnia współrzędne środka prostopadłościanu
   *
   *  Udostępnia przestrzenne współrzędne geometrycznego 
   *  środka prostopadłościanu.
   */
  const Wektor3D &GetCenter() const {return center; }
  /*!
   * \brief Udostępnia długości boków prostopadłościanu
   *
   *  Udostępnia długości boków prostopadłościanu.
   *  Zakłada się, że prostopadłościany są tak ustawione, że 
   *  jego ścianki są równoległe do jednej z powierzchni OXY, OXZ lub OYZ.
   *  Każda współrzędna wektora zawiera długość boku, który jest równoległy
   *  do danej osi. Tak więc np. współrzędna x-owa zawiera długość boku,
   *  który równoległy jest do osi OX.
   */
  const Wektor3D &GetSize() const {return size; }
  /*!
   * \brief Ustawia środek prostopadłościanu
   *
   * Funkcja ustawia punkt zawierający współrzędne środka przeszkody
   * \param[in] c - punkt, który ma zostać środkiem
   * \post Wektor center przyjmuje nową wartość, przekazaną w argumencie
   */
  void SetCenter(const Wektor3D &c) {center = c; }
    /*!
   * \brief Ustawia rozmiar prostopadłościanu
   *
   * Funkcja ustawia wektor zawierający rozmiar przeszkody
   * \param[in] s - wektor, który ma wyznaczać nowy rozmiar
   * \post Wektor size przyjmuje nową wartość, przekazaną w argumencie
   */
  void SetSize(const Wektor3D &s) {size = s; }
};


#endif

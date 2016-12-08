#ifndef SCENE_HH
#define SCENE_HH

#include <vector>
#include "Cuboid.hh"

/*!
 * \file
 * \brief Definicja klasy sceny
 *
 * Plik zawiera definicję klasy sceny, odpowiedzianej za przechowywanie 
 * obiektów przeszkód i badanie kolizji.
 */

/*!
 * \brief Klasa sceny
 * 
 * Klasa przechowuje informacje o obiektach typu Cuboid umieszczonych jako
 * przeszkody na scenie. Potrafi sprawdzić, czy dron koliduje z którąkolwiek
 * z zapisanych przeszkód. 
 */

class Scene{
  /*!
   * \brief Kontener przeszkód
   *
   * Wektor zawierający wszystkie obiekty przeszkód znajdujące się na scenie.
   */
  std::vector<Cuboid> obstacles;
 

public:
  /*!
   * \brief Dodaje przeszkode
   */
  void addObstacle(const Cuboid &obs){
    obstacles.push_back(obs);
  }
  /*!
   * \brief Zwraca zadaną przeszkodę
   *
   * Metoda zwraca przeszkodę o zadanym indeksie. Jest przydatna, gdy klasa
   * wizualizacyjna musi uzyskać informacje o przeszkodzie, by dopisać ją do
   * pliku. 
   * \param[in] index - numer przeszkody
   * \pre index musi być poprawnym indeksem wektora obstacles
   * \return Funckja zwraca stałą referencję do obiektu prostopadłościanu. 
   */
  const Cuboid& getObstacle(int index){ return obstacles[index]; }
  /*!
   * \brief Usuwa wszystkie obiekty
   *
   * Metoda usuwa wszystkie prostopadłościany z kontenera obstacles. Używana
   * przy resetowaniu sceny. 
   * \post Scena staje się pusta.
   */
  void eraseObjects(){ obstacles.clear(); }
  /*!
   * \brief Zwraca liczbę obiektów
   *
   * Metoda zwraca informację o liczbie prostopadłościanów znajdujących się na
   * scenie.
   * \return Zwracana wartośc to liczba przeszkód. 
   */
  int getObstaclesNumber(){ return obstacles.size(); }
  /*!
   * \brief Sprawdza, czy występuje kolizja
   *
   * Metoda sprawdza, czy między dronem o pozycji zadanej jako argument, a 
   * jakąkolwiek przeszkodą znajdująca się w kontenerze obstacles, zachodzi
   * kolizja. 
   * \param[in] pos - aktualna pozycja drona
   * \retval true - zachodzi kolizja
   * \retval false - nie zachodzi kolizja
   */
  bool checkCollision(const Wektor3D& pos);
};




#endif

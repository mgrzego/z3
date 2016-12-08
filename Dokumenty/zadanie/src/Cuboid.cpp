#include "Cuboid.hh"

// Połowa wysokości prostopadłościanu aproksymującego drona
const double DRONE_HEIGHT_HALVED = 10.0;

// Połowa boku kwadratu będącego podstawą prostopadłościanu
const double DRONE_BASE_EDGE_HALVED = 30.0;


bool Cuboid::intersects(const Wektor3D& pos) const{
  // powiększenie rozmiarów przeszkody o rozmiary drona
  double obs_upper = center.z() + size.z() + DRONE_HEIGHT_HALVED;
  double obs_lower = center.z() - size.z() - DRONE_HEIGHT_HALVED;
  // sprawdzenie, czy dron reprezentowany jako punkt koliduje z powiększonymi
  // przeszkodami
  if(pos.z() < obs_lower || pos.z() > obs_upper)
    return false;

  // wykonanie powyższych czynności dla osi y
  obs_upper = center.y() + size.y() + DRONE_BASE_EDGE_HALVED;
  obs_lower = center.y() - size.y() - DRONE_BASE_EDGE_HALVED;
  if(pos.y() < obs_lower || pos.y() > obs_upper)
    return false;

  // wykonanie powyższych czynności dla osi z
  obs_upper = center.x() + size.x() + DRONE_BASE_EDGE_HALVED;
  obs_lower = center.x() - size.x() - DRONE_BASE_EDGE_HALVED;
  if(pos.x() < obs_lower || pos.x() > obs_upper)
    return false;

  // jeśli we wszystkich osiach doszło do kolizji, to znaczy że dron koliduje
  // z przeszkodą
  return true;
}

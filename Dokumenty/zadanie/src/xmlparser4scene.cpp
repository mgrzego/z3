#include <xercesc/util/PlatformUtils.hpp>
#include "xmlparser4scene.hh"
#include <cassert>
#include <cstdlib>
#include <iostream>


// stałe definiujące nazwy, jakie moga pojawić się w parsowanym dokumencie
#define OBSTACLE "Obstacle"
#define PARAMETER "Parameter"
#define NAME "Name"
#define VALUE "Value"


using namespace std;


/*!
 * Konstruktor klasy. Tutaj należy zainicjalizować wszystkie
 * dodatkowe pola.
 */
XMLParser4Scene::XMLParser4Scene(Scene &Scn)
{
  _pScn = &Scn;
  clearFlags();
}


/*!
 * Metoda jest wywoływana po napotkaniu nowego elementu XML, np.
 * gdy zostanie napotkany element:
   \verbatim
     <Action Name="Rotate">
   \endverbatim
 *  to poprzez parametr \e xscElemName jest dostęp do nazwy elementu
 *  tzn. \p Action, 
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 *  \param[in] Attrs -  lista atrybutów danego symbolu XML.
 *                 W przykładzie pokazanym powyżej listę atrybutów
 *                 będą stanowiły napisy:
 */
void XMLParser4Scene::startElement(  const   XMLCh* const    pURI,
                                       const   XMLCh* const    pLocalName,
                                       const   XMLCh* const    pQNname,
				       const   xercesc::Attributes&     Attrs
                                    )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  if(strcmp(sElemName,OBSTACLE) == 0){
    if(Attrs.getLength() != 1){
      cerr << "Blad przy parsowaniu Obstacle - zla liczba atrubotow\n";
      return;
    }
    char* paramName = xercesc::XMLString::transcode(Attrs.getQName(0));
    if(strcmp(paramName,NAME)){
      cerr << "Blad przy parsowaniu Obstacle - nieprawidlowy atrybut\n";
      return;
    }
    char* value = xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(0)));
    tmpObstacle = Cuboid(value);
    xercesc::XMLString::release(&paramName);
    xercesc::XMLString::release(&value);
  }
  else if(strcmp(sElemName,PARAMETER) == 0)
    processParameterAttrs(Attrs);
  xercesc::XMLString::release(&sElemName);
  return;
}

void XMLParser4Scene::processParameterAttrs(const xercesc::Attributes &Attrs){
  if(Attrs.getLength() != 2){
    cerr << "Blad przy parsowaniu Parameter - zla liczba atrybotow\n";
    return;
  }
  // sprawdzenie czy nazwy atrybutow sa poprawne
  char* name = xercesc::XMLString::transcode(Attrs.getQName(0));
  char* value = xercesc::XMLString::transcode(Attrs.getQName(1));
  if(strcmp(name,NAME) || strcmp(value,VALUE))
    return;
  
  xercesc::XMLString::release(&value);
  xercesc::XMLString::release(&name);
  value = xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(1)));
  double val;
  if(string2double(value,val) == false){
    cerr << "Blad przy parsowaniu Parameter - wartosc nie jest liczba\n";
    return;
  }
  xercesc::XMLString::release(&value);

  name = xercesc::XMLString::transcode(Attrs.getValue(static_cast<XMLSize_t>(0)));
  if(strcmp(name,"Center_x") == 0){
    tmpCenter.x() = val;
    flags[0] = true;
  }
  else if(strcmp(name,"Center_y") == 0){
    tmpCenter.y() = val;
    flags[1] = true;
  }
  else if(strcmp(name,"Center_z") == 0){
    tmpCenter.z() = val;
    flags[2] = true;
  }
  else if(strcmp(name,"Size_x") == 0){
    tmpSize.x() = val;
    flags[3] = true;
  }
  else if(strcmp(name,"Size_y") == 0){
    tmpSize.y() = val;
    flags[4] = true;
  }
  else if(strcmp(name,"Size_z") == 0){
    tmpSize.z() = val;
    flags[5] = true;
  }
  else
    cerr <<  "Blad przy parsowaniu Parameter - zla wartosc Name\n";
  xercesc::XMLString::release(&name);
}


/*!
 * Metoda zostaje wywołana w momencie zakończenia danego elementu
 * XML, np. jeżeli w pliku jest wpis:
   \verbatim
     <Action Name="Rotate">
     </Action>
   \endverbatim
 * to metoda ta zostanie wywołana po napotkaniu znacznika
 * \p </Action>. Jeżeli element XML ma formę skróconą, tzn.
   \verbatim
     <Parametr Name="Rotate"/>
   \endverbatim
 * to wówczas wywołana metoda wywołana zostanie w momencie
 * napotkania sekwencji "/>"
 *  \param[in] pLocalName -  umożliwia dostęp do nazwy elementu XML.
 *                 W podanym przykładzie nazwą elementu XML jest "Action".
 */
void XMLParser4Scene::endElement(  const   XMLCh* const    pURI,
                                     const   XMLCh* const    pLocalName,
                                     const   XMLCh* const    pQName
                                  )
{
  char* sElemName = xercesc::XMLString::transcode(pLocalName);
  if(strcmp(sElemName,OBSTACLE) == 0){
    // jeśli wszystkie parametry przeszkody wczytane poprawnie - wyślij ją
    // do sceny
    if(isObstacleComplete()){
      tmpObstacle.SetCenter(tmpCenter);
      tmpObstacle.SetSize(tmpSize);
      _pScn->addObstacle(tmpObstacle);
    }
    // wyczyść flagi wczytanych parametrów przeszkody
    clearFlags();
  }
  xercesc::XMLString::release(&sElemName);
}



/*!
 * Metoda wywoływana jest, gdy napotkany zostanie błąd fatalny,
 * np.
  \verbatim
    <Action Name="Rotate">
    </Parametr>
  \endverbatim
 */
void XMLParser4Scene::fatalError(const xercesc::SAXParseException&  Exception)
{
   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Blad fatalny! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

/*!
 * Metoda jest wywoływana, gdy napotkany zostanie błąd, który nie
 * jest traktowany jako fatalny. W ten sposób traktowane są błędy
 * występujące w opisie gramatyki dokumentu.
 * \param[in] Except - zawiera informacje dotyczące błędu. Informacje
 *                     te to opis błędu oraz numer linii, w której
 *                     wystąpił błąd.
 */
void XMLParser4Scene::error(const xercesc::SAXParseException&  Exception)
{
   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Blad! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}


/*!
 *
 */
void XMLParser4Scene::warning(const xercesc::SAXParseException&  Exception)  
{
   char* sMessage = xercesc::XMLString::transcode(Exception.getMessage());
   char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

   cerr << "Ostrzezenie! " << endl
        << "    Plik:  " << sSystemId << endl
        << "   Linia: " << Exception.getLineNumber() << endl
        << " Kolumna: " << Exception.getColumnNumber() << endl
        << " Informacja: " << sMessage 
        << endl;

   xercesc::XMLString::release(&sMessage);
   xercesc::XMLString::release(&sSystemId);
}

void XMLParser4Scene::clearFlags(){
  for(int i=0; i<6; i++)
    flags[i] = false;
}

bool XMLParser4Scene::isObstacleComplete(){
  for(int i=0; i<6; i++){
    if(flags[i] == false)
      return false;
  }
  return true;
}

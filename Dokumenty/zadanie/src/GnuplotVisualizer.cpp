#include "GnuplotVisualizer.hh"
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include "Wektor3D.hh"
#include "xmlparser4scene.hh"

#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace std;
using namespace xercesc;


const string FILE_NAME_OBSTACLE_TEMPLATE = "przeszkoda";

/*!
 * Konstruktor inicjalizuje pracę z programem gnuplot.
 * Na potrzeby tej inicjalizacji wykonane są następujące operacje:
 * 
 * \li Kasowanie zawartości plików, których nazwy zdefiniowane są poprzez stałe
 *   \link GnuplotVisualizer.hh::FILE_NAME__TRAJECTORY FILE_NAME__TRAJECTORY\endlink
 *   oraz 
 *   \link GnuplotVisualizer.hh::FILE_NAME__DRON_BODY_VIEW FILE_NAME__DRON_BODY_VIEW\endlink.
 *   W pierwszym z plików zapisywane są współrzędne wierzchołków łamanej modelującej
 *   ścieżkę przelotu drona. W drugim natomiast są zapisywane współrzędne aktualnego
 *   widoku bryły reprezentującej korpus drona.
 *
 * \li Inicjacja pracy programu gnuplot.
 *
 * \li Dodanie nazw plików, z których będą czytane dane przy każdorazowym odrysowaniu
 *     rysunku.
 *
 * \li Ustawienie trybu rysowania jako rysowanie przestrzenne 3D.
 *
 * \li Wstępne ustawienie zakresu współrzędnych rysowanej sceny.
 *     Te zakresy należy dostosować do potrzeb własnego programu.
 *
 * \li Wstępne ustawienie kierunku, z którego widziana jest scena.
 *     W trakcie pracy aplikacji kierunek ten można modyfikować
 *     wykorzystując kursor myszki.
 */
GnuplotVisualizer::GnuplotVisualizer(): isValid(true)
{
  ofstream  Strm;
  Strm.open(FILE_NAME__TRAJECTORY);      Strm.close();  // Kasujemy poprzednia
  Strm.open(FILE_NAME__DRON_BODY_VIEW);  Strm.close();  // zawartość

  Plotter.Inicjalizuj(); 

  AddDronFileNames4Gnuplot();

  Plotter.ZmienTrybRys(PzG::TR_3D);
  Plotter.UstawZakresX(-100, 250);
  Plotter.UstawZakresY(-100, 250);
  Plotter.UstawZakresZ(-100, 200);
  //
  // Lepiej nie wymuszać ustawienia widoku. To pozwoli zmieniać widok za pomocą
  // myszki w trakcie wykonywania rysowania.
  //
  //  Plotter.UstawRotacjeXZ(40,60); 
}


/*
 * Moduł LaczeDoGnuplota posiada listę plików, z których gnuplot będzie brał
 * dane od rysowania brył.
 * Niniejsza metoda dodaje do tej listy nazwy plików, w których będzie obrysł
 * brył reprezentujących poszczególne elementy drona.
 *
 * Metodę tę można rozbudować wg własnych potrzeb.
 */
void GnuplotVisualizer::AddDronFileNames4Gnuplot()
{
    // Parametr 1 na końcu odpowiada rysowaniu kolorem czerwonym
  Plotter.DodajNazwePliku(FILE_NAME__TRAJECTORY,PzG::RR_Ciagly,2,1);

    // Parametr 1 na końcu odpowiada rysowaniu kolorem czarnym
  Plotter.DodajNazwePliku(FILE_NAME__DRON_BODY_VIEW,PzG::RR_Ciagly,1,7);
}


/*!
 * \brief Dodaje punkt do ścieżki ruchu
 *
 * Dodaje do pliku, którego nazwa jest zdefinowana
 * przez stałą 
 * \link Visualization.hh::FILE_NAME__DRON_BODY_VIEW
 *                                     FILE_NAME__DRON_BODY_VIEW\endlink,
 * współrzędne następnego punktu ścieżki ruchu drona.
 * \param[in] pPose - pozycja drona zawierająca dodawany punkt
 * \retval true - działanie funkcji przebiegło pomyślnie
 * \retval false - funkcja zakończyła się niepowodzeniem
 */
bool AddTrajectoryPoint( const DronPose *pPose )
{
  ofstream  OuStrm(FILE_NAME__TRAJECTORY,ios::app); // Plik otwarty w trybie dopisywania
  if (!OuStrm.is_open()) {
    cerr << " Blad otwarcia do zapisu pliku \"" FILE_NAME__TRAJECTORY "\""
	 << endl;
    return false;
  }
  OuStrm << pPose->GetPos_m() << endl;
  return true;
}


/*!
 * \brief Rotacja i skalowanie współrzędnych punktu
 *
 * Dokonuje rotacji i skalowania współrzędnych zadanego punktu.
 * \param[in] sn - sinus kąta rotacji,
 * \param[in] cn - cosinus kąta rotacji,
 * \param[in] rPnt   - współrzędne punktu, które mają być podane rotacji i skalowaniu,
 * \param[in] rScale - współczynniki skali wzdłuż każdej z osi.
 * \return Zwaraca przetransformowane współrzędne punktu.
 */
Wektor3D RotateXY( double sn, double cn, const Wektor3D & rPnt,
		   const Wektor3D & rScale = Wektor3D(1.0, 1.0, 1.0) )
{
  return Wektor3D( rScale.x()*(rPnt.x()*cn - rPnt.y()*sn), 
                   rScale.y()*(rPnt.x()*sn + rPnt.y()*cn), 
                   rScale.z()*rPnt.z()
                  );
}

/*
 * Czyta plik, który zawiera współrzędne bryły wzorocej. Przeczytane współrzędne
 * wierzchołków są transformowane, tzn. podane są:
 *   \li rotacji,
 *   \li skalowaniu,
 *   \li translacji.
 * Następnie zapisywane są do pliku, który będzie czytał gnuplot. Ważne jest,
 * że funkcja ta zachowuje budowę pliku wzorcowego, tzn. w odpowiednim miejscu
 * znajdzie się wolna linia między poszczególnymi zestawami współrzędnych
 * wierzchołków.
 *  
 * \param[in] sFile_Template - nazwa pliku zawierającego współrzędne wierzchołków bryły
 *                             wzorcowej. Z tego pliku wspomniane współrzędne są czytane.
 * \param[in] sFile_Target - nazwa pliku, do którego zostaną zapisane przetransformowane
 *                           współrzędne.
 * \param[in] rTrans_m     - wektor translacji, którego współrzędne wyrażone są w metrach.
 * \param[in] RotAngle_rad - kąt rotacji wyrażony w radianach.
 *
 * \retval true - gdy operacja otwarcia i zapisu odpowiednich plików zakończyła się
 *                powodzeniem,
 * \retval false - w przypadku przeciwnym.
 */
bool TransformGeom(
		   const char      *sFile_Template,
		   const char      *sFile_Target,
                   const Wektor3D  &rTrans_m,
                   double            RotAngle_rad,
                   const Wektor3D  &rScale
    	          )
{
  ofstream  OuStrm(sFile_Target);
  ifstream  InStrm(sFile_Template);
  Wektor3D  Pos;

  if (!OuStrm.is_open()) {
    cerr << " Blad otwarcia do zapisu pliku \"" << sFile_Target << "\""
	 << endl;
    return false;
  }
  if (!InStrm.is_open()) {
    cerr << " Blad otwarcia do odczytu pliku \"" << sFile_Template << "\""
	 << endl;
    return false;
  }

  char      Separator;
  double    sn = sin(RotAngle_rad),  cn = cos(RotAngle_rad);
 
  while (!InStrm.eof()) {
    if (InStrm >> Pos) {
        // Najpierw dokonujemy rotacji
      Pos = RotateXY(sn,cn,Pos,rScale);
        // Następnie translacja
      Pos += rTrans_m;
      OuStrm << Pos << endl;
      continue;
    }
    InStrm.clear();
    if (!(InStrm >> Separator)) break;
    if (Separator != '#') {
      cerr << " Blad w pliku \"" << sFile_Target <<  "\"" << endl
           << " oczekiwano znaku #. Zamiast tego odebrano znak " << Separator
	   << endl;
      return false;
    }
    OuStrm << "#\n\n";
  }
  return true;
}



/*!
 * Zapisanie pliku z zaktualnymi współrzędnymi wierzchołków bryły
 * opisującej drona.
 * Ze względu na specyfikę sposobu rysowania powierzchni przez program gnuplot,
 * format wejściowy i wyjściowy pliku musi zostać zachowany, tzn. muszą być
 * zachwane przerwy w postaci wolnych linii między kolejnymi zbiorami wierzchołków,
 * które stanowią tworzącą rysowanej siatki danej powierzchni.
 * Ta funkcja to zapewnia.
 * \param[in] pPose - wskaźnik na obiekt zawierający dane dotyczące aktualnej pozy
 *                    drona.
 *
 * \warning W tej funkcji brakuje uwzględnienia rotacji, która pozwoli odzwierciedlić
 *          aktualną orientację drona. W kodzie funkcji jest zaznaczone miejsce,
 *          w którym należy wpisać odpowiedni kod.
 *
 */
bool WriteCurrDonPose( const DronPose *pPose )
{
  double DronAngle_rad = pPose->GetAngle_deg() * M_PI / 180;
  Wektor3D      DronScale(20,20,10);


  if (!TransformGeom(FILE_NAME__DRON_BODY_TEMPLATE,FILE_NAME__DRON_BODY_VIEW,
                     pPose->GetPos_m(), DronAngle_rad, DronScale)) return false;
 
  return true;
}



/*!
 * Powoduje dopisanie aktualnej współrzędnej drona do pliku,
 * w którym zawarta jest sekwencja wcześniejszych położeń.
 * W ten sposób otrzymana łamana reprentuje trajektorię ścieżkę
 * lotu drona.
 * Ponadto na podstawie pliku wzorcowego opisującego korpus drona,
 * utworzony zostaje plik ze współrzędnymi wierzchołków w jego
 * nowej pozycji. Po tej pozycji następuje odrysowanie drona
 * w jego aktulanej pozycji.
 *
 * \param[in] pPose - wskaźnik na obiekt zawierający dane dotyczące aktualnej pozy
 *                    drona.
 */
void GnuplotVisualizer::Draw( const DronPose *pPose )
{
  AddTrajectoryPoint(pPose);
  WriteCurrDonPose(pPose);
  Plotter.Rysuj();
  if(scene.checkCollision(pPose->GetPos_m()))
    isValid = false;
}



/*!
 *  Metoda ma czytać opis sceny z pliku XML, który zawiera informację
 *  o rozmieszczeniu przeszkód. Każda z przeszkód reprezentowana jest
 *  poprzez prostopadłościan. Dla ułatwienia przyjmujemy, że 
 *  ścianki prostopadłościanów są albo prostopadle, albo też równoległe
 *  do płaszczyzn OXY, OXZ oraz OYZ.
 *
 *
 *  W tej chwili metoda ta jedynie symuluje czytanie z pliku.
 *  Wstawia przeszkody na sztywno.
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
bool GnuplotVisualizer::ReadScene(const char* FileName_XML)
{
   // 1. Powinniśmy sprawdzić, czy można otworzyć plik o podanej nazwie,
   //    jeśli nie, to kończymy działanie.
  fstream filestr;
  filestr.open (FileName_XML);
  if (filestr.is_open())  // wszystko w porządku, plik się otwiera
    filestr.close();
  else{   
    cerr << "Błąd otwarcia pliku ze sceną\n";
    return false;
  }
   // 2. Usuwamy dotychczasowe obiekty
  scene.eraseObjects(); 

   // 3. Następnie usuwamy wszystkie nazwy plików związne ze starymi
   //    obiektami.
  Plotter.UsunWszystkieNazwyPlikow();

   // 4. Pozostawiamy nazwy plików, które wiążą się z elementami konstrukcji
   //    drona
  AddDronFileNames4Gnuplot();

   // 5. Tu powinniśmy rozpocząć czytanie plików i dodać przeszkody. 
   //    Tworzymi pliki z obrysem prostopadłościanów modelujących przeszkody
   //    i przekazujemy ich nazwy do modułu lacze_do_gnuplota.
  if(readFile(FileName_XML) == false)
    return false;

  int number =  scene.getObstaclesNumber();
  for(int i=0; i<number; ++i){
    const Cuboid tmp = scene.getObstacle(i);
    string targetFileName = FILE_NAME_OBSTACLE_TEMPLATE + to_string(i) +".dat";
    if(!TransformGeom(FILE_NAME__DRON_BODY_TEMPLATE, targetFileName.c_str(),
		      tmp.GetCenter(), 0, tmp.GetSize()))  return false;
    Plotter.DodajNazwePliku(targetFileName.c_str(),PzG::RR_Ciagly,1,12);
  }
  return true;
}


bool GnuplotVisualizer::readFile(const char* fileName){
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    char* message = XMLString::transcode(toCatch.getMessage());
    cerr << "Error during initialization! :\n";
    cerr << "Exception message is: \n"
	 << message << "\n";
    XMLString::release(&message);
    return false;
  }

  SAX2XMLReader* pParser = XMLReaderFactory::createXMLReader();

  pParser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  pParser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  pParser->setFeature(XMLUni::fgXercesDynamic, false);
  pParser->setFeature(XMLUni::fgXercesSchema, true);
  pParser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
  pParser->setFeature(XMLUni::fgXercesValidationErrorAsFatal, true);

  DefaultHandler* pHandler = new XMLParser4Scene(scene);
  pParser->setContentHandler(pHandler);
  pParser->setErrorHandler(pHandler);

  try {    
    if (!pParser->loadGrammar("grammar/scene.xsd",
                              xercesc::Grammar::SchemaGrammarType,true)) {
      cerr << "!!! Plik grammar/scene.xsd, '" << endl
	   << "!!! ktory zawiera opis gramatyki, nie moze zostac wczytany."
	   << endl;
      return false;
    }
    pParser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true);
    pParser->parse(fileName);
  }
  catch (const XMLException& Exception) {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    cerr << "Informacja o wyjatku: \n"
	 << "   " << sMessage << "\n";
    XMLString::release(&sMessage);
    return false;
  }
  catch (const SAXParseException& Exception) {
    char* sMessage = XMLString::transcode(Exception.getMessage());
    char* sSystemId = xercesc::XMLString::transcode(Exception.getSystemId());

    cerr << "Blad! " << endl
	 << "    Plik:  " << sSystemId << endl
	 << "   Linia: " << Exception.getLineNumber() << endl
	 << " Kolumna: " << Exception.getColumnNumber() << endl
	 << " Informacja: " << sMessage 
	 << endl;

    XMLString::release(&sMessage);
    XMLString::release(&sSystemId);
    return false;
  }
  catch (...) {
    cout << "Zgloszony zostal nieoczekiwany wyjatek!\n" ;
    return false;
  }
  delete pParser;
  return true;
}

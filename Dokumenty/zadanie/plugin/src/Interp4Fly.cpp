#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include "Interp4Fly.hh"
#include "Visualization.hh"

using namespace std;


extern "C" {
 Interp4Command* CreateCmd(void);
}


Interp4Command* CreateCmd(void)
{
  return Interp4Fly::CreateCmd();
}


Interp4Fly::Interp4Fly(): horizontalSpeed(0), verticalSpeed(0), distance(0)
{}


void Interp4Fly::PrintCmd() const
{
  cout << GetCmdName() << " " << horizontalSpeed << " " << verticalSpeed <<
    " " << distance << endl;
}


const char* Interp4Fly::GetCmdName() const
{
  return "Fly";
}


bool Interp4Fly::ExecCmd( DronPose *pRobPose, Visualization *pVis) const
{
  Wektor3D originalPos = pRobPose->GetPos_m();
  double time;
  if(verticalSpeed == 0.0){
    if(horizontalSpeed == 0.0) // brak jakiegokolwiek ruchu
      return true;
    time = abs(distance / horizontalSpeed);
  }
  else{
    // kąt wznoszenia/opadania w rad
    double angle1 = atan(verticalSpeed / horizontalSpeed);
    time = abs((distance * sin(angle1)) / verticalSpeed);
  }
  // kąt obrotu robota w radianach
  double angle2 = (M_PI / 180.0) * (pRobPose->GetAngle_deg() + 90.0);
  // animacja lotu
  for(double t = 0.0; t < time; t += TIME_PRECISION){
    Wektor3D pos = originalPos;
    pos.x() += horizontalSpeed * t * cos(angle2);
    pos.y() += horizontalSpeed * t * sin(angle2);
    pos.z() += verticalSpeed * t;
    pRobPose->SetPos_m(pos);
    pVis->Draw(pRobPose);
    if(pVis->fail())
      return true;
    usleep(TIME_PRECISION * 1000000.0);
  }
  // finalna pozycja drona
  originalPos.x() += horizontalSpeed * time * cos(angle2);
  originalPos.y() += horizontalSpeed * time * sin(angle2);
  originalPos.z() += verticalSpeed * time;
  pRobPose->SetPos_m(originalPos);
  pVis->Draw(pRobPose);
  usleep(TIME_PRECISION * 1000000.0);
  return true;
}


bool Interp4Fly::ReadParams(std::istream& Strm_CmdsList)
{
  std::string errorBuffer;
  bool correctFlag = true;
  double tmp[3]; //tablica, do której w pętli wczytywane są wartości
  std::string valType[3] = {"predkosci poziomej", "predkosci pionowej",
			    "dlugosci drogi"};
  for(int i = 0; i<3; ++i){
    Strm_CmdsList >> tmp[i];
    if(Strm_CmdsList.fail()){
      std::cerr << GetCmdName() << ": Nieprawidlowa wartosc " << valType[i]
		<< "!\n";
      tmp[i] = 0.0;
      Strm_CmdsList.clear();
      Strm_CmdsList >> errorBuffer;
      correctFlag = false;
    }
  }
  horizontalSpeed = tmp[0];
  verticalSpeed = tmp[1];
  distance = tmp[2];
  return correctFlag;
}


Interp4Command* Interp4Fly::CreateCmd()
{
  return new Interp4Fly();
}


void Interp4Fly::PrintSyntax() const
{
  cout << "   Fly    hor_speed[m/s]  ver_speed[m/s]  dist[m]" << endl;
}

#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include "Interp4Turn.hh"
#include "Visualization.hh"

using namespace std;

extern "C" {
 Interp4Command* CreateCmd(void);
}


Interp4Command* CreateCmd(void)
{
  return Interp4Turn::CreateCmd();
}


Interp4Turn::Interp4Turn(): speed(0), distance(0), radius(0)
{}


void Interp4Turn::PrintCmd() const
{
  cout << GetCmdName() << " " << speed << " " << distance << " "
       << radius << endl;
}


const char* Interp4Turn::GetCmdName() const
{
  return "Turn";
}


bool Interp4Turn::ExecCmd( DronPose *pRobPose, Visualization *pVis) const
{
  if(radius == 0.0){
    std::cerr << "Blad! Zerowa wartosc promienia krzywizny!\n";
    return false;
  }
  double time = abs(distance / speed);
  Wektor3D pos = pRobPose->GetPos_m();
  double dAng = (M_PI / 180.0) * pRobPose->GetAngle_deg();

  // animacja ruchu
  for(double t = 0.0; t<time; t += TIME_PRECISION){
    double angle = t * speed / radius;
    double dy = radius * sin(angle);
    double dx = radius * cos(angle) - radius;
    Wektor3D tmpPos = pos;
    tmpPos.x() += (dx * cos(dAng) - dy * sin(dAng));
    tmpPos.y() += (dx * sin(dAng) + dy * cos(dAng));
    pRobPose->SetAngle_deg((dAng + angle) * (180.0 / M_PI));
    pRobPose->SetPos_m(tmpPos);
    pVis->Draw(pRobPose);
    if(pVis->fail())
      return true;
    usleep(TIME_PRECISION * 1000000.0);
  }
  // ostateczne położenie drona
  double finalAngle = distance / radius;
  double dy = radius * sin(finalAngle);
  double dx = radius * cos(finalAngle) - radius;
  pos.x() += (dx * cos(dAng) - dy * sin(dAng));
  pos.y() += (dx * sin(dAng) + dy * cos(dAng));
  pRobPose->SetAngle_deg((dAng + finalAngle) * (180.0 / M_PI));
  pRobPose->SetPos_m(pos);
  pVis->Draw(pRobPose);
  usleep(TIME_PRECISION * 1000000.0);
  return true;
}


bool Interp4Turn::ReadParams(std::istream& Strm_CmdsList)
{
  std::string errorBuffer;
  bool correctFlag = true;
  double tmp[3]; //tablica, do której w pętli wczytywane są wartości
  std::string valType[3] = {"predkosci", "drogi", "promienia krzywizny"};
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
  speed = tmp[0];
  distance = tmp[1];
  radius = tmp[2];
  return correctFlag;
}


Interp4Command* Interp4Turn::CreateCmd()
{
  return new Interp4Turn();
}


void Interp4Turn::PrintSyntax() const
{
  cout << "   Turn   speed[mm/s]     dist[mm]        radius[mm]" << endl;
}

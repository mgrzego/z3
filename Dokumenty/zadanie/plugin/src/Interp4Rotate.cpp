#include <iostream>
#include <cmath>
#include <string>
#include <unistd.h>
#include "Interp4Rotate.hh"
#include "Visualization.hh"

using namespace std;

extern "C" {
 Interp4Command* CreateCmd(void);
}


Interp4Command* CreateCmd(void)
{
  return Interp4Rotate::CreateCmd();
}


Interp4Rotate::Interp4Rotate(): speed(0), angle(0)
{}


void Interp4Rotate::PrintCmd() const
{
  cout << GetCmdName() << " " << speed << " " << angle << endl;
}


const char* Interp4Rotate::GetCmdName() const
{
  return "Rotate";
}


bool Interp4Rotate::ExecCmd( DronPose *pRobPose, Visualization *pVis) const
{
  // czas trwania rotacji w sekundach
  double time = abs(angle / speed);
  double dAng = pRobPose->GetAngle_deg();
  // animacja rotacji
  for(double t = 0.0; t < time; t += TIME_PRECISION){
    pRobPose->SetAngle_deg(dAng + t * speed);
    pVis->Draw(pRobPose);
    usleep(TIME_PRECISION * 1000000.0);
  }
  // ostatecznie położenie drona
  pRobPose->SetAngle_deg(dAng + time * speed);
  pVis->Draw(pRobPose);
  usleep(TIME_PRECISION * 1000000.0);
  return true;
}


bool Interp4Rotate::ReadParams(std::istream& Strm_CmdsList)
{
  std::string errorBuffer;
  bool correctFlag = true;
  double tmp[2]; //tablica, do której w pętli wczytywane są wartości
  std::string valType[2] = {"predkosci katowej", "kata obrotu"};
  for(int i = 0; i<2; ++i){
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
  angle = tmp[1];
  return correctFlag;
}


Interp4Command* Interp4Rotate::CreateCmd()
{
  return new Interp4Rotate();
}


void Interp4Rotate::PrintSyntax() const
{
  cout << "   Rotate speed[deg/s]    angle[deg]" << endl;
}

#include <iostream>
#include <string>
#include <unistd.h>
#include "Interp4Pause.hh"
#include "Visualization.hh"

using namespace std;


extern "C" {
 Interp4Command* CreateCmd(void);
}


Interp4Command* CreateCmd(void)
{
  return Interp4Pause::CreateCmd();
}


Interp4Pause::Interp4Pause(): time_ms(0) {}


void Interp4Pause::PrintCmd() const
{
  cout << GetCmdName() << " " << time_ms << endl;
}


const char* Interp4Pause::GetCmdName() const
{
  return "Pause";
}


bool Interp4Pause::ExecCmd( DronPose *pRobPose, Visualization *pVis) const
{
  usleep(time_ms * 1000.0);
  return true;
}


bool Interp4Pause::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> time_ms;
  return !Strm_CmdsList.fail();
}


Interp4Command* Interp4Pause::CreateCmd()
{
  return new Interp4Pause();
}


void Interp4Pause::PrintSyntax() const
{
  cout << "   Pause    time[ms]" << endl;
}

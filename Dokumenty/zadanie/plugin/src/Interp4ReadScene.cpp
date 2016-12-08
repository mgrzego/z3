#include <iostream>
#include "Interp4ReadScene.hh"
#include "Visualization.hh"

using namespace std;


extern "C" {
 Interp4Command* CreateCmd(void);
}


Interp4Command* CreateCmd(void)
{
  return Interp4ReadScene::CreateCmd();
}


Interp4ReadScene::Interp4ReadScene() {}


void Interp4ReadScene::PrintCmd() const
{
  cout << GetCmdName() << " " << fileName  << endl;
}


const char* Interp4ReadScene::GetCmdName() const
{
  return "ReadScene";
}


bool Interp4ReadScene::ExecCmd( DronPose *pRobPose, Visualization *pVis) const
{
  return pVis->ReadScene(fileName.c_str());
}


bool Interp4ReadScene::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> fileName;
  return true;
}


Interp4Command* Interp4ReadScene::CreateCmd()
{
  return new Interp4ReadScene();
}


void Interp4ReadScene::PrintSyntax() const
{
  cout << "   ReadScene   file_name.xml" << endl;
}

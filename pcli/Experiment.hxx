/*******************************************************************************
** Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
**
** This library is free software; you can redistribute it and/or modify it under
** the terms of the GNU Lesser General Public License as published by the Free
** Software Foundation; either version 2.1 of the License, or (at your option)
** any later version.
**
** This library is distributed in the hope that it will be useful, but WITHOUT
** ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
** FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
** details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this library; if not, write to the Free Software Foundation, Inc.,
** 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*******************************************************************************/

// ApplicationGroupObject
class ApplicationGroupObject
{
 private:
  bool remote;
  CommandWindowID *RemoteFW;
  EXPID RemoteExp;
  std::string App_Name;
  Experiment   *App;

 public:
  ApplicationGroupObject ()
    { remote = false;
      RemoteFW = NULL;
      RemoteExp = 0;
      App = NULL;
    }
  ApplicationGroupObject (std::string name, Experiment  *Local_App)
    { *this = ApplicationGroupObject ();
      App_Name = name;
      App = Local_App;
    }
  ApplicationGroupObject (CommandWindowID *Rfw, EXPID Rexp)
    { *this = ApplicationGroupObject ();
      remote = true;
      RemoteFW = Rfw;
      RemoteExp = Rexp;
    }
  bool Application_Is_Remote() {return remote;}
  Experiment   *Application_App() {return App;}
  void Print(FILE *TFile) {
      fprintf(TFile," %s",App_Name.c_str());
    }
};

// ExperimentObject
// Note: ALL the instrumentation in the experiment's list is applied
//       to ALL of the executables in the experiment's list.
class ExperimentObject;
extern EXPID Experiment_Sequence_Number;
extern std::list<ExperimentObject *> ExperimentObject_list;

class ExperimentObject
{
 private:
  EXPID Exp_ID;
  bool Data_File_Has_A_Generated_Name;
  OpenSpeedShop::Framework::Experiment *FW_Experiment;

  std::list<ApplicationGroupObject *> ApplicationObjectList;
  std::list<Collector *> CollectorList;

 public:
  ExperimentObject (std::string data_base_name = std::string("")) {
    Exp_ID = ++Experiment_Sequence_Number;

   // Allocate a data base file for the information connected with the experiment.
    std::string Data_File_Name;
    if (data_base_name.length() == 0) {
      char base[20];
      snprintf(base, 20, "ssdb%lld.XXXXXX",Exp_ID);
      Data_File_Name = std::string(tempnam ("./", &base[0] ) ) + ".openss";
      Data_File_Has_A_Generated_Name = true;
      OpenSpeedShop::Framework::Experiment::create (Data_File_Name);
    } else {
      Data_File_Name = data_base_name;
      Data_File_Has_A_Generated_Name = false;
    }

   // Create and open an experiment
    try {
      FW_Experiment = new OpenSpeedShop::Framework::Experiment (Data_File_Name);
      ExperimentObject_list.push_front(this);
    }
    catch(const std::exception& error) {
      Exp_ID = 0;
      Data_File_Has_A_Generated_Name = false;
      FW_Experiment = NULL;
    }

  }
  ~ExperimentObject () {
    ExperimentObject_list.remove (this);
    if (Data_File_Has_A_Generated_Name) {
      int err = remove (FW_Experiment->getName().c_str());
      Data_File_Has_A_Generated_Name = false;
    }
    if (FW_Experiment != NULL) {
      delete FW_Experiment;
      FW_Experiment = NULL;
    }
    Exp_ID = 0;
  }
  void ExperimentObject_Merge_Application(std::list<ApplicationGroupObject *> App_List)
    {
      ApplicationObjectList.merge(App_List);
    }
  void ExperimentObject_Merge_Instrumentation(std::list<Collector *> Collector_List)
    {
      CollectorList.merge(Collector_List);
    }
  void ExperimentObject_Add_Application(ApplicationGroupObject *App)
    {
      ApplicationObjectList.push_front(App);
    }
  void ExperimentObject_Add_Instrumention(Collector *Inst)
    {
      CollectorList.push_front(Inst);
    }
  EXPID ExperimentObject_ID() {return Exp_ID;}
  Experiment *FW() {return FW_Experiment;}
  void Print(FILE *TFile)
    { fprintf(TFile,"Experiment %lld data->%s:\n",ExperimentObject_ID(),
              FW_Experiment->getName().c_str());
      std::list<ApplicationGroupObject *>::iterator AppObji = ApplicationObjectList.begin();
      if (AppObji != ApplicationObjectList.end()) {
        fprintf(TFile,"  ");
        for (AppObji = ApplicationObjectList.begin(); AppObji != ApplicationObjectList.end(); AppObji++) {
          (*AppObji)->Print(TFile);
        }
        fprintf(TFile,"\n");
      }
      std::list<Collector *>::iterator  Ci = CollectorList.begin();
      if (Ci != CollectorList.end()) {
        fprintf(TFile," ");
        for (Ci = CollectorList.begin(); Ci != CollectorList.end(); Ci++) {
          fprintf(TFile," %s",(*Ci)->getMetadata().getShortName().c_str());
        }
        fprintf(TFile,"\n");
      }
    }
  void Dump(FILE *TFile)
    { std::list<ExperimentObject *>::reverse_iterator expi;
      for (expi = ExperimentObject_list.rbegin(); expi != ExperimentObject_list.rend(); expi++)
      {
        (*expi)->Print(TFile);
      }
    }
};

// Make sure all experiments are closed and associated files freed.
void Experiment_Termination ();

// Experiment Utilities
ExperimentObject *Find_Experiment_Object (EXPID ExperimentID);

// Experiment level commands
bool SS_expAttach (CommandObject *cmd);
bool SS_expClose (CommandObject *cmd);
bool SS_expCreate (CommandObject *cmd);
bool SS_expDetach (CommandObject *cmd);
bool SS_expDisable (CommandObject *cmd);
bool SS_expEnable (CommandObject *cmd);
bool SS_expFocus  (CommandObject *cmd);
bool SS_expGo (CommandObject *cmd);
bool SS_expPause (CommandObject *cmd);
bool SS_expRestore (CommandObject *cmd);
bool SS_expSave (CommandObject *cmd);
bool SS_expSetParam (CommandObject *cmd);
bool SS_expView (CommandObject *cmd);

// Information level commands
bool SS_ListBreaks (CommandObject *cmd);
bool SS_ListExp (CommandObject *cmd);
bool SS_ListHosts (CommandObject *cmd);
bool SS_ListObj (CommandObject *cmd);
bool SS_ListPids (CommandObject *cmd);
bool SS_ListMetrics (CommandObject *cmd);
bool SS_ListParams (CommandObject *cmd);
bool SS_ListReports (CommandObject *cmd);
bool SS_ListSrc (CommandObject *cmd);
bool SS_ListTypes (CommandObject *cmd);

// Session level commands
bool SS_ClearBreaks (CommandObject *cmd);
bool SS_Exit (CommandObject *cmd);
bool SS_Help (CommandObject *cmd);
bool SS_History (CommandObject *cmd);
bool SS_Log (CommandObject *cmd);
bool SS_OpenGui (CommandObject *cmd);
bool SS_Playback (CommandObject *cmd);
bool SS_Record (CommandObject *cmd);
bool SS_SetBreak (CommandObject *cmd);

// Place holders for comands that are not yet implemented
bool SS_no_value    	(CommandObject *cmd);
bool SS_string_value    (CommandObject *cmd);
bool SS_int_value   	(CommandObject *cmd);

// Define the basic input line structure
//
// The intent is that this will become the primary method for tracking
// user commands.  This object needs to be allocated as early as possible
// and needs to contain the current status of the command.  Later processing
// can define the COmmand object and associated methods.


enum Input_Line_Status
{
  ILO_UNKNOWN,
  ILO_QUEUED_INPUT,
  ILO_IN_PARSER,
  ILO_EXECUTING,
  ILO_COMPLETE,
  ILO_ERROR
};

class CommandObject;

// InputLineObject
class InputLineObject
{
 private:
  Input_Line_Status status;	// What is the current state.
  CMDID seq_num;		// Where in sequence that this command was parsed.
  time_t cmd_time;		// When the status field was set.
  CMDWID who;			// Who constructed the command.  (i.e. "gui", "cli", or "?")
  FILE *Trace_F;		// Echo stat changes to trace file.

  std::string command;		// The actual command to be executed.

 // The following fields contain "result" information.
  std::string msg_string;	// Intermediate processing or error information.
  oss_cmd_enum cmd_type;	// Filled in when the parser determines the type of command.
  std::list<CommandObject *> Cmd_Obj;  // list of associated command objects

 public:
  virtual void status_change () {
      if (Trace_F != NULL) {
        Print(Trace_F);
      }
  }
  virtual void issue_msg (char *msg) {fprintf(stdout,"%s\n",msg);}
  virtual void result_int (int64_t a) {fprintf(stdout,"TLI: %lld\n",a);}
  virtual void result_char (char *a) {fprintf(stdout,"%s\n",a);}

 private:
  void Basic_Initialization ()
    { 
      status = ILO_UNKNOWN;
      seq_num = 0;
      cmd_time = time(0);
      who = 0;
      Trace_F = NULL;
      command = std::string("");
      msg_string = std::string("");
      // cmd_type = CMD_NONE;
    }

 public:
  InputLineObject ()
    { this->Basic_Initialization();
    }
  InputLineObject (CMDWID From, std::string Cmd)
    { this->Basic_Initialization();
      who = From;
      command = Cmd;
    }
  InputLineObject (oss_cmd_enum type)
    { this->Basic_Initialization();
      cmd_type = type;
    }
  InputLineObject (CMDWID From, oss_cmd_enum type)
    { this->Basic_Initialization();
      who = From;
      cmd_type = type;
    }
  InputLineObject (CMDWID From, oss_cmd_enum type, std::string Cmd)
    { this->Basic_Initialization();
      who = From;
      cmd_type = type;
      command = Cmd;
    }
  ~InputLineObject ()
    {
    }

  void SetStatus (Input_Line_Status st) {
      cmd_time = time(0);
      status = st;
      status_change ();
  }
  void SetSeq (CMDID seq) {seq_num = seq;}
  CMDID Seq () { return seq_num; }
  CMDWID Who () { return who;}
  Input_Line_Status What() { return status; }
  time_t When () { return cmd_time; }
  CMDID Where () { return seq_num; }
  void Set_Trace (FILE *TFile) {Trace_F = TFile;}
  oss_cmd_enum Action () { return cmd_type; }
  std::string Command () {return command;}

  void Push_Cmd_Obj (CommandObject *C)
  {
    Cmd_Obj.push_back(C);
  }

  void Print (FILE *TFile) {
    if (TFile != NULL) {
      CMDWID who = Who();
      Input_Line_Status what = What();
      CMDID seq_num = Where();
      time_t cmd_time = When();
      std::string command = Command();
      fprintf(TFile,"C %lld (W%lld@%.24s) ",
                    seq_num,who,ctime(&cmd_time));
      char *what_c;
      switch (what)
      { 
        case ILO_UNKNOWN:      what_c = "  UNKNOWN"; break;
        case ILO_QUEUED_INPUT: what_c = "   QUEUED"; break;
        case ILO_IN_PARSER:    what_c = "  PARSING"; break;
        case ILO_EXECUTING:    what_c = "EXECUTING"; break;
        case ILO_COMPLETE:     what_c = " COMPLETE"; break;
        case ILO_ERROR:        what_c = "    ERROR"; break;
        default:               what_c = "  ILLEGAL"; break;
      }
      fprintf(TFile,"%s",what_c);
      fprintf(TFile,": ");
      if (command.length() != 0) {
        fprintf(TFile,"%s", command.c_str());
        int nline = strlen (command.c_str()) - 1;
        if ((nline <= 0) || (command.c_str()[nline] != *("\n"))) {
          fprintf(TFile,"\n");
        }
      }
      fflush(TFile);  // So that we can look at the file while still running
    }
  }

};

class TLI_InputLineObject : public InputLineObject
{
 public:
  virtual void issue_msg (char *msg) {fprintf(stdout,"%s\n",msg);}
  virtual void result_int (int64_t a) {fprintf(stdout,"TLI: %lld\n",a);}
  virtual void result_char (char *a) {fprintf(stdout,"%s\n",a);}

  TLI_InputLineObject (CMDWID From, std::string Cmd) :
    InputLineObject (From, Cmd)
    { }
};

class GUI_InputLineObject : public InputLineObject
{
 public:
  virtual void issue_msg (char *msg) {fprintf(stdout,"%s\n",msg);}
  virtual void result_int (int64_t a) {fprintf(stdout,"GUI: %lld\n",a);}
  virtual void result_char (char *a) {fprintf(stdout,"%s\n",a);}

  GUI_InputLineObject (CMDWID From, std::string Cmd) :
    InputLineObject (From, Cmd)
    { }
};

class RLI_InputLineObject : public InputLineObject
{
 public:
  virtual void issue_msg (char *msg) {fprintf(stdout,"%s\n",msg);}
  virtual void result_int (int64_t a) {fprintf(stdout,"RLI: %lld\n",a);}
  virtual void result_char (char *a) {fprintf(stdout,"%s\n",a);}

  RLI_InputLineObject (CMDWID From, std::string Cmd) :
    InputLineObject (From, Cmd)
    { }
};

void Link_Cmd_Obj_to_Input (InputLineObject *I, CommandObject *C);

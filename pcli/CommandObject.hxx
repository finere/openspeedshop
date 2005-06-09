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

// The CommandObject

// types of results that can be returned in a CommandObject
enum cmd_result_type_enum {
  CMD_RESULT_NULL,
  CMD_RESULT_UINT,
  CMD_RESULT_INT,
  CMD_RESULT_FLOAT,
  CMD_RESULT_STRING,
  CMD_RESULT_TITLE,
  CMD_RESULT_COLUMN_HEADER,
  CMD_RESULT_COLUMN_VALUES,
  CMD_RESULT_COLUMN_ENDER,
};

class CommandResult {
  cmd_result_type_enum Result_Type;

 private:
  CommandResult () {
    Result_Type = CMD_RESULT_NULL; }

 public:
  CommandResult (cmd_result_type_enum T) {
    Result_Type = T; }
  cmd_result_type_enum Type () {
    return Result_Type;
  }

  virtual void Value (char *&C) {
    C = NULL;
  }
  virtual void Print (ostream &to, int64_t fieldsize=20, bool leftjustified=false) {
    char F[20];
    char S[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%llds\0", fieldsize);
    sprintf(S, F, "(none)");
    to << S;
  }
  virtual void Print (FILE *TFile, int64_t fieldsize=20, bool leftjustified=false) {
    //fprintf(TFile,"              (none)");
    char F[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%llds\0", fieldsize);
    fprintf(TFile,&F[0],"(none)");
  }
};

class CommandResult_Uint : public CommandResult {
  uint64_t uint_value;

 public:
  CommandResult_Uint () : CommandResult(CMD_RESULT_UINT) {
    uint_value = 0;
  }
  CommandResult_Uint (uint64_t U) : CommandResult(CMD_RESULT_UINT) {
    uint_value = U;
  }

  static void Accumulate_Uint (CommandResult_Uint *A, CommandResult_Uint *B) {
    A->uint_value += B->uint_value;
  }


  virtual void Value (uint64_t &U) {
    U = uint_value;
  };
  virtual void Print (ostream &to, int64_t fieldsize, bool leftjustified) {
    char F[20];
    char S[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldllu\0", fieldsize);
    sprintf(S,&F[0],uint_value);
    to << S;
  }
  virtual void Print (FILE *TFile, int64_t fieldsize, bool leftjustified) {
    // fprintf(TFile,"%20llu\n",uint_value);
    char F[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldllu\0", fieldsize);
    fprintf(TFile,&F[0],uint_value);
  }
};

class CommandResult_Int : public CommandResult {
  int64_t int_value;

 public:
  CommandResult_Int () : CommandResult(CMD_RESULT_INT) {
    int_value = 0;
  }
  CommandResult_Int (CommandResult_Uint *U) : CommandResult(CMD_RESULT_INT) {
    uint64_t Uvalue;
    U->Value(Uvalue);
    int_value = Uvalue;
  }
  CommandResult_Int (int64_t I) : CommandResult(CMD_RESULT_INT) {
    int_value = I;
  }

  static void Accumulate_Int (CommandResult_Int *A, CommandResult_Int *B) {
    A->int_value += B->int_value;
  }


  virtual void Value (int64_t &I) {
    I = int_value;
  };
  virtual void Print (ostream &to, int64_t fieldsize, bool leftjustified) {
    char F[20];
    char S[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldlld\0", fieldsize);
    sprintf(S,F,int_value);
    to << S;
  }
  virtual void Print (FILE *TFile, int64_t fieldsize, bool leftjustified) {
    // fprintf(TFile,"%20lld\n",int_value);
    char F[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldlld\0", fieldsize);
    fprintf(TFile,&F[0],int_value);
  }
};

class CommandResult_Float : public CommandResult {
  double float_value;

 public:
  CommandResult_Float () : CommandResult(CMD_RESULT_FLOAT) {
    float_value = 0.0;
  }
  CommandResult_Float (CommandResult_Uint *U) : CommandResult(CMD_RESULT_FLOAT) {
    uint64_t Uvalue;
    U->Value(Uvalue);
    float_value = Uvalue;
  }
  CommandResult_Float (CommandResult_Int *I) : CommandResult(CMD_RESULT_FLOAT) {
    int64_t Ivalue;
    I->Value(Ivalue);
    float_value = Ivalue;
  }
  CommandResult_Float (double f) : CommandResult(CMD_RESULT_FLOAT) {
    float_value = f;
  }

  static void Accumulate_Float (CommandResult_Float *A, CommandResult_Float *B) {
    A->float_value += B->float_value;
  }


  virtual void Value (double &F) {
    F = float_value;
  };
  virtual void Print (ostream &to, int64_t fieldsize, bool leftjustified) {
    char F[20];
    char S[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldf\0", fieldsize);
    sprintf(S,F,float_value);
    to << S;
  }
  virtual void Print (FILE *TFile, int64_t fieldsize, bool leftjustified) {
    // fprintf(TFile,"%20f",float_value);
    char F[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%lldf\0", fieldsize);
    fprintf(TFile,&F[0],float_value);
  }
};

class CommandResult_String : public CommandResult {
  std::string string_value;

 public:
  CommandResult_String (std::string S) : CommandResult(CMD_RESULT_STRING) {
    string_value = S;
  }
  CommandResult_String (char *S) : CommandResult(CMD_RESULT_STRING) {
    string_value = std::string(S);
  }

  virtual void Value (std::string &S) {
    S = string_value;
  }
  virtual void Print (ostream &to, int64_t fieldsize, bool leftjustified) {
    if (leftjustified) {
     // Left justification is only done on the last column of a report.
     // Don't truncate the string if it is bigger than the field size.
     // This is done to make sure everything gets printed.
     // But make sure we fill the field.

      to << string_value;

     // If there is unused space in the field, pad with blanks.
      if ((string_value.length() < fieldsize) &&
          (string_value[string_value.length()-1] != *("\n"))) {
        for (int64_t i = string_value.length(); i < fieldsize; i++) to << " ";
      }

    } else {
     // Right justify the string in the field.
     // Don't let it exceed the size of the field.
     // Also, limit the size based on our internal buffer size.
      char F[20];
      char S[1000];
      int max_size = MIN(fieldsize,1000);
      int i = 0;
      F[i++] = *("%");
      sprintf(&F[i], "%lld.%llds\0", max_size, max_size);
      sprintf(S,F,string_value.c_str());
      to << S;
    }
  }
  virtual void Print (FILE *TFile, int64_t fieldsize, bool leftjustified) {
    // fprintf(TFile,"%s",string_value.c_str());
    char F[20];
    int i = 0;
    F[i++] = *("%");
    if (leftjustified) F[i++] = *("-");
    sprintf(&F[i], "%llds\0", fieldsize);
    fprintf(TFile,&F[0],string_value.c_str());
  }
};

class CommandResult_Title : public CommandResult {
  std::string string_value;

 public:
  CommandResult_Title (std::string S) : CommandResult(CMD_RESULT_TITLE) {
    string_value = S;
  }

  virtual void Value (std::string &S) {
    S = string_value;
  }
  virtual void Print (ostream &to, int64_t fieldsize, bool leftjustified) {
    to << string_value;
  }
  virtual void Print (FILE *TFile, int64_t fieldsize, bool leftjustified) {
    fprintf(TFile,"%s/n",string_value.c_str());
  }
};

class CommandResult_Headers : public CommandResult {

 int64_t number_of_columns;
 std::list<CommandResult *> Headers;

 public:
  CommandResult_Headers () : CommandResult(CMD_RESULT_COLUMN_HEADER) {
    number_of_columns = 0;
  }
  void Add_Header (CommandResult *R) {
    number_of_columns++;
    Headers.push_back(R);
  }

  virtual void Value (int64_t &C) {
    C = number_of_columns;
  }
  virtual void Print (ostream &to, int64_t fieldsize=20, bool leftjustified=false) {
    
    std::list<CommandResult *> cmd_object = Headers;
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = cmd_object.begin(); coi != cmd_object.end(); coi++) {
      if (num_results++ != 0) to << "  ";
      (*coi)->Print (to, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
  virtual void Print (FILE *TFile, int64_t fieldsize=20, bool leftjustified=false) {
    
    std::list<CommandResult *> cmd_object = Headers;
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = cmd_object.begin(); coi != cmd_object.end(); coi++) {
      if (num_results++ != 0) fprintf(TFile,"  ");
      (*coi)->Print (TFile, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
};

class CommandResult_Enders : public CommandResult {

 int64_t number_of_columns;
 std::list<CommandResult *> Enders;

 public:
  CommandResult_Enders () : CommandResult(CMD_RESULT_COLUMN_ENDER) {
    number_of_columns = 0;
  }
  void Add_Ender (CommandResult *R) {
    number_of_columns++;
    Enders.push_back(R);
  }

  virtual void Value (int64_t &C) {
    C = number_of_columns;
  }
  virtual void Print (ostream &to, int64_t fieldsize=20, bool leftjustified=false) {
    
    std::list<CommandResult *> cmd_object = Enders;
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = cmd_object.begin(); coi != cmd_object.end(); coi++) {
      if (num_results++ != 0) to << "  ";
      (*coi)->Print (to, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
  virtual void Print (FILE *TFile, int64_t fieldsize=20, bool leftjustified=false) {
    
    std::list<CommandResult *> cmd_object = Enders;
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = cmd_object.begin(); coi != cmd_object.end(); coi++) {
      if (num_results++ != 0) fprintf(TFile,"  ");
      (*coi)->Print (TFile, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
};

class CommandResult_Columns : public CommandResult {

 int64_t number_of_columns;
 std::list<CommandResult *> Columns;

 public:
  CommandResult_Columns (int64_t C = 0) : CommandResult(CMD_RESULT_COLUMN_VALUES) {
    number_of_columns = 0;
  }
  void Add_Column (CommandResult *R) {
    number_of_columns++;
    Columns.push_back(R);
  }

  virtual void Value (CommandResult &R) {
    R = *this;
  }
  virtual void Print (ostream &to, int64_t fieldsize=20, bool leftjustified=false) {
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = Columns.begin(); coi != Columns.end(); coi++) {
      if (num_results++ != 0) to << "  ";
      (*coi)->Print (to, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
  virtual void Print (FILE *TFile, int64_t fieldsize=20, bool leftjustified=false) {
    
    std::list<CommandResult *> cmd_object = Columns;
    std::list<CommandResult *>::iterator coi;
    int num_results = 0;
    for (coi = cmd_object.begin(); coi != cmd_object.end(); coi++) {
      if (num_results++ != 0) fprintf(TFile,"  ");
      (*coi)->Print (TFile, fieldsize, (num_results >= number_of_columns) ? true : false);
    }

  }
};

inline void Accumulate_CommandResult (CommandResult *A, CommandResult *B) {
  if (!A || !B) return;
  switch (A->Type()) {
  case CMD_RESULT_UINT:
    CommandResult_Uint::Accumulate_Uint ((CommandResult_Uint *)A, (CommandResult_Uint *)B);
    break;
  case CMD_RESULT_INT:
    CommandResult_Int::Accumulate_Int ((CommandResult_Int *)A, (CommandResult_Int *)B);
    break;
  case CMD_RESULT_FLOAT:
    CommandResult_Float::Accumulate_Float ((CommandResult_Float *)A, (CommandResult_Float *)B);
    break;
  }
}

inline CommandResult *Calculate_Percent (CommandResult *A, CommandResult *B) {
  double Avalue;
  double Bvalue;

  switch (A->Type()) {
   case CMD_RESULT_UINT:
    uint64_t Uvalue;
    ((CommandResult_Uint *)A)->Value(Uvalue);
    Avalue = Uvalue;
    break;
   case CMD_RESULT_INT:
    int64_t Ivalue;
    ((CommandResult_Int *)A)->Value(Ivalue);
    Avalue = Ivalue;
    break;
   case CMD_RESULT_FLOAT:
    ((CommandResult_Float *)A)->Value(Avalue);
    break;
  }
  switch (B->Type()) {
   case CMD_RESULT_UINT:
    uint64_t Uvalue;
    ((CommandResult_Uint *)B)->Value(Uvalue);
    Bvalue = Uvalue;
    break;
   case CMD_RESULT_INT:
    int64_t Ivalue;
    ((CommandResult_Int *)B)->Value(Ivalue);
    Bvalue = Ivalue;
    break;
   case CMD_RESULT_FLOAT:
    ((CommandResult_Float *)B)->Value(Bvalue);
    break;
  }

  double percent = (Avalue *100) / Bvalue;
  // if (percent > 100.0) percent = 100.0;
  if (percent < 0.0) percent = 0.0;
  return new CommandResult_Float (percent);
}
    

enum Command_Status
{
  CMD_UNKNOWN,
  CMD_PARSED,
  CMD_EXECUTING,
  CMD_COMPLETE,
  CMD_ERROR,
  CMD_ABORTED 
};

class CommandObject
{
  InputLineObject *Associated_Clip; // The input line that caused generation of this object.
  int Seq_Num; // The order this object was generated in from the input line.
  Command_Status Cmd_Status;
  oss_cmd_enum Cmd_Type; // A copy of information in the Parse_Result.
  // command_t *Parse_Result;
  // command_type_t *Parse_Result;
  OpenSpeedShop::cli::ParseResult *PR;
  bool results_used; // Once used, this object can be deleted!
  std::list<CommandResult *> CMD_Result;

  void Associate_Input ()
  {
    Associated_Clip = Current_ILO;
    Link_Cmd_Obj_to_Input (Associated_Clip, this);
  }

  void Attach_Result (CommandResult *R) {
    CMD_Result.push_back(R);
  }

  CommandObject() { } // Hide default constructor to catch errors at compile time

public:
//  CommandObject(command_t *P)
//  {
//    this->Associate_Input ();
//    Cmd_Status = CMD_PARSED;
//    Cmd_Type =  P->type;
//    Parse_Result = P;
//    PR = NULL;
//    results_used = false;
//  }
  CommandObject(OpenSpeedShop::cli::ParseResult *pr)
  {
    this->Associate_Input ();
    Cmd_Status = CMD_PARSED;
    Cmd_Type =  pr->GetCommandType();
//    Parse_Result = NULL;
    PR = pr;
    results_used = false;
  }
  ~CommandObject() {
  }

  InputLineObject *Clip () { return Associated_Clip; }
  Command_Status Status () { return Cmd_Status; }
  oss_cmd_enum Type () { return Cmd_Type; }
  bool Results_Used () { return results_used; }
  OpenSpeedShop::cli::ParseResult *P_Result () { return PR; }
  // command_t *P_Result () { return Parse_Result; }
  //command_type_t *P_Result () { return Parse_Result; }
    
  void SetSeqNum (int a) { Seq_Num = a; }
  void set_Status (Command_Status S); // defined in CommandObject.cxx
  void set_Results_Used () { results_used = true; }

  void Result_Uint (uint64_t U) {
    Attach_Result (new CommandResult_Uint(U));
  }
  void Result_Int (int64_t I) {
    Attach_Result (new CommandResult_Int(I));
  }
  void Result_Float (double F) {
    Attach_Result (new CommandResult_Float(F));
  }
  void Result_String (std::string S) {
    Attach_Result (new CommandResult_String (S));
  }
  void Result_String (char *C) {
    Attach_Result (new CommandResult_String (C));
  }
  void Result_Predefined (CommandResult *C) {
    Attach_Result (C);
  }

  std::list<CommandResult *> Result_List () {
    return CMD_Result;
  }

 // The following are defined in CommandObject.cxx

 // The simple Print is for dumping information to a trace file.
  void Print (FILE *TFile);
 // The Print_Results routine is for sending results to the user.
 // The result returned is "true" if there was information printed.
  bool Print_Results (ostream &to, std::string list_seperator, std::string termination_char);
  bool Print_Results (FILE *TFile, std::string list_seperator, std::string termination_char);
};

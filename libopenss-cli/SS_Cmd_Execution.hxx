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

// Information level commands
bool SS_expStatus(CommandObject *cmd);
bool SS_expView (CommandObject *cmd);

// Primitive Information level commands
bool SS_ListBreaks (CommandObject *cmd);
bool SS_ListExp (CommandObject *cmd);
bool SS_ListHosts (CommandObject *cmd);
bool SS_ListObj (CommandObject *cmd);
bool SS_ListPids (CommandObject *cmd);
bool SS_ListMetrics (CommandObject *cmd);
bool SS_ListParams (CommandObject *cmd);
bool SS_ListRanks (CommandObject *cmd);
bool SS_ListSrc (CommandObject *cmd);
bool SS_ListStatus (CommandObject *cmd);
bool SS_ListThreads (CommandObject *cmd);
bool SS_ListTypes (CommandObject *cmd);
bool SS_ListViews (CommandObject *cmd);

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

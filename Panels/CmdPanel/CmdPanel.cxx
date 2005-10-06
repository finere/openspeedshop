////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2005 Silicon Graphics, Inc. All Rights Reserved.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
// details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////


#include "CmdPanel.hxx"   // Change this to your new class header file name
#include "PanelContainer.hxx"   // Do not remove
#include "plugin_entry_point.hxx"   // Do not remove

#include <qapplication.h>
#include <qevent.h>

extern char *Current_OpenSpeedShop_Prompt;
QString prompt = QString::null;

#include "SS_Input_Manager.hxx"

/*! \class CmdPanel
  The CmdPanel class is designed to accept command line input from the user.
  As if they were typing in commands in cli only.   

  This is prototype code to show proof of concept.
  */
static  QTextEdit *output;

class OutputClass : public ss_ostream
{
  public:
    CmdPanel *cp;
    void setCP(CmdPanel *_cp) { cp = _cp;line_buffer = QString::null; };
    QString line_buffer;
  private:
    virtual void output_string (std::string s)
    {
       line_buffer += s.c_str();
       if( QString(s).contains("\n") )
       {
         QString *data = new QString(line_buffer);
         cp->postCustomEvent(data);
         line_buffer = QString::null;
       }
    }
    virtual void flush_ostream ()
    {
      qApp->flushX();
    }
};

CmdPanel::CmdPanel(PanelContainer *pc, const char *n, void *argument) : Panel(pc, n)
{
  nprintf(DEBUG_CONST_DESTRUCT) ( "CmdPanel::CmdPanel() constructor called.\n");

  // grab the prompt from the cli.
  prompt = QString(Current_OpenSpeedShop_Prompt);
// printf("prompt=(%s)\n", prompt.ascii() );

  frameLayout = new QHBoxLayout( getBaseWidgetFrame(), 1, 2, getName() );

  output = new QTextEdit( getBaseWidgetFrame() );
  output->setTextFormat(PlainText);

  frameLayout->addWidget(output);

  output->show();

/*
  output->append( prompt );
  output->moveCursor(QTextEdit::MoveEnd, FALSE);
*/
  putOutPrompt();
  output->setFocus();

  KeyEventFilter *keyEventFilter = new KeyEventFilter(output, this);
  output->installEventFilter( keyEventFilter );

  cmdHistoryListIterator = cmdHistoryList.begin();

  oclass = new OutputClass();
  oclass->setCP(this);


  show();

// printf("CmdPanel.   Redirect all output here...\n");
  int wid = getPanelContainer()->getMainWindow()->widStr.toInt();
  Redirect_Window_Output( wid, oclass, oclass );
}


/*
 *  Destroys the object and frees any allocated resources
 */
CmdPanel::~CmdPanel()
{
  nprintf(DEBUG_CONST_DESTRUCT) ( "  CmdPanel::~CmdPanel() destructor called.\n");
}

void Default_TLI_Command_Output(CommandObject *C)
{
  printf("CmdPanel::callback(well sort of) entered\n");
}

void Default_TLI_Line_Output( InputLineObject *clip)
{
  printf("Default_TLI_Line_Output() entered\n");
}

typedef QValueList<QString> CommandList;
void
CmdPanel::returnPressed()
{
  nprintf(DEBUG_PANELS)  ("CmdPanel::returnPressed()\n");

// printf("returnPressed() entered\n");

  output->scrollToBottom();

  if( user_line_buffer.stripWhiteSpace().isEmpty() )
  {
// printf("No command, simply put out prompt.\n");
    putOutPrompt();
    return;
  }

  int i = 0;
  CommandList commandList;
  commandList.clear();
  QString command_string = user_line_buffer.stripWhiteSpace();

  commandList.push_back(command_string);

  nprintf(DEBUG_PANELS) ("commandList.count()=%d\n", commandList.count() );

  for( CommandList::Iterator ci = commandList.begin(); ci != commandList.end(); ci++ )
  {
    QString command = (QString) *ci;
    nprintf(DEBUG_PANELS) ("Send down (%s)\n", command.ascii());
    int wid = getPanelContainer()->getMainWindow()->widStr.toInt();
    Redirect_Window_Output( wid, oclass, oclass );

    InputLineObject clip;
    cmdHistoryList.push_back(command);
    Append_Input_String( wid, (char *)command.ascii(), NULL, &Default_TLI_Line_Output, &Default_TLI_Command_Output);
//    Append_Input_String( wid, (char *)command.ascii());

    output->moveCursor(QTextEdit::MoveEnd, FALSE);
  } 

  nprintf(DEBUG_PANELS) ("Set the positions for the next command.\n");
  output->moveCursor(QTextEdit::MoveEnd, FALSE);
  nprintf(DEBUG_PANELS) ("Try to get another command.\n");

 
  user_line_buffer = QString::null;
  putOutPrompt();
}


void
CmdPanel::upKey()
{
  nprintf(DEBUG_PANELS) ("CmdPanel::upKey()\n");
// printf("upkey() entered\n");

  if( cmdHistoryListIterator != cmdHistoryList.begin() ) 
  {
    cmdHistoryListIterator--;
  }
  QString str = (QString)*cmdHistoryListIterator;

  if( str )
  {
    nprintf(DEBUG_PANELS) ("upKey() str=(%s)\n", str.ascii() );
// printf("upKey() str=(%s)\n", str.ascii() );

    clearCurrentLine();

    appendHistory(prompt+str);
    output->moveCursor(QTextEdit::MoveEnd, FALSE);
    user_line_buffer = str;
  }
}

void
CmdPanel::downKey()
{
  nprintf(DEBUG_PANELS) ("CmdPanel::downKey()\n");
// printf("downkey() entered\n");
  if( cmdHistoryListIterator != cmdHistoryList.end() ) 
  {
    cmdHistoryListIterator++;
  }
  
  QString str = (QString)*cmdHistoryListIterator;

  if( str )
  {
    nprintf(DEBUG_PANELS) ("downKey() str=(%s)\n", str.ascii() );
// printf("downKey() str=(%s)\n", str.ascii() );
    clearCurrentLine();
    appendHistory(prompt+str);
    output->moveCursor(QTextEdit::MoveEnd, FALSE);
    user_line_buffer = str;
  }
}

void 
CmdPanel::positionToEnd()
{
  output->moveCursor(QTextEdit::MoveEnd, FALSE);
}

void
CmdPanel::clearCurrentLine()
{
  positionToEnd();
  int para, index;
  output->getCursorPosition(&para, &index);
  output->setSelection(para, 0, para, index);
  output->removeSelectedText();
  output->moveCursor(QTextEdit::MoveEnd, FALSE);
//  output->moveCursor(QTextEdit::MoveLineStart, FALSE);
//  putOutPrompt();
}

void
CmdPanel::putOutPrompt()
{
// printf("PutOutPrompt() enterd\n");
output->moveCursor(QTextEdit::MoveEnd, FALSE);
output->append( prompt );
output->moveCursor(QTextEdit::MoveEnd, FALSE);

// int para; int index;
// output->getCursorPosition(&para, &index);
// output->setCursorPosition(para, index-1);
// printf("para=%d index=%d\n", para, index );
// output->moveCursor(QTextEdit::MoveLineEnd, FALSE);
// output->setCursorPosition(para, index-1);
}

void
CmdPanel::appendHistory(QString str)
{
// printf("appendHistory entered\n");

  output->append(str);
}

/*
 * Add local panel options here..
 */
bool
CmdPanel::menu(QPopupMenu* contextMenu)
{
  nprintf(DEBUG_PANELS) ("CmdPanel::menu() requested.\n");
  return( TRUE );
} /* * Add local save() functionality here.  */
void 
CmdPanel::save()
{
  nprintf(DEBUG_PANELS) ("CmdPanel::save() requested.\n");
}

/* 
 * Add local saveAs() functionality here.
 */
void 
CmdPanel::saveAs()
{
  nprintf(DEBUG_SAVEAS) ("CmdPanel::saveAs() requested.\n");
}

/* 
 * Add message listener() functionality here.
 */
#include "MessageObject.hxx"
int 
CmdPanel::listener(void *msg)
{
  nprintf(DEBUG_MESSAGES) ("CmdPanel::listener() requested.\n");

  nprintf(DEBUG_MESSAGES) ("CmdPanel::listener() getName(%s)\n", getName() );
  MessageObject *messageObject = (MessageObject *)msg;
  if( messageObject->msgType == getName() )
  {
    nprintf(DEBUG_MESSAGES) ("CmdPanel::listener() interested!\n");
    getPanelContainer()->raisePanel(this);
    return 1;
  }
  return 0;  // 0 means, did not want this message and did not act on anything.
}

/* 
 * Add message broadcaster() functionality here.
 */
int
CmdPanel::broadcast(char *msg, BROADCAST_TYPE bt)
{
  nprintf(DEBUG_MESSAGES) ("CmdPanel::broadcast() requested.\n");
  return 0;
}

void
CmdPanel::menu1callback()
{
  nprintf(DEBUG_PANELS) ("CmdPanel::menu1callback() entered\n");
}

void CmdPanel::menu2callback()
{
  nprintf(DEBUG_PANELS) ("CmdPanel::menu2callback() entered\n");
}

#define FRAP 10000
void
CmdPanel::postCustomEvent(QString *data)
{
  QCustomEvent *event;
  event = new QCustomEvent(FRAP);
  event->setData(data);
  QApplication::postEvent(this, event);
}

void CmdPanel::customEvent(QCustomEvent *e)
{
//printf("CmdPanel::customEvent() entered\n");
  if( e->type() == FRAP )
  {
// qApp->processEvents(30);
   QString *data = static_cast<QString *>(e->data());
//printf("PUt out the string (%s)", data->ascii() );
   // This goes to the text stream...
   output->moveCursor(QTextEdit::MoveEnd, FALSE);
   output->append(*data);
   output->moveCursor(QTextEdit::MoveEnd, FALSE);
//   delete data;
  }
}

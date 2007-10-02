////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2007 Krell Institute. All Rights Reserved.
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


//
//#define DEBUG_loadPanel 1
//

#include "loadPanel.hxx"   // Change this to your new class header file name
#include "PanelContainer.hxx"   // Do not remove
#include "plugin_entry_point.hxx"   // Do not remove
#include <qapplication.h>
#include <qvariant.h>
#include <qpushbutton.h>
#include <qwidgetstack.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qcheckbox.h>
#include <qframe.h>
#include <qradiobutton.h>
#include <qlineedit.h>
#include <qheader.h>
#include <qlistview.h>
#include <qlistbox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qfile.h>   // For the file dialog box.
#include <qfiledialog.h>  // For the file dialog box.
#include <qmessagebox.h>
#include <qscrollview.h>
#include <qvbox.h>
#include <qbitmap.h>
#include <qlistview.h>  // For QListView
#include <qvaluelist.h>  // For QTextEdit in example below...
#include <qsplitter.h>  // For QSplitter in example below...
#include <chartform.hxx>  // For chart in example below...


loadPanel::loadPanel(PanelContainer *pc, const char *n, ArgumentObject *ao) : Panel(pc, n)
{

#ifdef DEBUG_loadPanel
  printf("loadPanel::loadPanel(), entered\n");
#endif

  if( ao ) {

#ifdef DEBUG_loadPanel
    printf("loadPanel::loadPanel(), have non-null argument object\n");
#endif

    targetPanel = ao->panel_data;

#ifdef DEBUG_loadPanel
    printf("loadPanel::loadPanel(), panel name is=%s\n", targetPanel->getName());
#endif
    
  }

  setCaption("loadPanel");

  if ( !getName() )
  {
        setName( "loadPanel" );
  }


  vMPLoadPageLoadMPHostName = QString::null;
  vMPLoadPageLoadMPPidName = QString::null;
  vMPLoadPageLoadMPProgName = QString::null;

  loadPanelFormLayout = new QVBoxLayout( getBaseWidgetFrame(), 0, 0, "Load Panel" );

  mainFrame = new QFrame( getBaseWidgetFrame(), "mainFrame" );
  mainFrame->setMinimumSize( QSize(30,20) );
  mainFrame->setFrameShape( QFrame::StyledPanel );
  mainFrame->setFrameShadow( QFrame::Raised );
  mainFrame->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum, 0, 0, FALSE ) );
  mainFrameLayout = new QVBoxLayout( mainFrame, 11, 6, "mainFrameLayout");

  mainWidgetStack = new QWidgetStack( mainFrame, "mainWidgetStack" );
  mainWidgetStack->setMinimumSize( QSize(30,20) );
  mainWidgetStack->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum, 0, 0, FALSE ) );


// Begin: AttachOrLoad page
  vALStackPage0 = new QWidget( mainWidgetStack, "vALStackPage0" );
  vALStackPage0->setMinimumSize( QSize(30,20) );
  vALStackPage0->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred, 0, 0, FALSE ) );
  vALStackPage0Layout = new QVBoxLayout( vALStackPage0, 11, 6, "vALStackPage0Layout"); 

  vpage0sv = new QScrollView( vALStackPage0, "vpage0sv" );
  vpage0sv->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Maximum, 0, 0, FALSE ) );

  vpage0big_box = new QVBox(vpage0sv->viewport(), "vpage0big_box" );
  vpage0big_box->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Maximum, 0, 0, FALSE ) );
  vpage0big_box->setPaletteBackgroundColor("Tan");

  vpage0sv->addChild(vpage0big_box);

  vAttachOrLoadPageDescriptionLabel = new QTextEdit( vALStackPage0, "vAttachOrLoadPageDescriptionLabel" );
  vAttachOrLoadPageDescriptionLabel->setReadOnly(TRUE);
  vAttachOrLoadPageDescriptionLabel->setMinimumSize( QSize(30,20) );
  vAttachOrLoadPageDescriptionLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );
  vAttachOrLoadPageDescriptionLabel->setWordWrap( QTextEdit::WidgetWidth );

  vALStackPage0Layout->addWidget( vAttachOrLoadPageDescriptionLabel);

  const QColor vpage0acolor = vAttachOrLoadPageDescriptionLabel->paletteBackgroundColor();
  vpage0sv->viewport()->setBackgroundColor(vpage0acolor);
  vpage0sv->viewport()->setPaletteBackgroundColor(vpage0acolor);
  vpage0sv->viewport()->setBackgroundColor("Yellow");

  //
  // Separate the Intro Text Label from the ScrollView with the load/attach options
  //
  vLAPage0Line1 = new QFrame( vALStackPage0, "vLAPage0Line1" );
  vLAPage0Line1->setMinimumSize( QSize(10,10) );
  vLAPage0Line1->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred, 0, 0, FALSE ) );
  vLAPage0Line1->setFrameShape( QFrame::HLine );
  vLAPage0Line1->setFrameShadow( QFrame::Sunken );
  vALStackPage0Layout->addWidget( vLAPage0Line1 );

  // Add single process label here
  vLAPageTitleLabel1 = new QLabel( vpage0big_box, "vLAPageTitleLabel1" );
  vLAPageTitleLabel1->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed, 0, 0, FALSE ) );

  vAttachOrLoadPageLoadExecutableCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageLoadExecutableCheckBox" );

  vAttachOrLoadPageExecutableLabel = new QLabel( vpage0big_box, "vAttachOrLoadPageExecutableLabel" );
  vAttachOrLoadPageExecutableLabel->setMinimumSize( QSize(10,10) );
  vAttachOrLoadPageExecutableLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );

  // Add single process load different label here
  vAttachOrLoadPageLoadDifferentExecutableCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageLoadDifferentExecutableCheckBox" );
  vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
  vAttachOrLoadPageLoadDifferentExecutableCheckBox->hide();

  // Add single process attach label here
  vAttachOrLoadPageAttachToProcessCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageAttachToProcessCheckBox" );

  vAttachOrLoadPageProcessListLabel = new QLabel( vpage0big_box, "vAttachOrLoadPageProcessListLabel" );
  vAttachOrLoadPageProcessListLabel->setMinimumSize( QSize(10,10) );
  vAttachOrLoadPageProcessListLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );

  // Add multi-process label here

  vLAPage0SeqMPSeparatorLine = new QFrame( vpage0big_box, "vLAPage0SeqMPSeparatorLine" );
  vLAPage0SeqMPSeparatorLine->setMinimumSize( QSize(10,10) );
  vLAPage0SeqMPSeparatorLine->setFrameShape( QFrame::HLine );
  vLAPage0SeqMPSeparatorLine->setFrameShadow( QFrame::Sunken );
  vLAPage0SeqMPSeparatorLine->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );

  vLAPageTitleLabel2 = new QLabel( vpage0big_box, "vLAPageTitleLabel2" );
  vLAPageTitleLabel2->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Fixed, 0, 0, FALSE ) );

  // MultiProcess Load Executable Code
  vAttachOrLoadPageLoadMultiProcessExecutableCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageLoadMultiProcessExecutableCheckBox" );

  vAttachOrLoadPageMultiProcessExecutableLabel = new QLabel( vpage0big_box, "vAttachOrLoadPageMultiProcessExecutableLabel" );
  vAttachOrLoadPageMultiProcessExecutableLabel->setMinimumSize( QSize(10,10) );
  vAttachOrLoadPageMultiProcessExecutableLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );

  // MultiProcess Load Different
  vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox" );
  vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
  vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->hide();

  // MultiProcess Attach
  vAttachOrLoadPageAttachToMultiProcessCheckBox = new QCheckBox( vpage0big_box, "vAttachOrLoadPageAttachToMultiProcessCheckBox" );

  vAttachOrLoadPageMultiProcessListLabel = new QLabel( vpage0big_box, "vAttachOrLoadPageMultiProcessListLabel" );
  vAttachOrLoadPageMultiProcessListLabel->setMinimumSize( QSize(10,10) );
  vAttachOrLoadPageMultiProcessListLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );

  vALStackPage0Layout->addWidget( vpage0sv);

  vLAPage0Line2 = new QFrame( vALStackPage0, "vLAPage0Line2" );
  vLAPage0Line2->setMinimumSize( QSize(10,10) );
  vLAPage0Line2->setFrameShape( QFrame::HLine );
  vLAPage0Line2->setFrameShadow( QFrame::Sunken );
  vLAPage0Line2->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding, 0, 0, FALSE ) );
  vALStackPage0Layout->addWidget( vLAPage0Line2 );

  vAttachOrLoadPageSpacer = new QSpacerItem( 20, 30, QSizePolicy::Expanding, QSizePolicy::Expanding );
  vALStackPage0Layout->addItem( vAttachOrLoadPageSpacer );


  //
  // BUTTON LAYOUT
  //

  vAttachOrLoadPageButtonLayout = new QHBoxLayout( 0, 0, 6, "vAttachOrLoadPageButtonLayout"); 

  vAttachOrLoadPageButtonSpacer = new QSpacerItem( 1, 10, QSizePolicy::Expanding, QSizePolicy::Fixed );
  vAttachOrLoadPageButtonLayout->addItem( vAttachOrLoadPageButtonSpacer );

  vAttachOrLoadPageClearButton = new QPushButton( vALStackPage0, "vAttachOrLoadPageClearButton" );
  vAttachOrLoadPageClearButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageClearButton->sizePolicy().hasHeightForWidth() ) );
  vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageClearButton );

  vAttachOrLoadPageBackButton = new QPushButton( vALStackPage0, "vAttachOrLoadPageBackButton" );
  vAttachOrLoadPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageBackButton->sizePolicy().hasHeightForWidth() ) );
  vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageBackButton );

  vAttachOrLoadPageNextButton = new QPushButton( vALStackPage0, "vAttachOrLoadPageNextButton" );
  vAttachOrLoadPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageNextButton->sizePolicy().hasHeightForWidth() ) );
  vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageNextButton );

  vAttachOrLoadPageFinishButton = new QPushButton( vALStackPage0, "vAttachOrLoadPageFinishButton" );
  vAttachOrLoadPageFinishButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageFinishButton->sizePolicy().hasHeightForWidth() ) );
  vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageFinishButton );

  vALStackPage0Layout->addLayout( vAttachOrLoadPageButtonLayout );
  mainWidgetStack->addWidget( vALStackPage0, 1 );

  vpage0big_box->adjustSize();


#ifdef DEBUG_loadPanel
  printf("vpage0big_box->width()=%d\n", vpage0big_box->width());
  printf("vpage0sv->height()=%d\n", vpage0sv->height());
  printf("vpage0sv->width()=%d\n", vpage0sv->width());
  printf("vpage0sv->viewport()->width()=%d\n", vpage0sv->viewport()->width());
#endif

  vpage0big_box->resize(vpage0sv->width(), vpage0sv->height());


#ifdef DEBUG_loadPanel
  printf("after resize, vpage0big_box->width()=%d\n", vpage0big_box->width());
#endif

// End: AttachOrLoad page

// ----------------------------------------------------------
// Begin: Load Page ///  Page 2 of Load/Attach Wizard -------
// ----------------------------------------------------------


  vMPStackPage1 = new QWidget( mainWidgetStack, "vMPStackPage1" );
  vMPStackPage1->setMinimumSize( QSize(100,100) );

  vMPStackPage1Layout = new QVBoxLayout( vMPStackPage1, 11, 6, "vMPStackPage1Layout"); 

  vpage1sv = new QScrollView( vMPStackPage1, "vpage1sv" );

  vpage1big_box = new QVBox( vpage1sv->viewport(), "vpage1big_box" );
  vpage1big_box->setSizePolicy( QSizePolicy( QSizePolicy::Minimum, QSizePolicy::Maximum, 0, 0, FALSE ) );
  vpage1big_box->setPaletteForegroundColor("Dark Green");
  vpage1sv->addChild(vpage1big_box);

  vpage1big_box->setPaletteBackgroundColor("Tan");
  vpage1sv->viewport()->setBackgroundColor("Yellow");

  const QColor vpageColor = vLAPageTitleLabel2->paletteBackgroundColor();
  vpage1sv->viewport()->setBackgroundColor(vpageColor);
  vpage1sv->viewport()->setPaletteBackgroundColor(vpageColor);
  vpage1sv->viewport()->setPaletteBackgroundColor("Light Blue");

  // Line above big_box
  vMPLoadLine = new QFrame( vMPStackPage1, "vMPLoadLine" );
  vMPLoadLine->setMinimumSize( QSize(10,10) );
  vMPLoadLine->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Preferred, 0, 0, FALSE ) );
  vMPLoadLine->setFrameShape( QFrame::HLine );
  vMPLoadLine->setFrameShadow( QFrame::Sunken );
  vMPStackPage1Layout->addWidget( vMPLoadLine );

  // Create a MPI job command ... header label
  vMPLoadTitleLabel1 = new QLabel( vpage1big_box, "vMPLoadTitleLabel1" );
  vMPLoadTitleLabel1->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );


  // Create the parallel execution extra widget entities - parallel execution prefix label and text entry form  
  // Step 1: Enter MPI .... text for this label
  vMPLoadParallelPrefixLabel = new QLabel( vpage1big_box, "vMPLoadParallelPrefixLabel" );
  vMPLoadParallelPrefixLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );
  vMPLoadParallelPrefixLineedit = new QLineEdit( vpage1big_box );

  // Add the parallel execution text entry and label to the dialog form.
  vMPLoadPageLoadLabel = new QLabel( vpage1big_box, "vMPLoadPageLoadLabel");

  vMPLoadPageLoadButton = new QPushButton( vpage1big_box, "vMPLoadPageLoadButton");
  vMPLoadPageLoadButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageLoadButton->sizePolicy().hasHeightForWidth() ) );

  vMPLoadMPILoadLineedit = new QLineEdit( vpage1big_box );
  vMPLoadMPILoadLineedit->setMinimumSize( QSize(10,10) );
  vMPLoadMPILoadLineedit->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );
  vMPLoadMPILoadLineedit->setReadOnly(TRUE);

  // Add the parallel execution text entry and label to the dialog form.

  // Create the first extra widget entity - command line agrument label and text entry form
  vMPLoadCommandArgumentsLabel = new QLabel(vpage1big_box, "vMPLoadCommandArgumentsLabel" );
  vMPLoadCommandArgumentsLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );

  vMPLoadPageArgBrowseButton = new QPushButton( vpage1big_box, "vMPLoadPageArgBrowseButton");
  vMPLoadPageArgBrowseButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageArgBrowseButton->sizePolicy().hasHeightForWidth() ) );

  vMPLoadCommandArgumentsLineedit = new QLineEdit( vpage1big_box );

  // Add the entities to the dialog form

  vMPLoadPageShowLayout = new QHBoxLayout( 0, 0, 6, "vMPLoadPageShowLayout"); 

  //  Show the command 
  vMPLoadMPIShowCommandLabel = new QLabel( vpage1big_box, "vMPLoadMPIShowCommandLabel" );
  vMPLoadMPIShowCommandLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );

  vMPLoadPageShowButton = new QPushButton( vpage1big_box, "vMPLoadPageShowButton");
  vMPLoadPageShowButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageShowButton->sizePolicy().hasHeightForWidth() ) );

  const QColor vpage0color = vMPStackPage1->paletteBackgroundColor();

  vMPLoadMPICommandLineedit = new QLineEdit( vpage1big_box );
  vMPLoadMPICommandLineedit->setReadOnly(TRUE);
  vMPLoadMPICommandLineedit->setBackgroundColor(vpage0color);
  vMPLoadMPICommandLineedit->setPaletteBackgroundColor(vpage0color);
  vMPLoadMPICommandLineedit->setMinimumSize( QSize(10,10) );
  vMPLoadMPICommandLineedit->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );

  vMPLoadMPIAcceptCommandLabel = new QLabel( vpage1big_box, "vMPLoadMPIAcceptCommandLabel" );
  vMPLoadMPIAcceptCommandLabel->setSizePolicy( QSizePolicy( QSizePolicy::Expanding, QSizePolicy::Minimum, 0, 0, FALSE ) );

  vMPStackPage1Layout->addWidget( vpage1sv);

  vMPLoadLine1 = new QFrame( vMPStackPage1, "vMPLoadLine1" );
  vMPLoadLine1->setMinimumSize( QSize(10,10) );
  vMPLoadLine1->setFrameShape( QFrame::HLine );
  vMPLoadLine1->setFrameShadow( QFrame::Sunken );
  vMPStackPage1Layout->addWidget( vMPLoadLine1 );

  vMPLoadSpacer = new QSpacerItem( 20, 30, QSizePolicy::Expanding, QSizePolicy::Expanding );
  vMPStackPage1Layout->addItem( vMPLoadSpacer );

  vMPLoadButtonLayout = new QHBoxLayout( 0, 0, 6, "vMPLoadButtonLayout"); 

  vMPLoadButtonSpacer = new QSpacerItem( 251, 1, QSizePolicy::Expanding, QSizePolicy::Minimum );
  vMPLoadButtonLayout->addItem( vMPLoadButtonSpacer );

  vMPLoadPageClearButton = new QPushButton( vMPStackPage1, "vMPLoadPageClearButton" );
  vMPLoadPageClearButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageClearButton->sizePolicy().hasHeightForWidth() ) );
  vMPLoadButtonLayout->addWidget( vMPLoadPageClearButton );

  vMPLoadPageBackButton = new QPushButton( vMPStackPage1, "vMPLoadPageBackButton" );
  vMPLoadPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageBackButton->sizePolicy().hasHeightForWidth() ) );
  vMPLoadButtonLayout->addWidget( vMPLoadPageBackButton );

#ifdef MPNEXTBUTTON
  vMPLoadPageNextButton = new QPushButton( vMPStackPage1, "vMPLoadPageNextButton" );
  vMPLoadPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageNextButton->sizePolicy().hasHeightForWidth() ) );
  vMPLoadButtonLayout->addWidget( vMPLoadPageNextButton );
#endif

  vMPLoadPageFinishButton = new QPushButton( vMPStackPage1, "vMPLoadPageFinishButton" );
  vMPLoadPageFinishButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vMPLoadPageFinishButton->sizePolicy().hasHeightForWidth() ) );
  vMPLoadButtonLayout->addWidget( vMPLoadPageFinishButton );

  vMPStackPage1Layout->addLayout( vMPLoadButtonLayout );
  mainWidgetStack->addWidget( vMPStackPage1, 1 );

  mainFrameLayout->addWidget( mainWidgetStack );
  loadPanelFormLayout->addWidget( mainFrame );
//  vpage1big_box->adjustSize();

#ifdef DEBUG_loadPanel
  printf("vpage1big_box->width()=%d\n", vpage1big_box->width());
  printf("vpage1sv->height()=%d\n", vpage1sv->height());
  printf("vpage1sv->width()=%d\n", vpage1sv->width());
  printf("vpage1sv->viewport()->width()=%d\n", vpage1sv->viewport()->width());
#endif


  vpage1big_box->resize(vpage1sv->width(), vpage1sv->height());


#ifdef DEBUG_loadPanel
  printf("after resize, vpage1big_box->width()=%d\n", vpage1big_box->width());
#endif

// End: AttachOrLoad page
// -- --- End New attach load page

  languageChange();
  resize( QSize(631, 508).expandedTo(minimumSizeHint()) );
  clearWState( WState_Polished );

  connect( vAttachOrLoadPageBackButton, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageBackButtonSelected() ) );
  connect( vAttachOrLoadPageClearButton, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageClearButtonSelected() ) );

  connect( vAttachOrLoadPageAttachToMultiProcessCheckBox, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageAttachToMultiProcessCheckBoxSelected() ) );

  connect( vAttachOrLoadPageLoadMultiProcessExecutableCheckBox, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageLoadMultiProcessExecutableCheckBoxSelected() ) );

  connect( vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox,
           SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBoxSelected() ) );

  connect( vAttachOrLoadPageAttachToProcessCheckBox, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageAttachToProcessCheckBoxSelected() ) );

  connect( vAttachOrLoadPageLoadExecutableCheckBox, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageLoadExecutableCheckBoxSelected() ) );

  connect( vAttachOrLoadPageLoadDifferentExecutableCheckBox,
           SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageLoadDifferentExecutableCheckBoxSelected() ) );

  connect( vAttachOrLoadPageNextButton, SIGNAL( clicked() ), this,
           SLOT( vAttachOrLoadPageNextButtonSelected() ) );

  connect( vAttachOrLoadPageFinishButton, SIGNAL( clicked() ), this,
           SLOT( finishButtonSelected() ) );

  connect( vMPLoadPageBackButton, SIGNAL( clicked() ), this,
           SLOT( vMPLoadPageBackButtonSelected() ) );

  connect( vMPLoadPageClearButton, SIGNAL( clicked() ), this,
           SLOT( vMPLoadPageClearButtonSelected() ) );

  connect( vMPLoadPageFinishButton, SIGNAL( clicked() ), this,
           SLOT( finishButtonSelected() ) );

  connect( vMPLoadPageLoadButton, SIGNAL( clicked() ), this,
           SLOT( vMPLoadPageLoadButtonSelected() ) );

  connect( vMPLoadPageShowButton, SIGNAL( clicked() ), this,
           SLOT( vMPLoadPageShowButtonSelected() ) );

  connect( vMPLoadPageArgBrowseButton, SIGNAL( clicked() ), this,
           SLOT( vMPLoadPageArgBrowseSelected() ) );

  if( ao && ao->int_data == 0 )
  {
    // This wizard panel was brought up explicitly.   Don't
    // enable the hook to go back to the IntroWizardPanel.
    vAttachOrLoadPageBackButton->setEnabled(FALSE);
  }



  // Set up the first "wizard" page for the load
  // Initializes everything
  vUpdateAttachOrLoadPageWidget();

  mainWidgetStack->raiseWidget(vALStackPage0);
  getBaseWidgetFrame()->setCaption("loadPanelBaseWidget");

#ifdef DEBUG_loadPanel
  printf("loadPanel::loadPanel(), exited\n");
#endif
}


loadPanel::~loadPanel()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::~loadPanel(), entered\n");
#endif
  // Delete anything you new'd from the constructor.
}

void
loadPanel::languageChange()
{

#ifdef DEBUG_loadPanel
  printf("loadPanel::languageChange(), entered\n");
#endif

  setCaption( tr( "Load Program Panel" ) );

  vAttachOrLoadPageDescriptionLabel->setText( tr( "Open|SpeedShop can attach to an existing running process (or running processes) or load an executable from disk.<br>It can also start a multiprocess job from disk or automatically attach to all the running processes/ranks of a MPI job.<br>Please select the desired action.  Note: A dialog will be posted prompting for the information.</p>") );

  vAttachOrLoadPageAttachToProcessCheckBox->setText( tr( "Attach to one or more already running processes/ranks/threads." ) );
  vAttachOrLoadPageAttachToMultiProcessCheckBox->setText( tr( "Attach to all processes/ranks/threads in an already running multiprocess job (MPI)." ) );
  vAttachOrLoadPageLoadExecutableCheckBox->setText( tr( "Load an executable from disk." ) );
  vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setText( tr( "Start/Run a multi-process executable from disk (MPI)." ) );
  vAttachOrLoadPageLoadDifferentExecutableCheckBox->setText( tr( "Load a different executable from disk." ) );
  vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setText( tr( "Start/Run a different multi-process executable from disk (MPI)." ) );

  vAttachOrLoadPageBackButton->setText( tr( "< Back" ) );
  QToolTip::add( vAttachOrLoadPageBackButton, tr( "Takes you back one page." ) );
  vAttachOrLoadPageClearButton->setText( tr( "Reset" ) );
  QToolTip::add( vAttachOrLoadPageClearButton, tr( "This resets all settings restoring them to system defaults." ) );
  vAttachOrLoadPageNextButton->setText( tr( "> Next" ) );
  QToolTip::add( vAttachOrLoadPageNextButton, tr( "Advance to the next wizard page." ) );
  vAttachOrLoadPageFinishButton->setText( tr( ">> Finish" ) );
  QToolTip::add( vAttachOrLoadPageFinishButton, tr( "Advance to the wizard finish page." ) );


  // Set language specific information here.
  vMPLoadPageBackButton->setText( tr( "< Back" ) );
  QToolTip::add( vMPLoadPageBackButton, tr( "Takes you back one page." ) );
  vMPLoadPageClearButton->setText( tr( "Reset" ) );
  QToolTip::add( vMPLoadPageClearButton, tr( "This resets all settings restoring them to system defaults." ) );
#ifdef MPNEXTBUTTON
  vMPLoadPageNextButton->setText( tr( "> Next" ) );
  QToolTip::add( vMPLoadPageNextButton, tr( "Advance to the next wizard page." ) );
#endif
  vMPLoadPageFinishButton->setText( tr( ">> Finish" ) );
  QToolTip::add( vMPLoadPageFinishButton, tr( "Advance to the wizard finish page." ) );
  vMPLoadParallelPrefixLabel->setText( tr("<b>Step 1:</b> Enter MPI Execution Prefix: (For Example: mpirun -np 64 or srun -N 128 -n 128)") );
  vMPLoadCommandArgumentsLabel->setText( tr("<b>Step 3:</b> Enter MPI program command line arguments: (if not entered in load program dialog) ") );

  vMPLoadMPIShowCommandLabel->setText(tr("<b>Optional Step 4:</b> Review/Show the MPI Command Open|SpeedShop is building:") );
  vMPLoadMPIAcceptCommandLabel->setText(tr("<b>Step 5:</b> When you are ready to accept the MPI Command Open|SpeedShop has built, click on the Next button to go to the Finish page.") );
  vMPLoadPageLoadLabel->setText( tr("<b>Step 2:</b> Select the MPI executable you want to analyze:") );
  vMPLoadPageLoadButton->setText( tr("Browse") );
  vMPLoadPageArgBrowseButton->setText( tr("Browse") );
  QToolTip::add( vMPLoadPageArgBrowseButton, tr( "Raise a dialog box to choose an argument file." ) );
  QToolTip::add( vMPLoadPageLoadButton, tr( "Raise a dialog box to choose the MPI executable to run and analyze." ) );
  vMPLoadPageShowButton->setText( tr("Review") );
  QToolTip::add( vMPLoadPageShowButton, tr( "Review the current MPI command that Open|SpeedShop is building." ) );

  vLAPageTitleLabel1->setText( tr( "<h3>Use O|SS on Sequential/Single Process Code</h3>" ) );
  vLAPageTitleLabel2->setText( tr( "<h3>Use O|SS on MPI Code</h3>" ) );

  vMPLoadTitleLabel1->setText( tr( "<h4>Create a MPI job command including your application selection, by following these steps:</h4>" ) );

#ifdef DEBUG_loadPanel
  printf("loadPanel::languageChanged() , exit\n");
#endif
}

void loadPanel::vAttachOrLoadPageBackButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vAttachOrLoadPageBackButtonSelected() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageBackButtonSelected() \n");
#endif

//  mainWidgetStack->raiseWidget(vParameterPageWidget);
}


void loadPanel::vAttachOrLoadPageClearButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vAttachOrLoadPageClearButtonSelected() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageClearButtonSelected() \n");
#endif

  vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
  vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
  vAttachOrLoadPageLoadExecutableCheckBox->setChecked(TRUE);
  vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
  vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
  vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);

  if( getPanelContainer()->getMainWindow() )
  {
    OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
    if( mw )
    {
      mw->executableName = QString::null;
      mw->pidStr = QString::null;
    }
  }
  vUpdateAttachOrLoadPageWidget();
}

void loadPanel::vAttachOrLoadPageAttachToMultiProcessCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageAttachToMultiProcessCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() ) {
    vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageAttachToProcessCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageAttachToProcessCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() ) {
    vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageLoadExecutableCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageLoadExecutableCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageLoadExecutableCheckBox->isChecked() )
  {
    vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageLoadMultiProcessExecutableCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageLoadMultiProcessExecutableCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() ) {
    vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageLoadDifferentExecutableCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageLoadDifferentExecutableCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() ) {
    vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBoxSelected()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBoxSelected() \n");
#endif
  if( vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() )
  {
    vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadDifferentExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setChecked(FALSE);
    vAttachOrLoadPageAttachToMultiProcessCheckBox->setChecked(FALSE);
  }
}

void loadPanel::vAttachOrLoadPageNextButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vAttachOrLoadPageNextButtonSelected() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected() \n");
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageAttachToProcessCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageAttachToProcessCheckBox->isChecked() );
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageLoadExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadExecutableCheckBox->isChecked() );
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() );
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() );
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() );
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() );
#endif

  char buffer[2048];

  if( !vAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() )
  {
    QString msg = QString("You must either select the option to attach to an \nexisting process or load an executable.  Please select one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }

  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      vAttachOrLoadPageLoadExecutableCheckBox->isChecked() )
  {
    QString msg = QString("From this wizard you can only select to either attach or load.  Please select only one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();

  if( !mw ) {
#ifdef DEBUG_loadPanel
    printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageNextButtonSelected, mw=%d return\n", mw);
#endif
    return;
  } 

  // New MultiProcess duplicate
  if( vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() ) { 

    if( mw->pidStr.isEmpty() ) {
#ifdef DEBUG_loadPanel
      printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageNextButtonSelected, calling attachNewMultiProcess\n");
#endif
      mw->attachNewMultiProcess();
    }

#ifdef DEBUG_loadPanel
    printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), after attachNewMultiProcess, calling vMPLoadPageProcessAccept() \n");
#endif
    vMPLoadPageProcessAccept();

  }

  // Old existing attach
  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() ) {

    if( mw->pidStr.isEmpty() ) {
#ifdef DEBUG_loadPanel
      printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageNextButtonSelected, calling attachNewProcess\n");
#endif
      mw->attachNewProcess();
    }
#ifdef DEBUG_loadPanel
    printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), after attachNewProcess, calling vMPLoadPageProcessAccept() \n");
#endif
    vMPLoadPageProcessAccept();

  }

  // New MultiProcess load duplicate of existing
  if( vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() ||
      vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() ) {

#ifdef DEBUG_loadPanel
    printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), vAttachOrLoadPageNextButtonSelected, want to load multiprocess executable raiseWidget(vMPStackPage1)\n");
#endif
    mainWidgetStack->raiseWidget(vMPStackPage1);

  }

  // Old existing load executable code
  if( vAttachOrLoadPageLoadExecutableCheckBox->isChecked() ||
      vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() ) {

    if( mw->executableName.isEmpty() ||
        vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() ) {
#ifdef DEBUG_loadPanel
      printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), Load the QFile \n");
#endif
      mw->loadNewProgram();
    }

#ifdef DEBUG_loadPanel
    printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), after loadNewProgram, calling vMPLoadPageProcessAccept() \n");
#endif
    vMPLoadPageProcessAccept();

  }

#ifdef DEBUG_loadPanel
  printf("loadPanel::vAttachOrLoadPageNextButtonSelected(), exitted \n");
#endif
}


// End verbose AttachOrLoad callbacks

void loadPanel::vMPLoadPageBackButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageBackButtonSelected() \n");

#ifdef DEBUG_loadPanel
  printf("vMPLoadPageBackButtonSelected(), raise vALStackPage0 \n");
#endif

  mainWidgetStack->raiseWidget(vALStackPage0);
}

void loadPanel::vMPLoadPageAcceptButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageAcceptButtonSelected() \n");

#ifdef DEBUG_loadPanel
  printf("vMPLoadPageAcceptButtonSelected() called TBD\n");
#endif

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( !mw ) {
    return;
  }
  if(!mw->executableName.isEmpty() ) {
    mw->parallelPrefixCommandStr = vMPLoadParallelPrefixLineedit->text().ascii();
  }
  vAttachOrLoadPageNextButtonSelected();

}

void loadPanel::vMPLoadPageShowButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageShowButtonSelected() \n");

#ifdef DEBUG_loadPanel
  printf("vMPLoadPageShowButtonSelected() called\n");
#endif

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( !mw ) {
    return;
  }
  if(!mw->executableName.isEmpty() ) {

#ifdef DEBUG_loadPanel
    printf("vMPLoadPageShowButtonSelected(), mw->executableName.ascii()=%s\n",
            mw->executableName.ascii() );
#endif

  }

  QString allOfIt = QString::null;

  if ( !vMPLoadParallelPrefixLineedit->text().isEmpty() ) {
    allOfIt.append(vMPLoadParallelPrefixLineedit->text().ascii()) ;
    allOfIt.append(" ");
  }

  if ( !vMPLoadPageLoadMPProgName.isEmpty() ) {
    allOfIt.append(vMPLoadPageLoadMPProgName.ascii() );
    allOfIt.append(" ");
  }

  if (!vMPLoadCommandArgumentsLineedit->text().isEmpty()) {
    allOfIt.append(vMPLoadCommandArgumentsLineedit->text().ascii());
    allOfIt.append(" ");
  }

  vMPLoadMPICommandLineedit->setText( allOfIt.ascii() );

//  vMPLoadMPICommandLineedit->setText(vMPLoadParallelPrefixLineedit->text());
#ifdef DEBUG_loadPanel
  printf("vMPLoadPageShowButtonSelected(), vMPLoadParallelPrefixLineedit->text()=%s\n",
          vMPLoadParallelPrefixLineedit->text().ascii() );
#endif
//  vMPLoadMPICommandLineedit->setText(vMPLoadPageLoadMPProgName.ascii());
#ifdef DEBUG_loadPanel
  printf("vMPLoadPageShowButtonSelected(), vMPLoadPageLoadMPProgName.ascii()=%s\n",
          vMPLoadPageLoadMPProgName.ascii() );
#endif
//  vMPLoadMPICommandLineedit->setText(vMPLoadCommandArgumentsLineedit->text());
#ifdef DEBUG_loadPanel
  printf("vMPLoadPageShowButtonSelected(), vMPLoadCommandArgumentsLineedit->text()=%s\n",
          vMPLoadCommandArgumentsLineedit->text().ascii() );
#endif


}

void loadPanel::vMPLoadPageLoadButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageLoadButtonSelected() \n");

#ifdef DEBUG_loadPanel
  printf("vMPLoadPageLoadButtonSelected() called TBD\n");
#endif

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( !mw ) {
    return;
  }
  mw->loadNewProgram();

  if( mw->executableName.isEmpty() ) {
     // Fix me
     return;
  } else {

#ifdef DEBUG_loadPanel
   printf("vMPLoadPageLoadButtonSelected(), mw->executableName.ascii()=%s\n", mw->executableName.ascii() );
#endif

   vMPLoadPageLoadMPProgName = mw->executableName.ascii();
   vMPLoadMPILoadLineedit->setText(mw->executableName.ascii());

  } // end else clause

}

void loadPanel::vMPLoadPageArgBrowseSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageArgBrowseSelected() \n");
#ifdef DEBUG_loadPanel
  printf("vMPLoadPageArgBrowseSelected() called TBD\n");
#endif

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( !mw ) {
    return;
  }
  mw->loadArgumentFile();

  if( mw->ArgFileName.isEmpty() ) {
     // Fix me
     return;
  } else {
    vMPLoadCommandArgumentsLineedit->setText( mw->ArgFileName.ascii() );;
  }
}


void loadPanel::vMPLoadPageClearButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vMPLoadPageClearButtonSelected(), setting values in window to NULL \n");

#ifdef DEBUG_loadPanel
  printf("vMPLoadPageClearButtonSelected() called setting values in window to NULL\n");

  printf("loadPanel::vMPLoadPageClearButtonSelected(), vMPLoadParallelPrefixLineedit->text()=%s\n",
          vMPLoadParallelPrefixLineedit->text().ascii() );
  printf("loadPanel::vMPLoadPageClearButtonSelected(), vMPLoadPageLoadMPProgName.ascii()=%s\n",
          vMPLoadPageLoadMPProgName.ascii() );
  printf("loadPanel::vMPLoadPageClearButtonSelected(), vMPLoadCommandArgumentsLineedit->text()=%s\n",
          vMPLoadCommandArgumentsLineedit->text().ascii() );
#endif

  vMPLoadPageLoadMPProgName = QString::null;
  vMPLoadMPILoadLineedit->setText("");
  vMPLoadCommandArgumentsLineedit->setText("");;
  vMPLoadParallelPrefixLineedit->setText("");
  vMPLoadMPICommandLineedit->setText("");;

}

void
loadPanel::vUpdateAttachOrLoadPageWidget()
{
#ifdef DEBUG_loadPanel
  printf("loadPanel::vUpdateAttachOrLoadPageWidget() entered\n");
#endif

  vAttachOrLoadPageProcessListLabel->hide();
  vAttachOrLoadPageMultiProcessListLabel->hide();
  vAttachOrLoadPageExecutableLabel->hide();
  vAttachOrLoadPageMultiProcessExecutableLabel->hide();
  if( getPanelContainer()->getMainWindow() )
  {
    OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
    if( mw )
    {
      if( !mw->executableName.isEmpty() )
      {
        vAttachOrLoadPageAttachToProcessCheckBox->setChecked(FALSE);
        vAttachOrLoadPageLoadExecutableCheckBox->setChecked(TRUE);
        vAttachOrLoadPageExecutableLabel->setText( mw->executableName );
        vAttachOrLoadPageMultiProcessExecutableLabel->setText( mw->executableName );
        vAttachOrLoadPageLoadExecutableCheckBox->setText( tr( "Load the following executable from disk." ) );
        vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->setText( tr( "Start/Run the following multi-process executable from disk (MPI)." ) );
        vAttachOrLoadPageExecutableLabel->show();
        vAttachOrLoadPageMultiProcessExecutableLabel->show();
        vAttachOrLoadPageLoadDifferentExecutableCheckBox->show();
        vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->show();
      } else if( !mw->pidStr.isEmpty() )
      {
        vAttachOrLoadPageAttachToProcessCheckBox->setChecked(TRUE);
        vAttachOrLoadPageLoadExecutableCheckBox->setChecked(FALSE);
        vAttachOrLoadPageProcessListLabel->setText( mw->pidStr );
        vAttachOrLoadPageLoadExecutableCheckBox->setText( tr( "Load an executable from disk." ) );
        vAttachOrLoadPageProcessListLabel->show();
        vAttachOrLoadPageLoadDifferentExecutableCheckBox->hide();
      }
    }
    if( mw->executableName.isEmpty() )
    {
      vAttachOrLoadPageExecutableLabel->setText( "" );
      vAttachOrLoadPageLoadDifferentExecutableCheckBox->hide();
      vAttachOrLoadPageMultiProcessExecutableLabel->setText( "" );
      vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->hide();
    }
    if( mw->pidStr.isEmpty() )
    {
      vAttachOrLoadPageProcessListLabel->setText( mw->pidStr );
      vAttachOrLoadPageMultiProcessListLabel->setText( mw->pidStr );
    }
  }
}

void loadPanel::vMPLoadPageProcessAccept()

{
  nprintf(DEBUG_PANELS) ("vMPLoadPageProcessAccept() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::vMPLoadPageProcessAccept() \n");
#endif

  char buffer[2048];

  if( !vAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() &&
      !vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() )
  {
    QString msg = QString("You must either select the option to attach to an \nexisting process or load an executable.  Please select one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }

#ifdef DEBUG_loadPanel
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageAttachToProcessCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageAttachToProcessCheckBox->isChecked() );
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageLoadExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadExecutableCheckBox->isChecked() );
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() );
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() );
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() );
  printf("loadPanel::vMPLoadPageProcessAccept(), vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked()=%d \n",
         vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() );
#endif

  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      vAttachOrLoadPageLoadExecutableCheckBox->isChecked() )
  {
    QString msg = QString("From this wizard you can only select to either attach or load.  Please select only one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }
  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( !mw ) {
    return;
  } 


  // New MultiProcess duplicate
  if( vAttachOrLoadPageAttachToMultiProcessCheckBox->isChecked() ) { 

    if( mw->pidStr.isEmpty() ) {
      mw->attachNewMultiProcess();
    }

    if( mw->pidStr.isEmpty() ) {
      return;
    } else {
      vSummaryPageFinishButtonSelected();
    }

  }

  // Old existing attach
  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() ) { 

    if( mw->pidStr.isEmpty() ) {
      mw->attachNewProcess();
    }

    if( mw->pidStr.isEmpty() ) {
      return;
    } else {
      vSummaryPageFinishButtonSelected();
    }

#if 0

    QString host_name = mw->pidStr.section(' ', 0, 0, QString::SectionSkipEmpty);
    QString pid_name = mw->pidStr.section(' ', 1, 1, QString::SectionSkipEmpty);
    QString prog_name = mw->pidStr.section(' ', 2, 2, QString::SectionSkipEmpty);

    sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for process \"%s\" running on host \"%s\".  Furthermore, you've chosen a sampling rate of \"%s\".<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>After selecting the \"Finish\" button an experiment \"loadPanel\" panel will be raised to allow you to futher control the experiment, or click the \"RUN\" button to run the experiment as created by the wizard process.<br><br>Press the \"Back\" button to go back to the previous page.</p>", mw->pidStr.ascii(), mw->hostStr.ascii(), /* vParameterPageSampleRateText->text().ascii() */ "dummyRate");
#endif

  }

  // New MultiProcess load duplicate of existing
  if( vAttachOrLoadPageLoadMultiProcessExecutableCheckBox->isChecked() ||
      vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() ) {

    if( mw->executableName.isEmpty() ||
        vAttachOrLoadPageLoadDifferentMultiProcessExecutableCheckBox->isChecked() ) {

      nprintf(DEBUG_PANELS) ("Load the QFile \n");
      mainWidgetStack->raiseWidget(vMPStackPage1);
//      mw->loadNewMultiProcessProgram();

    }
    vSummaryPageFinishButtonSelected();

// Won't get here anymore because this handled by vMPStackPage1 logic
#if 0
    if( mw->executableName.isEmpty() ) {
      return;
    }

    QString host_name = mw->pidStr.section(' ', 0, 0, QString::SectionSkipEmpty);
    QString pid_name = mw->pidStr.section(' ', 1, 1, QString::SectionSkipEmpty);
    QString prog_name = mw->pidStr.section(' ', 2, 2, QString::SectionSkipEmpty);

    if( mw->parallelPrefixCommandStr.isEmpty() || mw->parallelPrefixCommandStr.isNull() ) {
        sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for command/executable \"%s\" to be run on host \"%s\".  Furthermore, you've chosen a sampling rate of \"%s\".<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>After selecting the \"Finish\" button an experiment \"loadPanel\" panel will be raised to allow you to futher control the experiment, or click the \"RUN\" button to run the experiment as created by the wizard process.<br><br>Press the \"Back\" button to go back to the previous page.</p>", mw->executableName.ascii(), mw->hostStr.ascii(), /* vParameterPageSampleRateText->text().ascii() */ "dummyRate" );
    } else {
        sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for command/executable <br>\"%s %s\" to be run on host<br>\"%s\".  Furthermore, you've chosen a sampling rate of \"%s\".<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>After selecting the \"Finish\" button an experiment \"loadPanel\" panel will be raised to allow you to futher control the experiment, or click the \"RUN\" button to run the experiment as created by the wizard process.<br><br>Press the \"Back\" button to go back to the previous page.</p>", mw->parallelPrefixCommandStr.ascii(), mw->executableName.ascii(), mw->hostStr.ascii(), /* vParameterPageSampleRateText->text().ascii()  */ "dummyRate");
    }
#endif

  }

  // Old existing load executable code
  if( vAttachOrLoadPageLoadExecutableCheckBox->isChecked() ||
      vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() ) {

    if( mw->executableName.isEmpty() ||
        vAttachOrLoadPageLoadDifferentExecutableCheckBox->isChecked() ) {
      nprintf(DEBUG_PANELS) ("Load the QFile \n");
      mw->loadNewProgram();
    }

    if( mw->executableName.isEmpty() ) {
      return;
    } else {
      vSummaryPageFinishButtonSelected();
    }

    // RAISE THE WIZARD SUMMARY PAGE INSTEAD
#if 0
    QString host_name = mw->pidStr.section(' ', 0, 0, QString::SectionSkipEmpty);
    QString pid_name = mw->pidStr.section(' ', 1, 1, QString::SectionSkipEmpty);
    QString prog_name = mw->pidStr.section(' ', 2, 2, QString::SectionSkipEmpty);
    if( mw->parallelPrefixCommandStr.isEmpty() || mw->parallelPrefixCommandStr.isNull() ) {
        sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for command/executable \"%s\" to be run on host<br>\"%s\".  Furthermore, you've chosen a sampling rate of \"%s\".<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>After selecting the \"Finish\" button an experiment \"loadPanel\" panel will be raised to allow you to futher control the experiment, or click the \"RUN\" button to run the experiment as created by the wizard process.<br><br>Press the \"Back\" button to go back to the previous page.</p>", mw->executableName.ascii(), mw->hostStr.ascii(), /* vParameterPageSampleRateText->text().ascii() */ "dummyRate" );
    } else {
        sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for command/executable <br>\"%s %s\" to be run on host<br>\"%s\".  Furthermore, you've chosen a sampling rate of \"%s\".<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>After selecting the \"Finish\" button an experiment \"loadPanel\" panel will be raised to allow you to futher control the experiment, or click the \"RUN\" button to run the experiment as created by the wizard process.<br><br>Press the \"Back\" button to go back to the previous page.</p>", mw->parallelPrefixCommandStr.ascii(), mw->executableName.ascii(), mw->hostStr.ascii(), /*  vParameterPageSampleRateText->text().ascii()*/ "dummyRate"  );
    }
#endif
  }

//  vSummaryPageFinishLabel->setText( tr( buffer ) );
//  mainWidgetStack->raiseWidget(2);

//  mainWidgetStack->raiseWidget(vSummaryPageWidget);
#ifdef DEBUG_loadPanel
  printf("loadPanel::vMPLoadPageProcessAccept() EXITED \n");
#endif

}

void loadPanel::finishButtonSelected()
{
  nprintf(DEBUG_PANELS) ("loadPanel::finishButtonSelected() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::finishButtonSelected() \n");
#endif

  OpenSpeedshop *mw = getPanelContainer()->getMainWindow();
  if( mw->executableName.isEmpty() && mw->pidStr.isEmpty() )
  {
      mainWidgetStack->raiseWidget(vALStackPage0);
#ifdef DEBUG_loadPanel
      printf("loadPanel::finishButtonSelected(),after raising mainWidgetStack->raiseWidget(vALStackPage0);\n" );
#endif
      vUpdateAttachOrLoadPageWidget();
#ifdef DEBUG_loadPanel
      printf("loadPanel::finishButtonSelected(),after vUpdateAttachOrLoadPageWidget()\n" );
#endif
      vAttachOrLoadPageNextButtonSelected();
#ifdef DEBUG_loadPanel
      printf("loadPanel::finishButtonSelected(),after vAttachOrLoadPageNextButtonSelected()\n" );
#endif
      vSummaryPageFinishButtonSelected();
#ifdef DEBUG_loadPanel
      printf("loadPanel::finishButtonSelected(),after vSummaryPageFinishButtonSelected()\n" );
#endif
  } else {

    if(mw && !vMPLoadParallelPrefixLineedit->text().isEmpty() ) {
      mw->parallelPrefixCommandStr = vMPLoadParallelPrefixLineedit->text().ascii();
    }

    if(mw && !vMPLoadMPILoadLineedit->text().isEmpty() ) {
      mw->executableName = vMPLoadMPILoadLineedit->text().ascii();
    }
#ifdef DEBUG_loadPanel
    printf("loadPanel::finishButtonSelected(),else clause call vSummaryPageFinishButtonSelected()\n" );
#endif
    vSummaryPageFinishButtonSelected();
  }
}

void loadPanel::vSummaryPageFinishButtonSelected()
{
  nprintf(DEBUG_PANELS) ("vSummaryPageFinishButtonSelected() \n");
#ifdef DEBUG_loadPanel
  printf("loadPanel::vSummaryPageFinishButtonSelected() \n");
#endif

  Panel *p = targetPanel;

#ifdef DEBUG_loadPanel
  printf("loadPanel::vSummaryPageFinishButtonSelected(), targetPanels name is: p->getName()=%s\n", p->getName() );
#endif

  if( getPanelContainer()->getMainWindow() ) {

    OpenSpeedshop *mw = getPanelContainer()->getMainWindow();

    if( mw ) {

      LoadAttachObject *lao = NULL;
      ParamList *paramList = new ParamList();
//      paramList->push_back(vParameterPageSampleRateText->text() );
// printf("loadPanel::vSummaryPageFinishButtonSelected(), A: push_back (%s)\n", vParameterPageSampleRateText->text().ascii() );

      if( !mw->executableName.isEmpty() ) {

#ifdef DEBUG_loadPanel
        printf("loadPanel::vSummaryPageFinishButtonSelected(), executable name was specified as: %s\n", mw->executableName.ascii());
        printf("loadPanel::vSummaryPageFinishButtonSelected(), parallelPrefix was specified as: %s\n", mw->parallelPrefixCommandStr.ascii());
#endif

        lao = new LoadAttachObject(mw->executableName, (char *)NULL, mw->parallelPrefixCommandStr, paramList, TRUE);

      } else if( !mw->pidStr.isEmpty() ) {

#ifdef DEBUG_loadPanel
        printf("loadPanel::vSummaryPageFinishButtonSelected(), pid was specified as: %s\n", mw->pidStr.ascii() );
#endif
        lao = new LoadAttachObject((char *)NULL, mw->pidStr, (char *)NULL, paramList, TRUE);

      } else {

#ifdef DEBUG_loadPanel
        printf("loadPanel::vSummaryPageFinishButtonSelected(), Warning: No attach or load paramaters available.\n");
#endif

      }

      if( lao != NULL ) {
//        vSummaryPageFinishButton->setEnabled(FALSE);
//        vSummaryPageBackButton->setEnabled(FALSE);
        qApp->flushX();

        if( !p ) {

#ifdef DEBUG_loadPanel
          printf("loadPanel::vSummaryPageFinishButtonSelected p is empty need to create\n");
#endif
          ArgumentObject *ao = new ArgumentObject("ArgumentObject", -1 );
          ao->lao = lao;
          p = getPanelContainer()->getMasterPC()->dl_create_and_add_panel(targetPanel->getName(), getPanelContainer(), ao);
          delete ao;

        } else {
#ifdef DEBUG_loadPanel
          printf("loadPanel::vSummaryPageFinishButtonSelected calling p->listener with lao\n");
          printf("loadPanel::vSummaryPageFinishButtonSelected calling p->listener with Wizard_Raise_Summary_Page msg\n");
#endif
          p->listener((void *)lao);
          MessageObject *msg = new MessageObject("Wizard_Raise_Summary_Page");
          p->listener((void *)msg);
          delete msg;
       }

//        getPanelContainer()->hidePanel((Panel *)this);
// The receiving routine should delete this...
// delete paramList;
      } // (lao != NULL)
    } // (mw)
  } // (getPanelContainer)

}



/*! This calls the user 'menu()' function
    if the user provides one.   The user can attach any specific panel
    menus to the passed argument and they will be displayed on a right
    mouse down in the panel.
    /param  contextMenu is the QPopupMenu * that use menus can be attached.
 */
bool
loadPanel::menu(QPopupMenu* contextMenu)
{
  return( FALSE );
}

/*! If the user panel save functionality, their function
     should provide the saving.
 */
void 
loadPanel::save()
{
}

/*! If the user panel provides save to functionality, their function
     should provide the saving.  This callback will invoke a popup prompting
     for a file name.
 */
void 
loadPanel::saveAs()
{
}

/*! This function listens for messages.
    When a message has been sent (from anyone) and the message broker is
    notifying panels that they may want to know about the message, this is the
    function the broker notifies.   The listener then needs to determine
    if it wants to handle the message.
    \param msg is the incoming message.
    \return 0 means you didn't do anything with the message.
    \return 1 means you handled the message.
 */
int
loadPanel::listener(void *msg)
{
  nprintf(DEBUG_PANELS) ("loadPanel::listener() requested.\n");
  MessageObject *messageObject = (MessageObject *)msg;

#ifdef DEBUG_loadPanel
  printf("loadPanel::listener() messageObject->msgType = %s\n", messageObject->msgType.ascii() );
#endif
  if( messageObject->msgType == getName() )
  {
//    vSummaryPageFinishButton->setEnabled(TRUE);
//    eSummaryPageFinishButton->setEnabled(TRUE);
//    vSummaryPageBackButton->setEnabled(TRUE);
//    eSummaryPageBackButton->setEnabled(TRUE);
    vMPLoadPageFinishButton->setEnabled(TRUE);
    qApp->flushX();
    return 1;
  }
  if( messageObject->msgType == "Wizard_Raise_First_Page" )
  {
//    vSummaryPageFinishButton->setEnabled(TRUE);
//    eSummaryPageFinishButton->setEnabled(TRUE);
//    vSummaryPageBackButton->setEnabled(TRUE);
//    eSummaryPageBackButton->setEnabled(TRUE);
    qApp->flushX();
    {
      mainWidgetStack->raiseWidget(vALStackPage0);
    } 
    return 1;
  }
  if( messageObject->msgType == "Wizard_Raise_Second_Page" )
  {
//    vSummaryPageFinishButton->setEnabled(TRUE);
//    eSummaryPageFinishButton->setEnabled(TRUE);
//    vSummaryPageBackButton->setEnabled(TRUE);
//    eSummaryPageBackButton->setEnabled(TRUE);
    qApp->flushX();
    mainWidgetStack->raiseWidget(vMPStackPage1);
    return 1;
  }
  if( messageObject->msgType == "Wizard_Hide_First_Page" )
  {
    qApp->flushX();
  }
  if( messageObject->msgType == "Wizard_Hide_Second_Page" )
  {
    qApp->flushX();
  }
  return 0;  // 0 means, did not want this message and did not act on anything.
}

/*! If the user wants to override the Panel::broadcast() functionality, put
    that logic here.  Otherwise, based on the broadcast type, send out the
    message.
 */
int 
loadPanel::broadcast(char *msg)
{
  return 0;
}

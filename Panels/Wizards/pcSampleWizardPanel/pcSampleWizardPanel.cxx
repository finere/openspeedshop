#include "pcSampleWizardPanel.hxx"   // Change this to your new class header file name
#include "PanelContainer.hxx"   // Do not remove
#include "plugin_entry_point.hxx"   // Do not remove
#include "AttachProcessDialog.hxx"

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

#include <qbitmap.h>
#include "rightarrow.xpm"
#include "leftarrow.xpm"


/*!  pcSampleWizardPanel Class
     This class is used by the script mknewpanel to create a new work area
     for the panel creator to design a new panel.


     Autor: Al Stipek (stipek@sgi.com)
 */


/*! The default constructor.   Unused. */
pcSampleWizardPanel::pcSampleWizardPanel()
{ // Unused... Here for completeness...
  nprintf(DEBUG_CONST_DESTRUCT) ("pcSampleWizardPanel::pcSampleWizardPanel() default constructor called\n");
}


/*! Constructs a new UserPanel object */
/*! This is the most often used constructor call.
    \param pc    The panel container the panel will initially be attached.
    \param n     The initial name of the panel container
 */
pcSampleWizardPanel::pcSampleWizardPanel(PanelContainer *pc, const char *n) : Panel(pc, n)
{
  nprintf(DEBUG_CONST_DESTRUCT) ("pcSampleWizardPanel::pcSampleWizardPanel() constructor called\n");
  QHBoxLayout * panelLayout = new QHBoxLayout( getBaseWidgetFrame(), 1, 2, getName() );

    if ( !getName() )
	setName( "pc Sample" );

    QWidget* topWidget = new QWidget( getBaseWidgetFrame(), "topWidget" );
    topLayout = new QVBoxLayout( topWidget, 11, 6, "topLayout"); 

    topFrame = new QFrame( topWidget, "topFrame" );
    topFrame->setFrameShape( QFrame::StyledPanel );
    topFrame->setFrameShadow( QFrame::Raised );
    topFrameLayout = new QVBoxLayout( topFrame, 11, 6, "topFrameLayout"); 

    pcSampleWizardPanelStack = new QWidgetStack( topFrame, "pcSampleWizardPanelStack" );

// Begin: verbose description page
    vDescriptionPageWidget = new QWidget( pcSampleWizardPanelStack, "vDescriptionPageWidget" );
    vDescriptionPageLayout = new QVBoxLayout( vDescriptionPageWidget, 11, 6, "vDescriptionPageLayout"); 

    vDescriptionPageTitleLabel = new QLabel( vDescriptionPageWidget, "vDescriptionPageTitleLabel" );
    vDescriptionPageTitleLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, vDescriptionPageTitleLabel->sizePolicy().hasHeightForWidth() ) );
    vDescriptionPageTitleLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    vDescriptionPageLayout->addWidget( vDescriptionPageTitleLabel );

    vDescriptionPageText = new QTextEdit( vDescriptionPageWidget, "vDescriptionPageText" );
    vDescriptionPageText->setWordWrap( QTextEdit::WidgetWidth );
    vDescriptionPageLayout->addWidget( vDescriptionPageText );

    vDescriptionPageButtonLayout = new QHBoxLayout( 0, 0, 6, "vDescriptionPageButtonLayout"); 

    vDescriptionPageButtonSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    vDescriptionPageButtonLayout->addItem( vDescriptionPageButtonSpacer );
    vDescriptionPageStartButton = new QPushButton( vDescriptionPageWidget, "vDescriptionPageStartButton" );
    vDescriptionPageStartButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vDescriptionPageStartButton->sizePolicy().hasHeightForWidth() ) );
    vDescriptionPageButtonLayout->addWidget( vDescriptionPageStartButton );

    vDescriptionPageNextButton = new QPushButton( vDescriptionPageWidget, "vDescriptionPageNextButton" );
    vDescriptionPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vDescriptionPageNextButton->sizePolicy().hasHeightForWidth() ) );
    vDescriptionPageButtonLayout->addWidget( vDescriptionPageNextButton );
    vDescriptionPageLayout->addLayout( vDescriptionPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( vDescriptionPageWidget, 0 );
// End: verbose description page

// Begin: verbose parameter page
    vParameterPageWidget = new QWidget( pcSampleWizardPanelStack, "vParameterPageWidget" );
    vParameterPageLayout = new QVBoxLayout( vParameterPageWidget, 11, 6, "vParameterPageLayout"); 

    vParameterPageDescriptionLabel = new QLabel( vParameterPageWidget, "vParameterPageDescriptionLabel" );
    vParameterPageDescriptionLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, vParameterPageDescriptionLabel->sizePolicy().hasHeightForWidth() ) );
    vParameterPageLayout->addWidget( vParameterPageDescriptionLabel );

    vParameterPageLine = new QFrame( vParameterPageWidget, "vParameterPageLine" );
    vParameterPageLine->setFrameShape( QFrame::HLine );
    vParameterPageLine->setFrameShadow( QFrame::Sunken );
    vParameterPageLine->setFrameShape( QFrame::HLine );
    vParameterPageLayout->addWidget( vParameterPageLine );

    vParameterPageParameterLayout = new QVBoxLayout( 0, 0, 6, "vParameterPageParameterLayout"); 

    vParameterPageSampleRateHeaderLabel = new QLabel( vParameterPageWidget, "vParameterPageSampleRateHeaderLabel" );
    vParameterPageSampleRateHeaderLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, vParameterPageSampleRateHeaderLabel->sizePolicy().hasHeightForWidth() ) );
    vParameterPageParameterLayout->addWidget( vParameterPageSampleRateHeaderLabel );

    vParameterPageSampleRateLayout = new QHBoxLayout( 0, 0, 6, "vParameterPageSampleRateLayout"); 

    vParameterPageSampleRateLabel = new QLabel( vParameterPageWidget, "vParameterPageSampleRateLabel" );
    vParameterPageSampleRateLayout->addWidget( vParameterPageSampleRateLabel );

    vParameterPageSampleRateText = new QLineEdit( vParameterPageWidget, "vParameterPageSampleRateText" );
    vParameterPageSampleRateLayout->addWidget( vParameterPageSampleRateText );
    vParameterPageParameterLayout->addLayout( vParameterPageSampleRateLayout );
    vParameterPageLayout->addLayout( vParameterPageParameterLayout );
    vParameterPageSpacer = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding );
    vParameterPageLayout->addItem( vParameterPageSpacer );

    vParameterPageButtonLayout = new QHBoxLayout( 0, 0, 6, "vParameterPageButtonLayout"); 

    vParameterPageButtonSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    vParameterPageButtonLayout->addItem( vParameterPageButtonSpacer );
    vParameterPageBackButton = new QPushButton( vParameterPageWidget, "vParameterPageBackButton" );
    vParameterPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vParameterPageBackButton->sizePolicy().hasHeightForWidth() ) );
    vParameterPageButtonLayout->addWidget( vParameterPageBackButton );

    vParameterPageResetButton = new QPushButton( vParameterPageWidget, "vParameterPageResetButton" );
    vParameterPageResetButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vParameterPageResetButton->sizePolicy().hasHeightForWidth() ) );
    vParameterPageButtonLayout->addWidget( vParameterPageResetButton );

    vParameterPageNextButton = new QPushButton( vParameterPageWidget, "vParameterPageNextButton" );
    vParameterPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vParameterPageNextButton->sizePolicy().hasHeightForWidth() ) );
    vParameterPageButtonLayout->addWidget( vParameterPageNextButton );
    vParameterPageLayout->addLayout( vParameterPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( vParameterPageWidget, 1 );
// End: verbose parameter page

// Begin: AttachOrLoad page
    vAttachOrLoadPageWidget = new QWidget( pcSampleWizardPanelStack, "vAttachOrLoadPageWidget" );
    vAttachOrLoadPageLayout = new QVBoxLayout( vAttachOrLoadPageWidget, 11, 6, "vAttachOrLoadPageLayout"); 

    vAttachOrLoadPageDescriptionLabel = new QLabel( vAttachOrLoadPageWidget, "vAttachOrLoadPageDescriptionLabel" );
    vAttachOrLoadPageDescriptionLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, vAttachOrLoadPageDescriptionLabel->sizePolicy().hasHeightForWidth() ) );
    vAttachOrLoadPageLayout->addWidget( vAttachOrLoadPageDescriptionLabel );

    vAttachOrLoadPageLine = new QFrame( vAttachOrLoadPageWidget, "vAttachOrLoadPageLine" );
    vAttachOrLoadPageLine->setFrameShape( QFrame::HLine );
    vAttachOrLoadPageLine->setFrameShadow( QFrame::Sunken );
    vAttachOrLoadPageLine->setFrameShape( QFrame::HLine );
    vAttachOrLoadPageLayout->addWidget( vAttachOrLoadPageLine );

    vAttachOrLoadPageAttachOrLoadLayout = new QVBoxLayout( 0, 0, 6, "vAttachOrLoadPageAttachOrLoadLayout"); 

     vAttachOrLoadPageAttachToProcessCheckBox = new QCheckBox( vAttachOrLoadPageWidget, "vAttachOrLoadPageAttachToProcessCheckBox" );
    vAttachOrLoadPageAttachOrLoadLayout->addWidget( vAttachOrLoadPageAttachToProcessCheckBox );
    vAttachOrLoadPageLoadProcessCheckBox = new QCheckBox( vAttachOrLoadPageWidget, "vAttachOrLoadPageLoadProcessCheckBox" );
    vAttachOrLoadPageAttachOrLoadLayout->addWidget( vAttachOrLoadPageLoadProcessCheckBox );

    vAttachOrLoadPageSampleRateLayout = new QHBoxLayout( 0, 0, 6, "vAttachOrLoadPageSampleRateLayout"); 

    vAttachOrLoadPageLayout->addLayout( vAttachOrLoadPageAttachOrLoadLayout );
    vAttachOrLoadPageSpacer = new QSpacerItem( 20, 30, QSizePolicy::Minimum, QSizePolicy::Expanding );
    vAttachOrLoadPageLayout->addItem( vAttachOrLoadPageSpacer );

    vAttachOrLoadPageButtonLayout = new QHBoxLayout( 0, 0, 6, "vAttachOrLoadPageButtonLayout"); 

    vAttachOrLoadPageButtonSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    vAttachOrLoadPageButtonLayout->addItem( vAttachOrLoadPageButtonSpacer );
    vAttachOrLoadPageBackButton = new QPushButton( vAttachOrLoadPageWidget, "vAttachOrLoadPageBackButton" );
    vAttachOrLoadPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageBackButton->sizePolicy().hasHeightForWidth() ) );
    vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageBackButton );

    vAttachOrLoadPageNextButton = new QPushButton( vAttachOrLoadPageWidget, "vAttachOrLoadPageNextButton" );
    vAttachOrLoadPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vAttachOrLoadPageNextButton->sizePolicy().hasHeightForWidth() ) );
    vAttachOrLoadPageButtonLayout->addWidget( vAttachOrLoadPageNextButton );
    vAttachOrLoadPageLayout->addLayout( vAttachOrLoadPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( vAttachOrLoadPageWidget, 1 );
// End: AttachOrLoad page

// Begin: verbose summary page
    vSummaryPageWidget = new QWidget( pcSampleWizardPanelStack, "vSummaryPageWidget" );
    vSummaryPageLayout = new QVBoxLayout( vSummaryPageWidget, 11, 6, "vSummaryPageLayout"); 

    vSummaryPageLabelLayout = new QVBoxLayout( 0, 0, 6, "vSummaryPageLabelLayout"); 
    vSummaryPageSpacer = new QSpacerItem( 20, 1, QSizePolicy::Minimum, QSizePolicy::Fixed );
    vSummaryPageLabelLayout->addItem( vSummaryPageSpacer );

    vSummaryPageFinishLabel = new QLabel( vSummaryPageWidget, "vSummaryPageFinishLabel" );
    vSummaryPageFinishLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, vSummaryPageFinishLabel->sizePolicy().hasHeightForWidth() ) );
    vSummaryPageLabelLayout->addWidget( vSummaryPageFinishLabel );
    vSummaryPageLayout->addLayout( vSummaryPageLabelLayout );

    vSummaryPageButtonLayout = new QHBoxLayout( 0, 0, 6, "vSummaryPageButtonLayout"); 

    vSummaryPageButtonSpacer = new QSpacerItem( 200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    vSummaryPageButtonLayout->addItem( vSummaryPageButtonSpacer );
    vSummaryPageBackButton = new QPushButton( vSummaryPageWidget, "vSummaryPageBackButton" );
    vSummaryPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vSummaryPageBackButton->sizePolicy().hasHeightForWidth() ) );
    vSummaryPageButtonLayout->addWidget( vSummaryPageBackButton );

    vSummaryPageFinishButton = new QPushButton( vSummaryPageWidget, "vSummaryPageFinishButton" );
    vSummaryPageFinishButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, vSummaryPageFinishButton->sizePolicy().hasHeightForWidth() ) );
    vSummaryPageButtonLayout->addWidget( vSummaryPageFinishButton );
    vSummaryPageLayout->addLayout( vSummaryPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( vSummaryPageWidget, 3 );
// End: verbose summary page

// The advanced (expert) wording starts here....
// Begin: advance (expert) description page
    eDescriptionPageWidget = new QWidget( pcSampleWizardPanelStack, "eDescriptionPageWidget" );
    eDescriptionPageLayout = new QVBoxLayout( eDescriptionPageWidget, 11, 6, "eDescriptionPageLayout"); 

    eDescriptionPageTitleLabel = new QLabel( eDescriptionPageWidget, "eDescriptionPageTitleLabel" );
    eDescriptionPageTitleLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, eDescriptionPageTitleLabel->sizePolicy().hasHeightForWidth() ) );
    eDescriptionPageTitleLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignCenter ) );
    eDescriptionPageLayout->addWidget( eDescriptionPageTitleLabel );

    eDescriptionPageText = new QLabel( eDescriptionPageWidget, "eDescriptionPageText" );
    eDescriptionPageLayout->addWidget( eDescriptionPageText );

    eDescriptionPageButtonLayout = new QHBoxLayout( 0, 0, 6, "eDescriptionPageButtonLayout"); 

    eDescriptionPageSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    eDescriptionPageButtonLayout->addItem( eDescriptionPageSpacer );
    eDescriptionPageStartButton = new QPushButton( eDescriptionPageWidget, "eDescriptionPageStartButton" );
    eDescriptionPageStartButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eDescriptionPageStartButton->sizePolicy().hasHeightForWidth() ) );
    eDescriptionPageButtonLayout->addWidget( eDescriptionPageStartButton );

    eDescriptionPageNextButton = new QPushButton( eDescriptionPageWidget, "eDescriptionPageNextButton" );
    eDescriptionPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eDescriptionPageNextButton->sizePolicy().hasHeightForWidth() ) );
    eDescriptionPageButtonLayout->addWidget( eDescriptionPageNextButton );
    eDescriptionPageLayout->addLayout( eDescriptionPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( eDescriptionPageWidget, 4 );
// End: advance (expert) description page

// Begin: advance (expert) parameter page
    eParameterPageWidget = new QWidget( pcSampleWizardPanelStack, "eParameterPageWidget" );
    eParameterPageLayout = new QVBoxLayout( eParameterPageWidget, 11, 6, "eParameterPageLayout"); 

    eParameterPageDescriptionLabel = new QLabel( eParameterPageWidget, "eParameterPageDescriptionLabel" );
    eParameterPageDescriptionLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, eParameterPageDescriptionLabel->sizePolicy().hasHeightForWidth() ) );
    eParameterPageLayout->addWidget( eParameterPageDescriptionLabel );

    eParameterPageLine = new QFrame( eParameterPageWidget, "eParameterPageLine" );
    eParameterPageLine->setFrameShape( QFrame::HLine );
    eParameterPageLine->setFrameShadow( QFrame::Sunken );
    eParameterPageLine->setFrameShape( QFrame::HLine );
    eParameterPageLayout->addWidget( eParameterPageLine );

    eParameterPageParameterLayout = new QVBoxLayout( 0, 0, 6, "eParameterPageParameterLayout"); 

    eParameterPageSampleRateHeaderLabel = new QLabel( eParameterPageWidget, "eParameterPageSampleRateHeaderLabel" );
    eParameterPageSampleRateHeaderLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)0, 0, 0, eParameterPageSampleRateHeaderLabel->sizePolicy().hasHeightForWidth() ) );
    eParameterPageParameterLayout->addWidget( eParameterPageSampleRateHeaderLabel );

    eParameterPageSampleRateLayout = new QHBoxLayout( 0, 0, 6, "eParameterPageSampleRateLayout"); 

    eParameterPageSampleRateLabel = new QLabel( eParameterPageWidget, "eParameterPageSampleRateLabel" );
    eParameterPageSampleRateLayout->addWidget( eParameterPageSampleRateLabel );

    eParameterPageSampleRateText = new QLineEdit( eParameterPageWidget, "eParameterPageSampleRateText" );
    eParameterPageSampleRateLayout->addWidget( eParameterPageSampleRateText );
    eParameterPageParameterLayout->addLayout( eParameterPageSampleRateLayout );
    eParameterPageLayout->addLayout( eParameterPageParameterLayout );
    eParameterPageSpacer = new QSpacerItem( 20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding );
    eParameterPageLayout->addItem( eParameterPageSpacer );

    eParameterPageButtonLayout = new QHBoxLayout( 0, 0, 6, "eParameterPageButtonLayout"); 

    eParameterPageButtonSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    eParameterPageButtonLayout->addItem( eParameterPageButtonSpacer );
    eParameterPageBackButton = new QPushButton( eParameterPageWidget, "eParameterPageBackButton" );
    eParameterPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eParameterPageBackButton->sizePolicy().hasHeightForWidth() ) );
    eParameterPageButtonLayout->addWidget( eParameterPageBackButton );

    eParameterPageResetButton = new QPushButton( eParameterPageWidget, "eParameterPageResetButton" );
    eParameterPageResetButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eParameterPageResetButton->sizePolicy().hasHeightForWidth() ) );
    eParameterPageButtonLayout->addWidget( eParameterPageResetButton );

    eParameterPageNextButton = new QPushButton( eParameterPageWidget, "eParameterPageNextButton" );
    eParameterPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eParameterPageNextButton->sizePolicy().hasHeightForWidth() ) );
    eParameterPageButtonLayout->addWidget( eParameterPageNextButton );
    eParameterPageLayout->addLayout( eParameterPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( eParameterPageWidget, 5 );
// End: advanced (exper) parameter page


// Begin: advance (expert) attach/load page
    eAttachOrLoadPageWidget = new QWidget( pcSampleWizardPanelStack, "eAttachOrLoadPageWidget" );
    eAttachOrLoadPageLayout = new QVBoxLayout( eAttachOrLoadPageWidget, 11, 6, "eAttachOrLoadPageLayout"); 

    eAttachOrLoadPageDescriptionLabel = new QLabel( eAttachOrLoadPageWidget, "eAttachOrLoadPageDescriptionLabel" );
    eAttachOrLoadPageDescriptionLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, eAttachOrLoadPageDescriptionLabel->sizePolicy().hasHeightForWidth() ) );
    eAttachOrLoadPageLayout->addWidget( eAttachOrLoadPageDescriptionLabel );

    eAttachOrLoadPageLine = new QFrame( eAttachOrLoadPageWidget, "eAttachOrLoadPageLine" );
    eAttachOrLoadPageLine->setFrameShape( QFrame::HLine );
    eAttachOrLoadPageLine->setFrameShadow( QFrame::Sunken );
    eAttachOrLoadPageLine->setFrameShape( QFrame::HLine );
    eAttachOrLoadPageLayout->addWidget( eAttachOrLoadPageLine );

    eAttachOrLoadPageAttachOrLoadLayout = new QVBoxLayout( 0, 0, 6, "eAttachOrLoadPageAttachOrLoadLayout"); 

     eAttachOrLoadPageAttachToProcessCheckBox = new QCheckBox( eAttachOrLoadPageWidget, "eAttachOrLoadPageAttachToProcessCheckBox" );
    eAttachOrLoadPageAttachOrLoadLayout->addWidget( eAttachOrLoadPageAttachToProcessCheckBox );
eAttachOrLoadPageLoadProcessCheckBox = new QCheckBox( eAttachOrLoadPageWidget, "eAttachOrLoadPageLoadProcessCheckBox" );
eAttachOrLoadPageAttachOrLoadLayout->addWidget( eAttachOrLoadPageLoadProcessCheckBox );
    eAttachOrLoadPageLayout->addLayout( eAttachOrLoadPageAttachOrLoadLayout );
    eAttachOrLoadPageSpacer = new QSpacerItem( 20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding );
    eAttachOrLoadPageLayout->addItem( eAttachOrLoadPageSpacer );

    eAttachOrLoadPageButtonLayout = new QHBoxLayout( 0, 0, 6, "eAttachOrLoadPageButtonLayout"); 

    eAttachOrLoadPageButtonSpacer = new QSpacerItem( 251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    eAttachOrLoadPageButtonLayout->addItem( eAttachOrLoadPageButtonSpacer );
    eAttachOrLoadPageBackButton = new QPushButton( eAttachOrLoadPageWidget, "eAttachOrLoadPageBackButton" );
    eAttachOrLoadPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eAttachOrLoadPageBackButton->sizePolicy().hasHeightForWidth() ) );
    eAttachOrLoadPageButtonLayout->addWidget( eAttachOrLoadPageBackButton );

    eAttachOrLoadPageNextButton = new QPushButton( eAttachOrLoadPageWidget, "eAttachOrLoadPageNextButton" );
    eAttachOrLoadPageNextButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eAttachOrLoadPageNextButton->sizePolicy().hasHeightForWidth() ) );
    eAttachOrLoadPageButtonLayout->addWidget( eAttachOrLoadPageNextButton );
    eAttachOrLoadPageLayout->addLayout( eAttachOrLoadPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( eAttachOrLoadPageWidget, 5 );
// End: advanced (expert) attach/load page

// Begin: advance (expert) summary page
    eSummaryPageWidget = new QWidget( pcSampleWizardPanelStack, "eSummaryPageWidget" );
    eSummaryPageLayout = new QVBoxLayout( eSummaryPageWidget, 11, 6, "eSummaryPageLayout"); 

    eSummaryPageFinishLabel = new QLabel( eSummaryPageWidget, "eSummaryPageFinishLabel" );
    eSummaryPageFinishLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)5, (QSizePolicy::SizeType)1, 0, 0, eSummaryPageFinishLabel->sizePolicy().hasHeightForWidth() ) );
    eSummaryPageLayout->addWidget( eSummaryPageFinishLabel );

    eSummaryPageButtonLayout = new QHBoxLayout( 0, 0, 6, "eSummaryPageButtonLayout"); 

    eSummaryPageButtonSpacer = new QSpacerItem( 200, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    eSummaryPageButtonLayout->addItem( eSummaryPageButtonSpacer );
    eSummaryPageBackButton = new QPushButton( eSummaryPageWidget, "eSummaryPageBackButton" );
    eSummaryPageBackButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eSummaryPageBackButton->sizePolicy().hasHeightForWidth() ) );
    eSummaryPageButtonLayout->addWidget( eSummaryPageBackButton );

    eSummaryPageFinishButton = new QPushButton( eSummaryPageWidget, "eSummaryPageFinishButton" );
    eSummaryPageFinishButton->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, eSummaryPageFinishButton->sizePolicy().hasHeightForWidth() ) );
    eSummaryPageButtonLayout->addWidget( eSummaryPageFinishButton );
    eSummaryPageLayout->addLayout( eSummaryPageButtonLayout );
    pcSampleWizardPanelStack->addWidget( eSummaryPageWidget, 7 );
    topFrameLayout->addWidget( pcSampleWizardPanelStack );
    topLayout->addWidget( topFrame );
// End: advance (expert) summary page


// Begin: add the bottom portion: The "wizard mode" and "brought to you by"
    bottomLayout = new QHBoxLayout( 0, 0, 6, "bottomLayout"); 

    wizardMode = new QCheckBox( topWidget, "wizardMode" );
    wizardMode->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, wizardMode->sizePolicy().hasHeightForWidth() ) );
    wizardMode->setChecked( TRUE );
    bottomLayout->addWidget( wizardMode );
    bottomSpacer = new QSpacerItem( 40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum );
    bottomLayout->addItem( bottomSpacer );

    broughtToYouByLabel = new QLabel( topWidget, "broughtToYouByLabel" );
    broughtToYouByLabel->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, broughtToYouByLabel->sizePolicy().hasHeightForWidth() ) );
    bottomLayout->addWidget( broughtToYouByLabel );
// End: add the bottom portion: The "wizard mode" and "brought to you by"

    topLayout->addLayout( bottomLayout );
    languageChange();
    resize( QSize(631, 508).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( eDescriptionPageNextButton, SIGNAL( clicked() ), this, SLOT( eDescriptionPageNextButtonSelected() ) );
    connect( eDescriptionPageStartButton, SIGNAL( clicked() ), this, SLOT( eDescriptionPageStartButtonSelected() ) );
    connect( eParameterPageBackButton, SIGNAL( clicked() ), this, SLOT( eParameterPageBackButtonSelected() ) );
    connect( eParameterPageNextButton, SIGNAL( clicked() ), this, SLOT( eParameterPageNextButtonSelected() ) );
    connect( eParameterPageResetButton, SIGNAL( clicked() ), this, SLOT( eParameterPageResetButtonSelected() ) );
    connect( eParameterPageSampleRateText, SIGNAL( returnPressed() ), this, SLOT( eParameterPageSampleRateTextReturnPressed() ) );

connect( eAttachOrLoadPageBackButton, SIGNAL( clicked() ), this, SLOT( eAttachOrLoadPageBackButtonSelected() ) );
connect( eAttachOrLoadPageNextButton, SIGNAL( clicked() ), this, SLOT( eAttachOrLoadPageNextButtonSelected() ) );

    connect( eSummaryPageBackButton, SIGNAL( clicked() ), this, SLOT( eSummaryPageBackButtonSelected() ) );
    connect( eSummaryPageFinishButton, SIGNAL( clicked() ), this, SLOT( eSummaryPageFinishButtonSelected() ) );
    connect( vDescriptionPageNextButton, SIGNAL( clicked() ), this, SLOT( vDescriptionPageNextButtonSelected() ) );
    connect( vDescriptionPageStartButton, SIGNAL( clicked() ), this, SLOT( vDescriptionPageStartButtonSelected() ) );
    connect( vParameterPageSampleRateText, SIGNAL( returnPressed() ), this, SLOT( vParameterPageSampleRateTextReturnPressed() ) );
    connect( vParameterPageBackButton, SIGNAL( clicked() ), this, SLOT( vParameterPageBackButtonSelected() ) );
    connect( vParameterPageResetButton, SIGNAL( clicked() ), this, SLOT( vParameterPageResetButtonSelected() ) );
    connect( vParameterPageNextButton, SIGNAL( clicked() ), this, SLOT( vParameterPageNextButtonSelected() ) );

connect( vAttachOrLoadPageBackButton, SIGNAL( clicked() ), this, SLOT( vAttachOrLoadPageBackButtonSelected() ) );
connect( vAttachOrLoadPageNextButton, SIGNAL( clicked() ), this, SLOT( vAttachOrLoadPageNextButtonSelected() ) );

    connect( vSummaryPageBackButton, SIGNAL( clicked() ), this, SLOT( vSummaryPageBackButtonSelected() ) );
    connect( vSummaryPageFinishButton, SIGNAL( clicked() ), this, SLOT( vSummaryPageFinishButtonSelected() ) );
    connect( wizardMode, SIGNAL( clicked() ), this, SLOT( wizardModeSelected() ) );

  // This next line makes it all magically appear and resize correctly.
  panelLayout->addWidget(topWidget);
}


//! Destroys the object and frees any allocated resources
/*! The only thing that needs to be cleaned up is the baseWidgetFrame.
 */
pcSampleWizardPanel::~pcSampleWizardPanel()
{
  nprintf(DEBUG_CONST_DESTRUCT) ("  pcSampleWizardPanel::~pcSampleWizardPanel() destructor called\n");
}

//! Add user panel specific menu items if they have any.
bool
pcSampleWizardPanel::menu(QPopupMenu* contextMenu)
{
  nprintf(DEBUG_PANELS) ("pcSampleWizardPanel::menu() requested.\n");

  return( FALSE );
}

//! Save ascii version of this panel.
/*! If the user panel provides save to ascii functionality, their function
     should provide the saving.
 */
void 
pcSampleWizardPanel::save()
{
  nprintf(DEBUG_PANELS) ("pcSampleWizardPanel::save() requested.\n");
}

//! Save ascii version of this panel (to a file).
/*! If the user panel provides save to ascii functionality, their function
     should provide the saving.  This callback will invoke a popup prompting
     for a file name.
 */
void 
pcSampleWizardPanel::saveAs()
{
  nprintf(DEBUG_PANELS) ("pcSampleWizardPanel::saveAs() requested.\n");
}

//! This function listens for messages.
int 
pcSampleWizardPanel::listener(char *msg)
{
  nprintf(DEBUG_PANELS) ("pcSampleWizardPanel::listener() requested.\n");
  return 0;  // 0 means, did not want this message and did not act on anything.
}


//! This function broadcasts messages.
int 
pcSampleWizardPanel::broadcast(char *msg)
{
  nprintf(DEBUG_PANELS) ("pcSampleWizardPanel::broadcast() requested.\n");
  return 0;
}

void pcSampleWizardPanel::wizardModeSelected()
{
  QWidget *raisedWidget = pcSampleWizardPanelStack->visibleWidget();
if( raisedWidget == vDescriptionPageWidget )
{
    nprintf(DEBUG_PANELS) ("vDescriptionPageWidget\n");
} else if( raisedWidget ==  vParameterPageWidget )
{
    nprintf(DEBUG_PANELS) ("vParameterPageWidget\n");
} else if( raisedWidget == vSummaryPageWidget )
{
    nprintf(DEBUG_PANELS) ("vSummaryPageWidget\n");
} else if( raisedWidget  == eDescriptionPageWidget )
{
    nprintf(DEBUG_PANELS) ("eDescriptionPageWidget\n");
} else if( raisedWidget == eParameterPageWidget )
{
    nprintf(DEBUG_PANELS) ("eParameterPageWidget\n");
} else if( raisedWidget == eSummaryPageWidget )
{
    nprintf(DEBUG_PANELS) ("eSummaryPageWidget\n");
}

  if( wizardMode->isOn() )
  {
    if( raisedWidget  == eDescriptionPageWidget )
    {
        nprintf(DEBUG_PANELS) ("eDescriptionPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(vDescriptionPageWidget);
    } else if( raisedWidget == eParameterPageWidget )
    {
        nprintf(DEBUG_PANELS) ("eParameterPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(vParameterPageWidget);
    } else if( raisedWidget == eAttachOrLoadPageWidget )
    {
        nprintf(DEBUG_PANELS) ("eAttachOrLoadPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(vAttachOrLoadPageWidget);
    } else if( raisedWidget == eSummaryPageWidget )
    {
        nprintf(DEBUG_PANELS) ("eSummaryPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(vSummaryPageWidget);
    } else
    {
        nprintf(DEBUG_PANELS) ("Verbose to Expert: unknown WStackPage\n");
    }
  } else
  {
    if( raisedWidget == vDescriptionPageWidget )
    {
        nprintf(DEBUG_PANELS) ("vDescriptionPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(eDescriptionPageWidget);
    } else if( raisedWidget ==  vParameterPageWidget )
    {
        nprintf(DEBUG_PANELS) ("vParameterPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(eParameterPageWidget);
    } else if( raisedWidget ==  vAttachOrLoadPageWidget )
    {
        nprintf(DEBUG_PANELS) ("vAttachOrLoadPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(eAttachOrLoadPageWidget);
    } else if( raisedWidget == vSummaryPageWidget )
    {
        nprintf(DEBUG_PANELS) ("vSummaryPageWidget\n");
        pcSampleWizardPanelStack->raiseWidget(eSummaryPageWidget);
    } else
    {
        nprintf(DEBUG_PANELS) ("Expert to Verbose: unknown WStackPage\n");
    }
  }
}


void pcSampleWizardPanel::eDescriptionPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("eDescriptionPageNextButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(eParameterPageWidget);
}

void pcSampleWizardPanel::eDescriptionPageStartButtonSelected()
{
nprintf(DEBUG_PANELS) ("eDescriptionPageStartButtonSelected() \n");
    Panel *p = getPanelContainer()->raiseNamedPanel("Intro Wizard");
    if( !p )
    {
      getPanelContainer()->_masterPC->dl_create_and_add_panel("Intro Wizard", getPanelContainer());
    }
}

void pcSampleWizardPanel::eParameterPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("eParameterPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(eDescriptionPageWidget);
}

void pcSampleWizardPanel::eParameterPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("eParameterPageNextButtonSelected() \n");

    pcSampleWizardPanelStack->raiseWidget(eAttachOrLoadPageWidget);
}

void pcSampleWizardPanel::eParameterPageResetButtonSelected()
{
nprintf(DEBUG_PANELS) ("eParameterPageResetButtonSelected() \n");
}

void pcSampleWizardPanel::eSummaryPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("eSummaryPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(eAttachOrLoadPageWidget);
}

void pcSampleWizardPanel::eSummaryPageFinishButtonSelected()
{
nprintf(DEBUG_PANELS) ("eSummaryPageFinishButtonSelected() \n");

  Panel *p = getPanelContainer()->_masterPC->dl_create_and_add_panel("pc Sampling", getPanelContainer());
}

// Begin advanced (expert) AttachOrLoad callbacks
void pcSampleWizardPanel::eAttachOrLoadPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("eAttachOrLoadPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(eParameterPageWidget);
}

void pcSampleWizardPanel::eAttachOrLoadPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("eAttachOrLoadPageNextButtonSelected() \n");

char buffer[2048];
  if( !eAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      !eAttachOrLoadPageLoadProcessCheckBox->isChecked() )
  {
    QString msg = QString("You must either select the option to attach to an \nexisting process or load an executable.  Please select one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }
  
  if( eAttachOrLoadPageAttachToProcessCheckBox->isChecked() )
  {
    QString result;
     AttachProcessDialog *dialog = new AttachProcessDialog(this, "AttachProcessDialog", TRUE);
    if( dialog->exec() == QDialog::Accepted )
    {
      result = dialog->selectedProcesses();
sprintf(buffer, "<p align=\"left\">Requesting to load process \"%s\" on host \"%s\",  sampling at \"%s\" milliseconds.<br><br></p>", result.ascii(), "localhost", vParameterPageSampleRateText->text().ascii() );
    }
    delete dialog;
  
    nprintf(DEBUG_PANELS) ("result.acsii()=(%s)\n", result.ascii() );
  }
  if( eAttachOrLoadPageLoadProcessCheckBox->isChecked() )
  {
    nprintf(DEBUG_PANELS) ("Load the QFile \n");
    QString fn = QFileDialog::getOpenFileName( QString::null, QString::null,
                             this);
    if( !fn.isEmpty() )
    {
      nprintf(DEBUG_PANELS) ("fn.ascii()=(%s)\n", fn.ascii() );
sprintf(buffer, "<p align=\"left\">Requesting to load executable \"%s\" on host \"%s\", sampling at \"%s\" milliseconds.<br><br></p>", fn.ascii(), "localhost", eParameterPageSampleRateText->text().ascii() );
    }
  }

  eSummaryPageFinishLabel->setText( tr( buffer ) );

    pcSampleWizardPanelStack->raiseWidget(eSummaryPageWidget);
}
// End  advanced (expert) AttachOrLoad callbacks

void pcSampleWizardPanel::vDescriptionPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("vDescriptionPageNextButtonSelected() \n");

    pcSampleWizardPanelStack->raiseWidget(vParameterPageWidget);
}

void pcSampleWizardPanel::vDescriptionPageStartButtonSelected()
{
nprintf(DEBUG_PANELS) ("vDescriptionPageStartButtonSelected() \n");
    Panel *p = getPanelContainer()->raiseNamedPanel("Intro Wizard");
    if( !p )
    {
      getPanelContainer()->_masterPC->dl_create_and_add_panel("Intro Wizard", getPanelContainer());
    }
}

void pcSampleWizardPanel::vParameterPageSampleRateTextReturnPressed()
{
nprintf(DEBUG_PANELS) ("vParameterPageSampleRateTextReturnPressed() \n");
}

void pcSampleWizardPanel::eParameterPageSampleRateTextReturnPressed()
{
nprintf(DEBUG_PANELS) ("eParameterPageSampleRateTextReturnPressed() \n");
}

void pcSampleWizardPanel::vParameterPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("vParameterPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(vDescriptionPageWidget);
}

void pcSampleWizardPanel::vParameterPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("vParameterPageNextButtonSelected() \n");

    pcSampleWizardPanelStack->raiseWidget(vAttachOrLoadPageWidget);
}

void pcSampleWizardPanel::vParameterPageResetButtonSelected()
{
nprintf(DEBUG_PANELS) ("vParameterPageResetButtonSelected() \n");
}

void pcSampleWizardPanel::vAttachOrLoadPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("vAttachOrLoadPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(vParameterPageWidget);
}

void pcSampleWizardPanel::vAttachOrLoadPageNextButtonSelected()
{
nprintf(DEBUG_PANELS) ("vAttachOrLoadPageNextButtonSelected() \n");

char buffer[2048];
  if( !vAttachOrLoadPageAttachToProcessCheckBox->isChecked() &&
      !vAttachOrLoadPageLoadProcessCheckBox->isChecked() )
  {
    QString msg = QString("You must either select the option to attach to an \nexisting process or load an executable.  Please select one.\n");
    QMessageBox::information( (QWidget *)this, "Process or executable needed...",
                               msg, QMessageBox::Ok );
    
    return;
  }
  
  if( vAttachOrLoadPageAttachToProcessCheckBox->isChecked() )
  {
    QString result;
     AttachProcessDialog *dialog = new AttachProcessDialog(this, "AttachProcessDialog", TRUE);
    if( dialog->exec() == QDialog::Accepted )
    {
      result = dialog->selectedProcesses();
sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for process \"%s\" running on host \"%s\".  Futher you've chosed a sample rate of \"%s\" milliseconds.<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>Upon selection of the \"Finish\" button an experiment \"pcSample\" panel will be raised to allow you to futher control the experiment.<br><br>Press the \"Back\" button to go back to the previous page.</p>", result.ascii(), "localhost", vParameterPageSampleRateText->text().ascii() );
    }
    delete dialog;
  
    nprintf(DEBUG_PANELS) ("result.acsii()=(%s)\n", result.ascii() );
  }
  if( vAttachOrLoadPageLoadProcessCheckBox->isChecked() )
  {
    nprintf(DEBUG_PANELS) ("Load the QFile \n");
    QString fn = QFileDialog::getOpenFileName( QString::null, QString::null,
                             this);
    if( !fn.isEmpty() )
    {
      nprintf(DEBUG_PANELS) ("fn.ascii()=(%s)\n", fn.ascii() );
sprintf(buffer, "<p align=\"left\">You've selected a pc Sample experiment for executable \"%s\" to be run on host \"%s\".  Futher you've chosed a sample rate of \"%s\" milliseconds.<br><br>To complete the experiment setup select the \"Finish\" button.<br><br>Upon selection of the \"Finish\" button an experiment \"pcSample\" panel will be raised to allow you to futher control the experiment.<br><br>Press the \"Back\" button to go back to the previous page.</p>", fn.ascii(), "localhost", vParameterPageSampleRateText->text().ascii() );
    }
  }

  vSummaryPageFinishLabel->setText( tr( buffer ) );
  pcSampleWizardPanelStack->raiseWidget(2);

    pcSampleWizardPanelStack->raiseWidget(vSummaryPageWidget);
}
// End verbose AttachOrLoad callbacks


void pcSampleWizardPanel::vSummaryPageBackButtonSelected()
{
nprintf(DEBUG_PANELS) ("vSummaryPageBackButtonSelected() \n");
    pcSampleWizardPanelStack->raiseWidget(vAttachOrLoadPageWidget);
}

void pcSampleWizardPanel::vSummaryPageFinishButtonSelected()
{
nprintf(DEBUG_PANELS) ("vSummaryPageFinishButtonSelected() \n");

  Panel *p = getPanelContainer()->_masterPC->dl_create_and_add_panel("pc Sampling", getPanelContainer());
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void
pcSampleWizardPanel::languageChange()
{
    setCaption( tr( "pc Sample Wizard Panel" ) );
    vDescriptionPageTitleLabel->setText( tr( "<h1>pc Sample Wizard</h1>" ) );
    vDescriptionPageText->setText( tr( "The pc Sample experiment estimates the actual CPU time for each source code line, machine code line, and function in your program. The report listing of this experiment shows exclusive pc Sample time. This experiment is a lightweight, high-speed operation that makes use of the operating system.\n"
"\n"
"CPU time is calculated by multiplying the number of times an instruction or function appears in the PC by the interval specified for the experiment (either 1 or 10 milliseconds).\n"
"\n"
"To collect the data, the operating system regularly stops the process, increments a counter corresponding to the current value of the PC, and resumes the process. The default sample interval is 10 millisecond.\n"
"\n"
"pc Sample runs should slow the execution time of the program down no more than 5 percent. The measurements are statistical in nature, meaning they exhibit variance inversely proportional to the running time." ) );
    vDescriptionPageStartButton->setText( tr( "<< Start" ) );
    QToolTip::add( vDescriptionPageStartButton, tr( "Takes you back to the Intro Wizard so you can make a different selection." ) );
    vDescriptionPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( vDescriptionPageNextButton, tr( "Advance to the next wizard page." ) );
    vParameterPageDescriptionLabel->setText( tr( "The following options (paramaters) are available to adjust.   These are the options the collector has exported.<br><br>\n"
"The smaller the number used for the sample rate, the more\n"
"pc Sample detail will be show.   However, the trade off will be slower\n"
"performance and a larger data file.<br><br>\n"
"It may take a little expermenting to find the right setting for your \n"
"particular executable.   We suggest starting with the default setting\n"
"of 10." ) );
    vParameterPageSampleRateHeaderLabel->setText( tr( "You can set the following option(s):" ) );
    vParameterPageSampleRateLabel->setText( tr( "pc Sample rate:" ) );
    vParameterPageSampleRateText->setText( tr( "10" ) );
    QToolTip::add( vParameterPageSampleRateText, tr( "The rate to sample.   (Default 10 milliseconds.)" ) );
    vParameterPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( vParameterPageBackButton, tr( "Takes you back one page." ) );
    vParameterPageResetButton->setText( tr( "Reset" ) );
    QToolTip::add( vParameterPageResetButton, tr( "Reset the values to the default setings." ) );
    vParameterPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( vParameterPageNextButton, tr( "Advance to the next wizard page." ) );

    vAttachOrLoadPageDescriptionLabel->setText( tr( "We can attach to an existing process (or processes) or load an executable from disk (or both).  Please select the required actions.<br><br>Note: A dialog will be posted prompting for the information.</p>") );
    vAttachOrLoadPageAttachToProcessCheckBox->setText( tr( "Attach to one or more processes." ) );
    vAttachOrLoadPageLoadProcessCheckBox->setText( tr( "Load an executable from disk." ) );
    vAttachOrLoadPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( vAttachOrLoadPageBackButton, tr( "Takes you back one page." ) );
    vAttachOrLoadPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( vAttachOrLoadPageNextButton, tr( "Advance to the next wizard page." ) );
    vSummaryPageFinishLabel->setText( tr( "<p align=\"left\">\n"
"You've selected a pc Sample experiment for executable \"%s\" to be run on host \"%s\".  Futher you've chosed a sample rate of \"%d\" milliseconds.<br><br>To complete the exeriment setup select the \"Finish\" button.<br><br>Upon selection of the \"Finish\" button an experiment \"pcSample\" panel will be raised to allow you to futher control the experiment.<br><br>Press the \"Back\" button to go back to the previous page.</p>" ) );
    vSummaryPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( vSummaryPageBackButton, tr( "Takes you back one page." ) );
    vSummaryPageFinishButton->setText( tr( "Finish..." ) );
    QToolTip::add( vSummaryPageFinishButton, tr( "Finishes loading the wizard information and brings up a \"pcSample\" panel" ) );
    eDescriptionPageTitleLabel->setText( tr( "<h1>pc Sample Wizard</h1>" ) );
    eDescriptionPageText->setText( tr( "<p align=\"center\"><p align=\"left\">\n"
"Program counter (pc Sample) reveals the amount of execution time \n"
"spent in various parts of a program. The count includes:  <br>\n"
" * CPU time and memory access time <br>\n"
" * Time spent in user routines<br><br>\n"
"The pc Sample does not count time spent swapping or time spent accessing external resources.</p></p>" ) );
    eDescriptionPageStartButton->setText( tr( "<< Start" ) );
    eDescriptionPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( eDescriptionPageNextButton, tr( "Advance to the next wizard page." ) );
    eParameterPageDescriptionLabel->setText( tr( "The following options (paramaters) are available to adjust.     <br>These are the options the collector has exported." ) );
    eParameterPageSampleRateHeaderLabel->setText( tr( "You can set the following option(s):" ) );
    eParameterPageSampleRateLabel->setText( tr( "pc Sample rate:" ) );
    eParameterPageSampleRateText->setText( tr( "10" ) );
    QToolTip::add( eParameterPageSampleRateText, tr( "The rate to sample.   (Default 10 milliseconds.)" ) );
    eParameterPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( eParameterPageBackButton, tr( "Takes you back one page." ) );
    eParameterPageResetButton->setText( tr( "Reset" ) );
    QToolTip::add( eParameterPageResetButton, tr( "Reset the values to the default setings." ) );
    eParameterPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( eParameterPageNextButton, tr( "Advance to the next wizard page." ) );
    eAttachOrLoadPageDescriptionLabel->setText( tr( "Select one of the following:" ) );
    eAttachOrLoadPageAttachToProcessCheckBox->setText( tr( "Attach to one or more processes." ) );
    eAttachOrLoadPageLoadProcessCheckBox->setText( tr( "Load an executable from disk." ) );
    eAttachOrLoadPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( eAttachOrLoadPageBackButton, tr( "Takes you back one page." ) );
    eAttachOrLoadPageNextButton->setText( tr( "> Next" ) );
    QToolTip::add( eAttachOrLoadPageNextButton, tr( "Advance to the next wizard page." ) );

    eSummaryPageFinishLabel->setText( tr( "<p align=\"left\">\n"
"You've selected a pc Sample experiment for executable \"%s\" to be run on host \"%s\".  Futher you've chosed a sample rate of \"%d\" milliseconds.<br><br></p>" ) );
    eSummaryPageBackButton->setText( tr( "< Back" ) );
    QToolTip::add( eSummaryPageBackButton, tr( "Takes you back one page." ) );
    eSummaryPageFinishButton->setText( tr( "Finish..." ) );
    QToolTip::add( eSummaryPageFinishButton, tr( "Finishes loading the wizard information and brings up a \"pc Sample\" panel" ) );
    wizardMode->setText( tr( "Verbose Wizard Mode" ) );
    broughtToYouByLabel->setText( tr( "Brought to you by SGI (SiliconGraphics)" ) );
}

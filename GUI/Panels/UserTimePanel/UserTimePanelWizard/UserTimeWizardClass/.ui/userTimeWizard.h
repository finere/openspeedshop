/****************************************************************************
** Form interface generated from reading ui file 'userTimeWizard.ui'
**
** Created: Mon Apr 19 11:47:03 2004
**      by: The User Interface Compiler ($Id$)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef FORM1_H
#define FORM1_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QFrame;
class QWidgetStack;
class QLabel;
class QTextEdit;
class QCheckBox;
class QPushButton;
class QLineEdit;

class Form1 : public QWidget
{
    Q_OBJECT

public:
    Form1( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~Form1();

    QFrame* frame3;
    QWidgetStack* userTimeWizardStack;
    QWidget* WStackVPage0;
    QLabel* vWizardTitleLabel;
    QTextEdit* vWizardDescription;
    QCheckBox* vpage0HideWizardCheckBox;
    QPushButton* vpage0StartButton;
    QPushButton* vpage0NextButton;
    QWidget* WStackVPage1;
    QLabel* vWizardOptionsLabel;
    QFrame* line8;
    QLabel* rateHeaderLabel;
    QLabel* rateLabel;
    QLineEdit* vpage1SampleRateText;
    QPushButton* vpage1BackButton;
    QPushButton* vpage1ResetButton;
    QPushButton* vpage1NextButton;
    QWidget* WStackVPage2;
    QLabel* vFinishLabel;
    QPushButton* vpage2BackButton;
    QPushButton* vpage2FinishButton;
    QWidget* WStackEPage0;
    QLabel* eWizardTitleLabel;
    QTextEdit* eWizardDescription;
    QCheckBox* epage0HideWizardCheckBox;
    QPushButton* epage0StartButton;
    QPushButton* epage0NextButton;
    QWidget* WStackEPage1;
    QLabel* eWizardOptionsLabel;
    QFrame* line8_2;
    QLabel* rateHeaderLabel_2;
    QLabel* rateLabel_2;
    QLineEdit* epage1SampleRateText;
    QPushButton* epage1BackButton;
    QPushButton* epage1ResetButton;
    QPushButton* epage1NextButton;
    QWidget* WStackEPage2;
    QLabel* eFinishLabel_2;
    QPushButton* epage2BackButton;
    QPushButton* epage2FinishButton;
    QCheckBox* wizardMode;
    QLabel* broughtToYouByLabel;

public slots:
    virtual void epage0HideWizardCheckBoxSelected();
    virtual void epage0StartButtonSelected();
    virtual void epage0NextButtonSelected();
    virtual void epage1BackButtonSelected();
    virtual void epage1NextButtonSelected();
    virtual void epage1ResetButtonSelected();
    virtual void epage1SampleRateTextSelected();
    virtual void epage2BackButtonSelected();
    virtual void epage2FinishButtonSelected();
    virtual void wizardModeSelected();
    virtual void vpage0HideWizardCheckBoxSelected();
    virtual void vpage0NextButtonSelected();
    virtual void vpage0StartButtonSelected();
    virtual void vpage1BackButtonSelected();
    virtual void vpage1NextButtonSelected();
    virtual void vpage1ResetButtonSelected();
    virtual void vpage2BackButtonSelected();
    virtual void vpage2FinishButtonSelected();
    virtual void vpage1SampleRateTextSelected();

protected:
    QVBoxLayout* layout16;
    QVBoxLayout* frame3Layout;
    QVBoxLayout* WStackVPage0Layout;
    QHBoxLayout* layout7;
    QSpacerItem* spacer4;
    QSpacerItem* spacer4_2;
    QHBoxLayout* layout17;
    QSpacerItem* spacer20_2;
    QVBoxLayout* WStackVPage1Layout;
    QSpacerItem* spacer7;
    QVBoxLayout* layout9;
    QHBoxLayout* layout1_2;
    QHBoxLayout* layout31;
    QVBoxLayout* WStackVPage2Layout;
    QVBoxLayout* layout25;
    QSpacerItem* spacer20;
    QHBoxLayout* layout7_2;
    QVBoxLayout* WStackEPage0Layout;
    QHBoxLayout* layout15;
    QSpacerItem* spacer9;
    QHBoxLayout* layout17_2;
    QSpacerItem* spacer20_2_2;
    QVBoxLayout* WStackEPage1Layout;
    QSpacerItem* spacer7_2;
    QVBoxLayout* layout9_2;
    QHBoxLayout* layout1_2_2;
    QHBoxLayout* layout31_2;
    QVBoxLayout* WStackEPage2Layout;
    QHBoxLayout* layout7_2_2;
    QHBoxLayout* layout15_2;
    QSpacerItem* spacer15;

protected slots:
    virtual void languageChange();

};

#endif // FORM1_H

/********************************************************************************
** Form generated from reading UI file 'connectdlg.ui'
**
** Created: Sun Mar 6 16:02:45 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECTDLG_H
#define UI_CONNECTDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectDlg
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *ipEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *portEdit;

    void setupUi(QDialog *ConnectDlg)
    {
        if (ConnectDlg->objectName().isEmpty())
            ConnectDlg->setObjectName(QString::fromUtf8("ConnectDlg"));
        ConnectDlg->resize(330, 130);
        buttonBox = new QDialogButtonBox(ConnectDlg);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 90, 271, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        widget = new QWidget(ConnectDlg);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(34, 30, 261, 52));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        ipEdit = new QLineEdit(widget);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));

        horizontalLayout->addWidget(ipEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        portEdit = new QLineEdit(widget);
        portEdit->setObjectName(QString::fromUtf8("portEdit"));

        horizontalLayout_2->addWidget(portEdit);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(ConnectDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), ConnectDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ConnectDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(ConnectDlg);
    } // setupUi

    void retranslateUi(QDialog *ConnectDlg)
    {
        ConnectDlg->setWindowTitle(QApplication::translate("ConnectDlg", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ConnectDlg", "IP Address:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ConnectDlg", "Port Number:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConnectDlg: public Ui_ConnectDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECTDLG_H

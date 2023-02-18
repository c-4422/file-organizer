/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *Pictures;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListView *listView_2;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QListView *listView;
    QPushButton *pushButton;
    QHBoxLayout *pictures_sorting_options;
    QCheckBox *isDateSorted;
    QCheckBox *isFileComments;
    QCheckBox *isPreserveFiles;
    QHBoxLayout *output_horizontal;
    QLineEdit *pictureDestinationField;
    QPushButton *pictureDestination;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(940, 505);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Pictures = new QWidget();
        Pictures->setObjectName(QString::fromUtf8("Pictures"));
        verticalLayout_4 = new QVBoxLayout(Pictures);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(Pictures);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        listView_2 = new QListView(Pictures);
        listView_2->setObjectName(QString::fromUtf8("listView_2"));

        verticalLayout_2->addWidget(listView_2);

        pushButton_2 = new QPushButton(Pictures);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(Pictures);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        listView = new QListView(Pictures);
        listView->setObjectName(QString::fromUtf8("listView"));

        verticalLayout->addWidget(listView);

        pushButton = new QPushButton(Pictures);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_4->addLayout(horizontalLayout);

        pictures_sorting_options = new QHBoxLayout();
        pictures_sorting_options->setObjectName(QString::fromUtf8("pictures_sorting_options"));
        pictures_sorting_options->setContentsMargins(-1, 0, -1, -1);
        isDateSorted = new QCheckBox(Pictures);
        isDateSorted->setObjectName(QString::fromUtf8("isDateSorted"));

        pictures_sorting_options->addWidget(isDateSorted);

        isFileComments = new QCheckBox(Pictures);
        isFileComments->setObjectName(QString::fromUtf8("isFileComments"));

        pictures_sorting_options->addWidget(isFileComments);

        isPreserveFiles = new QCheckBox(Pictures);
        isPreserveFiles->setObjectName(QString::fromUtf8("isPreserveFiles"));

        pictures_sorting_options->addWidget(isPreserveFiles);


        verticalLayout_4->addLayout(pictures_sorting_options);

        output_horizontal = new QHBoxLayout();
        output_horizontal->setObjectName(QString::fromUtf8("output_horizontal"));
        output_horizontal->setContentsMargins(-1, 0, -1, -1);
        pictureDestinationField = new QLineEdit(Pictures);
        pictureDestinationField->setObjectName(QString::fromUtf8("pictureDestinationField"));

        output_horizontal->addWidget(pictureDestinationField);

        pictureDestination = new QPushButton(Pictures);
        pictureDestination->setObjectName(QString::fromUtf8("pictureDestination"));

        output_horizontal->addWidget(pictureDestination);


        verticalLayout_4->addLayout(output_horizontal);

        tabWidget->addTab(Pictures, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 10, -1, -1);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        horizontalLayout_2->addWidget(pushButton_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 940, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input Directories", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Open Input Directory", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Excluded Directories", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Exclude Directory", nullptr));
        isDateSorted->setText(QCoreApplication::translate("MainWindow", "Sort by creation date", nullptr));
        isFileComments->setText(QCoreApplication::translate("MainWindow", "Preserve original file path in file comments", nullptr));
        isPreserveFiles->setText(QCoreApplication::translate("MainWindow", "Preserve non-media file grouping", nullptr));
        pictureDestination->setText(QCoreApplication::translate("MainWindow", "Pictures Destination", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Pictures), QCoreApplication::translate("MainWindow", "Pictures", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

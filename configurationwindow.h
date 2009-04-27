/*
* This file is part of GmNotifier, an open-source cross-platform Gmail Notifier
* Copyright (C) 2009  Eric Lembregts
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Contact e-mail: Eric Lembregts <eric@lembregts.net>
* Program URL   : http://code.google.com/p/gmnotifier/
*/

#ifndef _CONFIGURATIONWINDOW_H_GMAILNOTIFIER
#define _CONFIGURATIONWINDOW_H_GMAILNOTIFIER

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>
#include <QFileDialog>
#include <QIntValidator>
#include <QApplication>
#include <QDesktopWidget>
#include <QCheckBox>
#include "configuration.h"

class ConfigurationWindow : public QDialog
{
        Q_OBJECT

public:
        ConfigurationWindow(QWidget *parent = 0);
        ~ConfigurationWindow();

signals:
        void restartNotifier();

protected:
        void closeEvent(QCloseEvent * event);
    void reject();

public slots:
        void show(bool firstTime = false);

protected slots:
    void saveButtonClicked();

private:
        QLineEdit * userName;
        QLineEdit * password;
        QLineEdit * sleepTime;
        QCheckBox * showMessage;
        QCheckBox * playSound;
        QPushButton * saveButton;
        QPushButton * cancelButton;
        QLabel * userNameLabel;
        QLabel * passwordLabel;
        QLabel * sleepTimeLabel;
        QLabel * sleepTimeSecondLabel;
        QLabel * showMessageLabel;
        QLabel * playSoundLabel;
        QLabel * userNameExampleLabel;
        Configuration config;

        QGridLayout * mainLayout;
        QHBoxLayout * buttonsLayout;
        QHBoxLayout * userNameLayout;
        QHBoxLayout * passwordLayout;
        QHBoxLayout * sleepTimeLayout;

        void createWidgets();
        void createLayouts();
        void centerWindow();
};

#endif

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

#include "configurationwindow.h"

ConfigurationWindow::ConfigurationWindow(QWidget * parent)
        : QDialog(parent)
{
        //create all our stuff
        createWidgets();
        createLayouts();

        //connect the buttons
        connect(saveButton, SIGNAL(clicked()), this, SLOT(saveButtonClicked()));
        connect(cancelButton, SIGNAL(clicked()), this, SLOT(hide()));

        this->setLayout(mainLayout);

        this->resize(235,170);
        this->setWindowTitle("GmNotifier Configuration");
}

ConfigurationWindow::~ConfigurationWindow()
{
        //lets cleanup our memory will we!
        delete userName;
        delete password;
        delete sleepTime;
        delete showMessage;
        delete playSound;
        delete saveButton;
        delete cancelButton;
        delete userNameLabel;
        delete passwordLabel;
        delete sleepTimeLabel;
        delete showMessageLabel;
        delete playSoundLabel;

        delete buttonsLayout;
        delete userNameLayout;
        delete passwordLayout;
        delete sleepTimeLayout;
        delete mainLayout;
}

void ConfigurationWindow::createWidgets()
{
        //create all our widgets and preload them with the right information
        userNameLabel = new QLabel(tr("Username:"));
        userName = new QLineEdit(config.userName());
        userNameLabel->setBuddy(userName);

        userNameExampleLabel = new QLabel(tr("Gmail: user@gmail.com\nHosted: user@domain.ext"));

        passwordLabel = new QLabel(tr("Password:"));
        password = new QLineEdit(config.password());
        password->setEchoMode(QLineEdit::Password);
        passwordLabel->setBuddy(password);

        sleepTimeLabel = new QLabel(tr("Refresh Time:"));
        sleepTime = new QLineEdit(QString::number(config.sleepTime()));
        sleepTime->setValidator(new QIntValidator(60, 3600, sleepTime));
        sleepTimeLabel->setBuddy(sleepTime);

        sleepTimeSecondLabel = new QLabel(tr("(seconds)"));

        showMessageLabel = new QLabel(tr("Show Popup:"));
        showMessage = new QCheckBox();
        showMessage->setChecked(config.showMessage());
        showMessageLabel->setBuddy(showMessage);

        playSoundLabel = new QLabel(tr("Play Sound:"));
        playSound = new QCheckBox();
        playSound->setChecked(config.playSound());
        playSoundLabel->setBuddy(playSound);

        saveButton = new QPushButton(tr("Save"));
        cancelButton = new QPushButton(tr("Cancel"));
}

void ConfigurationWindow::createLayouts()
{
        //craete our layouts and set the widgets
        mainLayout = new QGridLayout();

        mainLayout->addWidget(userNameLabel, 0, 0);

        userNameLayout = new QHBoxLayout();
        userNameLayout->addWidget(userName);
        userNameLayout->addStretch(1);
        mainLayout->addLayout(userNameLayout, 0, 1);

        mainLayout->addWidget(userNameExampleLabel, 1, 1);

        mainLayout->addWidget(passwordLabel, 2, 0);

        passwordLayout = new QHBoxLayout();
        passwordLayout->addWidget(password);
        passwordLayout->addStretch(1);
        mainLayout->addLayout(passwordLayout, 2, 1);

        mainLayout->addWidget(sleepTimeLabel, 3, 0);

        sleepTimeLayout = new QHBoxLayout();
        sleepTimeLayout->addWidget(sleepTime);
        sleepTimeLayout->addWidget(sleepTimeSecondLabel);
        mainLayout->addLayout(sleepTimeLayout, 3, 1);

        mainLayout->addWidget(showMessageLabel, 4, 0);
        mainLayout->addWidget(showMessage, 4, 1);

        mainLayout->addWidget(playSoundLabel, 5, 0);
        mainLayout->addWidget(playSound, 5, 1);

        buttonsLayout = new QHBoxLayout();
        buttonsLayout->addWidget(saveButton);
        buttonsLayout->addWidget(cancelButton);

        mainLayout->addLayout(buttonsLayout, 6, 0, 1, 2);
}

void ConfigurationWindow::saveButtonClicked()
{
        if(userName->text().endsWith("@gmail.com")){
                config.setHosted(false);
                config.setDomain("");
                config.setUserName(userName->text());
        }else{
                config.setHosted(true);
                config.setDomain(userName->text().section('@', -1));
                config.setUserName(userName->text());
        }

        config.setPassword(password->text());

        if(sleepTime->text().toInt() < 30){
                if(config.sleepTime() < 30){
                        sleepTime->setText("30");
                        config.setSleepTime(30);
                }else{
                        sleepTime->setText(QString::number(config.sleepTime()));
                }
        }else{
                config.setSleepTime(sleepTime->text().toInt());
        }

        config.setShowMessage(showMessage->isChecked());
        config.setPlaySound(playSound->isChecked());

        config.writeConfiguration();

        this->hide();

        emit restartNotifier();
}

void ConfigurationWindow::closeEvent(QCloseEvent * event)
{
        this->hide();
        event->ignore();
}

void ConfigurationWindow::reject()
{
        //I've overridden the reject function to make sure that when the user
        //Escapes the window by pressing ESC the program does not get terminated
        this->hide();
}

void ConfigurationWindow::centerWindow()
{
        //This function was taken from http://lists.trolltech.com/qt-interest/2004-12/msg00856.html
        //Takes in account every possible screen setup I could find
        int screen = 0;

        if(QApplication::desktop()->isVirtualDesktop())
                screen = QApplication::desktop()->screenNumber(QCursor::pos());
        else
                screen = QApplication::desktop()->screenNumber(this);

        QRect desktop(QApplication::desktop()->availableGeometry(screen));

        move((desktop.width() - frameGeometry().width()) / 2,
                        (desktop.height() - frameGeometry().height()) / 2);
}

void ConfigurationWindow::show(bool firstTime)
{
        userName->setText(config.userName());
        password->setText(config.password());
        sleepTime->setText(QString::number(config.sleepTime()));

        showMessage->setChecked(config.showMessage());
        playSound->setChecked(config.playSound());

        if(firstTime){
                sleepTime->setText("60");
                showMessage->setChecked(true);
        }

        this->centerWindow();
        QDialog::show();
        this->raise();
        this->activateWindow();
}

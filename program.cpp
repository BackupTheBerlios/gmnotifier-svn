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

#include "program.h"

Program::Program(QWidget *parent, Qt::WFlags flags)
        : QWidget(parent, flags)
{
        notifier = 0;

        //read our configuration
        FileParseError readError = config.readConfiguration();

        //preload our configuration window
        configurationWindow = new ConfigurationWindow(this);
        configurationWindow->setModal(false);

        //If we have no configuartion file or it is malformed
        //Display the configuration window
        if(readError == NOEXIST || readError == MALFORMED){
                configurationWindow->show(true);
        }

        //Create the notifier
        notifier = new Notifier(this);

        //These thingy's depend on eachother, and they need the configurationwindows / notifier to be able
        //to connect there signals...
        createActions();
        createIcons();
        createTray();
        createSound();

        //connect our basic slots
        connect(configurationWindow, SIGNAL(restartNotifier()), notifier, SLOT(setParameters()));
        connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconClicked(QSystemTrayIcon::ActivationReason)));
        connect(trayIcon, SIGNAL(messageClicked()), this, SLOT(trayIconClicked()));
        connect(notifier, SIGNAL(newNotification(TrayStatus, QString, QString)), this, SLOT(changeTray(TrayStatus, QString, QString)));

        //lets start our engines!
        notifier->setParameters();
        notifier->start();
}

Program::~Program()
{
        //destruct all our created memory
        foreach (QAction * action, actions){
                delete action;
        }

        delete notifier;
        delete trayIconMenu;
        delete trayIcon;
        delete configurationWindow;
}

void Program::changeTray(TrayStatus status, QString tooltip, QString message)
{
        //this slot will let the notifier change the tray icon
        //and if needed display a message ofcourse!
        switch(status){
                case NEW:
                        trayIcon->setIcon(icons["new"]);
                        break;
                case NONEW:
                        trayIcon->setIcon(icons["nonew"]);
                        break;
                case BROKEN:
                default:
                        trayIcon->setIcon(icons["broken"]);
                        break;
        }

        trayIcon->setToolTip(tooltip + QTime::currentTime().toString(" - HH:mm"));

        if(message != ""){
                if(sound->fileName() != "" && config.playSound()){
                        sound->play();
                }

                if(config.showMessage()){
                        trayIcon->showMessage(message, tooltip, QSystemTrayIcon::Information, 3000);
                }
        }
}

void Program::createTray()
{
        //Lets create the icon menu and the icon itself!
        trayIconMenu = new QMenu(this);

        trayIconMenu->addAction(actions["manualCheck"]);
        trayIconMenu->addAction(actions["configuration"]);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(actions["aboutQt"]);
        trayIconMenu->addSeparator();
        trayIconMenu->addAction(actions["quit"]);

        trayIcon = new QSystemTrayIcon(this);

        //It seems there is a problem with the ContextMenu when you load the configuration window
        //and close it, I'm currently thinking of a sollution...
        trayIcon->setContextMenu(trayIconMenu);

        trayIcon->setIcon(icons["nonew"]);
        trayIcon->show();
}

void Program::createActions()
{
        //Create all the actions for the menus
        QAction * quitAction = new QAction(tr("&Quit"), this);
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

        actions.insert("quit", quitAction);

        QAction * manualCheckAction = new QAction(tr("&Check Mail"), this);
        connect(manualCheckAction, SIGNAL(triggered()), notifier, SLOT(manualCheck()));

        actions.insert("manualCheck", manualCheckAction);

        QAction * configurationAction = new QAction(tr("Con&figure"), this);
        connect(configurationAction, SIGNAL(triggered()), configurationWindow, SLOT(show()));

        actions.insert("configuration", configurationAction);

        QAction * aboutQtAction = new QAction(tr("About &Qt"), this);
        connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()), Qt::QueuedConnection);

        actions.insert("aboutQt", aboutQtAction);
}

void Program::createIcons()
{
        //Basic Icon stuff
        QIcon iconNew(":/images/new.png");
        QIcon iconNoNew(":/images/nonew.png");
        QIcon iconBroken(":/images/broken.png");

        icons.insert("new", iconNew);
        icons.insert("nonew", iconNoNew);
        icons.insert("broken", iconBroken);
}

void Program::createSound()
{
        if(QFile::exists("sound.wav")){
                sound = new QSound("sound.wav", this);
        }else{
                sound = new QSound("");
        }
}

void Program::trayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
        if(reason == QSystemTrayIcon::Trigger){
                QString url;

                if(config.hosted()){
                        url = "https://mail.google.com/a/" + config.domain() + "/#inbox";
                }else{
                        url = "https://mail.google.com/mail/#inbox";
                }

                changeTray(NONEW, "There is no new mail", "");
                QDesktopServices::openUrl(url);
        }
}

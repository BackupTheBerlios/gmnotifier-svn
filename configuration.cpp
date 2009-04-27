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

#include "configuration.h"

#include <QTextStream>
#include <QDir>
#include <QDesktopServices>

//Define our static variables here! Otherwise the compiler fails
QString Configuration::m_userName;
QString Configuration::m_password;
bool Configuration::m_hosted;
QString Configuration::m_domain;
unsigned int Configuration::m_sleepTime;
bool Configuration::m_showMessage;
bool Configuration::m_playSound;

FileParseError Configuration::readConfiguration(QString filename)
{
        QFile file(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "//gmnotifier.conf");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
                return NOEXIST;
        }

        QTextStream fileStream(&file);
        while (!fileStream.atEnd()) {
                QString line = fileStream.readLine();
                if(!parseLine(line)){
                        file.close();
                        return MALFORMED;
                }
        }

        file.close();

        return NONE;
}

bool Configuration::parseLine(QString line)
{
        //Very ugly implementation, needs to me XMLized or even better serialized !!
        //But I'm way to lazy to do that at this point
        //If anyone feels eager to do this... go ahead!
        if(line.startsWith("username=")){
                m_userName = line.right(line.length() - 9);
        }else if(line.startsWith("password=")){
                m_password = line.right(line.length() - 9);
        }else if(line.startsWith("hosted=")){
                if(line.right(line.length() - 7) == "true"){
                        m_hosted = true;
                }else{
                        m_hosted = false;
                }
        }else if(line.startsWith("domain=")){
                m_domain = line.right(line.length() - 7);
        }else if(line.startsWith("sleeptime=")){
                m_sleepTime = line.right(line.length() - 10).toInt();
        }else if(line.startsWith("showmessage=")){
                if(line.right(line.length() - 12) == "true"){
                        m_showMessage = true;
                }else{
                        m_showMessage = false;
                }
        }else if(line.startsWith("playsound=")){
                if(line.right(line.length() - 10) == "true"){
                        m_playSound = true;
                }else{
                        m_playSound = false;
                }
        }else{
                return false;
        }

        return true;
}

FileParseError Configuration::writeConfiguration(QString filename)
{
        QDir directory;

        if(!directory.exists(QDesktopServices::storageLocation(QDesktopServices::DataLocation))){
                directory.mkpath(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
        }

        QFile file(QDesktopServices::storageLocation(QDesktopServices::DataLocation) + "//gmnotifier.conf");

        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
                return WRITEERROR;
        }

        QTextStream fileStream(&file);
        fileStream << "username=" << m_userName << "\n";
        fileStream << "password=" << m_password << "\n";
        if(m_hosted){
                fileStream << "hosted=true\n";
        }else{
                fileStream << "hosted=false\n";
        }
        fileStream << "domain=" << m_domain << "\n";
        fileStream << "sleeptime=" << QString::number(m_sleepTime) << "\n";
        if(m_showMessage){
                fileStream << "showmessage=true\n";
        }else{
                fileStream << "showmessage=false\n";
        }
        if(m_playSound){
                fileStream << "playsound=true\n";
        }else{
                fileStream << "playsound=false\n";
        }
        file.close();

        return NONE;
}


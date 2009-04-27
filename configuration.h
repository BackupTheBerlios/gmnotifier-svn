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

#ifndef _CONFIGURATION_H_GMAILNOTIFIER
#define _CONFIGURATION_H_GMAILNOTIFIER

#include <QString>

enum FileParseError { NOEXIST, MALFORMED, WRITEERROR, NONE};

class Configuration
{
public:
        QString userName() { return m_userName; }
        QString password() { return m_password; }
        bool hosted() { return m_hosted; }
        QString domain() { return m_domain; }
        unsigned int sleepTime() { return m_sleepTime; }
        bool showMessage() { return m_showMessage; }
        bool playSound() { return m_playSound; }

        void setUserName(const QString userName) { m_userName = userName; }
        void setPassword(const QString password) { m_password = password; }
        void setHosted(const bool hosted) { m_hosted = hosted; }
        void setDomain(const QString domain) { m_domain = domain; }
        void setSleepTime(const unsigned int sleepTime) { m_sleepTime = sleepTime; }
        void setShowMessage(const bool showMessage) { m_showMessage = showMessage; }
        void setPlaySound(const bool playSound) { m_playSound = playSound; }

        FileParseError readConfiguration(QString filename = "");
        FileParseError writeConfiguration(QString filename = "");

private:
         static QString m_userName;
         static QString m_password;
         static bool m_hosted;
         static QString m_domain;
         static unsigned int m_sleepTime;
         static bool m_showMessage;
         static bool m_playSound;

         bool parseLine(QString line);
};

#endif

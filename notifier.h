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

#ifndef _NOTIFIER_H_GMAILNOTIFIER
#define _NOTIFIER_H_GMAILNOTIFIER

#include <QSize>
#include <QThread>
#include <QHttp>
#include <QUrl>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QAuthenticator>
#include <QList>

#include "configuration.h"

enum TrayStatus { NEW, NONEW, BROKEN };

class Notifier : public QThread
{
        Q_OBJECT

public:
        Notifier(QObject * parent = 0);
        ~Notifier();

public slots:
        void manualCheck();
        void setParameters();

signals:
        void newNotification(TrayStatus status, QString tooltip, QString message = "");

protected:
        void run();

private slots:
        void httpRequestFinished(int requestId, bool error);
        void loginUser(const QString &, quint16, QAuthenticator *);

private:
        void checkMail();
        void startHttpRequest();
        void parseXml();
        void parseNewMail(QList<QString> newEmailIds);

        int httpGetId;

        QHttp *httpConnection;
        QUrl  *connectionUrl;
        QXmlStreamReader xml;

        bool loginAttempt;
        bool terminateThread;

        Configuration config;
        QString userName;
        QString password;
        unsigned int sleepTime;

        QList<QString> emailIds;
};

#endif

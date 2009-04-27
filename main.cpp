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

#define OVERRIDE_LANG "en"

#include <QApplication>
#include <QTranslator>
#include "program.h"

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);

        app.setWindowIcon(QIcon(":/images/nonew.png"));
        app.setApplicationName("GmNotifier");
        app.setOrganizationName("Eric Lembregts");
        app.setApplicationVersion("0.2.0 beta");
        app.setQuitOnLastWindowClosed(false);

        QTranslator translator;

#ifdef OVERRIDE_LANG
        translator.load(QString("translation_")  + OVERRIDE_LANG);
#else
        translator.load(QString("translation_") + QLocale::system().name());
#endif

        app.installTranslator(&translator);

        Program w;

        return app.exec();
}

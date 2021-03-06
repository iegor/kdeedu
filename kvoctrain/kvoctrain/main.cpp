/***************************************************************************

    -----------------------------------------------------------------------

    begin                : Thu Mar 11 20:50:53 MET 1999

    copyright            : (C) 1999-2001 Ewald Arnold
                           (C) 2001 The KDE-EDU team
    email                : kvoctrain@ewald-arnold.de

    -----------------------------------------------------------------------

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


#include "kvoctrain.h"
#include "kvoctraincore.h"

# include <kcmdlineargs.h>
# include <kaboutdata.h>
# include <klocale.h>

int main(int argc, char* argv[]) {

static KCmdLineOptions options[] =
{
  { I18N_NOOP("+[file]"),   I18N_NOOP("Document file to open"), 0 },
  KCmdLineLastOption
};

static const char description[] = I18N_NOOP("Vocabulary Trainer");
static const char version[]     = KVOCTRAIN_VERSION_STRING;

  KAboutData aboutData("kvoctrain",
                       I18N_NOOP("KVocTrain"),
                       version,
                       description,
                       KAboutData::License_GPL,
                       I18N_NOOP("© 1999-2002\tEwald Arnold\n"
                       "© 2001-2002\tThe KDE team\n"
                       "© 2004-2007\tPeter Hedlund\n"
                       "© 2007     \tFrederik Gladhorn\n"),
                       I18N_NOOP("Helps you train your vocabulary"),
                       "http://edu.kde.org/kvoctrain",
                       "submit@bugs.kde.org");

  aboutData.addAuthor("Frederik Gladhorn",
                      I18N_NOOP("Current Maintainer"), "frederik.gladhorn@kdemail.net");

  aboutData.addAuthor("Peter Hedlund",
                      I18N_NOOP("Former Maintainer and Countless Improvements"), "peter.hedlund@kdemail.net");

  aboutData.addAuthor("Ewald Arnold", I18N_NOOP("Original Author"), "kvoctrain@ewald-arnold.de",
                      "http://www.ewald-arnold.de" );

  aboutData.addCredit("Waldo Bastian",
                      I18N_NOOP("Help with port to Qt3/KDE3"));

  aboutData.addCredit("Andrea Marconi",
                      I18N_NOOP("Initial Italian localization"));

  aboutData.addCredit("Hans Kottmann",
                      I18N_NOOP("Initial French localization"));

  aboutData.addCredit("Grzegorz Ilczuk",
                      I18N_NOOP("Initial Polish localization"));

  aboutData.addCredit("Eric Bischoff",
                      I18N_NOOP("Converting documentation to docbook format"));

  aboutData.addCredit("Kevin Kramer",
                      I18N_NOOP("Tool to create lists with ISO639 codes"));

  aboutData.addCredit("Andreas Neuper",
                      I18N_NOOP("Converter script \"langen2kvtml\" \nDownload files at http://www.vokabeln.de/files.htm"));

   aboutData.addCredit("Dennis Haney",
                      I18N_NOOP("Patch to implement Leitner learning method"));

   aboutData.addCredit("Anne-Marie Mahfouf",
                       I18N_NOOP("Port to KConfig XT"));

  aboutData.addCredit(I18N_NOOP("KDE Team"),
                      I18N_NOOP("Many small enhancements"));

  KCmdLineArgs::init( argc, argv, &aboutData );
  KCmdLineArgs::addCmdLineOptions( options );
  KApplication app;

  kvoctrainApp *kva = 0;
  if (app.isRestored()) {
    int n = 1;
    while (KMainWindow::canBeRestored(n)){
      kva = new kvoctrainApp;
      kva->restore(n);
      kva->show();
      n++;
    }
  }
  else
  {
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    kva = new kvoctrainApp;

    if ( args && args->count() == 1 )
      kva->loadfileFromPath(args->arg(0), true);

    kva->show();
  }
  return app.exec();
}


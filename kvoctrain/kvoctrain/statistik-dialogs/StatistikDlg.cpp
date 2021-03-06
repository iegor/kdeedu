/***************************************************************************

                      statistics dialog class

    -----------------------------------------------------------------------

    begin          : Sun Sep 19 20:50:53 MET 1999

    copyright      : (C) 1999-2001 Ewald Arnold <kvoctrain@ewald-arnold.de>
                     (C) 2001 The KDE-EDU team
                     (C) 2005 Peter Hedlund <peter.hedlund@kdemail.net>

    -----------------------------------------------------------------------

 ***************************************************************************

 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qlayout.h>

#include "StatistikDlg.h"
#include "StatistikPage.h"
#include "GenStatPage.h"

#include <klocale.h>

#include <langset.h>
#include <kvoctraindoc.h>

StatistikDlg::StatistikDlg(LangSet &langset, kvoctrainDoc *doc, QWidget *parent, const char *name, bool modal)
  : KDialogBase(Tabbed, i18n("Document Statistics"), Close, Close, parent, name, modal)
{
  QFrame * page;
  QVBoxLayout * topLayout;
  StatistikPage *spage;

  page = addPage(i18n("General"));
  topLayout = new QVBoxLayout( page, 0, KDialog::spacingHint() );
  GenStatPage *gspage = new GenStatPage (doc, page, name);
  topLayout->addWidget(gspage);

  for (int i = 1; i < (int) doc->numLangs(); i++)
  {
    QString s = langset.findLongId(doc->getIdent(i));
    if (s.isEmpty() )
      s = doc->getIdent(i);
    else
      s = i18n(s.local8Bit());

    page = addPage(s);
    topLayout = new QVBoxLayout( page, 0, KDialog::spacingHint() );
    spage = new StatistikPage (i, doc, page, name);
    topLayout->addWidget(spage);
  }
}

#include "StatistikDlg.moc"

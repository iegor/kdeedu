/***************************************************************************

                   language properties dialog page

    -----------------------------------------------------------------------

    begin          : Wed Oct 13 18:37:13 1999

    copyright      : (C) 1999-2001 Ewald Arnold <kvoctrain@ewald-arnold.de>
                     (C) 2001 The KDE-EDU team
                     (C) 2005 Peter Hedlund <peter.hedlund@kdemail.net>

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


#include <langset.h>

#include "LangPropPage.h"

#include <klocale.h>

#include <qlineedit.h>
#include <qcheckbox.h>
#include <qlabel.h>

LangPropPage::LangPropPage
(
  kvoctrainDoc      *_doc,
  QString            curr_lang,
  const Conjugation &conjug,
  const Article     &art,
  QWidget           *parent,
  const char        *name
)
  :
  LangPropPageForm( parent, name ),
  doc(_doc),
  conjugations(conjug),
  articles(art)
{
  l_langcode->setText(curr_lang);

  connect( indef_female, SIGNAL(textChanged(const QString&)), SLOT(indefFemaleChanged(const QString&)) );
  connect( def_female, SIGNAL(textChanged(const QString&)), SLOT(defFemaleChanged(const QString&)) );
  connect( def_male, SIGNAL(textChanged(const QString&)), SLOT(defMaleChanged(const QString&)) );
  connect( indef_male, SIGNAL(textChanged(const QString&)), SLOT(indefMaleChanged(const QString&)) );
  connect( def_natural, SIGNAL(textChanged(const QString&)), SLOT(defNaturalChanged(const QString&)) );
  connect( indef_natural, SIGNAL(textChanged(const QString&)), SLOT(indefNaturalChanged(const QString&)) );
  connect( first_singular, SIGNAL(textChanged(const QString&)), SLOT(firstSingularChanged(const QString&)) );
  connect( first_plural, SIGNAL(textChanged(const QString&)), SLOT(firstPluralChanged(const QString&)) );
  connect( second_singular, SIGNAL(textChanged(const QString&)), SLOT(secondSingularChanged(const QString&)) );
  connect( second_plural, SIGNAL(textChanged(const QString&)), SLOT(secondPluralChanged(const QString&)) );
  connect( thirdF_singular, SIGNAL(textChanged(const QString&)), SLOT(thirdFSingularChanged(const QString&)) );
  connect( thirdF_plural, SIGNAL(textChanged(const QString&)), SLOT(thirdFPluralChanged(const QString&)) );
  connect( thirdM_singular, SIGNAL(textChanged(const QString&)), SLOT(thirdMSingularChanged(const QString&)) );
  connect( thirdM_plural, SIGNAL(textChanged(const QString&)), SLOT(thirdMPluralChanged(const QString&)) );
  connect( thirdN_singular, SIGNAL(textChanged(const QString&)), SLOT(thirdNSingularChanged(const QString&)) );
  connect( thirdN_plural, SIGNAL(textChanged(const QString&)), SLOT(thirdNPluralChanged(const QString&)) );

  connect( thirdS_common, SIGNAL(toggled(bool)), SLOT(slotThirdSCommonToggled(bool)) );
  connect( thirdP_common, SIGNAL(toggled(bool)), SLOT(slotThirdPCommonToggled(bool)) );

  conjugations = conjug;

  first_plural->setText (conjugations.pers1Plural (CONJ_PREFIX));
  first_singular->setText (conjugations.pers1Singular (CONJ_PREFIX));
  second_singular->setText (conjugations.pers2Singular (CONJ_PREFIX));
  second_plural->setText (conjugations.pers2Plural (CONJ_PREFIX));
  thirdF_plural->setText (conjugations.pers3FemalePlural (CONJ_PREFIX));
  thirdF_singular->setText (conjugations.pers3FemaleSingular (CONJ_PREFIX));
  thirdN_plural->setText (conjugations.pers3NaturalPlural (CONJ_PREFIX));
  thirdN_singular->setText (conjugations.pers3NaturalSingular (CONJ_PREFIX));
  thirdM_plural->setText (conjugations.pers3MalePlural (CONJ_PREFIX));
  thirdM_singular->setText (conjugations.pers3MaleSingular (CONJ_PREFIX));

  bool common = conjugations.pers3SingularCommon(CONJ_PREFIX);
  thirdS_common->setChecked(common);
  thirdM_singular->setEnabled(!common);
  thirdN_singular->setEnabled(!common);

  common = conjugations.pers3PluralCommon(CONJ_PREFIX);
  thirdP_common->setChecked(common);
  thirdN_plural->setEnabled(!common);
  thirdM_plural->setEnabled(!common);

  QString def, indef;
  articles.female(def, indef);
  def_female->setText (def);
  indef_female->setText (indef);

  articles.male(def, indef);
  def_male->setText (def);
  indef_male->setText (indef);

  articles.natural(def, indef);
  def_natural->setText (def);
  indef_natural->setText (indef);

}


Conjugation LangPropPage::getConjugation()
{
  conjugations.cleanUp();
  return conjugations;
}


void LangPropPage::firstPluralChanged(const QString& s)
{
  conjugations.setPers1Plural (CONJ_PREFIX, s);
}


void LangPropPage::firstSingularChanged(const QString& s)
{
  conjugations.setPers1Singular (CONJ_PREFIX, s);
}


void LangPropPage::secondSingularChanged(const QString& s)
{
  conjugations.setPers2Singular (CONJ_PREFIX, s);
}


void LangPropPage::secondPluralChanged(const QString& s)
{
  conjugations.setPers2Plural (CONJ_PREFIX, s);
}


void LangPropPage::thirdFPluralChanged(const QString& s)
{
  conjugations.setPers3FemalePlural (CONJ_PREFIX, s);
}


void LangPropPage::thirdFSingularChanged(const QString& s)
{
  conjugations.setPers3FemaleSingular (CONJ_PREFIX, s);
}


void LangPropPage::thirdMSingularChanged(const QString& s)
{
  conjugations.setPers3MaleSingular (CONJ_PREFIX, s);
}


void LangPropPage::thirdNSingularChanged(const QString& s)
{
  conjugations.setPers3NaturalSingular(CONJ_PREFIX, s);
}


void LangPropPage::thirdNPluralChanged(const QString& s)
{
  conjugations.setPers3NaturalPlural (CONJ_PREFIX, s);
}


void LangPropPage::thirdMPluralChanged(const QString& s)
{
  conjugations.setPers3MalePlural (CONJ_PREFIX, s);
}


void LangPropPage::slotThirdSCommonToggled(bool common)
{
  conjugations.setPers3SingularCommon(CONJ_PREFIX, common);
  thirdN_singular->setEnabled(!common);
  thirdM_singular->setEnabled(!common);
}


void LangPropPage::slotThirdPCommonToggled(bool common)
{
  conjugations.setPers3PluralCommon(CONJ_PREFIX, common);
  thirdN_plural->setEnabled(!common);
  thirdM_plural->setEnabled(!common);
}


void LangPropPage::defFemaleChanged(const QString& s)
{
  QString def, indef;
  articles.female(def, indef);
  articles.setFemale(s, indef);
}


void LangPropPage::indefFemaleChanged(const QString& s)
{
  QString def, indef;
  articles.female(def, indef);
  articles.setFemale(def, s);
}


void LangPropPage::defMaleChanged(const QString& s)
{
  QString def, indef;
  articles.male(def, indef);
  articles.setMale(s, indef);
}


void LangPropPage::indefMaleChanged(const QString& s)
{
  QString def, indef;
  articles.male(def, indef);
  articles.setMale(def, s);
}


void LangPropPage::defNaturalChanged(const QString& s)
{
  QString def, indef;
  articles.natural(def, indef);
  articles.setNatural(s, indef);
}


void LangPropPage::indefNaturalChanged(const QString& s)
{
  QString def, indef;
  articles.natural(def, indef);
  articles.setNatural(def, s);
}

#include "LangPropPage.moc"

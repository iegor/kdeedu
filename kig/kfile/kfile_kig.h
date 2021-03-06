/***************************************************************************
 *   Copyright (C) 2004 by Pino Toscano                                    *
 *   toscano.pino@tiscali.it                                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.             *
 ***************************************************************************/

#ifndef KIG_KFILE_KFILE_KIG_H
#define KIG_KFILE_KFILE_KIG_H

#include <kfilemetainfo.h>

class QStringList;

class KigPlugin: public KFilePlugin
{
    Q_OBJECT
    
public:
    KigPlugin( QObject *parent, const char *name, const QStringList& args );

    virtual bool readInfo( KFileMetaInfo& metainfo, uint what);
protected:
    KFileMimeTypeInfo* info;
    KFileMimeTypeInfo::GroupInfo* group;
};

#endif

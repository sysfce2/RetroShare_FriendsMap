/*! 
 * @file FriendMapController.h
 *  @author RetroShare Team
 *  
 * Copyright (C) 2021 - RetroShare Team
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 * 
 */

#ifndef FRIENDMAPMANAGER_H
#define FRIENDMAPMANAGER_H

#include <QObject>
#include <QPointer>
#include <retroshare/rsplugin.h>
#include "FriendMapSettings.h"
#include "FriendMapPage.h"
#include "FriendMapConfigPage.h"
#include <retroshare-gui/mainpage.h>

class FriendMapController : public QObject
{
    Q_OBJECT
public:
    RsPeers* peers;
    RsDisc*  mDisc;
    explicit FriendMapController(QObject *parent = 0);
    ~FriendMapController();
    MainPage* qt_page()const;
    ConfigPage* qt_config_page() const;
    FriendMapSettings* getSettings();

private:
    bool detached; //cache settings value to do not allow to change it at runtime
    FriendMapSettings* settings;
    mutable MainPage* mainPage;
    mutable QPointer<FriendMapPage> friendMapPage;
signals:

public slots:
    void configChanged();
    void openWindow();
};

#endif // FRIENDMAPMANAGER_H

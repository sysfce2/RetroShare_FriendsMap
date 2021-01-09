/*! 
 * @file FriendMapController.cpp
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

#include "FriendMapController.h"
#include "FriendMapDetached.h"

FriendMapController::FriendMapController(QObject *parent) :
    QObject(parent)
{
    settings = new FriendMapSettings();
    this->detached = settings->getDetached();
    mainPage = NULL;
}

FriendMapController::~FriendMapController()
{
    delete settings;
    delete mainPage;
    if(friendMapPage)
        delete friendMapPage;
}

MainPage *FriendMapController::qt_page() const
{
    
	if(mainPage == NULL)
    {
        if(detached)
        {
            mainPage = new FriendMapDetached(this);
        }else{
            friendMapPage = new FriendMapPage(peers, mDisc);
            friendMapPage->setConfig(settings);
            mainPage = friendMapPage;
        }
    }
    return mainPage;
}

ConfigPage *FriendMapController::qt_config_page() const
{
    FriendMapConfigPage* configPage = new FriendMapConfigPage(settings);
    connect(configPage, SIGNAL(configChanged()), this, SLOT(configChanged()));
    return configPage;
}

FriendMapSettings *FriendMapController::getSettings()
{
    return settings;
}

void FriendMapController::configChanged()
{
    if(friendMapPage)
        friendMapPage->setConfig(settings);
}

void FriendMapController::openWindow()
{
    if(friendMapPage.isNull())
    {
        friendMapPage = new FriendMapPage(peers, mDisc);
        friendMapPage->setAttribute(Qt::WA_DeleteOnClose, true);
        friendMapPage->show();
        friendMapPage->setConfig(settings);
    }else{
        friendMapPage->activateWindow();
    }
}

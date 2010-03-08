/*
* Copyright (c) 2005-2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  
*
*/


#ifndef WEBCLIENT_PAN
#define WEBCLIENT_PAN

enum TClientPanics 
    {
    EClientUi = 1,
    EClientView,
    EClientEngine
    // add further panics here
    };

inline void Panic(TClientPanics aReason)
    {
    _LIT(applicationName,"WebClient");
    User::Panic(applicationName, aReason);
    }

#endif // WEBCLIENT_PAN

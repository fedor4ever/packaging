/*
* Copyright (c) 2007 Nokia Corporation and/or its subsidiary(-ies).
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



#ifndef __STYLUSPOPUPMENUEX_APPLICATION_H__
#define __STYLUSPOPUPMENUEX_APPLICATION_H__

// INCLUDES
#include <aknapp.h>


// CLASS DECLARATION

/**
* CStylusPopupMenuExApp application class.
* Provides factory to create concrete document object.
* An instance of CStylusPopupMenuExApp is the application part of the
* AVKON application framework for the StylusPopupMenu example application.
*/
class CStylusPopupMenuExApp : public CAknApplication
    {
public:  // from CAknApplication

    /**
    * From CApaApplication, AppDllUid.
    * @return Application's UID
    */
    TUid AppDllUid() const;

protected: // from CAknApplication

    /**
    * From CApaApplication, CreateDocumentL.
    * Creates CStylusPopupMenuExDoc object. The returned
    * pointer is not owned by the CStylusPopupMenuExApp object.
    * @return A pointer to the created document object.
    */
    CApaDocument* CreateDocumentL();
    };

#endif // __STYLUSPOPUPMENUEX_APPLICATION_H__


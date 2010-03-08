/*
* Copyright (c) 2003 Nokia Corporation and/or its subsidiary(-ies).
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


#include <eikstart.h>
#include "EcmtGuiApplication.h"

// Create an application, and return a pointer to it
LOCAL_C CApaApplication* NewApplication() 
    {
    return (static_cast<CApaApplication*>(new CEcmtGuiApplication));
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

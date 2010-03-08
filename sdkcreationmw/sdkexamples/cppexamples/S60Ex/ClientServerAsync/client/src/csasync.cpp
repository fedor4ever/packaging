/*
* Copyright (c) 2004-2006 Nokia Corporation and/or its subsidiary(-ies).
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



// INCLUDE FILES
#include <EikStart.h>

#include "CSAsyncApplication.h"

// ========================== OTHER EXPORTED FUNCTIONS =========================

// -----------------------------------------------------------------------------
// NewApplication()
// Create a CSAsync application, and return a pointer to it
// -----------------------------------------------------------------------------
//
EXPORT_C CApaApplication* NewApplication()
    {
    return ( static_cast<CApaApplication*>( new CCSAsyncApplication ) );
    }

// -----------------------------------------------------------------------------
// E32Main()
// DLL entry point
// -----------------------------------------------------------------------------
//
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File

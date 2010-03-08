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
#include    <eikstart.h>
#include    "SimpleCubeApp.h"
#include    "SimpleCubeDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CSimpleCubeApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CSimpleCubeApp::AppDllUid() const
    {
    return KUidSimpleCube;
    }


// ---------------------------------------------------------
// CSimpleCubeApp::CreateDocumentL()
// Creates CSimpleCubeDocument object
// ---------------------------------------------------------
//
CApaDocument* CSimpleCubeApp::CreateDocumentL()
    {
    return CSimpleCubeDocument::NewL( *this );
    }


// ================= OTHER EXPORTED FUNCTIONS ==============


CApaApplication* NewApplication()
    {
    return new CSimpleCubeApp;
    }

TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File


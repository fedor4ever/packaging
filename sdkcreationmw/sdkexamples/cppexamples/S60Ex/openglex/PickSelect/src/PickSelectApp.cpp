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
#include    "PickSelectApp.h"
#include    "PickSelectDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CPickSelectApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CPickSelectApp::AppDllUid() const
    {
    return KUidPickSelect;
    }


// ---------------------------------------------------------
// CPickSelectApp::CreateDocumentL()
// Creates CPickSelectDocument object
// ---------------------------------------------------------
//
CApaDocument* CPickSelectApp::CreateDocumentL()
    {
    return CPickSelectDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============

LOCAL_C CApaApplication* NewApplication()
    {
    return new CPickSelectApp;
    }

GLDEF_C TInt E32Main()
    {
        return EikStart::RunApplication(NewApplication);
    }

// End of File


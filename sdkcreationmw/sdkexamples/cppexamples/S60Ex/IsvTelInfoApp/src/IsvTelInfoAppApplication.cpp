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


// INCLUDE FILES
#include <eikstart.h>
#include "IsvTelInfoAppApplication.h"
#include "IsvTelInfoAppUi.h"
#include "IsvTelInfoAppDocument.h"

// ================= MEMBER FUNCTIONS =========================================

// ----------------------------------------------------------------------------
// TUid CIsvTelInfoAppApplication::AppDllUid()
// Returns application UID.
// ----------------------------------------------------------------------------
//
TUid CIsvTelInfoAppApplication::AppDllUid() const
    {
    return KUidIsvTelInfoApp;
    }

// ----------------------------------------------------------------------------
// CApaDocument* CIsvTelInfoAppApplication::CreateDocumentL()
// Creates CIsvTelInfoAppDocument object.
// ----------------------------------------------------------------------------
//
CApaDocument* CIsvTelInfoAppApplication::CreateDocumentL()
    {
    return CIsvTelInfoAppDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS =================================


// ----------------------------------------------------------------------------
// CApaApplication* NewApplication()
// Constructs CIsvTelInfoAppApplication.
// Returns: CApaApplication*: created application object
// ----------------------------------------------------------------------------
//



LOCAL_C CApaApplication* NewApplication()
    {
    return new CIsvTelInfoAppApplication;
    }

GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }




// End of File

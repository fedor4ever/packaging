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
#include    <eikstart.h>
#include    "ParticlesApp.h"
#include    "ParticlesDocument.h"

// ================= MEMBER FUNCTIONS =======================

// ---------------------------------------------------------
// CParticlesApp::AppDllUid()
// Returns application UID
// ---------------------------------------------------------
//
TUid CParticlesApp::AppDllUid() const
    {
    return KUidParticles;
    }


// ---------------------------------------------------------
// CParticlesApp::CreateDocumentL()
// Creates CParticlesDocument object
// ---------------------------------------------------------
//
CApaDocument* CParticlesApp::CreateDocumentL()
    {
    return CParticlesDocument::NewL( *this );
    }

// ================= OTHER EXPORTED FUNCTIONS ==============

// ---------------------------------------------------------
// NewApplication()
// Creates and returns the CParticlesApp object
// ---------------------------------------------------------
//
CApaApplication* NewApplication()
    {
    return new CParticlesApp;
    }

// ---------------------------------------------------------
// E32Main()
// Main entry point for exe application. Creates and starts
// the rest of the application.
// ---------------------------------------------------------
//
TInt E32Main()
    {
    return EikStart::RunApplication(NewApplication);
    }

// End of File

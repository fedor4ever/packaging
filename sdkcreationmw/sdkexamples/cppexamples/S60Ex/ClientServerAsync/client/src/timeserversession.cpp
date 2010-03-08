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
#include <e32math.h>

#include "ClientServerCommon.h"
#include "TimeServerSession.h"

// FUNCTION PROTOTYPES
static TInt StartServer();
static TInt CreateServerProcess();

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// RTimeServerSession::RTimeServerSession()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
RTimeServerSession::RTimeServerSession()
: RSessionBase(), iTimeBuffer( NULL, 0, 0 )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// RTimeServerSession::Connect()
// Connects to the server and create a session.
// -----------------------------------------------------------------------------
//
TInt RTimeServerSession::Connect()
    {
    TInt error = ::StartServer();

    if ( KErrNone == error )
        {
        error = CreateSession( KTimeServerName,
                               Version(),
                               KDefaultMessageSlots );
        }
    return error;
    }

// -----------------------------------------------------------------------------
// RTimeServerSession::Version()
// Gets the version number.
// -----------------------------------------------------------------------------
//
TVersion RTimeServerSession::Version() const
    {
    return( TVersion( KTimeServMajorVersionNumber,
                      KTimeServMinorVersionNumber,
                      KTimeServBuildVersionNumber ) );
    }

// -----------------------------------------------------------------------------
// RTimeServerSession::RequestTime()
// Issues a request for the time to the server.
// -----------------------------------------------------------------------------
//
void RTimeServerSession::RequestTime( TTime& aTime, TRequestStatus& aStatus )
    {
    iTimeBuffer.Set( reinterpret_cast<TUint8*>( &aTime ), sizeof( aTime ),
                     sizeof( aTime ) );
    
    // Package message arguments before sending to the server
    TIpcArgs args( &iTimeBuffer );
    
    // This call completes immediately, however the server will not
    // complete the request until later, so don't pass any local
    // descriptors as they will be out of scope by the time the server
    // attempts to write to them
    SendReceive( ETimeServRequestTime, args, aStatus );
    }

// -----------------------------------------------------------------------------
// RTimeServerSession::CancelRequestTime()
// Cancels any outstanding request to the server.
// -----------------------------------------------------------------------------
void RTimeServerSession::CancelRequestTime() const
    {
    SendReceive( ETimeServCancelRequestTime, TIpcArgs(NULL) );
    }

// ============================= OTHER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// StartServer()
// Starts the server if it is not already running
// -----------------------------------------------------------------------------
//
static TInt StartServer()
    {
    TInt result;

    TFindServer findTimeServer( KTimeServerName );
    TFullName name;

    result = findTimeServer.Next( name );
    if ( result == KErrNone )
        {
        // Server already running
        return KErrNone;
        }

    RSemaphore semaphore;
    result = semaphore.CreateGlobal( KTimeServerSemaphoreName, 0 );
    if ( result != KErrNone )
        {
        return  result;
        }

    result = CreateServerProcess();
    if ( result != KErrNone )
        {
        return  result;
        }

    semaphore.Wait();
    semaphore.Close();

    return KErrNone;
    }

// -----------------------------------------------------------------------------
// CreateServerProcess()
// Creates a server process
// -----------------------------------------------------------------------------
//
static TInt CreateServerProcess()
    {
    TInt result;

    const TUidType serverUid( KNullUid, KNullUid, KServerUid3 );

    RProcess server;

    result = server.Create( KTimeServerFilename, KNullDesC, serverUid );

    if ( result != KErrNone )
        {
        return  result;
        }

    server.Resume();
    server.Close();

    return  KErrNone;
    }


// End of File

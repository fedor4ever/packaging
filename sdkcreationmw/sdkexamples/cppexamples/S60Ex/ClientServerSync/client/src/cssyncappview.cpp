/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
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
#include <coemain.h>
#include <eikenv.h>

#include <avkon.rsg>
#include "CSSyncAppView.h"
#include "CSSyncDocument.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CCSSyncAppView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCSSyncAppView* CCSSyncAppView::NewL( const TRect& aRect,
                                      CCSSyncDocument& aDocument )
    {
    CCSSyncAppView* self = CCSSyncAppView::NewLC( aRect, aDocument );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CCSSyncAppView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CCSSyncAppView* CCSSyncAppView::NewLC( const TRect& aRect,
                                       CCSSyncDocument& aDocument )
    {
    CCSSyncAppView* self = new ( ELeave ) CCSSyncAppView( aDocument );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CCSSyncAppView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CCSSyncAppView::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CCSSyncAppView::CCSSyncAppView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CCSSyncAppView::CCSSyncAppView( CCSSyncDocument& aDocument )
: iDocument( aDocument )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CCSSyncAppView::~CCSSyncAppView()
// Destructor.
// -----------------------------------------------------------------------------
//
CCSSyncAppView::~CCSSyncAppView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CCSSyncAppView::Draw()
// Draws this CCSSyncAppView to the screen.
// -----------------------------------------------------------------------------
//
void CCSSyncAppView::Draw( const TRect& /*aRect*/ ) const
    {

    // Clear the screen
    CWindowGc& gc = SystemGc();
    gc.Clear( Rect() );

    TBuf<30> des;
    const TTime& time = iDocument.Time();

    // Read time format string from AVKON resource
    HBufC* timeFormatString = iEikonEnv->AllocReadResourceLC(R_QTN_TIME_LONG);
    // It would also be possible to define your own format string instead, 
    // for example like this:
    // _LIT( KHoursMinsSecs, "%-B%:0%J%:1%T%:2%S%:3%+B" );

    TRAPD( err, time.FormatL( des, *timeFormatString ) );
    CleanupStack::PopAndDestroy(); // timeFormatString

    if ( err == KErrNone )
        {
        const CFont* font = iEikonEnv->NormalFont();
        gc.UseFont( font );
        gc.DrawText( des, TPoint( 10,20 ) );
        }
    }


// End of File


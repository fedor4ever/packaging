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
* Description:  Declares container control for Browser Control Sample application.
*
*/


#ifndef BRCTLSAMPLEAPPCONTAINER_H
#define BRCTLSAMPLEAPPCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include "BrCtlInterface.h"

// FORWARD DECLARATIONS
class CBrCtlSampleAppSpecialLoadObserver;
class CBrCtlSampleAppLayoutObserver;
class CBrCtlSampleAppSoftkeysObserver;
class CBrCtlSampleAppLoadEventObserver;
class CBrCtlSampleAppLinkResolver;
class CBrCtlSampleAppStateChangeObserver;
class CBrCtlSampleAppDialogsProvider;

// CLASS DECLARATION

/**
*  CBrCtlSampleAppContainer class.
*  This is the container control class.
*/
class CBrCtlSampleAppContainer : public CCoeControl, MCoeControlObserver, MBrCtlDataLoadSupplier
    {
    public: // Constructors and destructor
        
        /**
        * EPOC default constructor.
        * @param aRect Frame rectangle for container.
        */
        void ConstructL(const TRect& aRect);

        /**
        * Destructor.
        */
        ~CBrCtlSampleAppContainer();

    public: // New functions

        /**
        * Pass a command to the Browser Control
        * @since 2.8
        * @param aCommand The command that the Browser Control should process
        * @return void
        */
        void HandleCommandL(TInt aCommand);

        /**
        * Dynamically initialises a menu pane. The Uikon framework calls this 
        *   function, if it is implemented in a menu�s observer, immediately before 
        *   the menu pane is activated. 
        * @since 2.8
        * @param aResourceId Resource ID identifying the menu pane to initialise
        * @param aMenuPane The in-memory representation of the menu pane.
        * @return void
        */
        void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);

        /**
        * Handles key events
        * @since 2.8
        * @param aKeyEvent The key event that occurred.
        * @param aType The window server event type that is being handled
        * @return TKeyResponse Value indicates whether or not the key event was consumed by the control. The default implementation simply returns EKeyWasNotConsumed.
        */
        TKeyResponse HandleKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
        
        /**
        * Accessor method for iText
        * @since 2.8
        * @param void
        * @return TDesc& The descriptor of the text
        */
        inline const TDesC& Text() const {return iText;}
       
        /**
        * Setter method for iText
        * @since 2.8
        * @param aText The descriptor for the text you wish to display
        * @return void
        */
        void SetText( const TDesC& aText );
        
        /**
        * Setter method for iPoint
        * @since 2.8
        * @param aPoint The point at which you want to display the text
        * @return void
        */
        void SetPoint( const TPoint& aPoint );
        
        /**
        * Accessor method iBrCtlInterface
        * @since 2.8
        * @param void
        * @return CBrCtlInterface* A pointer to the browser control interface as a convenience to the observers
        */
        inline CBrCtlInterface* BrCtlInterface() const {return iBrCtlInterface;}

    private: // Functions from base classes

        /**
        * From CoeControl,SizeChanged.
        */
        void SizeChanged();

        /**
        * From CoeControl,CountComponentControls.
        */
        TInt CountComponentControls() const;

        /**
        * From CCoeControl,ComponentControl.
        */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
        * From CCoeControl,Draw.
        */
        void Draw(const TRect& aRect) const;

        /**
        * Handle key events.
        */
        TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);

        /**
        * From MBrCtlDataLoadSupplier, Cancel an on-going load
        */
        void CancelLoad();

        /**
        * Create a Basic Browser Control that does not have observers with scrolling
        * and HTTP framework capabilities
        */
        void CreateBasicBrowserControlL();

        /**
        * Create Browser Control with observers with the given capabilities
        */
        void CreateBrowserControlWithObserversL(TUint aCapabilities);

	    /**
        * Read the file.
        */
        HBufC8* ReadFileLC(const TDesC& aFileName);

        /**
        * Handles an event from an observed control.
        */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);
        
        /**
        * The following methods are used to demonstrate the functionality of 
        * the browser control API
        */
        void BasicBrowserControlL();
        void BrowserControlWithObserversL();
        void LoadingContentWithFileHandleL();
        void LoadingContentWithBufferL();
        void IncrementalLoadingL();
        void SpecialLoadRequestsL();
        void CustomizedDialogsL();
        void CustomizedSoftKeysL();
        void ResolvingEmbeddedLinksL();
        void CustomizedScrollBarsL();
        void HandleStateChangedL();
        void ChangeSizeExtentsL();
        void PageInfoL();
        void ContentSizeImageCountL();
        
    private: //data 
        // Pointer to the browser control interface
        CBrCtlInterface* iBrCtlInterface;
        // Desired capabilities of the browser control
        TUint iBrCtlCapabilities;
        // Command Base
        TInt iCommandBase;
        // Special Load Observer
        CBrCtlSampleAppSpecialLoadObserver* iBrCtlSampleAppSpecialLoadObserver;
        // Layout Observer
        CBrCtlSampleAppLayoutObserver* iBrCtlSampleAppLayoutObserver;
        // Softkeys Observer
        CBrCtlSampleAppSoftkeysObserver* iBrCtlSampleAppSoftkeysObserver;
        // Load Event Observer
        CBrCtlSampleAppLoadEventObserver* iBrCtlSampleAppLoadEventObserver;
        // Link Resolver
        CBrCtlSampleAppLinkResolver* iBrCtlSampleAppLinkResolver;
        // State Change Observer
        CBrCtlSampleAppStateChangeObserver* iBrCtlSampleAppStateChangeObserver;
        // Dialogs Provider
        CBrCtlSampleAppDialogsProvider* iBrCtlSampleAppDialogsProvider;
        // Informs whether or not CancelLoad has been called
        TBool iCancelInitDataLoad;
        // A graphics device to which a bitmap managed by the font and bitmap server can be drawn
        CFbsScreenDevice* iFbsScrDev;
        // Abstract font interface
        CFont* iFont;
        // Text to display to the screen if desired
        TPtrC iText;
        // Point at which to display text
        TPoint iPoint;
    };

#endif

// End of File


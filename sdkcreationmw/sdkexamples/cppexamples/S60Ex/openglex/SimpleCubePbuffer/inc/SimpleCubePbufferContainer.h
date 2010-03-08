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


#ifndef SIMPLECUBEPBUFFERCONTAINER_H
#define SIMPLECUBEPBUFFERCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <GLES/egl.h>
#include <akndef.h>
#include <aknappui.h> 
#include "SimpleCubePbuffer.h"

// CLASS DECLARATION

/**
 * Container control class that handles the OpenGL ES initialization and deinitializations.
 * Also uses the CSimpleCubePbuffer class to do the actual OpenGL ES rendering.
 */
class CSimpleCubePbufferContainer : public CCoeControl, MCoeControlObserver
    {
    public: // Constructors and destructor

        /**
         * EPOC default constructor. Initializes the OpenGL ES for rendering to the PBuffer surface.
         * @param aRect Screen rectangle for container.
         */
        void ConstructL(const TRect& aRect, CAknAppUi* aAppUi);

        /**
         * Destructor. Destroys the CPeriodic, CSimpleCubePbuffer and uninitializes OpenGL ES.
         */
        virtual ~CSimpleCubePbufferContainer();

    public: // New functions

        /**
         * Callback function for the CPeriodic. Calculates the current frame, keeps the background
         * light from turning off and orders the CSimpleCubePbuffer to do the rendering for each frame.
         *@param aInstance Pointer to this instance of CSimpleCubePbufferContainer.
         */
        static TInt DrawCallBack( TAny* aInstance );

    private: // Functions from base classes


        /**
         * Method from CoeControl that gets called when the display size changes.
         * If OpenGL has been initialized, notifies the renderer class that the screen
         * size has changed.
         */
        void SizeChanged();

        /**
         * Handles a change to the control's resources. This method
         * reacts to the KEikDynamicLayoutVariantSwitch event (that notifies of
         * screen size change) by calling the SetExtentToWholeScreen() again so that
         * this control fills the new screen size. This will then trigger a call to the
         * SizeChanged() method.
         * @param aType Message UID value, only KEikDynamicLayoutVariantSwitch is handled by this method.
         */
        void HandleResourceChange(TInt aType);

        /**
         * Method from CoeControl. Does nothing in this implementation.
         */
        TInt CountComponentControls() const;

        /**
         * Method from CCoeControl. Does nothing in this implementation.
         */
        CCoeControl* ComponentControl(TInt aIndex) const;

        /**
         * Method from CCoeControl. Does nothing in this implementation.
         * All rendering is done in the DrawCallBack() method.
         */
        void Draw(const TRect& aRect) const;


        /**
         * Method from MCoeControlObserver that handles an event from the observed control.
         * Does nothing in this implementation.
		 * @param aControl   Control changing its state.
		 * @param aEventType Type of the control event.
         */
        void HandleControlEventL(CCoeControl* aControl,TCoeEvent aEventType);

    private: //data

        /** Display where the OpenGL ES surface resides. */
        EGLDisplay  iEglDisplay;

        /** PBuffer surface that is the target of OpenGL ES graphics rendering. */
        EGLSurface  iEglSurface;

        /** Describes the format, type and size of the color buffers and ancillary buffers for EGLSurface. */
        EGLConfig iConfig;

        /** OpenGL ES rendering context. */
        EGLContext  iEglContext;

        /** Active object that is the timing source for the animation. */
        CPeriodic*  iPeriodic;

        // A bitmap where the framebuffer is drawn
        CWsBitmap*  iPixmap;

        /**
         * Flag that indicates if OpenGL ES has been initialized or not.
         * Used to check if SizeChanged() can react to incoming notifications.
         */
        TBool iOpenGlInitialized;

/** Application UI class for querying the client rectangle size. */ 
        CAknAppUi* iAppUi;

    public:  //data

        /** Frame counter variable, used in the animation. */
        TInt iFrame;

        /** Used in DrawCallBack() method to do the actual OpenGL ES rendering.  */
        CSimpleCubePbuffer* iSimpleCubePbuffer;
    };

#endif

// End of File

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


#ifndef __FLOATINGDUCKH__
#define __FLOATINGDUCKH__

//  INCLUDES

#include <e32base.h> // for CBase definition
#include <GLES\gl.h> // OpenGL ES header file
#include "utils3d.h" // OpenGL ES Example Utilities
#include "glutils.h" // Misc GLU and GLUT methods
#include "duck.h"    // Duck model

/**
 * Class that does the actual OpenGL ES rendering.
 * Subclass of CFiniteStateMachine because the application
 * needs to handle loading textures and running states.
 */
class CFloatingDuck
	: public CFiniteStateMachine, public MTextureLoadingListener
	{
	public: // Constructors and destructor

        /**
         * Factory method for creating a new CFloatingDuck object.
		 * Calls the hidden constructors.
         */
		static CFloatingDuck* NewL( GLuint aWidth, GLuint aHeight );

        /**
         * Destructor. Does nothing.
         */
		virtual ~CFloatingDuck();

	protected: // Hidden constructors

        /**
         * Standard constructor that must never Leave.
         * Stores the given screen width and height.
         * @param aWidth Width of the screen.
         * @param aHeight Height of the screen.
         */
		CFloatingDuck( GLuint aWidth, GLuint aHeight );

        /**
         * Second phase constructor that can call methods that may leave. Does nothing.
         */
		void ConstructL( void );


	public: // New methods

        /**
         * Initializes OpenGL ES, sets the vertex and color
         * arrays and pointers. Also selects the shading mode and
         * creates the CTextureManager instance and starts loading
         * of required textures.
         */
		void AppInitL( void );

        /**
         * Called upon application exit. Destroys the CTextureManager
         * instance that was created in AppInitL() method.
         */
		void AppExit( void );

        /**
         * Renders one frame.
         * @param aFrame Number of the frame to be rendered.
		 * @param aTimeSecs Seconds elapsed since the application started running.
		 * @param aDeltaTimeSecs Seconds elapsed since last call to AppCycle().
         */
		void AppCycle( GLuint aFrame, GLfloat aTimeSecs, GLfloat aDeltaTimeSecs );

    	/**
    	 * Called when the finite state machine enters a new state.
    	 * Does nothing in this implementation.
    	 * @param aState State that is about to be entered.
    	 */
		void OnEnterStateL( TInt aState);

    	/**
    	 * Called when texture manager starts loading the textures.
    	 * Sets the current state to "loading textures".
    	 */
		void OnStartLoadingTexturesL();

    	/**
    	 * Called when texture manager has completed texture loading.
    	 * Changes the current state to "running".
    	 */
		void OnEndLoadingTexturesL();

        /**
         * Notifies that the screen size has dynamically changed during execution of
         * this program. Resets the viewport to this new size and sets this size
         * to the CTextureManager.
         * @param aWidth New width of the screen.
         * @param aHeight New height of the screen.
         */
        void SetScreenSize( GLuint aWidth, GLuint aHeight );

    private: // Internal methods

        /**
         * Draws the duck and uses the clip plane to clip it to water surface.
         * @param aFrame Number of the frame to be rendered.
		 * @param aTimeSecs Seconds elapsed since the application started running.
		 * @param yScale Scale of the duck in y-axis.
         */
        void DrawDuck( GLuint aFrame, GLfloat aTimeSecs, GLfloat yScale );

        /**
         * Draws the semitransparent water surface.
         * @param aFrame Number of the frame to be rendered.
		 * @param aTimeSecs Seconds elapsed since the application started running.
         */
        void DrawWater( GLuint aFrame, GLfloat aTimeSecs );

        /**
         * Draws the semitransparent water surface ripples.
         * @param aFrame Number of the frame to be rendered.
		 * @param aTimeSecs Seconds elapsed since the application started running.
         */
        void DrawRipples( GLuint aFrame, GLfloat aTimeSecs );

	public: // Data
    	/**
    	 * Application states:
    	 * ELoadingTextures - indicates that the app. is loading textures.
    	 * ERunning - indicates that the app. is running.
    	 */
		enum
		{
		ELoadingTextures,
		ERunning
		};

	private: // Data

        /** Width of the screen */
        GLuint iScreenWidth;
        /** Height of the screen */
        GLuint iScreenHeight;
        /** Camera. */
		TCamera iCamera;
		/** Up and down y-axis offset for the duck. */
		GLfloat iDuckOffset;

		/** Buffer object id that referes to the duck vertex data. */
		GLuint iVertexDataBufferId;
		/** Buffer object id that referes to the duck normal data. */
		GLuint iNormalDataBufferId;
		/** Buffer object id that referes to the duck indices data. */
		GLuint iIndexDataBufferId;
        /** Ripple vertex data */
        GLfloat* iRippleVertices;
        /** Ripple index data */
        GLushort* iRippleIndices;
	};

#endif

// End of File


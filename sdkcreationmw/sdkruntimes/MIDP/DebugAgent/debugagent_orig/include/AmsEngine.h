/*
* Copyright (c) 2004 Nokia Corporation and/or its subsidiary(-ies).
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


#ifndef HEADER_AGENT_ENGINE
#define HEADER_AGENT_ENGINE

#include "AgentEngine.h"


class CAmsEngine : public CAgentEngine
	{
public:
	CAmsEngine (CDriver* aDriver);
	~CAmsEngine ();
public:
	// jar and jad
	virtual TInt InstallL(HBufC* aJad, HBufC* aJar, TBool aTrusted);
	// remove by name and vendor
	virtual void RemoveL(HBufC* aName, HBufC* aVendor);
	};

#endif
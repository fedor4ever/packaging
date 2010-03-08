/*
* Copyright (c) 2000 - 2005 Nokia Corporation and/or its subsidiary(-ies).
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


/*
 * Created on Aug 20, 2004
 *
 * To change this generated comment go to
 * Window>Preferences>Java>Code Generation>Code and Comments
 */
package com.nokia.wtk.sdkSimulator.diagnosticsAdapter;

import com.nokia.wtk.device.DeviceMessageListener;


/**
 * <p>Title: SMSAdapter</p>
 * <p>Description: Specifies the APIs bewteen the SDK and an adapter object for
 *  SMS traffic events.
 *  For this simple implementation of the diagnostics adapter, the interface
 *  just extends the DeviceMessageListener interface with no additions.
 *  However, this doesn't have to be the case: DeviceMessageListener is
 *  the interface to the Diagnostics component itself, while SMSAdapter
 *  is the interface between the SDK and the diagnostics adapter. The two interfaces
 *  may be different. </p>
 * <p>Company: Nokia</p>
 * @version 1.0
 */
public interface SMSAdapter extends DeviceMessageListener {
}




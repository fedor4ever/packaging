/*
* Copyright (c) 1999 - 2004 Nokia Corporation and/or its subsidiary(-ies).
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

package com.symbian;

import com.symbian.utils.*;
import com.symbian.tools.j2me.sei.SDKRuntimeProperties;

import junit.framework.*;

/**
 * Conatains all API tests, naive and win32 tests.
 *
 * <p>Title: PREQ 425</p>
 * <p>Description: Java debugging</p>
 * <p>Copyright: Copyright (c) 2004 By Symbian Ltd. All Rights Reserved</p>
 * <p>Company: Symbian Ltd</p>
 * @author Roy Ben Hayun
 * @version 2.0
 */
public class PREQ425AllTests extends PREQ425AllAPITests {

  public PREQ425AllTests(String s) {
    super(s);
  }

  public static Test suite() {
    TestSuite suite = (TestSuite)(PREQ425AllAPITests.suite());
    suite.addTest(com.symbian.tools.j2me.sei.emulator.AllNaiveTests.suite());
    suite.addTest(com.symbian.tools.j2me.sei.emulator.AllWin32Tests.suite());
    return suite;
  }
}

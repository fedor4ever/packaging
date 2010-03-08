/*
* Copyright (c) 2003 - 2004 Nokia Corporation and/or its subsidiary(-ies).
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

package com.symbian.utils;

/**
 * Enables to control access to System.exit calls.
 * This is required in the tests inorder to keep the tests running.
 * The default operation is to exit with the given code.
 *
 * <p>Title: PREQ 425</p>
 * <p>Description: Java debugging</p>
 * <p>Copyright: Copyright (c) 2004 By Symbian Ltd. All Rights Reserved</p>
 * <p>Company: Symbian Ltd</p>
 * @author Roy Ben Hayun
 * @version 2.0
 */
public class SystemExitHandler {

  //
  // Static members
  //

  /**
   * Indicates if to exit
   */
  private static boolean sExit = true;

  /**
   * Exit listener
   */
  private static SystemExitListener iListener;

  /**
   * Indicates exiting was already called
   */
  private static boolean iAlreadyInvoked = false;


  //
  // Operations
  //

  static
  {
    //enable clean shutdown
    Runtime.getRuntime().addShutdownHook(new Thread("shutdown-hook-Thread")
    {
      public void run()
      {
        try
        {
          Debug.println(this, "+ShutdownHook " + this);
          if(!iAlreadyInvoked && iListener != null)
          {
            Debug.println(this, "iListener.systemExitInvoked");
            iListener.systemExitInvoked();
          }
        }
        finally
        {
          Debug.println(this, "-ShutdownHook " + this);
        }
      }
    });
  }

  /**
   * Let the handler know about required System.exit call
   *
   * @param aExitCode exit code
   */
  public static synchronized final void invokeSystemExit(int aExitCode){
    Debug.println
        (SystemExitHandler.class,
         "SystemExitHandler.invokeSystemExit(" + aExitCode
         + "). already invoked=" + iAlreadyInvoked);
    if(!iAlreadyInvoked)
    {
      //set flag
      iAlreadyInvoked = true;
      //allow listener to cleanup
      if(iListener != null)
      {
        try {
          iListener.systemExitInvoked();
        }
        catch (Exception ex) {
          Debug.printStackTrace(SystemExitHandler.class, ex);
        }
        iListener = null;
      }
      if (sExit)
      {
        final String str = "-System.exit(" + aExitCode + ")";
        Debug.println
            (SystemExitHandler.class,
             "SystemExitHandler.invokeSystemExit() is calling " + str);
        //System.out.println(str);
        System.exit(aExitCode);
      }
    }
  }
  /**
   * Set System exit handler behaviour
   *
   * @param aExit Indicates if to exit
   */
  public static final void setExitOperation(boolean aExit){
    sExit = aExit;
  }

  /**
   * Set listener
   * @param aListener SystemExitListener
   */
  public static final void setExitListener(SystemExitListener aListener){
    iListener = aListener;
    iAlreadyInvoked = false;//patch for JUnit
  }

}

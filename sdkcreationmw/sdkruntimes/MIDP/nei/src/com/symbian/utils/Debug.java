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

import java.io.*;
import java.util.*;
import com.symbian.tools.j2me.sei.emulator.*;
import com.symbian.tools.j2me.sei.preferences.CommandLinePreferences;

import com.symbian.io.StreamsPiper;

/**
 * Debug class to print to System.out and to log files.
 *
 * <p>Copyright: Copyright (c) 2003 By Symbian Ltd. All Rights Reserved.</p>
 * <p>Company: Symbian Ltd</p>
 * @author Roy Ben Hayun
 * @version 1.1 (CLDC-HI)
 */
public class Debug
{

  /**
   * Logs folder
   */
  private static final String DEF_LOGS_FOLDER = "C:\\";

  /**
   * Main log file
   */
  private static final String MAIN_LOG = "mainlog";

  //
  // Static Memebers
  //


  /**
   * Logs folder
   */
  private static String sLogsFolder = DEF_LOGS_FOLDER;

  /**
   * Mute all printing
   */
  private static boolean sMute = System.getProperty("sei.trace.mute") == null ||
                                 Boolean.getBoolean("sei.trace.mute");

  /**
   * Log all flags
   */
  private static boolean sWildCard = Boolean.getBoolean("sei.trace.all");

  /**
   * main log file printer
   */
  private static PrintStream sPrinter;

  /**
   * Log to System.out
   */
  private static boolean sUseSystemOUT = Boolean.getBoolean("sei.trace");

  /**
   * Set of flags
   */
  private static Set sFlags = new HashSet();

  /**
   * Table of flags with optional PrintStream
   */
  private static Map sFlags2Printers = new HashMap();


  /**
   * Static Initialization
   * setFlag method is private, therefor this is the only place to
   * enable/disable logging.
   *
   * @param folder logs folder
   */
  public static final void init(String folder)
  {
    sLogsFolder = folder;
    new File(folder).mkdirs();

    if(!sMute)
    {
      //force finalization
      System.runFinalization();

      sWildCard = true;
      //init flags
      //setFlag("history", true);
      //setFlag(Debug.class.getName(), true);
      //setFlag(kdp.Log.class.getName(), true);
      //setFlag(EmulatorLauncher.class.getName(), true);
      //setFlag(KDPAgentLauncher.class.getName(), false);
      //setFlag("kdp.SocketConnection", true);

      //init main log file
      try
      {
        sPrinter = new PrintStream(new FileOutputStream(getLogFile(MAIN_LOG)));
      }
      catch (Exception ex)
      {
        ex.printStackTrace();
      }
    }
  }

  /**
   * init specific debug settings
   */
  public static final void initLogSettings(CommandLinePreferences aPrefs){
    sMute = false;//aPrefs.isLoggingEnabled();
    if(!aPrefs.isLogFileEnabled()){
      //releasePrinters();
    }
  }

  /**
   * Flush the streams and close them
   *
   * @throws Throwable
   */
  protected void finalize() throws Throwable
  {
    releasePrinters();
    super.finalize();
  }


  /**
   * Release printers resources
   */
  private static final void releasePrinters(){
    //main print stream
    if(sPrinter != null){
      sPrinter.flush();
      sPrinter.close();
      sPrinter = null;
    }
    //various flags printers
    Iterator printStreams = sFlags2Printers.values().iterator();
    while(printStreams.hasNext()){
      PrintStream ps = (PrintStream)printStreams.next();
        try {
          ps.flush();
          ps.close();
        }
        catch (Exception ex) {
          System.out.println(ex.getMessage());
        }
    }
  }



  /**
   * Get a log file in the logs folder
   *
   * @param flag flag name
   * @return new log file
   */
  static synchronized File getLogFile(String flag)
  {
    return new File(sLogsFolder + File.separator + flag + ".log");
  }



  /**
   * Enable/disable a flag
   *
   * @param flag new flag
   * @param file indicates if to create a new log file only for this flag
   */
  private static synchronized void setFlag(String flag, boolean file)
  {
    sFlags.add(flag);
    if(file && !sMute)
    {
      try
      {
        sFlags2Printers.put(flag,
                            new PrintStream(new FileOutputStream(
                                            getLogFile(flag))));
      }
      catch (Exception ex)
      {
        System.out.println("Could not create PrintStream for debug log file");
      }
    }
  }


  /**
   * Print string
   *
   * @param o the object should have his class name set as a flag
   * @param o2 convert with toString()
   */
  public synchronized static final void println(Object o, Object o2)
  {
    println(o.getClass().getName(), o2.toString());
  }


  /**
   * Print array of string
   *
   *
   * @param o the object should have his class name set as a flag
   * @param args string array
   */
  public synchronized static final void println(Object o, String[] args){
    for(int i = 0; i < args.length; i++)
    {
      print(o, args[i] + " ");
    }
    println();

  }


  /**
   * Print string
   *
   * @param o the object should have his class name set as a flag
   * @param s string to log
   */
  public synchronized static final void println(Object o, String s)
  {
    println(o.getClass().getName(), s);
  }



  /**
   * Print string
   *
   * @param flag flag name
   * @param s string to log
   */
  public synchronized static final void println(String flag, String s)
  {
    if ((sFlags.contains(flag) || sWildCard) && !sMute)
    {
      if (sUseSystemOUT)
      {
        System.out.println(s);
      }
      if(sPrinter != null){
        sPrinter.println(s);
        sPrinter.flush();
      }
      PrintStream ps = (PrintStream)sFlags2Printers.get(flag);
      if(ps != null)
      {
        ps.println(s);
        ps.flush();
      }
    }
  }



  /**
   * Print string
   *
   * @param o the object should have his class name set as a flag
   * @param s string to log
   */
  public synchronized static final void print(Object o, String s)
  {
    print(o.getClass().getName(), s);
  }



  /**
   * Print string
   *
   * @param flag flag name
   * @param s string to log
   */
  public synchronized static final void print(String flag, String s)
  {
    if ((sFlags.contains(flag) || sWildCard) && !sMute)
    {
      if (sUseSystemOUT)
      {
        System.out.print(s);
      }
      if(sPrinter != null){
        sPrinter.print(s);
      }
      PrintStream ps = (PrintStream)sFlags2Printers.get(flag);
      if(ps != null)
      {
        ps.print(s);
        ps.flush();
      }
    }
  }



  /**
   * Print exception
   *
   * @param o the object should have his class name set as a flag
   * @param s string to log
   */
  public synchronized static final void printStackTrace(Object o, Throwable t)
  {
    printStackTrace(o.getClass().getName(), t);
  }



  /**
   * Print excpetion
   *
   * @param flag flag name
   * @param s string to log
   */
  public synchronized static final void printStackTrace(String flag,
                                                        Throwable t)
  {
    if ((sFlags.contains(flag) || sWildCard) && !sMute)
    {
      if (sUseSystemOUT)
      {
        t.printStackTrace();
      }
      if(sPrinter != null){
        t.printStackTrace(sPrinter);
        sPrinter.flush();
      }
      PrintStream ps = (PrintStream)sFlags2Printers.get(flag);
      if(ps != null)
      {
        t.printStackTrace(ps);
        ps.flush();
      }
    }
  }



  /**
   * Print new line
   */
  public synchronized static final void println()
  {
    println(Debug.class.getName(), "\n");
  }

  /**
   * Append string array to end of existing log file
   *
   * @param flag flag name
   * @param args string array
   */
  public synchronized static final void append(String flag, String[] args)
  {
    StringBuffer buffer = new StringBuffer();
    for (int i = 0; i < args.length; i++)
    {
      buffer.append(args[i]).append(" ");
    }
    append(flag, buffer.toString());
  }

  /**
   * Append string to end of existing log file
   *
   * @param flag flag name
   * @param s string to log
   */
  public synchronized static final void append(String flag, String s)
  {
    if(!sMute)
    {
      try
      {
        RandomAccessFile file = new RandomAccessFile(getLogFile(flag), "rw");
        file.skipBytes( (int) (Math.max(0, file.length())));
        file.writeBytes(s);
        file.close();
      }
      catch (Exception ex)
      {
        Debug.printStackTrace(Debug.class.getName(), ex);
      }
    }
  }


  /**
   * Print Manifest properties
   *
   * @param manifest SEIManifest
   */
  public static final void printAttributes(String flag, SEIManifest manifest)
  {
    Debug.println(flag, "SEIManifest attributes: keys.size()= " + manifest.getMainAttributes().size());
    String key;
    for (Iterator iter = manifest.getMainAttributes().keySet().iterator(); iter.hasNext(); ) {
      key = (String) iter.next();
      Debug.println(flag, key + ": " + manifest.getMainAttributes().get(key));
    }
  }


//  public static final void pipeOutput(String flag, InputStream in) {
//    //pipeOutput cant be muted
//    //flag is only regarding log file and not System.out
//    FileOutputStream fos = null;
//    String name = StreamsPiperServiceThread.getUniqueName();
//    if (sFlags.contains(flag) || sWildCard) {
//      try {
//        fos = new FileOutputStream(Debug.getLogFile(name));
//      }
//      catch (Exception ex) {
//        Debug.printStackTrace(Debug.class.getName(), ex);
//      }
//    }
//    new StreamsPiperServiceThread(name, in, fos).start();
//  }


}








/**
 * Thread to pipe output
 */
//class StreamsPiperServiceThread extends Thread
//{
//
//  //
//  // Constants
//  //
//
//  /**
//   * Threads name
//   */
//  private static final String NAME = "StreamsPiperServiceThread";
//
//  //
//  // Memebers
//  //
//
//  /**
//   * Threads counter
//   */
//  private static int counter = 0;
//
//  /**
//   * Source input stream
//   */
//  private InputStream iIn;
//
//  /**
//   * Optional log file
//   */
//  private FileOutputStream iFos;
//
//  /**
//   * create a new piper thread
//   *
//   * @param in input stream
//   * @param aFos file output stream
//   */
//  StreamsPiperServiceThread(String aName, InputStream in, FileOutputStream aFos)
//  {
//    super(aName);
//    setDaemon(true);
//    iIn = in;
//    iFos = aFos;
//  }
//
//
//
//  protected void finalize() throws Throwable
//  {
//    if(iFos != null)
//    {
//      try
//      {
//        iFos.flush();
//        iFos.close();
//      }
//      catch (Exception ex)
//      {
//        ex.printStackTrace();
//      }
//    }
//    iFos = null;
//    super.finalize();
//  }
//
//
//
//  /**
//   * Thread run
//   */
//  public void run()
//  {
//    //output always goes to System.out
//    StreamsPiper p = new StreamsPiper(iIn, System.out);
//    if(iFos != null)
//    {
//      p.addOutputStream(iFos);
//    }
//    try
//    {
//      p.pipeAll();
//    }
//    catch (Exception ex)
//    {
//      Debug.printStackTrace(Debug.class.getName(), ex);
//    }
//  }
//
//  /**
//   * Return a unique name for Threads
//   *
//   * @return String unique name
//   */
//  public static String getUniqueName(){
//    return NAME + counter++;
//  }
//}

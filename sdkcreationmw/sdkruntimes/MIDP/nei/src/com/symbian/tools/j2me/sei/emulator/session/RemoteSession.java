// RemoteSession.java
//
// Copyright (c) Symbian Software Ltd 2003 - 2004.  All rights reserved.
//
package com.symbian.tools.j2me.sei.emulator.session;

import java.net.*;
import java.io.*;
import java.util.*;

import com.symbian.tools.j2me.sei.preferences.*;
import com.symbian.tools.j2me.sei.emulator.commands.*;
import com.symbian.tools.j2me.sei.emulator.session.commands.*;
import com.symbian.io.*;
import com.symbian.vm.*;
import com.symbian.utils.Debug;

/**
 * <p>Title: </p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: </p>
 * @author not attributable
 * @version 1.0
 */
public abstract class RemoteSession extends Session{

  /**
   * Abstraction interface to support various bearers
   *
   * CUSTOMIZATION NOTE: Licensees interested in other bearers should use
   * this hierarchy.
   */
  public interface SessionTransport {
      InputStream getInputStream() throws IOException;
      OutputStream getOutputStream() throws IOException;
      void close() throws IOException;
  }

  /**
   * TCP support.
   * NOTE: This is the only supported protocol by Symbian.
   *
   * CUSTOMIZATION NOTE: Licensees interested in other bearers should use
   * this hierarchy.
   */
  private abstract static class SocketTransport implements SessionTransport {
      protected Socket socket;
      public InputStream getInputStream() throws IOException {
        return socket.getInputStream();
      }
      public OutputStream getOutputStream() throws IOException {
        return socket.getOutputStream();
      }
      public void close() throws IOException {
          socket.close();
      }
      String getHostName() {
        return socket.getInetAddress().getHostName();
      }
  }

  /**
   * TCP support for client connections.
   * NOTE: This is the only supported protocol by Symbian.
   *
   * CUSTOMIZATION NOTE: Licensees interested in other bearers should use
   * this hierarchy.
   */
  private static class ClientSocketTransport extends SocketTransport {
      ClientSocketTransport(String host, int port) throws IOException {
        
    	  for(int attempt = 0; attempt<50; attempt++)
    	  {
	    	  try{
	    		  socket = new Socket(host, port);
	    		  break;
	    	  }
	    	  catch(IOException ex){
	    		try{
	    			  Thread.currentThread().sleep(3000);
	    		}
	    		catch(InterruptedException e){}
	    	  }
    	  
    	  }
    	  
      }
  }
  /**
   * TCP support for server connections.
   * NOTE: This is the only supported protocol by Symbian.
   *
   * CUSTOMIZATION NOTE: Licensees interested in other bearers should use
   * this hierarchy.
   */
  private static class ServerSocketTransport extends SocketTransport {
      ServerSocketTransport(int port) throws IOException {
        ServerSocket ss = new ServerSocket(port);
        socket = ss.accept();
        ss.close();
      }
  }

  //
  // Constants
  //

  /**
   * number of times to give the VM timeout to exit
   */
  private static final int NUM_TIMEOUT_ATTEMPTS = 20;

  /**
   * number of ms for each time out
   */
  private static final int VM_EXIT_TIMEOUT = 500;

  //
  // Members
  //

  /**
   * At the moment, TCP is the only transport we support.
   */
  private SessionTransport iTransport;

  /**
   * Connection output stream.
   * (The concrete subclasses should use streams)
   */
  private DataOutputStream iDos;

  /**
   * Connection input stream
   * (The concrete subclasses should use streams)
   */
  private DataInputStream iDis;






  //
  // Operations
  //


  /**
   * Send handshake command
   *
   * @param aChallenge challenge string
   *
   * @throws Exception if some error occured
   */
  protected void doHandshake(String aChallenge) throws Exception{
    new HandshakeCommand(aChallenge).execute(iDis, iDos);
  }




  /**
   * Connect to the SEI-Slave
   *
   * @throws IOException if some error occured
   */
  protected void connectToSlave() throws IOException{
    SocketTransport transport;
    if (iPrefs.isOutgoing())
    {
      Debug.println(this, "Outgoing connection to Agent");
      transport = new ClientSocketTransport(iPrefs.getHost(), iPrefs.getPort());
    }
    else
    {
      Debug.println(this, "Waiting for incoming connection from Agent");
      transport = new ServerSocketTransport(iPrefs.getLocalPort());
      //get the remote address from the incoming connection
      iPrefs.setHost(transport.getHostName());
    }
    Debug.println(this, "Connected to Agent");
    connectToSlave(transport);
  }


  /**
   * Connect to the SEI-Slave
   *
   * @param aTransport the transport to use
   * @throws IOException if some error occured
   */
  protected void connectToSlave(SessionTransport aTransport) throws IOException{
    iTransport = aTransport;
    iDis = new DataInputStream(iTransport.getInputStream());
    iDos = new DataOutputStream(iTransport.getOutputStream());
    Debug.println(this, "Connected to Agent");
  }


  /**
   * Start the MIDlet
   *
   * @param aMIDletInfo MIDlet to start
   *
   * @return VM process
   *
   * @throws Exception if some error occured
   */
  public synchronized VMProcess startMIDlet(VMLaunchArguments aVMLaunchArguments, boolean aDeferred) throws Exception {
    new StartVMCommand(aVMLaunchArguments, aDeferred).execute(iDis, iDos);
    aVMLaunchArguments.getMIDletInfo().setActive(true);
    final MIDletSuiteInfo info = aVMLaunchArguments.getMIDletInfo().getMIDletSuiteInfo();
    VMProcess process = new RemoteVMProcessImpl(this, info);
    iSuiteInfo2Process.put(info, process);
    return process;
  }


  /**
   * Start another MIDlet in the same suite VM which must be already running
   *
   * @param aMIDletInfo MIDlet info
   *
   * @throws Exception if some error occured
   */
  public synchronized void startMIDlet(MIDletInfo aMIDletInfo) throws Exception {
    new StartMIDletCommand(aMIDletInfo).execute(iDis, iDos);
    aMIDletInfo.setActive(true);
  }





  /**
   * Install the MIDlet suite with cached VM launch arguments that will be used
   * every time the MIDlets are started.
   * This is to enable debugging of pushed MIDlets.
   *
   * @param aJar MIDlet suite Jar file
   * @param aJad MIDlet suite Jad file
   * @param aVMLaunchArguments arguments to cache with the binaries
   *
   * @return MIDletSuiteInfo MIDlet suite information
   *
   * @throws Exception if some error occured
   */
  public synchronized MIDletSuiteInfo installMIDletSuite(JARFile aJar, JADFile aJad, boolean aTrusted) throws Exception {
    InstallCommand cmd = new InstallCommand(aTrusted, aJad, aJar);
    cmd.execute(iDis, iDos);
    return cmd.getMIDletSuiteInfo();
  }


  /**
   * Remove the MIDlet suite
   *
   * @param aSuiteInfo removed MIDlet suite info
   *
   * @throws Exception if some error occured
   */
  public synchronized void removeMIDletSuite(MIDletSuiteInfo aSuiteInfo) throws Exception {
    Debug.println(this, "Removing: " + aSuiteInfo.getSuiteName());
    int counter = 0;
    try
    {
      VMProcess vmProcess = (VMProcess)iSuiteInfo2Process.get(aSuiteInfo);
      while (vmProcess.isAlive() && counter++ < NUM_TIMEOUT_ATTEMPTS)
      {
        Debug.println(this, "VM process still running");
        wait(VM_EXIT_TIMEOUT);
      }
    }
    catch (Throwable t)
    {
      Debug.printStackTrace(this, t);
    }
    new RemoveCommand(aSuiteInfo).execute(iDis, iDos);
  }


  /**
   * Get the list of installed MIDlet suites
   *
   * @return list of installed MIDlet suites
   *
   * @throws Exception if some error occured
   */
  //public synchronized MIDletSuiteInfo[] getInstalledMIDletSuitesInfo() throws Exception {
    //get suites
    /*ListSuitesCommand listSuitesCmd = new ListSuitesCommand();
    listSuitesCmd.execute(iDis, iDos);
    MIDletSuiteInfo[] suites = listSuitesCmd.getInstalledSuites();
    return suites;*/
	 // return null;
  //}


  /**
   * Brute force terminate the sessions
   */
  public synchronized void terminate() {
    Debug.println(this, "+RemoteSession.terminate");
    //terminate running suites
    try {
      //for each suite
      for (Iterator iter = iSuiteInfo2Process.values().iterator(); iter.hasNext(); ) {
        //for each active MIDlet
        MIDletSuiteInfo suiteInfo = ((VMProcess)iter.next()).getMIDletSuiteInfo();
        MIDletInfo[] midletsInfo = suiteInfo.getMIDletsInfos();
        for(int i = 0; i < midletsInfo.length; i++){
          if(midletsInfo[i].isActive()){
            Debug.println(this, "Terminating: " + midletsInfo[i].getMIDletName());
            new TerminateCommand(midletsInfo[i]).execute(iDis, iDos);
          }
        }
      }
    }
    catch (Throwable t)    {
      Debug.printStackTrace(this, t);
    }

    //un-install suites
    try {
      //NOTE: removal might fail if VM didnt close yet
      removeAll();
    }
    catch (Throwable t) {
      Debug.printStackTrace(this, t);
    }
    iSuiteInfo2Process.clear();

    //socket cleanup
    try {
      iTransport.close();
    }
    catch (Exception e) {}
    iTransport = null;
    Debug.println(this, "-RemoteSession.terminate");
  }


  /**
   * Get a free port on the device
   *
   * @return int free port
   *
   * @throws Exception if some error occured
   */
    /*public synchronized int getFreePort() throws Exception {
      //get ports
      GetPortCommand portCmd = new GetPortCommand(1);
      portCmd.execute(iDis, iDos);
      return portCmd.getFreePorts()[0];
    }*/

    /**
     * Get SEI-Slave TCP Inet address
     *
     * @return SEI-Slave TCP Inet address
     *
     * @exception UnknownHostException if failed to resolve the host name
     */
    public InetAddress getSlaveInetAddress() throws UnknownHostException{
      return InetAddress.getByName(iPrefs.getHost());
    }

}

















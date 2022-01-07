/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSserver.java                                 |
 |    Desc: Main SDGS server program                        |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.rmi.server.*;
import java.rmi.registry.*;
import java.rmi.*;
import java.net.*;
import java.io.*;
import java.util.*;

public class SDGSserver extends UnicastRemoteObject implements SDGSremote
{
  public static final String  SDGStag="SDGS Remote Server v1.0 - Configuration file";
  public static final String  SDGSfile="SDGSserver.cfg";

  public String       id;
  public SDGSdatabase db;
  public SDGSlist     svr;
  public SDGSsettings ini;
  public int          count;
  public boolean      verbose;

  public SDGSserver() throws java.rmi.RemoteException
  { verbose=false; }

  public boolean initialize( String filename ) throws java.rmi.RemoteException
  {
    String str=new String("");
    boolean registered=false;

    ini=new SDGSsettings();  //ini.setVerbose(this.verbose);
    if (!ini.init(filename))  return(false);

    db=new SDGSdatabase(ini.reglocal); svr=new SDGSlist();
    if (svr.loadList()==0)  return(false);
    svr.listReset();  count=1;

    try {
      while (svr.listHasNext())
      {
        str=new String(svr.listNext());
        if (verbose) System.out.println("trying server ID: "+str);
        Naming.lookup(str);
      }
    } catch(NotBoundException e) {
      try {
        id=new String(str);
        /*if (verbose)*/ System.out.println("registering with ID: "+str);
        Naming.rebind(str,this);
        registered=true;
        if (db.load(this.id+File.separator)==0) {
            System.out.println("Warning: unable to load DB for current server");
            registered=false; }
      } catch(Exception e1) {
        System.out.println("Error: unable to register server instance.");
        registered=false;
      }
    } catch(Exception e) {
      System.out.println("Error: unable to register server instance.");
      registered=false;
    }

    return(registered);
  }

  public String lookupKey( int id ) throws java.rmi.RemoteException, SDGSexception
  {
    String  srec;
    System.out.println("rcvd: lookupKey REQ#"+(count++)+" (id='"+id+"')");
    srec=db.lookupKey(id);
    System.out.println("sent: RESP#"+(count-1)+" {"+srec.toString()+"}");
    return(srec);
  }

  public static void main( String args[] )
  {
    Properties          cfg=new Properties();
    FileOutputStream    cfgfile;


    System.out.println("SDGS Remote Server, version 1.0 - Harris Georgiou (c) 2000.\n");

    //System.setSecurityManager(new RMISecurityManager());

    try
    {
      SDGSserver sdgs=new SDGSserver();

      if (!sdgs.initialize(SDGSsettings.ini_file))
      {
        System.out.println("initialization failed!");
        System.exit(1);
      }

      System.out.println("saving current configuration");
      cfg.put("SDGShost",InetAddress.getLocalHost().getHostName());
      cfg.put("SDGSname",sdgs.id);
      if (sdgs.ini.reglocal) {
        cfg.put("SDGSmode","LOCAL");
        System.out.println("server grouping mode: LOCAL");
      } else {
        cfg.put("SDGSmode","REMOTE");
        System.out.println("server grouping mode: REMOTE"); }

      if (sdgs.ini.reglocal)  cfgfile=new FileOutputStream(sdgs.id+File.separator+sdgs.SDGSfile);
      else  cfgfile=new FileOutputStream(sdgs.SDGSfile);
      cfg.store(cfgfile,sdgs.SDGStag);
      cfgfile.close();

      System.out.println("server is running at '//"+cfg.get("SDGShost")+":"+Registry.REGISTRY_PORT+"/"+cfg.get("SDGSname")+"'\n");
      System.out.println("server is idle\n");
    }
    catch(Exception e)
    {
      System.out.println("Error: " + e.getMessage());
      e.printStackTrace();
    }
  }

}

/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSsettings.java                               |
 |    Desc: SDGS servers group setup                        |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.io.*;
import java.util.*;
import java.rmi.registry.*;

public class SDGSsettings //extends Object
{
  public static final String  ini_tag="SDGS Remote Server v1.1 - Settings file";
  public static final String  ini_file="SDGSserver.ini";
  public boolean reglocal;    // many servers on same machine?
  public String reghost;      // RMIregistry hostname (remote mode only)
  public int regport;         // RMIregistry port (remote mode only)

  public SDGSsettings()
  {
    reghost=new String("localhost");
    regport=Registry.REGISTRY_PORT;  reglocal=true;
  }

  public boolean init( String filename )
  {
    if (read(filename))  return(true);
    else return(write(filename));
  }

  public boolean init()
  {
    return(init(ini_file));
  }

  public boolean write( String filename )
  {
    Properties          cfg;
    FileOutputStream    cfgfile;

    try {
      cfg=new Properties();
      cfg.put("reghost",reghost);
      cfg.put("regport",(new Integer(regport)).toString());
      cfg.put("reglocal",(new Boolean(reglocal)).toString());
      //System.out.println("Writing file: "+cfg.toString());
      cfgfile=new FileOutputStream(filename,true);
      cfg.store(cfgfile,ini_tag);
      cfgfile.close();
      return(true);
    } catch(Exception e) {
      e.printStackTrace();
      return(false);
    }
  }

  public boolean read( String filename )
  {
    Properties         cfg;
    FileInputStream    cfgfile;

    try {
      cfg=new Properties();
      cfgfile=new FileInputStream(filename);
      cfg.load(cfgfile);
      cfgfile.close();
      reglocal=(new Boolean(cfg.getProperty("reglocal"))).booleanValue();
      reghost=(new String(cfg.getProperty("reghost")));
      regport=(new Integer(cfg.getProperty("regport"))).intValue();
      return(true);
    } catch(Exception e) {
      e.printStackTrace();
      return(false);
    }
  }

  public String toString()
  {
    return(new String("{ reglocal="+reglocal+" , reghost="+reghost+" , regport="+regport+" }"));
  }

  public static void main( String args[] )
  {
    SDGSsettings s=new SDGSsettings();
    System.out.println("SDGS Server - Settings Manager\n");
    if (s.read(s.ini_file)) System.out.println(s.toString());
    else if (s.write(s.ini_file)) System.out.println("Created ini file:\n"+s.toString());
    else  System.out.println("Error: unable to initialize.");
  }

}
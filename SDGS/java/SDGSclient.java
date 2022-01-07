/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSclient.java                                 |
 |    Desc: Main SDGS client program                        |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.rmi.server.*;
import java.rmi.registry.*;
import java.rmi.*;
import java.io.*;
import java.util.*;
import java.net.*;


public class SDGSclient
{
  public SDGSlist svrlist;
  public boolean verbose;


  public SDGSclient()  { svrlist=new SDGSlist(); verbose=false; }

  public boolean initialize()
  {
    return(svrlist.loadList()!=0);
  }

  public void setVerbose( boolean state )
  {
    verbose=state;
  }

  public SDGSrecord lookup( int id ) throws SDGSnotFoundException, SDGSexception
  {
    int  tcount, retries, sltime, state, tried;
    SDGSrecord rrec=null;
    String asvrID;
    Random rnd=new Random(System.currentTimeMillis());
    String  srec;


    if (svrlist==null)
    {
      if (verbose) System.out.println("failed: active servers list is empty.");
      throw(new SDGSexception("no active servers"));
    }
    else
    {
      SDGSremote sdgs;
      svrlist.listReset();  state=-1;  tried=0;
      while (svrlist.rndHasNext())
      {
        asvrID=svrlist.randomSelect();  // select any one server
        for ( tcount=1,state=-1; (state==-1)&&(tcount<=SDGStimeout.maxRetries); tcount++ )
        {
          try { // to locate one of the available servers
            if (verbose) System.out.println("trying server: "+asvrID);
            sdgs=(SDGSremote)Naming.lookup(asvrID);
            for ( retries=1,state=-1; (state==-1)&&(retries<=SDGStimeout.maxSameRetries); retries++ )  {
              try { // to send request to selected server
                srec=sdgs.lookupKey(id);  // throws exception on connect error
                rrec=SDGSrecord.translateString(srec);
                if (rrec!=null) { /*state=1;*/ return(rrec); }
                else { /*state=0;*/ throw(new SDGSnotFoundException("key not found")); }
              } catch (Exception e1) { // communication error
                if (!(e1 instanceof SDGSnotFoundException))  {
                  if (verbose) System.out.println("failed: connect to server '"+asvrID+"' failed");
                  try {  // wait some time before continuing (same server)
                    sltime=SDGStimeout.waitAtLeast+rnd.nextInt(SDGStimeout.waitSome);
                    Thread.currentThread().sleep(sltime);
                  } catch (InterruptedException e000) { }
                }
                else state=0;
              }
            }

            switch(state) {
              case -1: if (verbose) System.out.println("failed: request to '"+asvrID+"' aborted after "+(retries-1)+" retries"); break;
              case  0: if (verbose) System.out.println("failed: server '"+asvrID+"' does not have it");
              //case  1: System.out.println("success: server '"+asvrID+"' has it");
            }
          } catch(Exception e0)  { // timeout on selected server, try another one
            if (!(e0 instanceof SDGSnotFoundException))  {
              if (verbose) System.out.println("failed: selected server unreachable");
              try {  // wait some time before continuing (same server)
                sltime=SDGStimeout.waitAtLeast+rnd.nextInt(SDGStimeout.waitSome);
                Thread.currentThread().sleep(sltime);
              } catch (InterruptedException e000) { }
            }
          }
        }
        if (verbose) System.out.println("failed: gave up on '"+asvrID+"' after "+(tcount-1)+" retries");
      }
      if (verbose) System.out.println("failed: all servers failed.");
      throw(new SDGSnotFoundException("key not found"));
    }

    //return(null);   // normally never reached
  }

  public static void main( String args[] )
  {
    SDGSclient  cli=new SDGSclient();
    int     id;
    SDGSrecord  rec;

    System.out.println("SDGS Client, version 1.1 - Harris Georgiou (c) 2000.\n");

    //System.setSecurityManager(new RMISecurityManager());

    if (cli.initialize())  {
      //cli.setVerbose(true);
      for ( id=1; id<=5; id++ )  {
        try {
          System.out.println("lookup: key '"+id+"'");
          rec=cli.lookup(id);
          System.out.println("result: "+rec);
        } catch(SDGSnotFoundException e) {
          System.out.println("result: NOT FOUND: "+e.toString());
          //e.printStackTrace();
        } catch(Exception e) {
          System.out.println("ERROR: "+e.toString());
          //e.printStackTrace();
          System.exit(1);
        }
      }
    }
    else {
      System.out.println("Error: servers list file empty or not found.");
      System.exit(1);
    }

    System.exit(0);
  }
}


/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSlist.java                                   |
 |    Desc: SDGS servers group list management              |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.util.*;
import java.io.*;

public class SDGSlist extends Object
{
  public static int versionTag = 100;
  public static String fileName = "SDGSlist.cfg";
  public Vector server, vlist;
  public Enumeration list;
  public Random rnd;

  public SDGSlist()
  {
    rnd=new Random(System.currentTimeMillis());
  }

  public int hashCode()
  {
    return(versionTag);
  }

  public int loadList( String lstpath )
  {
    BufferedReader  ifile;
    server=new Vector();
    String str;
    boolean  eof=false;

    try {
      ifile=new BufferedReader(new FileReader(lstpath+fileName));
      while (!eof)  {
        try {
          str=ifile.readLine();
          if ((str==null)||(str.equals(""))) eof=true;
          else server.addElement(str);  }
        catch(IOException e1) { eof=true; }
      }
      ifile.close();  listReset();
    }
    catch(IOException e) { }

    return(server.size());
  }

  public int loadList()
  {
    return(loadList(""));
  }

  public synchronized void listReset()
  {
    vlist=new Vector(server);
    list=server.elements();
  }

  public int listSize()
  {
    return(server.size());
  }

  public boolean listHasNext()
  {
    return(list.hasMoreElements());
  }

  public String listNext()
  {
    return((String)list.nextElement());
  }

  public boolean rndHasNext()
  {
    return(vlist.size()>0);
  }

  public String randomSelect()
  {
    String  sval;
    if ((vlist==null)||(vlist.size()==0))  return(null);
    else
    {
      try {
        Enumeration e=vlist.elements();
        int rndpos=rnd.nextInt(vlist.size()), c=0;
        while (c<rndpos-1)  { c++; e.nextElement(); }
        sval=(String)e.nextElement();
        vlist.removeElement(sval);
        return(sval);
      } catch(Exception e0) { return(null); }
    }
  }

  public static void main( String args[] )
  {
    SDGSlist svrs=new SDGSlist();

    System.out.println("SDGS - Server list class");
    if (svrs.loadList()==0)
      System.out.println("Error: server list file empty or not found.");
    else
    {
      svrs.listReset();
      System.out.println("Sequential selection:");
      while(svrs.listHasNext())
        System.out.println("server name: "+svrs.listNext());
      System.out.println("total #servers: "+svrs.listSize());

      svrs.listReset();
      System.out.println("Random selection:");
      while(svrs.rndHasNext())
        System.out.println("server name: "+svrs.randomSelect());
      System.out.println("total #servers: "+svrs.listSize());
    }
  }

}



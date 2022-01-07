/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSdatabase.java                               |
 |    Desc: SDGS database package                           |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.util.*;
import java.io.*;


public class SDGSdatabase extends Object
{
  public static int versionTag = 100;
  public static String fileName = "SDGSdatabase.dat";
  public Hashtable data;
  public boolean isLocal;

  public SDGSdatabase()  { isLocal=false; }
  public SDGSdatabase( boolean localmode )  { isLocal=localmode; }

  public int load( String dbpath )
  {
    BufferedReader  ifile;
    data=new Hashtable();
    String str, rkey, rval;
    SDGSrecord rrec;
    boolean  eof=false;
    StringTokenizer stok;

    try {
      if (isLocal)  ifile=new BufferedReader(new FileReader(dbpath+fileName));
      else  ifile=new BufferedReader(new FileReader(fileName));
      
      while (!eof)  {
        try {
          str=ifile.readLine();
          if ((str==null)||(str.equals(""))) eof=true;
          else
          {
            stok=new StringTokenizer(str,",");
            rkey=(String)stok.nextElement();  rval=(String)stok.nextElement();
            rrec=new SDGSrecord(Integer.parseInt(rkey),rval);
            data.put(rrec.key,rrec);
          }
        }
        catch(Exception e1) { eof=true; }
      }
      ifile.close();
    }
    catch(IOException e)
    {
        System.out.println("DBerror: "+e.toString());
    }

    return(data.size());
  }

  public int load()
  {
    return(load(""));
  }

  public String lookupKey( int key ) throws SDGSnotFoundException
  {
    SDGSkey  rkey=new SDGSkey(key);
    SDGSrecord rrec;
    //boolean res;

    if (data.containsKey(rkey)) {
      try {
          rrec=(SDGSrecord)data.get(rkey);
          if (rkey==null)  {
            //System.out.println("throw level-1");
            throw(new SDGSnotFoundException("key not found (code=1)")); }
      } catch(Exception e) {
            //System.out.println("throw level-2");
            throw(new SDGSnotFoundException("key not found (code=2)")); }
    } else {
        //System.out.println("throw level-3");
        throw(new SDGSnotFoundException("key not found (code=3)")); }

    //System.out.println("found requested key: "+rrec);
    return(rrec.toString());
  }


  public static void main( String args[] )
  {
    SDGSdatabase  db=new SDGSdatabase();
    Enumeration e;

    System.out.println("SDGS - Server database class");
    if (db.load()==0)
      System.out.println("Error: server database file empty or not found.");
    else
    {
      e=db.data.elements();
      while(e.hasMoreElements())
        System.out.println("record: "+(SDGSrecord)e.nextElement());
      System.out.println("total #records: "+db.data.size());
    }
  }

}





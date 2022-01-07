/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSrecord.java                                 |
 |    Desc: SDGS database record (complete key-value pair)  |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


import java.util.*;


public class SDGSrecord extends Object
{
    public SDGSkey   key;
    public SDGSvalue val;

    public SDGSrecord()  { }

    public SDGSrecord( SDGSrecord other )
    {
      key=new SDGSkey(other.key);
      val=new SDGSvalue(other.val);
    }

    public SDGSrecord( int newid, String newvalue )
    {
      key=new SDGSkey(newid);
      val=new SDGSvalue(newvalue);
    }

    public String toString()
    {
      return(key.toString()+","+val.toString());
    }

    public boolean equals( Object obj )
    {
      return (key.equals(((SDGSrecord)obj).key) && val.equals(((SDGSrecord)obj).val) );
    }

    public int hashCode()
    {
      return(key.hashCode()+val.hashCode());
    }

    public static SDGSrecord translateString( String str )
    {
      StringTokenizer stok;
      String  rkey, rval;
      SDGSrecord    rrec;

      try {
        if ((str==null)||(str.equals(""))) return(null);
        else
        {
          stok=new StringTokenizer(str,",");
          rkey=(String)stok.nextElement();  rval=(String)stok.nextElement();
          rrec=new SDGSrecord(Integer.parseInt(rkey),rval);
          return(rrec);
        }
      } catch(Exception e1) { return(null); }
    }
}


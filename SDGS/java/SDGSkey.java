/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSkey.java                                    |
 |    Desc: SDGS database key field (on key-value pairs)    |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public class SDGSkey extends Object
{
  public Integer id;

  public SDGSkey()    {}
  public SDGSkey( int newid )  { id=new Integer(newid); }
  public SDGSkey( SDGSkey other )  { id=new Integer(other.id.intValue()); }

  public String toString()
  {
    return(id.toString());
  }

  public boolean equals( Object obj )
  {
    return(id.intValue()==((SDGSkey)obj).id.intValue());
  }

  public int hashCode()
  {
    return(id.hashCode());
  }
}


/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSvalue.java                                  |
 |    Desc: SDGS database value field (on key-value pairs)  |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public class SDGSvalue extends Object
{
    public String value;

    public SDGSvalue() {}
    public SDGSvalue( SDGSvalue other )  { value=new String(other.value); }
    public SDGSvalue( String newvalue )  { value=new String(newvalue); }

    public String toString()
    {
      return(value);
    }

    public boolean equals( Object obj )
    {
      return (value.equals(((SDGSvalue)obj).value));
    }

    public int hashCode()
    {
      return(value.hashCode());
    }
}
    
    
/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSValue.java                            |
 |    Desc: Registry entry record-value              |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public class SNSValue extends Object
{
    public String   svr_intrf, svr_addr;


    public SNSValue()
    {}

    public SNSValue( String intrf, String addr )
    {
        this.svr_intrf = intrf;
        this.svr_addr = addr;
    }

    public String toString()
    {
        return("SNSval:  { "+svr_intrf+" , "+svr_addr+" }");
    }

    public boolean equals( Object obj )
    {
        if (!(obj instanceof SNSValue))  return(false);
        SNSValue other=(SNSValue)obj;

        return ( svr_intrf.equals(other.svr_intrf) && svr_addr.equals(other.svr_addr) );
    }

    public int hashCode()
    {
        return( svr_intrf.hashCode()+svr_addr.hashCode() );
    }
}
    
    
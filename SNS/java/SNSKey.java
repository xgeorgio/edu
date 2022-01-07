/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSKey.java                              |
 |    Desc: Registry entry record-key                |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public class SNSKey extends Object
{
    public String   svr_name, svr_ver;


    public SNSKey()
    {}

    public SNSKey( String name, String ver )
    {
        this.svr_name = name;
        this.svr_ver = ver;
    }

    public String toString()
    {
        return("SNSkey:  { "+svr_name+" , "+svr_ver+" }");
    }

    public boolean equals( Object obj )
    {
        if (!(obj instanceof SNSKey))  return(false);
        SNSKey other=(SNSKey)obj;

        return (svr_name.equals(other.svr_name) && svr_ver.equals(other.svr_ver));
    }

    public int hashCode()
    {
        return( svr_name.hashCode()+svr_ver.hashCode() );
    }
}
    
    
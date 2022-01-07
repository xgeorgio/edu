/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSRecord.java                           |
 |    Desc: Registry entry record                    |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public class SNSRecord extends Object
{
    public SNSKey   key;
    public SNSValue val;
    


    public SNSRecord()
    {
        key=new SNSKey();
        val=new SNSValue();
    }

    public SNSRecord( String name, String ver, String intrf, String addr )
    {
        key=new SNSKey(name,ver);
        val=new SNSValue(intrf,addr);
    }

    public SNSRecord( String name, String ver, String intrf )
    {
        key=new SNSKey(name,ver);
        val=new SNSValue(intrf,"");
    }

    public SNSRecord( String name, String ver )
    {
        key=new SNSKey(name,ver);
        val=new SNSValue();
    }

    public String toString()
    {
        return("SNSrec:  { "+key.toString()+" , "+val.toString()+" }");
    }

    public boolean equals( Object obj )
    {
        if (!(obj instanceof SNSRecord))  return(false);
        SNSRecord other=(SNSRecord)obj;

        return (key.equals(other.key) && val.equals(other.val) );
    }

    public int hashCode()
    {
        return( key.hashCode()+val.hashCode() );
    }
}
    
    
/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSNotFoundException.java                |
 |    Desc: Entry not found exception                |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public class SNSNotFoundException extends SNSException
{
    public SNSKey errobj;
    
    public SNSNotFoundException()
    {}

    public SNSNotFoundException( String errstring )
    {
        super(errstring);
    }

    public SNSNotFoundException( SNSKey unknown )
    {
        this.errobj=unknown;
    }

    public SNSNotFoundException( SNSKey unknown, String errstring )
    {
        super(errstring);
        this.errobj=unknown;
    }
}


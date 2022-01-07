/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSException.java                        |
 |    Desc: Generic program exception                |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public class SNSException extends Exception
{
    public SNSException()
    {}

    public SNSException( String errstring )
    {
        super(errstring);
    }
}


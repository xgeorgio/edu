/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSexception.java                              |
 |    Desc: SDGS generic exception                          |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public class SDGSexception extends Exception
{
    public SDGSexception()
    {}

    public SDGSexception( String errstring )
    {
        super(errstring);
    }
}


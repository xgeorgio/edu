/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSnotFounException.java                       |
 |    Desc: SDGS lookup failure exception                   |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public class SDGSnotFoundException extends SDGSexception
{
    public SDGSkey errobj;

    public SDGSnotFoundException()
    {}

    public SDGSnotFoundException( String errstring )
    {
        super(errstring);
    }

    public SDGSnotFoundException( SDGSkey unknown )
    {
        this.errobj=unknown;
    }

    public SDGSnotFoundException( SDGSkey unknown, String errstring )
    {
        super(errstring);
        this.errobj=unknown;
    }
}


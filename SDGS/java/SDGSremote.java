/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGSclient.java                                 |
 |    Desc: SDGS server remote interface                    |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public interface SDGSremote extends java.rmi.Remote
{
    public String lookupKey( int id )
            throws java.rmi.RemoteException, SDGSexception;
}

    
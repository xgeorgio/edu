/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSRemote.java                           |
 |    Desc: SNS remote interface                     |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

public interface SNSRemote extends java.rmi.Remote
{
    public boolean register( String svr_name, String svr_ver, String svr_intrf, String svr_addr )
            throws java.rmi.RemoteException, SNSException;

    public boolean unregister( String svr_name, String svr_ver )
            throws java.rmi.RemoteException, SNSException;

    public String lookup( String svr_name, String svr_ver, String svr_intrf )
            throws java.rmi.RemoteException, SNSNotFoundException, SNSException;
}

    
/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSRemoteImpl.java                       |
 |    Desc: Main RMI server program                  |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

import java.rmi.server.*;
import java.rmi.registry.*;
import java.rmi.*;
import java.net.*;
import java.io.*;
import java.util.*;

public class SNSRemoteImpl extends UnicastRemoteObject implements SNSRemote
{
    public static final String  SNSid="SNSRemoteServer";
    public static final String  SNStag="SNS Remote Server v1.0 - Configuration file";
    public static final String  SNSfile="SNSRemote.cfg";
    
    public Hashtable    keyindex, inventory;

    public SNSRemoteImpl() throws java.rmi.RemoteException
    {
        keyindex=new Hashtable();
        inventory=new Hashtable();
    }

    public boolean register( String svr_name, String svr_ver, String svr_intrf, String svr_addr )
            throws java.rmi.RemoteException, SNSException
    {
        SNSRecord rec=new SNSRecord(svr_name,svr_ver,svr_intrf,svr_addr);
        System.out.println("RMI call: register");
        return(register(rec));
    }

    public boolean unregister( String svr_name, String svr_ver )
            throws java.rmi.RemoteException, SNSException
    {
        SNSRecord rec=new SNSRecord(svr_name,svr_ver);
        System.out.println("RMI call: unregister");
        return(unregister(rec));
    }

    public String lookup( String svr_name, String svr_ver, String svr_intrf )
            throws java.rmi.RemoteException, SNSNotFoundException, SNSException
    {
        String  result;
        SNSRecord rec=new SNSRecord(svr_name,svr_ver,svr_intrf);
        System.out.println("RMI call: lookup");
        result=lookup(rec);
        if (result==null) throw(new SNSNotFoundException());
        return(result);
    }
    
    public synchronized boolean register( SNSRecord rec )
            throws java.rmi.RemoteException, SNSException
    {
        Hashtable   currinv;
        SNSKey      key=rec.key;
        Integer     hashkey=new Integer(key.hashCode());

        if (! keyindex.containsKey(hashkey) )
        {
            currinv=new Hashtable();
            keyindex.put(hashkey,key);
            inventory.put(hashkey,currinv);
        }
        else currinv=(Hashtable)this.inventory.get(hashkey);
        
        currinv.put(rec.val.svr_intrf,rec.val.svr_addr);

        return(true);
    }

    public synchronized boolean unregister( SNSRecord rec )
            throws java.rmi.RemoteException, SNSException
    {
        Hashtable   currinv;
        SNSKey      key=rec.key;
        Integer     hashkey=new Integer(key.hashCode());

        if (! keyindex.containsKey(hashkey) )  return(false);
        else
        {
            currinv=(Hashtable)this.inventory.get(hashkey);
            currinv.clear();

            keyindex.remove(hashkey);
            inventory.remove(hashkey);
        }
        
        return(true);
    }
           
    public String lookup( SNSRecord rec )
            throws java.rmi.RemoteException, SNSNotFoundException, SNSException
    {
        Hashtable   currinv;
        SNSKey      key=rec.key;
        Integer     hashkey=new Integer(key.hashCode());

        if (! keyindex.containsKey(hashkey) )  return(null);
        else
        {
            currinv=(Hashtable)this.inventory.get(hashkey);
            return((String)currinv.get(rec.val.svr_intrf));
        }
    }


    public static void main( String args[] )
    {
        Properties          cfg=new Properties();
        FileOutputStream    cfgfile;
        
        System.out.println("SNS Remote Server, version 1.0 - Harris Georgiou (c) 2000.\n");
        
        //System.setSecurityManager(new RMISecurityManager());

        try
        {
            SNSRemoteImpl sns=new SNSRemoteImpl();
            Naming.rebind(SNSid,sns);

            cfg.put("SNShost",InetAddress.getLocalHost().getHostName());
            cfg.put("SNSname",SNSid);
            cfgfile=new FileOutputStream(SNSfile);
            cfg.store(cfgfile,SNStag);
            cfgfile.close();
            
            System.out.println("server is running at '//"+cfg.get("SNShost")+":"+Registry.REGISTRY_PORT+"/"+cfg.get("SNSname")+"'\n");
        }
        catch(Exception e)
        {
            System.out.println("SNS Error: " + e.getMessage());
            //e.printStackTrace();
        }
    }

}
/*
 +---------------------------------------------------+
 |                                                   |
 |    SNS - Simple Naming Service (Java/RMI)         |
 |    --------------------------------------         |
 |    File: SNSClient.java                           |
 |    Desc: Main SNS client program                  |
 |                                                   |
 +---------------------------------------------------+
*/


//package SNS;

import java.rmi.server.*;
import java.rmi.registry.*;
import java.rmi.*;
import java.io.*;
import java.util.*;


public class SNSClient
{
    public static final String  SNSfile="SNSRemote.cfg";

    public static void main( String args[] )
    {
        Properties          cfg=new Properties();
        FileInputStream     cfgfile;
        boolean     result;
        String      address, SNShost, SNSname;
        
        System.out.println("SNS Client, version 1.0 - Harris Georgiou (c) 2000.\n");
        
        //System.setSecurityManager(new RMISecurityManager());

        try
        {
            cfgfile=new FileInputStream(SNSfile);
            cfg.load(cfgfile);
            cfgfile.close();
            SNShost=(String)cfg.get("SNShost");
            SNSname=(String)cfg.get("SNSname");
            
            SNSRemote sns=(SNSRemote)Naming.lookup("//"+SNShost+"/"+SNSname);

            System.out.println("Connected to SNS server at '//"+SNShost+":"+Registry.REGISTRY_PORT+"/"+SNSname+"'\n");

            System.out.println("Adding entry:");
            result=sns.register("svr1","1.0","init","localhost");
            System.out.println("Result -->  "+result+"\n");

            System.out.println("Lookup entry:");
            address=sns.lookup("svr1","1.0","init");
            System.out.println("Result -->  "+address+"\n");

            System.out.println("Remove entry:");
            result=sns.unregister("svr1","1.0");
            System.out.println("Result -->  "+result+"\n");

            System.out.println("Lookup entry:");
            address=sns.lookup("svr1","1.0","init");
            System.out.println("Result -->  "+address+"\n");
        }
        catch(SNSNotFoundException e)
        {
            System.out.println("SNS: entry not found in registry");
            //System.out.println(e.toString());
            //e.printStackTrace();
        }
        catch(Exception e)
        {
            System.out.println("SNS Error: "+e.toString());
            //e.printStackTrace();
        }
    }

}

    
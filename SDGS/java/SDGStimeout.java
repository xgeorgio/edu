/*
 +----------------------------------------------------------+
 |                                                          |
 |    SDGS - Simple Distributed Group Service (Java/RMI)    |
 |    --------------------------------------------------    |
 |    File: SDGStimeout.java                                |
 |    Desc: SDGS connection parameters (limits)             |
 |                                                          |
 +----------------------------------------------------------+
*/


//package SDGS;


public class SDGStimeout extends Object
{
  public static int maxRetries = 5;     // max. serverID lookup failures
  public static int maxSameRetries = 3; // max. retries on same serverID
  public static int waitAtLeast = 100;  // minimum delay time between retries
  public static int waitSome = 200;     // additional random delay range
}

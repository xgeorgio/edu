/*
------------------------------------------------------------------------------    
	
	Program:    SPATH.C

	Purpose:    Find shortest path between nodes in a weighted graph.

Description:    The program implements Dijkstra's classic algorithm,
				using an array of costs, and finds the shortest path
				(if any) and the total cost for this path.

------------------------------------------------------------------------------    
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <limits.h>


typedef         int             TCost;


#define         INFCOST         (TCost)INT_MAX/2    /* see shortpath() about choosing this value */
#define         MEMBER          1
#define         NONMEMBER       !MEMBER

#define         EXIT_NOERR          0       /* No error (normal exit) */
#define         EXIT_USERBRK        -1      /* User break (Ctrl-C) */
#define         EXIT_FLTPERR        -2      /* Floating-point error */
#define         EXIT_MEMVERR        -3      /* Memory violation error */
#define         EXIT_HEAPERR        -4      /* Out of memory */

#define         pause()             {printf("\n...<Press any key to continue>...\n");getch();}
#define         ANSI_clrscr()       printf("\033[2J")



TCost   **net, **baknet, mincost;
int     *path, maxnode;



/******************************/

void network_done( void );


/*%%%%%%%%%%   SYSTEM HANDLING   %%%%%%%%%%*/

void exit_to_system( char *exittype, int exitcode )
{
	printf("\nExiting to system: %s\n",exittype);
	
	printf("Destroying network...");
	network_done();             /* destroy network before exit */
	printf("done!\n");
	
	printf("\nTotal run-time:  %1.0fhrs %02.0fmin %04.1fsec\n\n",
						(double)( (long)(clock()/CLK_TCK)/3600 ),
						(double)( ((long)(clock()/CLK_TCK)%3600)/60 ),
						(double)( ((long)(clock()/CLK_TCK)%60)+((double)clock()/CLK_TCK-(long)(clock()/CLK_TCK)) ) );
	
	/*fcloseall();*/   /*not available!*/
	
	exit(exitcode);
}


void catch_cbrk( void )
{
	exit_to_system("User break",EXIT_USERBRK);
}

void catch_fpe( void )
{
	exit_to_system("Floating point error",EXIT_FLTPERR);
}

void catch_segv( void )
{
	exit_to_system("Memory violation",EXIT_MEMVERR);
}



/*%%%%%%%%%%   NETWORK HANDLING   %%%%%%%%%%*/

void network_done( void )
{
	int     i;


	if (net!=NULL)
		for ( i=0; i<maxnode; i++ )
			if (net[i]!=NULL)  free(net[i]);

	if (baknet!=NULL)
		for ( i=0; i<maxnode; i++ )
			if (baknet[i]!=NULL)  free(baknet[i]);

	if (path!=NULL)
		free(path);
}



int network_init( void )
{
	int     i, j, res;


	res = 0;

	/*** Initialize primary network */
	if ( (net=(TCost **)calloc(maxnode,sizeof(TCost *)))==NULL )
	{
		printf("\nERROR: Cannot allocate memory for network array\n");
		res = -1;
	}
	else
	{
		for ( i=0; (res==0)&&(i<maxnode); i++ )
		{
			if ( (net[i]=(TCost *)calloc(maxnode,sizeof(TCost)))==NULL )
			{
				printf("ERROR: Cannot allocate memory for nodes array\n");
				res = -2;
			}
		}
	}

	if (res==0)
	{
		if ( (path=(int *)calloc(maxnode,sizeof(int)))==NULL )
		{
			printf("\nERROR: Cannot allocate memory for path array\n");
			res = -3;
		}
	}

	if (res==0)
	{
		for ( i=0; i<maxnode; i++ )
		{
			path[i] = -1;
			for ( j=0; j<i; j++ )
				net[i][j] = INFCOST;
			net[i][i] = (TCost)0;
			for ( j=i+1; j<maxnode; j++ )
				net[i][j] = INFCOST;
		}
	}

	/*** Initialize backup network */
	if ( (baknet=(TCost **)calloc(maxnode,sizeof(TCost *)))==NULL )
	{
		printf("\nERROR: Cannot allocate memory for network-copy array\n");
		res = -4;
	}
	else
	{
		for ( i=0; (res==0)&&(i<maxnode); i++ )
		{
			if ( (baknet[i]=(TCost *)calloc(maxnode,sizeof(TCost)))==NULL )
			{
				printf("ERROR: Cannot allocate memory for nodes-copy array\n");
				res = -5;
			}
		}
	}

	if (res==0)
	{
		for ( i=0; i<maxnode; i++ )
			memcpy( baknet[i], net[i], sizeof(TCost)*maxnode );
	}

	
	/*** Deallocate any memory, if any error occurred ***/
	if (res!=0)
		network_done();

	return(res);
}


void network_save( void )
{    
	int     i;

	for ( i=0; i<maxnode; i++ )
		memcpy( baknet[i], net[i], sizeof(TCost)*maxnode );
}


void network_restore( void )
{    
	int     i;

	for ( i=0; i<maxnode; i++ )
		memcpy( net[i], baknet[i], sizeof(TCost)*maxnode );
}


void network_show( void )
{
	int     i, j;


	printf("\nNetwork has %1d nodes\n",maxnode);
	printf("\nNetwork's cost array:\n");

	printf("      ");
	for ( i=0; i<maxnode; i++)
		printf(" [%2d] ",i+1);
	printf("\n\n");
	
	for ( i=0; i<maxnode; i++ )
	{
		printf(" [%2d] ",i+1);
		for ( j=0; j<maxnode; j++ )
		{
			if (net[i][j]<INFCOST)
				printf("  %2d  ",(TCost)net[i][j]);
			else
				printf("   -  ");  
		}
		printf("\n");
	}
	printf("\n");
}


int network_define( void )
{
	int     i, j, newc, res;
	char    str[20];


	if (prompt("Destroy current network?"))
	{
		do  {
			network_done();
			printf("\nGive number of nodes:  ");
			scanf("%d",&maxnode);
			network_init();

			printf("Give cost array values for connections (* = none):\n");
			for ( i=0; i<maxnode; i++ )
			{
				net[i][i] = 0;
				printf("\tCost(%1d-%1d):  0  (fixed)\n",i+1,i+1);
				for ( j=i+1; j<maxnode; j++ )
				{
					printf("\tCost(%1d-%1d):  ",i+1,j+1);
					scanf("%s",str);
					
					if (str[0]=='*')
						newc = INFCOST;
					else
						newc = (TCost)atoi(str);
					
					net[i][j] = net[j][i] = newc;
				}
			}

			network_show();  }
		while ( prompt("Is the network defined correctly?")==0 );

		network_save();
		printf("New network defined successfully.\n");
		res = 1;
	}
	else
		res = 0;

	return(res);
}



/*%%%%%%%%%%   FIND & SHOW SHORTEST PATH (Dikjstra)   %%%%%%%%%%*/

/*** Find shortest path (& cost) from node "s" to node "t" ***/
void shortpath( int s, int t )
{
	TCost       *dist, smldist, newdist, dc;
	int         *perm, current, i, k, prev;


	if ( (dist=(TCost *)calloc(maxnode,sizeof(TCost)))==NULL )
	{
		printf("ERROR: Cannot allocate memory for distance array\n");
		exit_to_system("Out of memory",EXIT_HEAPERR);
	}
	if ( (perm=(int *)calloc(maxnode,sizeof(int)))==NULL )
	{
		printf("ERROR: Cannot allocate memory for nodes array\n");
		exit_to_system("Out of memory",EXIT_HEAPERR);
	}

	for ( i=0; i<maxnode; i++ )
	{
		perm[i] = NONMEMBER;
		dist[i] = INFCOST;
	}
	perm[s] = MEMBER;
	dist[s] = (TCost)0;
	current = s;
	prev = -1;

	while ((current!=t)&&(current!=prev))   /* check for termination or progress */
	{
		smldist = INFCOST;
		dc = dist[current];

		for ( i=0; i<maxnode; i++ )
		{
			if (perm[i]==NONMEMBER)
			{
				newdist = dc + net[current][i];  /* both must be at most INFCOST to avoid integer overflow */
				if (newdist<dist[i])
				{
					dist[i] = newdist;
					path[i] = current;
				}

				if (dist[i]<smldist)
				{
					smldist = dist[i];
					k = i;
				}
			}
		}

		prev = current;
		current  = k;
		perm[current] = MEMBER;
	}

	if (current==prev)
		mincost = INFCOST;
	else
		mincost = dist[t];

	free(dist);
	free(perm);
}


/*** Show shortest path (already found) from node "s" to node "t" ***/
void showpath( int s, int t )
{
	int         i, d, *p;


	if ( (p=(int *)calloc(maxnode,sizeof(int)))==NULL )
	{
		printf("ERROR: Cannot allocate memory for path array\n");
		exit_to_system("Out of memory",EXIT_HEAPERR);
	}
	
	i=t;  d=0;
	while ( i != s )
	{
		p[d] = i;
		i = path[i];
		d++;
	}
	p[d] = s;

	printf("(%1d)  ",p[d]+1);
	for ( i=d-1; i>=0; i-- )
		printf("--->  (%1d)  ", p[i]+1 );
	printf("\n");

	free(p);
}



/*%%%%%%%%%%   PROGRAM ENVIRONMENT   %%%%%%%%%%*/

int destroy_node( void )
{
	int     todes, i, res;


	do  {
		printf("Give node # to destroy (1-%1d):  ",maxnode);
		scanf("%d",&todes);  }
	while ((todes<1)||(todes>maxnode));

	if (prompt("Are you sure?"))
	{
		for ( i=0; i<maxnode; i++ )
			net[todes-1][i] = net[i][todes-1] = INFCOST;
		net[todes-1][todes-1] = (TCost)0;
		printf("\nNode %1d has been destroyed.\n",todes);
		res = 1;
	}
	else
		res =  0;

	return(res);
}        


int destroy_line( void )
{
	int         i, j, res;


	do  {
		printf("Give node # FROM and TO to destroy connection between (1-%1d):  ",maxnode);
		scanf("%d%d",&i,&j);  }
	while ((i<1)||(i>maxnode)||(j<1)||(j>maxnode)||(i==j));
	
	if (prompt("Are you sure?"))
	{
		if ((net[i-1][j-1]<INFCOST)||(net[j-1][i-1]<INFCOST))
		{
			net[i-1][j-1] = net[j-1][i-1] = INFCOST;
			printf("\nConnection between nodes %1d and %1d has been destroyed.\n",i,j);
			res = 1;
		}
		else
		{
			printf("\nConnection not found between nodes %1d and %1d.\n",i,j);
			res = 0;
		}
	}

	return(res);
}


int change_line( void )
{
	int         i, j, res;
	TCost       newc;
	char        str[20];


	do  {
		printf("Give node # FROM and TO to update connection between (1-%1d):  ",maxnode);
		scanf("%d%d",&i,&j);  }
	while ((i<1)||(i>maxnode)||(j<1)||(j>maxnode)||(i==j));
	
	if (net[i-1][j-1]<INFCOST)
		printf("Current connection cost is: %1d\n",net[i-1][j-1]);
	else
		printf("Currently, nodes %1d and %1d are not connected.\n",i,j);

	printf("Give new cost value for %1d-%1d connection (* = oo):  ",i,j);
	scanf("%s",str);
    if (str[0]!='*')
        newc = (TCost)atoi(str);
	else
		newc = INFCOST;

	if (prompt("Are you sure?"))
	{
		net[i-1][j-1] = net[j-1][i-1] = newc;
		printf("\nConnection between nodes %1d and %1d has been updated.\n",i,j);
		res = 1;
	}
	else
		res = 0;

	return(res);
}


int find_short_path( void )
{
	int     i, j, res;

	
	while (1)
	{
		printf("\nGive FROM and TO node #:  ");
		scanf("%d%d",&i,&j);
		if ((i>=1)&&(i<=maxnode)&&(j>=1)&&(j<=maxnode))
			break;
		else
			printf("Error: Invalid node numbers\n");
	}
	printf("Searching shortest path from node #%1d to node #%1d...",i,j);
	shortpath( i-1, j-1 );
	printf("done.\n");

	if ( mincost<INFCOST )
	{
		printf("\nShortest path:  (cost = %1d)\n\t",mincost);
		showpath( i-1, j-1 );
		res = 1;
	}
	else
	{
		printf("\nNo path found\n");
		res = 0;
	}

	return(res);
}


void restore_orig_net( void )
{
	network_restore();
	printf("Original network restored.\n");
}



int menu( void ) 
{
	char    str[5];
	int     res;


	do  {
		ANSI_clrscr();
		printf("\n");
		printf("                           ***  MAIN MENU  ***\n");
		printf("                           -------------------\n\n");
		printf("                   1.  Define New Network\n");
		printf("                   2.  Show Current Network Costs\n");
		printf("                   3.  Find Shortest Path\n\n");
		printf("                   4.  Destroy Network's Node\n");
		printf("                   5.  Destroy Network's Connection\n");
		printf("                   6.  Change Network's Connection Cost\n");
		printf("                   7.  Restore Original Network\n\n");
		printf("                   0.  ...EXIT...\n");
		printf("                     ____________________________________\n");
		printf("\n");                  
		printf("                       Choose number of action:  ");
		scanf("%s",str);
		printf("\n\n");

		if ( (isdigit(str[0]))||(isdigit(str[0])&&isdigit(str[1])) )
			res = atoi(str);   
		else
			res = -1;   }
	while((res<0)||(res>7));

	return(res);
}


int prompt( const char *msg )
{
	char    str[5];
	int     res;

	while(1)
	{
		printf("%s (y/n): ",msg);
		scanf("%s",str);
		if ((str[0]=='y')||(str[0]=='Y'))
		{
			res = 1;
			break;
		}
		else if ((str[0]=='n')||(str[0]=='N'))
		{
			res = 0;
			break;
		}
		/* else continue loop */
	}

	return(res);
}



/*****************************************/

/*%%%%%%%%%%   PROGRAM MANAGER - MAIN PROGRAM   %%%%%%%%%%*/

void main( void )
{
	int     i, j, sel, fin;


	signal( SIGINT, catch_cbrk );
	signal( SIGFPE, catch_fpe );
	signal( SIGSEGV, catch_segv );
	
	printf("Find Shortest Path in Network, version 1.0 - Harris Georgiou, 1996.\n\n");

	printf("Initializing network...");
	maxnode = 7;
	network_init();
	printf("done.\n");

	printf("Defining network structure...");
	net[0][1]=net[1][0]=4;    
	net[0][2]=net[2][0]=6;
	net[1][2]=net[2][1]=1;
	net[1][3]=net[3][1]=2;
	net[1][4]=net[4][1]=5;
	net[2][3]=net[3][2]=7;
	net[2][5]=net[5][2]=6;
	net[3][4]=net[4][3]=8;
	net[3][5]=net[5][3]=4;
	net[4][5]=net[5][4]=5;
	net[4][6]=net[6][4]=5;
	net[5][6]=net[6][5]=4;

	network_save();

	printf("done.\n");
	/*network_show();*/

	fin = 0;
	do  {
		sel = menu();
		switch(sel)
		{
			case 0: if (prompt("Quit program?"))
						fin = 1;
					break;

			case 1: ANSI_clrscr(); network_define();   pause(); break;
			case 2: ANSI_clrscr(); network_show();     pause(); break;
			case 3: ANSI_clrscr(); find_short_path();  pause(); break;
			case 4: ANSI_clrscr(); destroy_node();     pause(); break;
			case 5: ANSI_clrscr(); destroy_line();     pause(); break;
			case 6: ANSI_clrscr(); change_line();      pause(); break;
			case 7: ANSI_clrscr(); restore_orig_net(); pause(); break;
			default:                    break;
		} }
	while( !fin );
			
	/*network_done();*/     /* automatically done by exit_to_system() */

	ANSI_clrscr();
	exit_to_system("Normal termination",EXIT_NOERR);
}





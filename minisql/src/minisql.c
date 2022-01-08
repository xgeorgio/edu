/*
	--------------------------------------------
		MINISQL v1.0
		Main File

		This file contains the main code
		for the implementation of the
		"Mini-SQL" system.
	--------------------------------------------
*/


#include		"minisql.h"


void Menu_CreateNew(TARRPOOL *arArrayPool, TARRNUM *idActiveArray);
void Menu_ChooseActive(TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM *idFstFreeArray);
void Menu_DestroyOld(TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM *idFstFreeArray);
void Menu_Describe(TARRPOOL *arArrayPool, TARRNUM *idActiveArray);
void Menu_TotalPrint(TARRPOOL *arArrayPool, TARRNUM *idActiveArray);
void Menu_InputRecord(TARRPOOL *arArrayPool, TARRNUM *idActiveArray);
void Menu_PrintRecord(TARRPOOL *arArrayPool, TARRNUM *idActiveArray);
int  Menu_Exit(void);


int  main( int  argc, char *argv[] )
{
	char		stDataFile[30], str[3];
	FILE		*fpDataFile;
        TARRPOOL	arArrayPool;
	TARRNUM	        idActiveArray, idFstFreeArray;
        int		resp=1;


	if (argc > 1)  stDataFile=argv[1];
	else stDataFile=DEF_DATAFILE;

	if ((fpDataFile=fopen(stDataFile,"r+b"))==NULL) {
		perror("Data file error");
		return( EXIT_FAILURE );  }

	InitArrPool( arArrayPool );
	freadarrpool( fpDataFile, arArrayPool );
     InitArrParam( arArrayPool, &idActiveArray, &idFstFreeArray );

/* ---> Here, the data are in memory and ready for use. */

	do  {
		printf("\n");
		printf("                 |--------------------------------------------|\n");
		printf("                 |           Mini-SQL System v1.0             |\n");
		printf("                 |                MAIN MENU                   |\n");
		printf("                 |--------------------------------------------|\n");
		printf("                 |                                            |\n");
		printf("                 |         1.  Create New Array               |\n");
		printf("                 |         2.  Choose Active Array            |\n");
		printf("                 |         3.  Destroy Old Array              |\n");
		printf("                 |         4.  Show Array Structure           |\n");
		printf("                 |         5.  Print Array Contents           |\n");
		printf("                 |                                            |\n");
		printf("                 |         6.  Input Record Data              |\n");
		printf("                 |         7.  Print Record Data              |\n");
		printf("                 |                                            |\n");
		printf("                 |         0.  EXIT                           |\n");
		printf("                 |                                            |\n");
		printf("                 |--------------------------------------------|\n");
		printf("                     Enter your choice: ");
		scanf("%s",str);

		switch( str[0] )  {
			case '1':  Menu_CreateNew(arArrayPool,&idActiveArray);
                        break;
               case '2':  Menu_ChooseActive(arArrayPool,&idActiveArray,&idFstFreeArray);
                        break;
               case '3':  Menu_DestroyOld(arArrayPool,&idActiveArray,&idFstFreeArray);
                        break;
               case '4':  Menu_Describe(arArrayPool,&idActiveArray);
                        break;
               case '5':  Menu_TotalPrint(arArrayPool,&idActiveArray);
                        break;
               case '6':  Menu_InputRecord(arArrayPool,&idActiveArray);
                        break;
               case '7':  Menu_PrintRecord(arArrayPool,&idActiveArray);
                        break;
               case '0':  resp=Menu_Exit();   /* ---> double verification of choice */
                        break;
               default: printf("\nERROR: Invalid choice number\n");
                        printf("\n ... Press <ENTER> to continue ... ");
                        getch();  }

		printf("\n\n\n");  }
     while( resp != 0 );

	if ( ( fflush( fpDataFile ) || fclose( fpDataFile ) ) ) {
		perror("Data file error");
		return( EXIT_FAILURE ); }
     else  {
          printf("Thank you for using Mini-SQL System v1.0\n");
          return( EXIT_SUCCESS );  }

}



void Menu_CreateNew( TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM *idFstFreeArray )
{
     TARRDESC		*adDescr;
     char		str[3];
     int		num, spoint, nint, ndec;

     printf("\n\n");
     printf("   CREATE NEW ARRAY\n");
     printf("----------------------\n\n");

     printf("     Give the name of the Array: ");
	scanf("%s",str);  strncpy( *adDescr.name, str, MAXNAMELEN );

     printf("     Give number of fields: ");
     scanf("%s",str);  *adDescr.numfields = (TFLDNUM)atoi( str );

     printf("     ARRAY NAME: %s  ,  #FIELDS: %i\n", *adDescr.name, *adDescr.numfields );
	printf("     Is this correct? (y/n): ");  scanf("%s",str);

     if ( (str[0]=='y') || (str[0]=='Y') )  {
          *adDescr.numrecords = 0;
		for ( int idx=0; idx < *adDescr.numfields; idx++ )  {
          	printf("\n     Field #(%3i) Description:\n", idx);
               spoint = 0;

               printf("       Name: ");  scanf("%s",str);
			strncpy( *adDescr.fields[idx].name, str, MAXNAMELEN );

               printf("       Type (%1i=CHAR,%1i=NUM): ", FLD_CHAR, FLD_NUM);
			scanf("%s",str);  num = (TFLDTYPE)atoi( str );
               if ( (num != FLD_CHAR) && (num != FLD_NUM) )  num = FLD_CHAR;
               *adDescr.fields[idx].type = num;

               if ( num == FLD_CHAR )  {
               	printf("       Length: ");  scanf("%s",str);
                    *adDescr.fields[idx].len = (TSTRLEN)atoi( str );
				*adDescr.fields[idx].spos = (TSTRPOS)spoint;
                    spoint = spoint + (*adDescr.fields[idx].len);  }
			else if ( num == FLD_NUM )  {
               	printf("       Int.Digits: ");  scanf("%s",str);
                    nint = atoi( str );
               	printf("       Dec.Digits: ");  scanf("%s",str);
                    ndec = atoi( str );  if ( ndec > 0 )  ndec++;
				*adDescr.fields[idx].len = (TSTRLEN)( 1 + nint + ndec );
				*adDescr.fields[idx].spos = (TSTRPOS)spoint;
                    spoint = spoint + (*adDescr.fields[idx].len);  }  }

          printf("\n\n");
	     printf("     ARRAY NAME: %s  ,  #FIELDS: %i\n", *adDescr.name, *adDescr.numfields );
		for ( int idx=0; idx < *adDescr.numfields; idx++ )  {
          	printf("\n     Field #(%3i) Description:\n", idx);
			printf("       Name: %-15s  Type: %1i  Length: %-i\n", *adDescr.fields[idx].name,
							*adDescr.fields[idx].type, *adDescr.fields[idx].len );  }

		printf("\n\n     Is this correct? (y/n): ");  scanf("%s",str);
	     if ( (str[0]=='y') || (str[0]=='Y') )  {
			num = CreateArray( arArrayPool, adDescr, idActiveArray, idFstFreeArray );
               if ( num == ERR_NULL )  printf("\nArray successfully created.\n");
			else  printf("\nERROR: Cannot create array with these parameters.\n"); }
		else  printf("\nArray creation aborted.\n");  }

	else  printf("\nArray creation aborted.\n");

     printf("\n ... Press <ENTER> to continue ... ");
     getch();

}



void Menu_ChooseActive(TARRPOOL *arArrayPool, TARRNUM *idActiveArray)
{
     TARRNUM        idArrayNum=0;

     printf("\n\n");
     printf("   CHOOSE ACTIVE ARRAY\n");
     printf("-------------------------\n\n");

     printf("   Valid Arrays List:\n");
     printf("   ~~~~~~~~~~~~~~~~~~\n");
     for (idArrayNum=0; idArrayNum < MAXARRNUM; idArrayNum++)  {
         if (IsDefinedArray(arArrayPool,idArrayNum))  {
             printf("     #(%3i):  %s\n",idArrayNum,*arArrayPool[idArrayNum].desc.name);  } }
     printf("\n   Current Active Array number: %i\n",*idActiveArray);
     printf("\n   Give new Active Array number: ");  scanf("%i",&idArrayNum);

     if (IsDefinedArray(arArrayPool,idArrayNum))  {
         *idActiveArray = idArrayNum;
         printf("   New Active Array = #(%3i): %s\n",*idActiveArray,*arArrayPool[*idActiveArray].desc.name);  }
     else  {
         printf("\n   ERROR: Undefined Array specified as Active.");
         printf("\n          Active Array unghanged.\n");  }

     printf("\n ... Press <ENTER> to continue ... ");
     getch();
}



void Menu_DestroyOld(TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM *idFstFreeArray)
{
     TARRNUM        idArrayNum=0;
     char           str[3];

     printf("\n\n");
     printf("   DESTROY OLD ARRAY\n");
     printf("-----------------------\n\n");

     printf("   Valid Arrays List:\n");
     printf("   ~~~~~~~~~~~~~~~~~~\n");
     for (idArrayNum=0; idArrayNum < MAXARRNUM; idArrayNum++)  {
         if (IsDefinedArray(arArrayPool,idArrayNum))  {
             printf("     #(%3i):  %s\n",idArrayNum,*arArrayPool[idArrayNum].desc.name);  } }

     printf("\n   Give Array number to dispose: ");  scanf("%i",&idArrayNum);
     if (idArrayNum == *idActiveArray)  {
         printf("\nERROR: Cannot dispose Active Array.\n");  }
     else if (!IsDefinedArray(arArrayPool,idArrayNum))  {
         printf("\nERROR: Cannot dispose undefined Array.\n");  }
     else  {
         if (DestroyArray(arArrayPool,idArrayNum)==ERR_NULL)  {
             *idFstFreeArray = NewFstFreeArray(arArrayPool);
             printf("   Array number #(%3i) disposed and free list updated.\n");  }

     printf("\n ... Press <ENTER> to continue ... ");
     getch();
}



void Menu_Describe(TARRPOOL *arArrayPool, TARRNUM *idActiveArray)
{
     TARRDESC        *arDesc;
     TFLDNUM         idFldNum;
     TSTRLEN         StrLen; 
     TFLDNAME        fdFldName;


     printf("/n/n");
     printf("   (ACTIVE) ARRAY DESCRIPTION\n");
     printf("--------------------------------\n\n");

     if (IsDefinedArray(arArrayPool,*idActiveArray))  {
         arDesc = &arArrayPool[*idActiveArray].desc;
         
         printf("   ARRAY #(%3i):  %s , #Fields = %3i , #Records = %i\n\n",*idActiveArray,*arDesc.name,*arDesc.numfields,*arDesc.numrecords);

         for (idFldNum=0; idFldNum < *arDesc.numfields; idFldNum++ )  {
             StrLen = *arDesc.fields[idFldNum].len;
             strcpy(fdFldName,arDesc.fields[idFldNum].name);
             printf("%-*.*s     ",StrLen+1,StrLen,fdFldName);

             switch(*arDesc.fields[*idActiveArray].type)  {
                 case FLD_CHAR:  printf("CHARACTER(%3i)",StrLen);  break;
                 case FLD_NUM:   printf("NUMBER(%3i,%2i)",StrLen,DEC_POINTS);  break;
                 default:               }
             printf("\n");  }
     else  {
          printf("\nERROR: Invalid Active Array (select ChooseNew - Main Menu).\n");  }
    
     printf("\n ... Press <ENTER> to continue ... ");
     getch();
}



void Menu_TotalPrint(TARRPOOL *arArrayPool, TARRNUM *idActiveArray)
{
     printf("\n\n");
     printf("   SHOW (ACTIVE) ARRAY CONTENTS\n"
     printf("----------------------------------\n\n");

     if (ShowArray(arArrayPool,*idActiveArray)!=ERR_NULL)  {
         printf("\nERROR: Invalid Active Array (select ChooseNew - Main Menu).\n");  }

     printf("\n ... Press <ENTER> to continue ... ");
     getch();
}



void Menu_PrintRecord(TARRPOOL *arArrayPool, TARRNUM *idActiveArray)
{
     TRECNUM        rnRecNum;


     printf("\n\n");
     printf("   SHOW (ACTIVE) ARRAY'S RECORD\n");
     printf("----------------------------------\n\n");

     printf("   Give Array's Record Number: ");  scanf("%i",&rnRecNum);
     if (ShowRecord(arArrayPool,*idActiveArray,rnRecNum)!=ERR_NULL)  {
         printf("\nERROR: Invalid Active Array or Record out of bounds.\n");  }

     printf("\n ... Press <ENTER> to continue ... ");
     getch();
}



void Menu_InputRecord(TARRPOOL *arArrayPool, TARRNUM *idActiveArray)
{
	TARRDESC	*arDesc;
	TARRDATA	*arData;
        TARRNUM         idArrayNum;
        TRECNUM         idRecNum;
	TFLDNUM		idFldNum;
	TSTRING		StrData;
	float		NumData;
	TFLDNAME	fdFldName;
	TSTRPOS		StrStart=0;
	TSTRLEN		StrLen=0;


        idArrayNum = *ActiveArray;
        printf("\n\n");
        printf("   (ACTIVE) ARRAY'S RECORD INPUT\n");
        printf("-----------------------------------\n\n");

        printf("   Give Record Number: ");  scanf("%i",&idRecNum);


	if ( IsDefinedArray( arArrayPool, idArrayNum ) )  {
		arDesc = &arArrayPool[ idArrayNum ].desc;
		arData = &arArrayPool[ idArrayNum ].data;

		printf("\n\n");
		printf("  ARRAY #(%3i):  %s , #Fields = %3i  /  #Records = %i\n",
				idArrayNum, *arDesc.name, *arDesc.numfields, *arDesc.numrecords );
		printf("************************************************************\n\n");

		for ( idFldNum=0; idFldNum < *arDesc.numfields; idFldNum++ )  {
			StrLen  = *arDesc.fields[ idFldNum ].len;
			strcpy( fdFldName, arDesc.fields[ idFldNum ].name );
			printf("%-*.*s", StrLen+1, StrLen, fdFldName );  }
		printf("------------------------------------------------------------\n");

		if ( (idRecNum >= 0) && (idRecNum < *arDesc.numrecords) )  {
			for ( idFldNum=0; idFldNum < *arDesc.numfields; idFldNum++ )  {
				switch( *arDesc.fields[ idFldNum ].type )  {
					case FLD_NULL:  break;
					case FLD_CHAR:
						StrStart = *arDesc.fields[ idFldNum ].spos;
						StrLen   = *arDesc.fields[ idFldNum ].len;
                                                printf("R(#%3i).F(#%3i)?  ",idRecNum,idFldNum);
                                                scanf("%s",StrData);
						strncpy( arData[ StrStart ], StrData, StrLen );
						break;
					case FLD_NUM:
						StrStart = *arDesc.fields[ idFldNum ].spos;
						StrLen   = *arDesc.fields[ idFldNum ].len;
                                                printf("R(#%3i).F(#%3i)?  ",idRecNum,idFldNum);
                                                scanf("%f",&NumData);
                                                StrData = num2str( NumData, StrLen-DEC_POINTS-2,DEC_POINTS,1);
						strncpy( arData[ StrStart ], StrData, StrLen );
						break;
					default:
						return( ERR_INV );  } } }
		else  {
			printf("\nERROR: Record out of bounds.\n");  } }

	else  {
             printf("\nERROR: Invalid Active Array (select ChooseNew - Main Menu).\n");  }

        printf("\n ... Press <ENTER> to continue ... ");
        getch();
}


int  Menu_Exit(void)
{
        char        str[3];

        printf("\n\n");
        printf("     ARE YOU SURE YOU WANT TO QUIT? (Y/N): ");
        scanf("%s",str);

        if ((str[1]=='y')||(str[1]=='Y'))  return(0);
        else  return(1);
}





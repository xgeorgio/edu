/*
	---------------------------------------------------
		MINISQL v1.0
		Subroutines File #2 - Memory I/O Support

		This file contains the necessary routines
		for memory I/O support system, used for
		the array-pool management, by the main
		program.
	---------------------------------------------------
*/


/* ++++++++++++  GENERAL ARRAY FUNCTIONS  ++++++++++++ */

int	IsValidArray( TARRNUM idArrayNum )
{
	if ( (idArrayNum >= 0) && (idArrayNum < MAXARRNUM) )  return( 1 );
     else  return( 0 );
}



int	IsDefinedArray( TARRPOOL *arArrayPool, TARRNUM idArrayNum )
{
	int	res=0;

	if ( IsValidArray( idArrayNum ) )  {
     	if ( ! ( (*arArrayPool[ idArrayNum ].desc.numrecords == 0) &&
				(*arArrayPool[ idArrayNum ].desc.numrecords == 0) ) )
			res = 1;  }

    	return( res );
}



int  NewFstFreeArray( TARRPOOL *arArrayPool )
{
	TARRNUM		idArrayNum;

	for ( idArrayNum=0; idArrayNum < MAXARRNUM; idArrayNum++ )
          if ( ! IsDefinedArray( arArrayPool, idArrayNum ) )
			return( idArrayNum );
	return( ERR_FULL );
}



/* ++++++++++++++  INITIALIZATION FUNCTIONS  ++++++++++++++ */

int	InitArray( TARRPOOL	*arArrayPool, TARRNUM idArrayNum )
{
	TFLDNUM		idFieldNum;
	TRECNUM		idRecordNum;

	if ( IsValidArray( idArrayNum ) )  {
		*arArrayPool[ idArrayNum ].desc.name = "";
		*arArrayPool[ idArrayNum ].desc.numrecords = 0;
		*arArrayPool[ idArrayNum ].desc.numfields  = 0;

		for ( idFieldNum=0; idFieldNum < MAXFLDNUM; idFieldNum++ )  {
			*arArrayPool[ idArrayNum ].desc.fields[ idFieldNum ].name = "";
			*arArrayPool[ idArrayNum ].desc.fields[ idFieldNum ].spos = 0;
			*arArrayPool[ idArrayNum ].desc.fields[ idFieldNum ].len  = 0;
			*arArrayPool[ idArrayNum ].desc.fields[ idFieldNum ].type = FLD_NULL;  }

		for ( idRecordNum=0; idRecordNum < MAXRECNUM; idRecordNum++ )  {
			*arArrayPool[ idArrayNum ].data[ idRecordNum ] = "";  }

		return( ERR_NULL );  }
	else
		return( ERR_PRM );

}



void	InitArrPool( TARRPOOL	*arArrayPool )
{
	TARRNUM		idArrayNum;

	for ( idArrayNum=0; idArrayNum < MAXARRNUM; idArrayNum++ )
		InitArray( arArrayPool, idArrayNum );
}



void	InitArrParam( TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM *idFstFreeArray )
{
	for ( TARRNUM idArrayNum=0, *idActiveArray = 0; idArrayNum < MAXNUM; idArrayNum++ )
		if ( ! IsDefinedArray( arArrayPool, idArrayNum ) )
          	{  *idActiveArray = idArrayNum;  break;  }

	*idFstFreeArray = NewFstFreeArray( arArrayPool );
}



/* ++++++++++++++++  BASIC ARRAY FUNCTIONS  +++++++++++++++ */

int	DestroyArray( TARRPOOL	*arArrayPool, TARRNUM idArrayNum )
{
	return( InitArray( arArrayPool, idArrayNum ) );
}


int	CreateArray( TARRPOOL *arArrayPool, TARRDESC *adDescr,
				 TARRNUM *idActiveArray, TARRNUM *idFstFreeArray )
{
	if ( IsValidArray( *idFstFreeArray ) )  {
		*arArrayPool[ *idFstFreeArray ].desc = *adDescr;
		MakeActiveArray( arArrayPool, idActiveArray, *idFstFreeArray );    /* ---> make the new array "active" */
	     *idFstFreeArray = NewFstFreeArray( arArrayPool );   /* ---> find new "first" empty array */
		return( ERR_NULL );  }
	else
     	return( ERR_FULL );
}



int	DescribeArray( TARRPOOL *arArrayPool, TARRNUM idArrayNum, TARRDESC *adDescr )
{
	if ( IsDefinedArray( arArrayPool, idArrayNum ) )  {
		*adDescr = *arArrayPool[ idArrayNum ].desc;
		return( ERR_NULL );  }
	else
		return( ERR_PRM );
}



int	MakeActiveArray( TARRPOOL *arArrayPool, TARRNUM *idActiveArray, TARRNUM idNewActiveArray=0 )
{
	if ( IsDefinedArray( arArrayPool, idNewActiveArray ) )  {
		*idActiveArray = idNewActiveArray;
		return( ERR_NULL );  }
	else
		return( ERR_PRM );
}



int	ShowArray( TARRPOOL *arArrayPool, TARRNUM idArrayNum )
{
	TARRDESC		*arDesc;
	TARRDATA		*arData;
	TFLDNUM		idFldNum;
	TRECNUM		idRecNum;
	TSTRING		StrData;
	float		NumData;
	TFLDNAME		fdFldName;
	TSTRPOS		StrStart=0;
	TSTRLEN		StrLen=0;

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

		for ( idRecNum=0; idRecNum < *arDesc.numrecords; idRecNum++ )  {
			for ( idFldNum=0; idFldNum < *arDesc.numfields; idFldNum++ )  {
				switch( *arDesc.fields[ idFldNum ].type )  {
					case FLD_NULL:  break;
					case FLD_CHAR:
						StrStart = *arDesc.fields[ idFldNum ].spos;
						StrLen   = *arDesc.fields[ idFldNum ].len;
						strncpy( StrData, arData[ StrStart ], StrLen );
						printf("%s", StrData );
						break;
					case FLD_NUM:
						StrStart = *arDesc.fields[ idFldNum ].spos;
						StrLen   = *arDesc.fields[ idFldNum ].len;
						strncpy( StrData, arData[ StrStart ], StrLen );
						NumData  = str2num( StrData );
						printf("%f", NumData );
						break;
					default:
						return( ERR_INV );  }  }
				printf("\n");  }

		printf("\n------------------------------------------------------------\n");
		printf("\n  ... Press <ENTER> to continue ... "); scanf("%s", &StrData );
		printf("\n\n");

		return( ERR_NULL );  }

	else
		return( ERR_PRM );
}



int	ShowRecord( TARRPOOL *arArrayPool, TARRNUM idArrayNum, TRECNUM idRecNum )
{
	TARRDESC	*arDesc;
	TARRDATA	*arData;
	TFLDNUM		idFldNum;
	TSTRING		StrData;
	float		NumData;
	TFLDNAME	fdFldName;
	TSTRPOS		StrStart=0;
	TSTRLEN		StrLen=0;

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
						strncpy( StrData, arData[ StrStart ], StrLen );
						printf("%s", StrData );
						break;
					case FLD_NUM:
						StrStart = *arDesc.fields[ idFldNum ].spos;
						StrLen   = *arDesc.fields[ idFldNum ].len;
						strncpy( StrData, arData[ StrStart ], StrLen );
						NumData  = str2num( StrData );
						printf("%f", NumData );
						break;
					default:
						return( ERR_INV );  }  }
				printf("\n");  }
		else  {
			printf("\nERROR: No such record.\n");  }

		printf("\n------------------------------------------------------------\n");
		printf("\n  ... Press <ENTER> to continue ... "); scanf("%s", &StrData );
		printf("\n\n");

		return( ERR_NULL );  }

	else
		return( ERR_PRM );
}


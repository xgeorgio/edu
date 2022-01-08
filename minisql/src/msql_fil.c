/*
	---------------------------------------------------
		MINISQL v1.0
		Subroutines File #1 - File I/O Support

		This file contains the necessary routines
		for file I/O support system, used by main
		program.
	---------------------------------------------------
*/



/* ..... "High-level" array-pool retrieval from data file ..... */

int	freadarrpool( FILE *fpDataFile, TARRPOOL *arArrayPool )
{
	TARRNUM	idArrayPos;

	rewind( fpDataFile );
	for ( idArrayPos=0; ((idArrayPos <= MAXARRNUM) && ( !feof(fpDataFile)); idArrayPos++)  {

		freadarr( fpDataFile, arArrayPool, idArrayPos);  }
	return( idArrayPos );  /* ---> return number of arrays read */
}



/* ..... "High-level" array-pool storing to data file ..... */

int	fwritearrpool( FILE *fpDataFile, TARRPOOL *arArrayPool )
{
	TARRNUM	idArrayPos;

	rewind( fpDataFile );
	for ( idArrayPos=0; (idArrayPos <= MAXARRNUM); idArrayPos++ ) {
		fwritearr( fpDataFile, arArrayPool, idArrayPos);  }
	return( idArrayPos );  /* ---> return number of arrays written */
}



/* ..... "Low-level" array retrieval from binary file .....
		Note: Only for internal use from "freadarrpool"	*/

int	freadarr( FILE *fpDataFile, TARRPOOL *arArrayPool, TARRNUM idArrayPos)
{
	if ( ferror(fpDataFile) || feof(fpDataFile) )  return( ERR_IO );

	fgets( arArrayPool[ idArrayPos ].desc.name, MAXNAMELEN, fpDataFile );
	*arArrayPool[ idArrayPos ].desc.numrecords = (int)fgetc( fpDataFile );
	*arArrayPool[ idArrayPos ].desc.numfields  = (int)fgetc( fpDataFile );

	for ( BYTE idx=0; idx < MAXFLDNUM; idx++ )  {
		fgets( arArrayPool[ idArrayPos ].desc.fields[ idx ].name, MAXNAMELEN, fpDataFile );
		*arArrayPool[ idArrayPos ].desc.fields[ idx ].spos = (BYTE)fgetc( fpDataFile );
		*arArrayPool[ idArrayPos ].desc.fields[ idx ].len  = (BYTE)fgetc( fpDataFile );
		*arArrayPool[ idArrayPos ].desc.fields[ idx ].type = (BYTE)fgetc( fpDataFile );  }

	for ( BYTE idx=0; idx < MAXRECNUM; idx++ )  {
		fgets( arArrayPool[ idArrayPos ].data[ idx ], MAXSTRLEN, fpDataFile );

	if ( ferror(fpDataFile) ) return( ERR_IO );
	else return( ERR_NULL );
}


/* ..... "Low-level" array storing to binary file .....
		Note: Only for internal use from "fwritearrpool"	*/

int	fwritearr( FILE *fpDataFile, TARRPOOL *arArrayPool, TARRNUM idArrayPos)
{
	if ( ferror(fpDataFile) || feof(fpDataFile) )  return( ERR_IO );

	fputs( *arArrayPool[ idArrayPos ].desc.name, fpDataFile );
	fputc( *(int)arArrayPool[ idArrayPos ].desc.numrecords, fpDataFile );
	fputc( *(int)arArrayPool[ idArrayPos ].desc.numfields, fpDataFile );

	for ( BYTE idx=0; idx < MAXFLDNUM; idx++ )  {
		fputs( *arArrayPool[ idArrayPos ].desc.fields[ idx ].name, fpDataFile );
		fputc( *(int)arArrayPool[ idArrayPos ].desc.fields[ idx ].spos, fpDataFile );
		fputc( *(int)arArrayPool[ idArrayPos ].desc.fields[ idx ].len, fpDataFile );
		fputc( *(int)arArrayPool[ idArrayPos ].desc.fields[ idx ].type, fpDataFile );  }

	for ( BYTE idx=0; idx < MAXRECNUM; idx++ )  {
		fputs( *arArrayPool[ idArrayPos ].data[ idx ], fpDataFile );

	if ( ferror(fpDataFile) ) return( ERR_IO );
	else return( ERR_NULL );
}


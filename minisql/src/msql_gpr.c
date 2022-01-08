/*
	--------------------------------------------------------
		MINISQL v1.0
		Subroutines File #3 - General Purpose Routines

		This file contains all the necessary routines
		for data types conversions and checks, used for
		the array-pool management, by the main
		program.
	--------------------------------------------------------
*/



/* ..... String-to-Upper conversion .....
	    Note: Can be used circularly, like: "str = str2upper(str)"  */

char	*str2upper( char *str )
{
	char	*ustr="";
	while ( *str != NULL )  {
		*ustr = toupper( *(int)str );
		str++; ustr++;  }
	*ustr=NULL;

	return( ustr );
}



/* ..... String filling with spaces .....
	    Note: (dir=0) => fill right, (dir<>0)=> fill left	*/

char *fillstr( char *str, int newlen, char fillchar=' ', int dir=0 )
{
	char *fstr="", *spc=" ", *spcstr="";
	int	numspc;

	*spc=fillchar;
	numspc=newlen-strlen( str );
	if ( numspc )  {
		for (int c=0; c < numspc; c++)  spcstr=strlink( spcstr, spc );
		if ( dir=0 ) fstr=strlink( str, spcstr );
		else fstr=strlink( spcstr, str );  }

	return( fstr );
}



/* ..... String strip from spaces (including: \t,\n,\b, ...) .....
	    Note: Can be used circularly, like: "str = stripstr(str)"  */

char	*stripstr( char *str )
{
	char	*sstr="";
	while ( *str != NULL )  {
		if ( ! isspace( *str ) ) *sstr = *str;
		str++; sstr++;  }
	*sstr=NULL;

	return( sstr );
}



/* ..... Merge two strings into one .....
	    Note: Can be used circularly, like:  "str = strlink( str, s1 )"  */

char *strlink( char *s1, char *s2 )
{
	char	*cstr="", *str;

	str = cstr;
	while ( (*cstr = *s1++) != NULL )  cstr++;
	while ( (*cstr = *s2++) != NULL )  cstr++;

	return( str );
}



/* ..... String-to-Number conversion ..... */

float str2num( char *str )
{
	return( (float)atof( str ) );
}




/* ..... Number-to-String conversion .....
	   Notes:  The routine converts a real number
			to a formated string. The format is:
				nint  =  number of digits on integer part
				ndec  =  number of digits on decimal part
				sign  =  signed result if <> 0, else unsigned
			If either (nint) or (ndec) are too small, the
			result is NULL.							*/

char	*num2str( float num, int nint, int ndec, int sign=1 )
{
	char	*fstr="", *ostr="", *istr="", *dstr="";
	char *zerostr="0", *decpstr=".", *plusign="+", *minusign="-", *spcstr=" ";
	int	dec, sig;

	ostr = ecvt( (double)num, (nint+ndec), &dec, &sig );

	strncpy( istr, ostr, dec );	/* ---> copy integer part */
	strcpy( dstr, &ostr[dec] );   /* ---> copy decimal part */

	if ( (strlen(istr) > nint) || (strlen(dstr) > ndec) )  return( fstr );

	istr = fillstr( istr, nint, ' ', 1 );	/* ---> fill with spaces */
	dstr = fillstr( dstr, ndec, '0', 0 );	/* ---> fill with zeroes */

	fstr = strlink( fstr, istr );
	fstr = strlink( fstr, decpstr );
	fstr = strlink( fstr, dstr );

	if (sign <> 0)  {
		if (sig <> 0)  fstr = strlink( minusign, fstr );
		else  fstr = strlink( plusign, fstr );  }

	result( fstr );
}






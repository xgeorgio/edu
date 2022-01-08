//--------------------------------------------
//
//--------------------------------------------
//               Harris Georgiou, 1997.
//--------------------------------------------



#ifndef     __STRINGS_H
#define     __STRINGS_H

#include "basearrs.cpp"
#include <string.h>


#ifndef     MAXSTRLEN
#define     MAXSTRLEN       32000
#endif



class string : public BaseArray<char>
{
    public:
        string() : BaseArray<char>()                        {}
        string( int len ) : BaseArray<char>(len+1)          {}
        string( string &s ) : BaseArray<char>(s)            {}
        string( const char *s ) : BaseArray<char>()
            {  (*this) = s;  }

        // ~string()        {}

        string & operator =( string &s )
            {  Copy(s);  return(s);  }
        string & operator =( const char *s )
            {  if (Resize(strlen(s)+1)==(strlen(s)+1))
                    strcpy(arr,s);  return(*this);  }
        operator const char *()
            {  return(arr);  }
        char * CharPtr( void )
            {  return(arr);  }

        int isNull( void )          
            {  return(!IsValid());  }
        int Length( void )
            {  if (isNull())  return(0);
               else  return(GetSize()-1);  }
        const char * Inverse( void )
            {  (*this)=InverseStr(*this);  return(*this);  }
        
        void SqueezeFromBegin( int nchars );
        void SqueezeFromEnd( int nchars );
        void SqueezeCharAt( int npos );
        void InsertAt( string &s, int pos );
        void InsertAt( const char *s, int pos );

        int operator <( string &s )
            {  return( stricmp(arr,s.arr)<0 );  }
        int operator >( string &s )
            {  return( stricmp(arr,s.arr)>0 );  }
        int operator ==( string &s )
            {  return( stricmp(arr,s.arr)==0 );  }
        int operator <=( string &s )
            {  return( stricmp(arr,s.arr)<=0 );  }
        int operator >=( string &s )
            {  return( stricmp(arr,s.arr)>=0 );  }

        // Note: return value of type 'string' does not work!
        friend const char * operator +( string &s1, string &s2 );
        friend const char * operator +( const char *s1, string &s2 );
        friend const char * operator +( string &s1, const char *s2 );
        friend const char * operator +( char ch, string &s2 );
        friend const char * operator +( string &s1, char ch );
        
        friend const char * InverseStr( string &s );

};


const char * InverseStr( string &s )
{
    int     i, m, u;
    char    ch;

    if (s.Length()>1)
    {
        u = s.Length()-1;
        m = s.Length()/2;
        for ( i=0; i<m; i++ )
            { ch=s(i); s(i)=s(u-i); s(u-i)=ch; }
    }
    return(s);
}


const char * InverseStr( const char *s )
{
    string      ss=s;
    
    return(InverseStr(ss));
}


void string::SqueezeFromBegin( int nchars )
{
    if ((nchars>0)&&(nchars<=Length()))
    {
        memmove(&arr[0],&arr[nchars],Length()+1-nchars);
        Resize(Length()+1-nchars);
    }
}


void string::SqueezeFromEnd( int nchars )
{
    if ((nchars>0)&&(nchars<=Length()))
    {
        ItemAt(Length()-nchars)='\0';
        Resize(Length()+1-nchars);
    }
}


void string::SqueezeCharAt( int npos )
{
    string      s1, s2;

    if ((npos>=0)&&(npos<=Length()))
    {
        ItemAt(npos)='\0';
        s1=(const char *)(&arr[0]);
        s2=(const char *)(&arr[npos+1]);
        (*this)=s1+s2;
    }
}

#include <iostream.h>

void string::InsertAt( string &s, int npos )
{
    string      s1;
    int         i;

    if (npos==0)
        { s1=(*this); (*this)=s+s1; }
    else if (npos==Length())  
        { s1=(*this); (*this)=s1+s; }
    else
    {
        for ( i=0; i<npos; i++ )  s1=s1+ItemAt(i);
        for ( i=0; i<s.Length(); i++ )  s1=s1+s(i);
        for ( i=npos; i<Length(); i++ )  s1=s1+ItemAt(i);

        cout << s1 << "("<<s1.Length()<<")     ";
        (*this) = s1;
        cout << (*this) << "("<<Length()<<")     "<< endl;
    }
}


void string::InsertAt( const char *s, int npos )
{
    string      ss(s);

    InsertAt(ss,npos);
}



#include <iostream.h>

// Note: operator << works fine with "string" (as: os << (char*) )

istream & operator >>( istream &is, string &s )
{
    char *t=new char[MAXSTRLEN];
    
    if (t)  { is>>t; s=t; }
    return(is);
}


ostream & operator <<( ostream &os, string &s )
{
    os<<(const char *)s;  return(os);
}


const char * operator +( string &s1, string &s2 )
{
    string      res;
    int         pos, len1, len2;
    char        *str;
    
    
    len1=s1.Length();
    len2=s2.Length();
    str=new char[len1+len2+1];
    
    strcpy(&str[0],s1);  strcpy(&str[len1],s2);
    res=str;  delete [] str;  
    
    return(res);
}


const char * operator +( const char *s1, string &s2 )
{
    string      ss1=s1;
    
    return(ss1+s2);
}


const char * operator +( string &s1, const char *s2 )
{
    string      ss2=s2;
    
    return(s1+ss2);
}


const char * operator +( char ch, string &s2 )
{
    string      s1(1);

    s1(0)=ch;
    return(s1+s2);
}


const char * operator +( string &s1, char ch )
{
    string      s2(1);

    s2(0)=ch;
    return(s1+s2);
}



#endif




#include <stdio.h>
#include "LDVector3.h"

namespace live2d
{


//------ Debug ------
void LDVector3::dump( const char* title , ld_bool newline , ld_int32 keta )
{
	if ( keta == 3 )
	{
		printf( "%s{%7.3f ,%7.3f ,%7.3f }(len=%7.3f)%s" , title , x , y , z , length() , ( newline?"\n":"" ) ) ;
	}
	else
	{
		if ( keta < 0 )
		{
			keta = 0 ;
		}
		else if ( keta > 5 )
		{
			keta = 5 ;
		}
		char dst[32] ;//絶対超えないサイズにする

		sprintf( dst , "%%s{%%7.%df,%%7.%df,%%7.%df %7.3f }%s" , keta , keta , keta , length(), ( newline? "\n" : "" ) ) ;

		printf( dst , title , x , y , z ) ;
	}
}


} // namespace live2d

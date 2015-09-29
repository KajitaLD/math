#include <cassert>
#include "LDMathUtil.h"

namespace live2d
{


const ld_float	LDMathUtil::PI				= 3.14159265f ;             //!< @brief 3.14159265f
const ld_float	LDMathUtil::PI2				= LDMathUtil::PI * 2.0f ;    //!< @brief EUC_PI * 2.0f ;
const ld_float	LDMathUtil::PI_OVER_2		= LDMathUtil::PI / 2.0f ;    //!< @brief EUC_PI / 2.0f ;
const ld_float	LDMathUtil::ONE_OVER_PI		= 1.0f / LDMathUtil::PI ;    //!< @brief 1.0f / EUC_PI ;
const ld_float	LDMathUtil::ONE_OVER_PI2		= 1.0f / LDMathUtil::PI2 ;   //!< @brief 1.0f / EUC_2PI ;
const ld_float	LDMathUtil::TOLERANCE			=0.000001;				//!< @brief 通常計算時の許容誤差 ;
const ld_float	LDMathUtil::GINBAL_TOLERANCE	=0.000001;				//!< @brief ジンバルロック時の許容誤差 ;


#if LD_CORE_ENABLE_QT
//float4つを見やすく表示するための文字列を返す
QString LDMathUtil::format4args( ld_float a,ld_float b,ld_float c,ld_float d )
{
	//args( <変数>, <表示幅>, <'f'でfloat指定>, <小数点以下の表示桁>  )
	return QString( "[ %1 %2 %3 %4 ]" ).arg( a,7,'f',3 ).arg( b,7,'f',3 ).arg( c,7,'f',3 ).arg( d,7,'f',3 );
}
//float3つを見やすく表示するための文字列を返す
QString LDMathUtil::format3args( ld_float a,ld_float b,ld_float c )
{
	//args( <変数>, <表示幅>, <'f'でfloat指定>, <小数点以下の表示桁>  )
	return QString( "[ %1 %2 %3 ]" ).arg( a,7,'f',3 ).arg( b,7,'f',3 ).arg( c,7,'f',3 );
}
#endif
} // namespace live2d

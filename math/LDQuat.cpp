#include <stdio.h>
#include <cassert>
#include "LDQuat.h"
#include "LDMathUtil.h"


namespace live2d
{

/**
* @brief 回転軸を返す
* @return 回転軸を返す
*/
LDVector3  LDQuat::getAxis() const
{
	ld_float  sinQ_over2Sq = 1.0f - w*w ;

	if ( sinQ_over2Sq <= 0.0f )
	{
		return LDVector3( 1.0f , 0.0f , 0.0f ) ;
	}

	ld_float  one_overSinQ_over2 = 1.0f / sqrt( sinQ_over2Sq ) ;

	return LDVector3(
	           x * one_overSinQ_over2 ,
	           y * one_overSinQ_over2 ,
	           z * one_overSinQ_over2
	       ) ;
}

/**
* @brief 最小弧クォータニオン (Game Gems1 p211)
* @param &v1 EVector3をセットする
* @param &v2 EVector3をセットする
* @param useNormalize 正規化する場合はtrue, そうでない場合はfalseをセットする。(入力無き場合はtrue)
*/
void LDQuat::setToRotationArc( const LDVector3& v1 , const LDVector3& v2 , bool useNormalize )
{
	const LDVector3* vv1 ;
	const LDVector3* vv2 ;
	LDVector3 tmp1 ;
	LDVector3 tmp2 ;

	if ( useNormalize )
	{
		tmp1 = v1 ;
		tmp1.normalize();

		tmp2 = v2 ;
		tmp2.normalize();
		vv1 = &tmp1 ;
		vv2 = &tmp2 ;
	}
	else
	{
		vv1 = &v1 ;
		vv2 = &v2 ;
	}

	LDVector3 c = crossProduct( *vv1 , *vv2 ) ;
	ld_float d = vv1->dotProduct( *vv2 ) ;

	ld_float s = ( ld_float )sqrt( ( 1+d )*2 ) ;
	this->x = c.x / s ;
	this->y = c.y / s ;
	this->z = c.z / s ;
	this->w = s / 2.0f ;
}

/**
* @brief オブジェクト空間->慣性空間への回転
* @param &orientation オイラー角(EEulerAngles)をセットする
*/
void LDQuat::setToRotateObjectToInertial( const LDEulerAngles& orientation )
{
	ld_float	sp , sb , sh ;
	ld_float	cp , cb , ch ;

	LDMathUtil::sinCos( &sp , &cp , orientation.pitch  * 0.5f ) ;
	LDMathUtil::sinCos( &sb , &cb , orientation.bank   * 0.5f ) ;
	LDMathUtil::sinCos( &sh , &ch , orientation.heading* 0.5f ) ;

	w =  ch*cp*cb + sh*sp*sb ;
	x =  ch*sp*cb + sh*cp*sb ;
	y = -ch*sp*sb + sh*cp*cb ;
	z = -sh*sp*cb + ch*cp*sb ;
}

/**
* @brief 慣性空間->オブジェクト空間への回転
* @param &orientation オイラー角(EEulerAngles)をセットする
*/
void LDQuat::setToRotateInertialToObject( const LDEulerAngles& orientation )
{
	ld_float	sp , sb , sh ;
	ld_float	cp , cb , ch ;

	LDMathUtil::sinCos( &sp , &cp , orientation.pitch  * 0.5f ) ;
	LDMathUtil::sinCos( &sb , &cb , orientation.bank   * 0.5f ) ;
	LDMathUtil::sinCos( &sh , &ch , orientation.heading* 0.5f ) ;

	w =  ch*cp*cb + sh*sp*sb ;
	x = -ch*sp*cb - sh*cp*sb ;
	y =  ch*sp*sb - sh*cp*cb ;
	z =  sh*sp*cb - ch*cp*sb ;
}

/**
* @brief 球面線形補間
* @param &q1 クォータニオン(EQuat)をセットする
* @param t　補間位置を表す数値をセットする
* @return 補間結果を返す
*/
LDQuat  LDQuat::slerp( const LDQuat& q1 , ld_float t ) const
{
	const LDQuat& q0 = *this ;

	// 範囲外の時は端点を返す
	if ( t <= 0.0f )
	{
		return q0 ;
	}
	if ( t >= 1.0f )
	{
		return q1 ;
	}

	// 内積でクォータニオン間の角度のcosを計算する
	ld_float  cosOmega = q0.dot( q1 ) ;

	ld_float  q1w = q1.w ;
	ld_float  q1x = q1.x ;
	ld_float  q1y = q1.y ;
	ld_float  q1z = q1.z ;

	if ( cosOmega < 0.0f )
	{
		q1w  = -q1w ;
		q1x  = -q1x ;
		q1y  = -q1y ;
		q1z  = -q1z ;
		cosOmega = -cosOmega ;
	}

	// 各クォータニオンは、単位クォータニオンである必要があり、内積は <= 1.0 になるはず
	assert( cosOmega < 1.1f ) ;

	ld_float  k0 , k1 ;
	if ( cosOmega > 0.9999f )
	{
		// 非常に近いので、単純に線形補間を用いる（0-divideを防ぐ）
		k0 = 1.0f -t ;
		k1 = t ;
	}
	else
	{
		ld_float  sinOmega = sqrt( 1.0f - cosOmega*cosOmega ) ;
		ld_float  omega    = atan2( sinOmega , cosOmega ) ;
		ld_float  one_overSinOmega = 1.0f / sinOmega ;
		k0 = sin( ( 1.0f-t )*omega ) * one_overSinOmega ;
		k1 = sin( t*omega ) * one_overSinOmega ;
	}

	// 補間する
	LDQuat  result ;
	result.x  = k0*q0.x + k1*q1x ;
	result.y  = k0*q0.y + k1*q1y ;
	result.z  = k0*q0.z + k1*q1z ;
	result.w  = k0*q0.w + k1*q1w ;

	return result ;
}

/**
* @brief 独自の球面線形補間（回転角度を保つ）。y軸90度、z軸90度の回転をSLERPで計算する場合、t　が変化した時、軸は最小距離を移動するが、角度は、90度ではなく小さな値となる。この計算を 90度の回転を保って、中心を通る計算についてテスト実装。
* @param &q1 クォータニオン(EQuat)をセットする
* @param t　補間位置を表す数値をセットする
* @return 補間結果を返す
*/
LDQuat  LDQuat::mySlerp( const LDQuat& q1 , ld_float t ) const
{
	const LDQuat& q0 = *this ;

	// 範囲外の時は端点を返す
	if ( t <= 0.0f )
	{
		return q0 ;
	}
	if ( t >= 1.0f )
	{
		return q1 ;
	}

	LDVector3	n0	= q0.getAxis() ;
	LDVector3	n1	= q1.getAxis() ;
	ld_float		a0	= q0.getAngle() ;
	ld_float		a1	= q1.getAngle() ;

	//
	ld_float		adiff	= LDMathUtil::getAngleDiff( a1,a0 ) ;
	ld_float		at		= a0 + adiff*t ;
	LDVector3	nt		= blend( n0,n1, 1-t , t ) ;
	nt.normalize();

	LDQuat ret ;
	ret.setToRotateAxis( nt, at );
	return ret ;
}

/**
* @brief 累乗 pow
* @param exponent クォータニオンの乗数をセットする
* @return クォータニオンの累乗を返す
*/
LDQuat  LDQuat::pow( ld_float  exponent ) const
{
	const LDQuat& q = *this ;
	if ( fabs( q.w ) > 0.9999f )
	{
		return q ;    //0-divideを防ぐ
	}

	ld_float  alpha = acos( q.w ) ;
	ld_float  newAlpha = alpha * exponent ;
	LDQuat  result ;
	result.w = cos( newAlpha ) ;

	ld_float  mult = sin( newAlpha ) / sin( alpha ) ;
	result.x  = q.x * mult ;
	result.y  = q.y * mult ;
	result.z  = q.z * mult ;

	return result ;
}

//------ Debug ------
void LDQuat::dump( const char* title , ld_bool newline , ld_int32 keta )
{
	if ( keta == 3 )
	{
		printf( "%s{%7.3f ,%7.3f ,%7.3f ,%7.3f }(len=%7.3f)%s" , title , w , x , y , z , length() , ( newline?"\n":"" ) ) ;
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

		sprintf( dst , "%%s{%%7.%df,%%7.%df,%%7.%df,%%7.%df %7.3f }%s" , keta , keta , keta , keta , length(), ( newline? "\n" : "" ) ) ;

		printf( dst , title , w , x , y , z ) ;
	}
}


} // namespace live2d

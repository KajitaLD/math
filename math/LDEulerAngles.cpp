#include <cassert>
#include "LDEulerAngles.h"
#include "LDQuat.h"
#include "LDMathUtil.h"
#include "LDMatrix44.h"

namespace live2d
{

/**
* @brief 正準オイラー角の３つ組を決定する
*/
void LDEulerAngles::canonize()
{
	pitch = LDMathUtil::wrapPi( pitch ) ;

	if ( pitch < - LDMathUtil::PI_OVER_2 )
	{
		pitch   =  -LDMathUtil::PI - pitch ;
		heading +=  LDMathUtil::PI ;
		bank    +=  LDMathUtil::PI ;
	}
	else if ( pitch > LDMathUtil::PI_OVER_2 )
	{
		pitch   =   LDMathUtil::PI - pitch ;
		heading +=  LDMathUtil::PI ;
		bank    +=  LDMathUtil::PI ;
	}

	// ジンバルロックのケースをチェックする
	if ( fabs( pitch ) > LDMathUtil::PI_OVER_2 - LDMathUtil::GINBAL_TOLERANCE )
	{
		// ジンバルロック内にいる。回転を差し替える
		heading += bank ;
		bank    = 0.0f ;
	}
	else
	{
		bank = LDMathUtil::wrapPi( bank ) ;
	}

	heading = LDMathUtil::wrapPi( heading ) ;
}

/**
* @brief オブジェクト空間->慣性空間へのクォータニオンからオイラー角を設定
* @param &q クォータニオンをセットする
*/
void  LDEulerAngles::fromObjectToInertialQuaternion( const LDQuat& q )
{
	ld_float  sp = -2.0f * ( q.y*q.z - q.w*q.x ) ;

	// ジンバルロックチェック
	if ( fabs( sp ) > 1.0f -LDMathUtil::GINBAL_TOLERANCE )
	{
		// 真上か下を向いている
		pitch  = LDMathUtil::PI_OVER_2 * sp ;
		heading  = atan2( -q.x*q.z + q.w*q.y , 0.5f - q.y*q.y - q.z*q.z ) ;
		bank     = 0.0f ;
	}
	else
	{
		// 角度を計算する
		pitch   = asin( sp ) ;
		heading = atan2( q.x*q.z + q.w*q.y , 0.5f - q.x*q.x - q.y*q.y ) ;
		bank    = atan2( q.x*q.y + q.w*q.z , 0.5f - q.x*q.x - q.z*q.z ) ;
	}
}

/**
* @brief 慣性空間->オブジェクト空間へのクォータニオンからオイラー角を設定
* @param &q クォータニオンをセットする
*/
void  LDEulerAngles::fromInertialToObjectQuaternion( const LDQuat& q )
{
	ld_float  sp = -2.0f * ( q.y*q.z + q.w*q.x ) ;

	if ( fabs( sp ) > 1.0f -LDMathUtil::GINBAL_TOLERANCE )
	{
		//真上か真下を向いている
		pitch    = LDMathUtil::PI_OVER_2 * sp ;
		heading  = atan2( -q.x*q.z - q.w*q.y , 0.5f - q.y*q.y - q.z*q.z ) ;
		bank     = 0.0f ;
	}
	else
	{
		pitch    = asin( sp ) ;
		heading  = atan2( q.x*q.z - q.w*q.y , 0.5f - q.x*q.x - q.y*q.y ) ;
		bank     = atan2( q.x*q.y - q.w*q.z , 0.5f - q.x*q.x - q.z*q.z ) ;
	}
}

/**
* @brief 世界座標->オブジェクト空間への変換行列をオイラー角に変換する(この行列は直交している必要がある)
* @param &m Ematrix44をセットする
*/
void  LDEulerAngles::fromWorldToObjectMatrix( const LDMatrix44& m )
{
	// m23からsin(pitch)を取り出す
	ld_float  sp = -m.m23 ;

	// ジンバルロックのチェック
	if ( fabs( sp ) > 1.0f -LDMathUtil::GINBAL_TOLERANCE )
	{
		//真上か真下
		pitch   = LDMathUtil::PI_OVER_2 * sp ;
		heading = atan2( -m.m31 , m.m11 ) ;
		bank    = 0.0f ;
	}
	else
	{
		heading = atan2( m.m13 , m.m33 ) ;
		pitch   = asin( sp ) ;
		bank    = atan2( m.m21 , m.m22 ) ;
	}
}

/**
* @brief 回転行列をオイラー角に変換する
* @param &m RotationMatrixをセットする
*/
//void  EEulerAngles::fromRotationMatrix( const ERotationMatrix &m )
//{
//	float  sp  = -m.m23 ;

//	// ジンバルロックのチェック
//	if( fabs(sp) > 1.0f -LDMathUtil::GINBAL_TOLERANCE )
//	{
//		//真上か真下
//		pitch   = EMathUtil::PI_OVER_2 * sp ;
//		heading = atan2( -m.m31 , m.m11 ) ;
//		bank    = 0.0f ;
//	}
//	else
//	{
//		heading = atan2( m.m13 , m.m33 ) ;
//		pitch   = asin( sp ) ;
//		bank    = atan2( m.m21 , m.m22 ) ;
//	}
//}

} // namespace live2d

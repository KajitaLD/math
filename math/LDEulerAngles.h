/**
 * @brief The EEulerAngles class
 * cf. [3D Math Primer for Graphics and Game Development] (利用許諾コード)
 */

#pragma once

#include "common.h"


namespace live2d
{


class LDQuat ;
class LDMatrix44 ;



class LDEulerAngles
{
public:
	ld_float  heading ;  //!< @brief heading
	ld_float  pitch ;    //!< @brief pitch
	ld_float  bank ;     //!< @brief bank

public:
	/**
	* @brief コンストラクタ
	*/
	LDEulerAngles() {}

	/**
	* @brief コンストラクタ
	* @param h headingをセットする
	* @param p pitchをセットする
	* @param b bankをセットする
	*/
	LDEulerAngles( ld_float h , float p , float b )
		: heading( h ) , pitch( p ) , bank( b ) {}

	/**
	* @brief オイラー角を初期化する
	*/
	void  identity()
	{
		heading = pitch = bank = 0.0f ;
	}

	/**
	* @brief 正準オイラー角の３つ組を決定する
	*/
	void  canonize() ;

	/**
	* @brief オブジェクト空間->慣性空間へのクォータニオンからオイラー角を設定
	* @param &q クォータニオンをセットする
	*/
	void  fromObjectToInertialQuaternion( const LDQuat& q ) ;

	/**
	* @brief 慣性空間->オブジェクト空間へのクォータニオンからオイラー角を設定
	* @param &q クォータニオンをセットする
	*/
	void  fromInertialToObjectQuaternion( const LDQuat& q ) ;

	/**
	* @brief オブジェクト空間->世界座標への変換行列をオイラー角に変換する(この行列は直交している必要がある)
	* @param &m Ematrix44をセットする
	*/
	void  fromObjectToWorldMatrix( const LDMatrix44& m ) ;

	/**
	* @brief 世界座標->オブジェクト空間への変換行列をオイラー角に変換する(この行列は直交している必要がある)
	* @param &m Ematrix44をセットする
	*/
	void  fromWorldToObjectMatrix( const LDMatrix44& m ) ;

	/**
	* @brief 回転行列をオイラー角に変換する
	* @param &m RotationMatrixをセットする
	*/
	//	void  fromRotationMatrix( const RotationMatrix &m ) ;
};


} // namespace live2d

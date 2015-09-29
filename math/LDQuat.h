
#pragma once

#include <cassert>
#include "LDVector3.h"
#include "LDEulerAngles.h"
#include "LDMathUtil.h"

namespace live2d
{

/**
 *
 */

class LDQuat
{
public:
	ld_float		x ; //!< @brief クォータニオンの要素：x
	ld_float		y ; //!< @brief クォータニオンの要素：y
	ld_float		z ; //!< @brief クォータニオンの要素：z
	ld_float		w ;	//!< @brief クォータニオンの要素：w

public:
	//------ constructor ------

	/**
	* @brief 高速化のため初期化は行わない
	*/
	inline LDQuat() ;

	/**
	* @brief 全ての値を val で初期化する
	* @param val 初期値をセットする
	*/
	inline LDQuat( ld_float val ) ;

	/**
	* @brief x,y,z,w を指定して初期化
	* @param x 初期値をセットする
	* @param y 初期値をセットする
	* @param z 初期値をセットする
	* @param w 初期値をセットする
	*/
	inline LDQuat( ld_float _x ,ld_float _y ,ld_float _z ,ld_float _w ) ;

	/**
	* @brief vector3 ,w を指定して初期化
	* @param _v EVector3をセットする
	* @param w 初期値をセットする
	*/
	inline LDQuat( LDVector3 _v ,ld_float _w ) ;

	/**
	* @brief コピーコンストラクタ
	* @param quat EQuatをセットする
	*/
	inline LDQuat( const LDQuat& quat ) ;

	//------ static factory ------
	static inline const LDQuat getIdentity() ;

	/**
	* @brief 軸と回転角を指定して、クォータニオンを返す
	* @param unitVec EVector3をセットする
	* @param radian 回転角[rad]をセットする
	* @return クォータニオンを返す
	*/
	static inline const LDQuat getRotation( const LDVector3& unitVec , float radian ) ;

	/**
	* @brief 単位ベクトル1 から 単位ベクトル2への回転を表すクォータニオンを返す
	* @param unitVec1 EVector3をセットする
	* @param unitVec2 EVector3をセットする
	* @return クォータニオンを返す
	*/
	static inline const LDQuat getRotation( const LDVector3& unitVec1 , const LDVector3& unitVec2 ) ;

	// 指定の回転のクォータニオンを生成する
	/**
	* @brief 指定の回転のクォータニオンを生成する
	* @param radian 回転角[rad]をセットする
	* @return クォータニオンを返す
	*/
	static inline const LDQuat getRotateX( ld_float radian ) ;

	/**
	* @brief 指定の回転のクォータニオンを生成する
	* @param radian 回転角[rad]をセットする
	* @return クォータニオンを返す
	*/
	static inline const LDQuat getRotateY( ld_float radian ) ;

	/**
	* @brief 指定の回転のクォータニオンを生成する
	* @param radian 回転角[rad]をセットする
	* @return クォータニオンを返す
	*/
	static inline const LDQuat getRotateZ( ld_float radian ) ;

	//--------------------
	/**
	* @brief 回転角を取り出して返す
	*/
	inline ld_float	getAngle() const ;

	/**
	* @brief 回転軸を取り出して返す
	* @return 回転軸を返す
	*/
	LDVector3		getAxis()  const ; //not inline

	/**
	* @brief クォータニオンの長さを返す
	* @return クォータニオンの長さを返す
	*/
	inline ld_float	length()
	{
		return ( ld_float )sqrt( w*w + x*x + y*y + z*z ) ;
	}

	/**
	* @brief 正規化
	*/
	inline void		normalize() ;

	/**
	* @brief クォータニオンを初期化する
	*/
	inline void		setToIdentity()
	{
		w = 1.0f ;
		x = y = z = 0.0f ;
	}

	/**
	* @brief X軸に特定の角度を設定
	* @param q X軸の角度をセットする
	*/
	inline void		setToRotateX( ld_float q ) ;

	/**
	* @brief Y軸に特定の角度を設定
	* @param q Y軸の角度をセットする
	*/
	inline void		setToRotateY( ld_float q ) ;

	/**
	* @brief Z軸に特定の角度を設定
	* @param q Z軸の角度をセットする
	*/
	inline void		setToRotateZ( ld_float q ) ;

	inline void		setToRotateAxis( const LDVector3& axis , ld_float q ) ;

	/**
	* @brief 最小弧クォータニオン　二点を結ぶ最小の弧を描く。(v1,v2が単位ベクトルであることがわかっている場合は useNormalizeを　false にすると計算量が多少減る)
	* @param &v1 EVector3をセットする
	* @param &v2 EVector3をセットする
	* @param useNormalize 正規化する場合はtrue, そうでない場合はfalseをセットする。(入力無き場合はtrue)
	*/
	void			setToRotationArc( const LDVector3& v1 , const LDVector3& v2 , bool useNormalize = true ) ; // not inline

	// オブジェクト空間->慣性空間への回転
	//inline void		setToRotateObjectToInertial( const EEulerAngles & orientation ) ;
	//inline void		setToRotateInertialToObject( const EEulerAngles & orientation ) ;
	/**
	* @brief オブジェクト空間->慣性空間への回転
	* @param &orientation オイラー角(EEulerAngles)をセットする
	*/
	void		setToRotateObjectToInertial( const LDEulerAngles& orientation ) ;

	/**
	* @brief 慣性空間->オブジェクト空間への回転
	* @param &orientation オイラー角(EEulerAngles)をセットする
	*/
	void		setToRotateInertialToObject( const LDEulerAngles& orientation ) ;

	/**
	* @brief 球面線形補間
	* @param &q1 クォータニオン(EQuat)をセットする
	* @param t　補間位置を表す数値をセットする
	* @return 補間結果を返す
	*/
	LDQuat			slerp( const LDQuat& q1 , ld_float t ) const ; // not inline

	/**
	* @brief 独自の球面線形補間（回転角度を保つ）。y軸90度、z軸90度の回転をSLERPで計算する場合、t　が変化した時、軸は最小距離を移動するが、角度は、90度ではなく小さな値となる。この計算を 90度の回転を保って、中心を通る計算についてテスト実装
	* @param &q1 クォータニオン(EQuat)をセットする
	* @param t　補間位置を表す数値をセットする
	* @return 補間結果を返す
	*/
	LDQuat			mySlerp( const LDQuat& q1 , ld_float t ) const ; // not inline

	/**
	* @brief 共役 conjugate
	*/
	inline LDQuat	conjugate( ) const;

	/**
	* @brief 累乗 pow
	* @param exponent クォータニオンの乗数をセットする
	* @return クォータニオンの累乗を返す
	*/
	LDQuat			pow( ld_float  exponent ) const ; // not inline

	/**
	* @brief 内積
	*/
	inline ld_float	dot( const LDQuat& b ) const ;

	//------ operator ------
	/**
	* @brief 外積
	*/
	inline LDQuat	operator * ( const LDQuat& a ) const ;

	inline LDQuat&	operator *= ( const LDQuat& a ) ;

	//------ Debug ------
	inline void		dump( const char* title = "" , ld_bool newline = true , ld_int32 keta = 3 ) ;

}; // -- endof class --

//--------------------------------------------------------------
//	非メンバ関数
//--------------------------------------------------------------
/**
* @brief 内積
*/
inline ld_float  dot( const LDQuat& a , const LDQuat& b )
{
	return a.dot( b ) ;
}

/**
* @brief SLERP 球面線形補間
* @param &q0 クォータニオン(EQuat)をセットする
* @param &q1 クォータニオン(EQuat)をセットする
* @param t 補間位置を表す数値をセットする
* @return 補間結果を返す
*/
inline LDQuat  slerp( const LDQuat& q0 , const LDQuat& q1 , ld_float t )
{
	return q0.slerp( q1,t ) ;
}

/**
* @brief 独自の球面線形補間（回転角度を保つ）
* @param &q0 クォータニオン(EQuat)をセットする
* @param &q1 クォータニオン(EQuat)をセットする
* @param t 補間位置を表す数値をセットする
* @return 補間結果を返す
*/
inline LDQuat  mySlerp( const LDQuat& q0 , const LDQuat& q1 , ld_float t )
{
	return q0.mySlerp( q1,t ) ;
}

/**
* @brief 共役 conjugate
* @param &q クォータニオン(EQuat)をセットする
* @return 共役を返す
*/
inline LDQuat  conjugate( const LDQuat& q )
{
	return q.conjugate() ;
}

/**
* @brief 累乗 pow
* @param &q クォータニオン(EQuat)をセットする
* @param exponent クォータニオンの乗数をセットする
* @return クォータニオンの累乗を返す
*/
inline LDQuat  pow( const LDQuat& q , ld_float  exponent )
{
	return q.pow( exponent ) ;
}


//--------------------------------------------------------------
//	メンバ関数の実装
//--------------------------------------------------------------
/**
* @brief コンストラクタ（高速化のため初期化は行わない）
*/
inline LDQuat::LDQuat()
{
}

/**
* @brief コンストラクタ（全ての値を val で初期化する）
* @param val 初期値をセットする
*/
inline LDQuat::LDQuat( ld_float val )
{
	x = y = z = w = val ;
}

/**
* @brief コンストラクタ（x,y,z,w を指定して初期化）
* @param x 初期値xをセットする
* @param y 初期値yをセットする
* @param z 初期値zをセットする
* @param w 初期値wをセットする
*/
inline LDQuat::LDQuat( ld_float _x ,ld_float _y ,ld_float _z ,ld_float _w )
{
	x=_x ;
	y=_y;
	z=_z;
	w=_w;
}

/**
* @brief コンストラクタ（vector3 ,w を指定して初期化）
* @param _v EVector3をセットする
* @param _w wをセットする
*/
inline LDQuat::LDQuat( LDVector3 _v ,ld_float _w )
{
	x=_v.x;
	y=_v.y;
	z=_v.z;
	w=_w ;
}

/**
* @brief コンストラクタ（コピーコンストラクタ）
* @param quat EQuatをセットする
*/
inline LDQuat::LDQuat( const LDQuat& quat )
{
	x=quat.x;
	y=quat.y;
	z=quat.z;
	w=quat.w;
}

//------ static factory ------
/**
* @brief クォータニオンを初期化する
* @return EQuat(0,0,0,1)を返す
*/
inline const LDQuat LDQuat::getIdentity()
{
	return LDQuat( 0,0,0,1 ) ;
}

/**
* @brief 軸と回転角を指定して、クォータニオンを返す
* @param unitVec
* @param radian
*/
inline const LDQuat	LDQuat::getRotation( const LDVector3& /*unitVec*/ , float /*radian*/ )
{
	//TODO not impl
}

/**
* @brief 単位ベクトル1 から 単位ベクトル2への回転を表すクォータニオンを返す
* @param unitVec
* @param unitVec2
*/
inline const LDQuat	LDQuat::getRotation( const LDVector3& /*unitVec1*/ , const LDVector3& /*unitVec2*/ )
{
	//TODO not impl

}

/**
* @brief X軸の回転のクォータニオンを生成する
* @param radian
*/
inline const LDQuat	LDQuat::getRotateX( ld_float /*radian*/ )
{
	//TODO not impl
}

/**
* @brief Y軸の回転のクォータニオンを生成する
* @param radian
*/
inline const LDQuat	LDQuat::getRotateY( ld_float /*radian*/ )
{
	//TODO not impl
}

/**
* @brief Z軸の回転のクォータニオンを生成する
* @param radian
*/
inline const LDQuat	LDQuat::getRotateZ( ld_float /*radian*/ )
{
	//TODO not impl
}

//------ setter ------
/**
* @brief X軸の回転のクォータニオンを生成する
* @param radian
*/
inline void LDQuat::setToRotateX( ld_float theta )
{
	ld_float	theta_over2 = theta * 0.5f ;
	w = cos( theta_over2 ) ;
	x = sin( theta_over2 ) ;
	y = 0.0f ;
	z = 0.0f ;
}

/**
* @brief Y軸の回転のクォータニオンを生成する
* @param radian
*/
inline void LDQuat::setToRotateY( ld_float theta )
{
	ld_float	theta_over2 = theta * 0.5f ;
	w = cos( theta_over2 ) ;
	x = 0.0f ;
	y = sin( theta_over2 ) ;
	z = 0.0f ;
}

/**
* @brief Z軸の回転のクォータニオンを生成する
* @param radian
*/
inline void LDQuat::setToRotateZ( ld_float theta )
{
	ld_float	theta_over2 = theta * 0.5f ;
	w = cos( theta_over2 ) ;
	x = 0.0f ;
	y = 0.0f ;
	z = sin( theta_over2 ) ;
}

/**
* @brief 回転軸と角度でクォータニオンを生成する(正規化した軸を渡す必要がある)
* @param axis 回転軸をセットする
* @param theta 角度をセットする
*/
inline void LDQuat::setToRotateAxis( const LDVector3& axis , ld_float theta )
{
	// 回転軸の正規化をチェック
	assert( fabs( axis.length() - 1.0f ) < 0.01f ) ;

	ld_float	theta_over2	= theta * 0.5f ;
	ld_float	sinQ_over2	= sin( theta_over2 ) ;

	w = cos( theta_over2 ) ;
	x = axis.x * sinQ_over2 ;
	y = axis.y * sinQ_over2 ;
	z = axis.z * sinQ_over2 ;
}


//------ operator ------

/**
* @brief クォータニオンの外積。乗算の順番は左から右で各変位が適用される順番に対応する。これはクォータニオンの乗算の標準的な定義から外れる (cf. 3D Math Primer for .. )
* @param a クォータニオンをセットする
* @return クォータニオンの外積を返す
*/
inline LDQuat  LDQuat::operator *( const LDQuat& a ) const
{
	LDQuat  result ;

	result.w = w * a.w - x * a.x - y * a.y - z * a.z;
	result.x = w * a.x + x * a.w + y * a.z - z * a.y;
	result.y = w * a.y - x * a.z + y * a.w + z * a.x;
	result.z = w * a.z + x * a.y - y * a.x + z * a.w;

	//	result.w = w*a.w - x*a.x - y*a.y - z*a.z ;
	//	result.x = w*a.x + x*a.w + y*a.y - z*a.z ;
	//	result.y = w*a.y + x*a.w + y*a.z - z*a.x ;
	//	result.z = w*a.z + x*a.w + y*a.x - z*a.y ;

	return result ;
}

inline LDQuat&  LDQuat::operator *=( const LDQuat& a )
{
	*this = *this * a ;
	return *this ;
}

/**
* @brief クォータニオンの正規化。浮動小数点の誤差の蓄積を防ぐ
*/
inline void LDQuat::normalize()
{
	ld_float  mag = ( ld_float )sqrt( w*w + x*x + y*y + z*z ) ;

	if ( mag > 0.0f )
	{
		ld_float  oneOverMag = 1.0f / mag ;
		w *= oneOverMag ;
		x *= oneOverMag ;
		y *= oneOverMag ;
		z *= oneOverMag ;
	}
	else
	{
		// 不正な状態
		assert( false ) ;

		// リリースビルドではとりあえず動作させる
		setToIdentity() ;
	}
}

/**
* @brief 回転角を返す
* @return 回転角(safeAcos(w) * 2.0f)を返す
*/
inline ld_float  LDQuat::getAngle() const
{
	return LDMathUtil::safeAcos( w ) * 2.0f ;
}

/**
* @brief 内積
* @param b クォータニオンをセットする
* @return 内積を返す
*/
inline ld_float  LDQuat::dot( const LDQuat& b ) const
{
	return w *b.w + x *b.x + y *b.y + z *b.z ;
}

//// 内積
//ld_float  dotProduct( const EQuaternion &a , const EQuaternion &b )
//{
//	return a.dotProduct(b) ;
//}

/**
* @brief 共役 conjugate
* @return 共役を返す
*/
inline LDQuat  LDQuat::conjugate( ) const
{
	//同じ回転量で反転した物を返す
	return  LDQuat( -x,-y,-z, w ) ;
}




} // namespace live2d

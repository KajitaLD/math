/**
 * @brief The EucVector3f class
 * ld_float型 ３次元ベクトルクラス
 * OpenGL準拠の列ベクトル(縦に並ぶ)として用いる前提
 *
 * 実装方針としては
 * ・継承なし ( 仮想関数テーブルを持たないようにする )
 * ・隠蔽なし
 * ・右手座標系（OpenGL/Mayaに準拠）
 * ・右手の法則による回転
 *
 * cf. [3D Math Primer for Graphics and Game Development] (利用許諾コード)
 *   但し、上記資料中では行ベクトルで利用するため、行列等が転置の関係になる
 */

#pragma once

#include <math.h>
#include "common.h"

namespace live2d
{



class LDVector3
{
public:
	ld_float	x ; //!< @brief 行列の要素：x
	ld_float	y ; //!< @brief 行列の要素：y
	ld_float	z ; //!< @brief 行列の要素：z

public:
	/**
	* @brief コンストラクタ
	*/
	LDVector3() : x( 0 ) , y( 0 ) , z( 0 ) {}

	/**
	* @brief コンストラクタ
	* @param &v EVector3をセットする
	*/
	LDVector3( const LDVector3& v ) : x( v.x ) ,  y( v.y ) ,  z( v.z ) {}

	/**
	* @brief コンストラクタ
	* @param vx EVector3の行列要素xをセットする
	* @param vy EVector3の行列要素yをセットする
	* @param vz EVector3の行列要素zをセットする
	*/
	LDVector3( ld_float vx , ld_float vy , ld_float vz ) : x( vx ) ,  y( vy ) ,  z( vz ) {}

	/**
	* @brief 代入する
	* @param &v EVector3をセットする
	* @return 自身を返す
	*/
	LDVector3& operator = ( const LDVector3& v )
	{
		x = v.x ;
		y = v.y ;
		z = v.z ;
		return *this ;
	}

	/**
	* @brief すべての要素が一致するか確認する
	* @param &v EVector3をセットする
	* @return 要素が一致していればtrue, そうでなければfalseを返す
	*/
	ld_bool operator == ( const LDVector3& v ) const
	{
		return x == v.x && y == v.y && z == v.z ;
	}

	/**
	* @brief 一致しない要素があるか確認する
	* @param &v EVector3をセットする
	* @return 一致しない要素があればtrue, そうでなければfalseを返す
	*/
	ld_bool operator != ( const LDVector3& v ) const
	{
		return x != v.x || y != v.y || z != v.z ;
	}

	/**
	* @brief ゼロベクトル化
	*/
	void zero()
	{
		x = y = z = 0.0f ;
	}

	/**
	* @brief ベクトル(Evector3)を正規化する
	*/
	void normalize()
	{
		ld_float magSq = x*x + y*y + z*z ;
		if ( magSq > 0.0 )  //0-divide check
		{
			ld_float invMag = 1.0f / sqrt( magSq ) ;
			x *= invMag ;
			y *= invMag ;
			z *= invMag ;
		}
	}

	/**
	* @brief 単項演算子のマイナス
	* @return EVector3(-x,-y,-z)を返す
	*/
	LDVector3 operator - () const
	{
		return LDVector3( -x,-y,-z ) ;
	}

	/**
	* @brief 二項演算子の"+"
	* @param &v Evector3をセットする
	* @return EVector3( x + v.x , y + v.y , z + v.z )を返す
	*/
	LDVector3 operator + ( const LDVector3& v ) const
	{
		return LDVector3( x + v.x , y+v.y , z + v.z ) ;
	}

	/**
	* @brief 二項演算子の"-"
	* @param &v Evector3をセットする
	* @return EVector3( x - v.x , y - v.y , z - v.z )を返す
	*/
	LDVector3 operator - ( const LDVector3& v ) const
	{
		return LDVector3( x -v.x , y -v.y , z -v.z ) ;
	}

	/**
	* @brief 二項演算子の"*"
	* @param a 行列の要素にかける係数をセットする
	* @return EVector3( a *x , a *y , a *z )を返す
	*/
	LDVector3 operator * ( ld_float a ) const
	{
		return LDVector3( a *x , a *y , a *z ) ;
	}

	/**
	* @brief 二項演算子の"/"
	* @param a 行列の要素を割る係数をセットする
	* @return EVector3( inv *x , inv *y , inv *z )を返す
	*/
	LDVector3 operator / ( ld_float a ) const
	{
		ld_float inv = 1.0f / a ;
		return LDVector3( inv *x , inv *y , inv *z ) ;
	}

	/**
	* @brief 二項演算子の"+="
	* @param &v 加算するEVector3をセットする
	* @return EVector3( x+v.x, y+v.y, z+v.z )を返す
	*/
	LDVector3& operator += ( const LDVector3& v )
	{
		x += v.x ;
		y += v.y ;
		z += v.z ;
		return *this ;
	}

	/**
	* @brief 二項演算子の"-="
	* @param &v 減算するEVector3をセットする
	* @return EVector3( x-v.x, y-v.y, z-v.z )を返す
	*/
	LDVector3& operator -= ( const LDVector3& v )
	{
		x -= v.x ;
		y -= v.y ;
		z -= v.z ;
		return *this ;
	}

	/**
	* @brief 二項演算子の"*="
	* @param a 乗算する係数をセットする
	* @return EVector3( a*x, a*y, a*z )を返す
	*/
	LDVector3& operator *= ( ld_float a )
	{
		x *= a ;
		y *= a ;
		z *= a ;
		return *this ;
	}

	/**
	* @brief 二項演算子の"/="
	* @param a 除算する係数をセットする
	* @return EVector3( (1.0f / a)*x, (1.0f / a)*y, (1.0f / a)*z )を返す
	*/
	LDVector3& operator /= ( ld_float a )
	{
		ld_float inv = 1.0f / a ;
		x *= inv ;
		y *= inv ;
		z *= inv ;
		return *this ;
	}

	/**
	* @brief ベクトルの内積 (乗算演算子のオーバーロード)
	* @param &v EVector3をセットする
	* @return ベクトルの内積を返す
	*/
	ld_float operator * ( const LDVector3& v ) const
	{
		return x *v.x + y *v.y + z *v.z ;
	}

	/**
	* @brief ベクトルの長さ　（メンバ関数 v1.length() と　外部関数の length( v1 ) が共に利用可能）
	* @return ベクトルの長さを返す
	*/
	ld_float length() const
	{
		return sqrt( x*x + y*y + z*z ) ;
	}

	/**
	* @brief ベクトルの内積
	* @param &v2 EVector3をセットする
	* @return ベクトルの内積を返す
	*/
	ld_float dotProduct( const LDVector3& v2 ) const
	{
		return this->x*v2.x + this->y*v2.y + this->z*v2.z ;
	}

	//------ Debug ------
	void dump( const char* title = "" , ld_bool newline = true , ld_int32 keta = 3 ) ;

};

//====================================================
//	非メンバ関数
//====================================================
/**
* @brief ベクトルの長さ
* @param &v EVector3をセットする
* @return ベクトルの長さを返す
*/
inline ld_float length( const LDVector3& v )
{
	return sqrt( v.x*v.x + v.y*v.y + v.z*v.z ) ;
}

/**
* @brief ベクトルの外積
* @param &v1 EVector3をセットする
* @param &v2 EVector3をセットする
* @return ベクトルの外積を返す
*/
inline LDVector3 crossProduct( const LDVector3& v1 , const LDVector3& v2 )
{
	return LDVector3( v1.y *v2.z - v1.z *v2.y ,
	                  v1.z *v2.x - v1.x *v2.z ,
	                  v1.x *v2.y - v1.y *v2.x ) ;
}

/**
* @brief ベクトルの内積
* @param &v1 EVector3をセットする
* @param &v2 EVector3をセットする
* @return ベクトルの内積を返す
*/
inline ld_float dot( const LDVector3& v1 , const LDVector3& v2 )
{
	return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z ;
}

/**
* @brief 左からスカラーを乗算
* @param k スカラー値をセットする
* @param &v EVector3をセットする
* @return EVector3( k*v.x, k*v.y, k*v.z )を返す
*/
inline LDVector3 operator * ( ld_float k , const LDVector3& v )
{
	return LDVector3( k *v.x , k *v.y , k *v.z ) ;
}

/**
* @brief ２つの点の距離を取得する
* @param &v1 EVector3をセットする
* @param &v2 EVector3をセットする
* @return ２つの点の距離を返す
*/
inline ld_float distance( const LDVector3& v1 ,const LDVector3& v2 )
{
	ld_float dx = v1.x - v2.x ;
	ld_float dy = v1.y - v2.y ;
	ld_float dz = v1.z - v2.z ;
	return sqrt( dx*dx + dy*dy + dz*dz ) ;
}

/**
* @brief ２つのベクトルをブレンドする
* @param &v1 EVector3をセットする
* @param &v2 EVector3をセットする
* @param t1 v1にかけるスカラー値t1をセットする
* @param t2 v2にかけるスカラー値t2をセットする
* @return ブレンドしたベクトルを返す
*/
inline LDVector3 blend( const LDVector3& v1 ,const LDVector3& v2 , ld_float t1 , ld_float t2 )
{
	return LDVector3( v1.x*t1+v2.x*t2 , v1.y*t1+v2.y*t2 , v1.z*t1+v2.z*t2 ) ;
}

//====================================================
} // namespace live2d

/**
 * 行列
 *
 *  (c) CYBERNOIDS Co.,Ltd. All rights reserved.
 */
#include <cassert>
#include <stdio.h>

#include "LDMatrix44.h"

namespace live2d
{

//=====================================================
/**
* @brief コンストラクタ
*/
//=====================================================
LDMatrix44::LDMatrix44()
	: m11( 1.0f ) , m21( 0.0f ) , m31( 0.0f ) , m41( 0.0f )
	, m12( 0.0f ) , m22( 1.0f ) , m32( 0.0f ) , m42( 0.0f )
	, m13( 0.0f ) , m23( 0.0f ) , m33( 1.0f ) , m43( 0.0f )
	, m14( 0.0f ) , m24( 0.0f ) , m34( 0.0f ) , m44( 1.0f )
{
}

//=====================================================
/**
* @brief 単位行列に初期化
*/
//=====================================================
void LDMatrix44::identity()
{
	m11 = m22 = m33 = m44 = 1.0f ;
	m12 = m32 = m42 = m21 = m31 = m41 = m13 = m23 = m43 = m14 = m24 = m34 = 0.0f ;
}

//=====================================================
/**
* @brief 行列を設定
* @param *_m 行列配列をセットする
*/
//=====================================================
void LDMatrix44::setMatrix( const ld_float* _m )
{
	for ( int i = 15 ; i >= 0 ; --i )
	{
		m[i] = _m[i] ;
	}
}


//=====================================================
/**
* @brief 行列を設定
* @param &m2 EMatrix44をセットする
*/
//=====================================================
void LDMatrix44::setMatrix( const LDMatrix44& m2 )
{
	for ( int i = 15 ; i >= 0 ; --i )
	{
		this->m[i] = m2.m[i] ;
	}
}

//=====================================================
/**
* @brief 受け取った２つの行列の掛け算を行う(指定の行列 m2 を右から掛け、dstに設定する)
* @param &b EMatrix44をセットする
* @param *dst 変換行列を受け取るポインタをセットする
*/
//=====================================================
// 指定の行列 m2 を右から掛け、dstに設定する
// TODO 最適化
void LDMatrix44::mult( const LDMatrix44& b , LDMatrix44* dst , ld_bool omit4thRow )
{
	assert( this != dst ) ;

	if ( this == dst )
	{
		mult_safe( this->m , b.m , dst->m , omit4thRow ) ;
	}
	else
	{
		mult_fast( this->m , b.m , dst->m , omit4thRow ) ;
	}
}

//=====================================================
/**
* @brief 安全な乗算. a , b と dst が同じでも良い安全な乗算(ld_float[16]を別に用意するため負荷大)
* @param *a 行列aをセットする
* @param *b 行列bをセットする
* @param *dst 変換行列を受け取るポインタをセットする
*/
//=====================================================
void LDMatrix44::mult_safe( const ld_float* a , const ld_float* b , ld_float* dst, ld_bool omit4thRow )
{
	ld_float tmp[16] ;
	if ( a == dst )
	{
		mult_fast( a, b , tmp , omit4thRow );
		for ( int i = 15 ; i >= 0 ; --i )
		{
			dst[i] = tmp[i] ;
		}
	}
	else
	{
		mult_fast( a, b, dst , omit4thRow ) ;
	}
}

//=====================================================
/**
* @brief 高速な乗算. a , b と dst が同じ場合は不正な計算になる
* @param *a 行列aをセットする
* @param *b 行列bをセットする
* @param *dst 乗算した行列を受け取るポインタをセットする
*/
//=====================================================
void LDMatrix44::mult_fast( const ld_float* a , const ld_float* b , ld_float* dst , ld_bool omit4thRow )
{
	// 透視変換を除けば通常4行は 0,0,0,1 であるため計算を省略できる場合が多い
	if ( omit4thRow )
	{
		dst[ 0] = a[ 0]*b[ 0] + a[ 4]*b[ 1] + a[ 8]*b[ 2] ;
		dst[ 4] = a[ 0]*b[ 4] + a[ 4]*b[ 5] + a[ 8]*b[ 6] ;
		dst[ 8] = a[ 0]*b[ 8] + a[ 4]*b[ 9] + a[ 8]*b[10] ;
		dst[12] = a[ 0]*b[12] + a[ 4]*b[13] + a[ 8]*b[14] + a[12] ;

		dst[ 1] = a[ 1]*b[ 0] + a[ 5]*b[ 1] + a[ 9]*b[ 2] ;
		dst[ 5] = a[ 1]*b[ 4] + a[ 5]*b[ 5] + a[ 9]*b[ 6] ;
		dst[ 9] = a[ 1]*b[ 8] + a[ 5]*b[ 9] + a[ 9]*b[10] ;
		dst[13] = a[ 1]*b[12] + a[ 5]*b[13] + a[ 9]*b[14] + a[13] ;

		dst[ 2] = a[ 2]*b[ 0] + a[ 6]*b[ 1] + a[10]*b[ 2] ;
		dst[ 6] = a[ 2]*b[ 4] + a[ 6]*b[ 5] + a[10]*b[ 6] ;
		dst[10] = a[ 2]*b[ 8] + a[ 6]*b[ 9] + a[10]*b[10] ;
		dst[14] = a[ 2]*b[12] + a[ 6]*b[13] + a[10]*b[14] + a[14] ;

		dst[ 3] = dst[ 7] = dst[11] = 0 ;
		dst[15] = 1 ;
	}
	else
	{
		dst[ 0] = a[ 0]*b[ 0] + a[ 4]*b[ 1] + a[ 8]*b[ 2] + a[12]*b[ 3] ;
		dst[ 4] = a[ 0]*b[ 4] + a[ 4]*b[ 5] + a[ 8]*b[ 6] + a[12]*b[ 7] ;
		dst[ 8] = a[ 0]*b[ 8] + a[ 4]*b[ 9] + a[ 8]*b[10] + a[12]*b[11] ;
		dst[12] = a[ 0]*b[12] + a[ 4]*b[13] + a[ 8]*b[14] + a[12]*b[15] ;

		dst[ 1] = a[ 1]*b[ 0] + a[ 5]*b[ 1] + a[ 9]*b[ 2] + a[13]*b[ 3] ;
		dst[ 5] = a[ 1]*b[ 4] + a[ 5]*b[ 5] + a[ 9]*b[ 6] + a[13]*b[ 7] ;
		dst[ 9] = a[ 1]*b[ 8] + a[ 5]*b[ 9] + a[ 9]*b[10] + a[13]*b[11] ;
		dst[13] = a[ 1]*b[12] + a[ 5]*b[13] + a[ 9]*b[14] + a[13]*b[15] ;

		dst[ 2] = a[ 2]*b[ 0] + a[ 6]*b[ 1] + a[10]*b[ 2] + a[14]*b[ 3] ;
		dst[ 6] = a[ 2]*b[ 4] + a[ 6]*b[ 5] + a[10]*b[ 6] + a[14]*b[ 7] ;
		dst[10] = a[ 2]*b[ 8] + a[ 6]*b[ 9] + a[10]*b[10] + a[14]*b[11] ;
		dst[14] = a[ 2]*b[12] + a[ 6]*b[13] + a[10]*b[14] + a[14]*b[15] ;

		dst[ 3] = a[ 3]*b[ 0] + a[ 7]*b[ 1] + a[11]*b[ 2] + a[15]*b[ 3] ;
		dst[ 7] = a[ 3]*b[ 4] + a[ 7]*b[ 5] + a[11]*b[ 6] + a[15]*b[ 7] ;
		dst[11] = a[ 3]*b[ 8] + a[ 7]*b[ 9] + a[11]*b[10] + a[15]*b[11] ;
		dst[15] = a[ 3]*b[12] + a[ 7]*b[13] + a[11]*b[14] + a[15]*b[15] ;
	}
}


//=====================================================
/**
* @brief 変換
* @param x 行列の要素xをセットする
* @param y 行列の要素yをセットする
* @param z 行列の要素zをセットする
*/
//=====================================================
void LDMatrix44::translate( ld_float x, ld_float y , ld_float z )
{
	m14 = m11* x + m12*y + m13*z + m14 ;
	m24 = m21* x + m22*y + m23*z + m24 ;
	m34 = m31* x + m32*y + m33*z + m34 ;
	m44 = m41* x + m42*y + m43*z + m44 ;
}

void LDMatrix44::setToTranslate(ld_float x, ld_float y, ld_float z)
{
	m14 = x ;
	m24 = y ;
	m34 = z ;
}

//=====================================================
/**
* @brief スケール変換
* @param scaleX Xスケール変換係数をセットする
* @param scaleY Yスケール変換係数をセットする
* @param scaleZ Zスケール変換係数をセットする
*/
//=====================================================
void LDMatrix44::scale( ld_float scaleX ,ld_float scaleY , ld_float scaleZ )
{
	m11 *= scaleX ;
	m12 *= scaleY ;
	m13 *= scaleZ ;

	m21 *= scaleX ;
	m22 *= scaleY ;
	m23 *= scaleZ ;

	m31 *= scaleX ;
	m32 *= scaleY ;
	m33 *= scaleZ ;

	m41 *= scaleX ;
	m42 *= scaleY ;
	m43 *= scaleZ ;
}

//=====================================================
/**
* @brief X軸周りの回転を行う
* @param theta 角度をセットする
*/
//=====================================================
void LDMatrix44::rotateX( ld_float thetaX )
{
	ld_float c = cos( thetaX ) ;
	ld_float s = sin( thetaX ) ;
	ld_float tmp = m12 ;
	m12 =  tmp  * c + m13* s ;
	m13 =  tmp  *-s + m13* c ;

	tmp = m22 ;
	m22 =  tmp  * c + m23* s ;
	m23 =  tmp  *-s + m23* c ;

	tmp = m32 ;
	m32 =  tmp  * c + m33* s ;
	m33 =  tmp  *-s + m33* c ;

	tmp = m42 ;
	m42 =  tmp  * c + m43* s ;
	m43 =  tmp  *-s + m43* c ;
}

//=====================================================
/**
* @brief Y軸周りの回転を行う
* @param theta 角度をセットする
*/
//=====================================================
void LDMatrix44::rotateY( ld_float thetaY )
{
	ld_float c = cos( thetaY ) ;
	ld_float s = sin( thetaY ) ;

	ld_float tmp__ = m11 ;
	m11 = tmp__* c + m13*-s ;
	m13 = tmp__* s + m13* c ;

	tmp__ = m21 ;
	m21 = tmp__* c + m23*-s ;
	m23 = tmp__* s + m23* c ;

	tmp__ = m31 ;
	m31 = tmp__* c + m33*-s ;
	m33 = tmp__* s + m33* c ;

	tmp__ = m41 ;
	m41 = tmp__* c + m43*-s ;
	m43 = tmp__* s + m43* c ;
}

//=====================================================
/**
* @brief Z軸周りの回転を行う
* @param theta 角度をセットする
*/
//=====================================================
void LDMatrix44::rotateZ( ld_float thetaZ )
{
	ld_float c = cos( thetaZ ) ;
	ld_float s = sin( thetaZ ) ;

	ld_float tmp__ = m11 ;
	m11 = tmp__*  c + m12*  s ;
	m12 = tmp__* -s + m12*  c ;

	tmp__ = m21 ;
	m21 = tmp__*  c + m22*  s ;
	m22 = tmp__* -s + m22*  c ;

	tmp__ = m31 ;
	m31 = tmp__*  c + m32*  s ;
	m32 = tmp__* -s + m32*  c ;

	tmp__ = m41 ;
	m41 = tmp__*  c + m42*  s ;
	m42 = tmp__* -s + m42*  c ;
}

//=====================================================
/**
* @brief 変換を行う
* @param &p EVector3をセットする
* @return 変換行列を返す
*/
//=====================================================
LDVector3  LDMatrix44::transform( const LDVector3& p )const
{
	return LDVector3(
	           m11 * p.x + m12*p.y + m13*p.z + m14 ,
	           m21 * p.x + m22*p.y + m13*p.z + m24 ,
	           m31 * p.y + m32*p.y + m13*p.z + m34
	       ) ;
}

//=====================================================
/**
* @brief 変換を行う
* @param &p EVector3をセットする
* @param *dst 変換行列を受け取るポインタをセットする
*/
//=====================================================
void	LDMatrix44::transform( const LDVector3& p , LDVector3* dst )
{
	//p == dst の場合も考慮し、退避して計算する
	ld_float x = m11 * p.x + m12*p.y + m13*p.z + m14 ;
	ld_float y = m21 * p.x + m22*p.y + m13*p.z + m24 ;
	dst->z  = m31 * p.y + m32*p.y + m13*p.z + m34 ;
	dst->x = x ;
	dst->y = y ;
}

#define EUC_3D_COORD_RIGHT_HAND		(1)		//右手座標系/右手法則による回転の時に 1

//=====================================================
//=====================================================
void  LDMatrix44::fromQuaterion( const LDQuat& q )
{
#if 0
	// http://miffysora.wikidot.com/quaternion:matrix
	ld_float  ww = 2.0f * q.w ;
	ld_float  xx = 2.0f * q.x ;
	ld_float  yy = 2.0f * q.y ;
	ld_float  zz = 2.0f * q.z ;

	// TODO 最適化
	m11 = 1.0f - yy*q.y + zz*q.z ;
	m12 = xx*q.y + ww*q.z ;
	m13 = xx*q.z - ww*q.y ;

	m21 = xx*q.y - ww*q.z ;
	m22 = 1.0f - zz*q.z + xx*q.x ;
	m23 = yy*q.z + ww*q.x ;

	m31 = xx*q.z + ww*q.y ;
	m32 = yy*q.z - ww*q.x ;
	m33 = 1.0f - xx*q.x + yy*q.y ;

	// 平行移動をなくす
	tx = ty = tz = 0.0f ;


#else
	//ゲーム3D数学方式（左手系）
#if EUC_3D_COORD_RIGHT_HAND
	ld_float  ww = -2.0f * q.w ;
#else
	ld_float  ww = 2.0f * q.w ;
#endif
	ld_float  xx = 2.0f * q.x ;
	ld_float  yy = 2.0f * q.y ;
	ld_float  zz = 2.0f * q.z ;

	// TODO 最適化
	m11 = 1.0f - yy*q.y - zz*q.z ;
	m12 = xx*q.y + ww*q.z ;
	m13 = xx*q.z - ww*q.y ;

	m21 = xx*q.y - ww*q.z ;
	m22 = 1.0f - xx*q.x - zz*q.z ;
	m23 = yy*q.z + ww*q.x ;

	m31 = xx*q.z + ww*q.y ;
	m32 = yy*q.z - ww*q.x ;
	m33 = 1.0f - xx*q.x - yy*q.y ;

	// 平行移動をなくす
	tx = ty = tz = 0.0f ;
#endif
	// 他の要素は要確認
	m41 = m42 = m43 = 0.0f ;
	m44 = 1.0f ;
}

//=====================================================
//=====================================================

void LDMatrix44::dump44( )
{
	printf( "[ %7.3f  %7.3f  %7.3f  %7.3f ]\n" , m11 , m12 , m13 , m14 ) ;
	printf( "[ %7.3f  %7.3f  %7.3f  %7.3f ]\n" , m21 , m22 , m23 , m24 ) ;
	printf( "[ %7.3f  %7.3f  %7.3f  %7.3f ]\n" , m31 , m32 , m33 , m34 ) ;
	printf( "[ %7.3f  %7.3f  %7.3f  %7.3f ]\n" , m41 , m42 , m43 , m44 ) ;
}

void LDMatrix44::dump( )
{
	printf( "{ %7.3f %7.3f %7.3f %7.3f , %7.3f %7.3f %7.3f %7.3f  , %7.3f %7.3f %7.3f %7.3f  , %7.3f %7.3f %7.3f %7.3f }\n"
	        , m[0],m[1],m[2],m[3] , m[4],m[5],m[6],m[7] , m[8],m[0],m[10],m[11] , m[12],m[13],m[14],m[15] ) ;
}

//***************************************
// Serialize
//***************************************
template<class Archive>
void LDMatrix44::serialize( Archive& ar, unsigned int /*version*/ )
{
	LD_SERIALIZE_VALUE(ar, m );
}
LD_SERIALIZE_IMPL(LDMatrix44);


//=====================================================
//	外部関数
//=====================================================
/**
* @brief EMatrix44 * EVector3f
* @param　&m EMatrix44をセットする
* @param &p EVector3をセットする
* @return EMatrix44 * EVector3fを返す
*/
LDVector3		operator  *( const LDMatrix44& m  , const LDVector3& p )
{
	return LDVector3(
	           m.m11 * p.x + m.m12*p.y + m.m13*p.z + m.m14 ,
	           m.m21 * p.x + m.m22*p.y + m.m23*p.z + m.m24 ,
	           m.m31 * p.x + m.m32*p.y + m.m33*p.z + m.m34
	       ) ;
}

/**
* @brief EMatrix44 * EMatrix44(コピーが発生するので、速度重視の場合は使わない)
* @param　&m EMatrix44をセットする
* @param &p EMatrix44をセットする
* @return EMatrix44 * EMatrix44を返す
*/
LDMatrix44		operator  *( const LDMatrix44& a , const LDMatrix44& b )
{
	LDMatrix44  r ;
	//	dst[ 0] = a[ 0]*b[ 0] + a[ 4]*b[ 1] + a[ 8]*b[ 2] + a[12]*b[ 3] ;

	r.m11 = a.m11*b.m11 + a.m12*b.m21 + a.m13*b.m31 + a.m14*b.m41 ;
	r.m12 = a.m11*b.m12 + a.m12*b.m22 + a.m13*b.m32 + a.m14*b.m42 ;
	r.m13 = a.m11*b.m13 + a.m12*b.m23 + a.m13*b.m33 + a.m14*b.m43 ;
	r.m14 = a.m11*b.m14 + a.m12*b.m24 + a.m13*b.m34 + a.m14*b.m44 ;

	r.m21 = a.m21*b.m11 + a.m22*b.m21 + a.m23*b.m31 + a.m24*b.m41 ;
	r.m22 = a.m21*b.m12 + a.m22*b.m22 + a.m23*b.m32 + a.m24*b.m42 ;
	r.m23 = a.m21*b.m13 + a.m22*b.m23 + a.m23*b.m33 + a.m24*b.m43 ;
	r.m24 = a.m21*b.m14 + a.m22*b.m24 + a.m23*b.m34 + a.m24*b.m44 ;

	r.m31 = a.m31*b.m11 + a.m32*b.m21 + a.m33*b.m31 + a.m34*b.m41 ;
	r.m32 = a.m31*b.m12 + a.m32*b.m22 + a.m33*b.m32 + a.m34*b.m42 ;
	r.m33 = a.m31*b.m13 + a.m32*b.m23 + a.m33*b.m33 + a.m34*b.m43 ;
	r.m34 = a.m31*b.m14 + a.m32*b.m24 + a.m33*b.m34 + a.m34*b.m44 ;

	r.m41 = a.m41*b.m11 + a.m42*b.m21 + a.m43*b.m31 + a.m44*b.m41 ;
	r.m42 = a.m41*b.m12 + a.m42*b.m22 + a.m43*b.m32 + a.m44*b.m42 ;
	r.m43 = a.m41*b.m13 + a.m42*b.m23 + a.m43*b.m33 + a.m44*b.m43 ;
	r.m44 = a.m41*b.m14 + a.m42*b.m24 + a.m43*b.m34 + a.m44*b.m44 ;

	return r ;//コピーが発生するので、速度重視の場合は使わない
}


//EVector3f		operator *=( const EMatrix44 &m  , const EVector3f &p ) ;//
LDMatrix44		operator *=( const LDMatrix44& m1 , const LDMatrix44& m2 ) ;

bool			operator ==(const LDMatrix44& a, const LDMatrix44& b)
{
	for (int i = 0; i < 16; ++i) {
		if(a.m[i]!=b.m[i])return false;
	}
	return true;
}

bool			operator !=(const LDMatrix44& a, const LDMatrix44& b)
{
	return !(a==b);
}

QDebug operator<<( QDebug dbg, const LDMatrix44& m )
{
	dbg.nospace() << "\n"
	              << LDMathUtil::format4args( m.m11,m.m12,m.m13,m.m14 ) <<"\n"
	              << LDMathUtil::format4args( m.m21,m.m22,m.m23,m.m24 ) <<"\n"
	              << LDMathUtil::format4args( m.m31,m.m32,m.m33,m.m34 ) <<"\n"
	              << LDMathUtil::format4args( m.m41,m.m42,m.m43,m.m44 );

	return dbg.space();
}




} // namespace live2d

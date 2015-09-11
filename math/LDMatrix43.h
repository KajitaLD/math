/**
 * EMatrix43 行列クラス
 *
 * 行列・ベクトルの仕様は、OpenGLに準拠する。
 * ・座標系は右手座標系、回転は右手の法則（右ねじ）
 * ・座標変換は、列ベクトル(縦に並ぶ)を右側から掛ける
 *
 * ----------------------------
 * 設計方針
 * ・ld_float[12]で定義された行列を、キャストして使えるようにする
 *　・上記目的のため隠蔽、継承を行わない（仮想関数テーブルを持たせない）
 * ・より高機能な行列クラスが必要になった場合は、この行列を拡張するのではなく、集約（ラップ）するか、別途用意する
 *
 * ----------------------------
 * 行列の形と、列ベクトルとの乗算
 * [ m11 m12 m13 m14 ][ x ]
 * [ m21 m22 m23 m24 ][ y ]
 * [ m31 m32 m33 m34 ][ z ]
 *
 * ----------------------------
 * union によりアクセス方法の意味付けを多様化する。隠蔽せずに直接以下の形でアクセスする。
 *
 * ・m[12] = { m11,m21,m31 , m12,m22,m32 , m13,m23,m33 , m14,m24,m34 } ;
 *    配列としての意味は、OpenGLに直接渡せる並び
 *　・a[3][4] は a[row][col]
 * ・m11 , m21 , mij.. (i=row,j=col)でのアクセス
 * ・scaleX , scaleY , scaleZ , tx , ty , tz でのアクセス
 *
 *  (c) CYBERNOIDS Co.,Ltd. All rights reserved.
 */

#pragma once

#include "common.h"
#include "LDVector3.h"
#include "LDQuat.h"


namespace live2d
{



//--------- EMatrix43 ------------
class LDMatrix43
{
public:
	// 行列の要素に多用な形でアクセスできるように union で定義
	union
	{
		ld_float m[12] ;     //!< @brief OpenGLで扱う形式
		ld_float a[3][4] ;	//!< @brief a[row][col]でアクセス
		struct
		{
			ld_float m11,m21,m31   ,m12 ,m22,m32  ,m13,m23,m33  ,m14,m24,m34 ;
		};
		struct
		{
			ld_float scaleX ,_m21,_m31   ,_m12 ,scaleY ,_m32  ,_m13,_m23,scaleZ   ,tx ,ty ,tz ;
		};
	};

public:
	/**
	* @brief コンストラクタ
	*/
	LDMatrix43() ;

	//------ 初期化 -------
	/**
	* @brief 単位行列に初期化
	*/
	void  identity() ;

	/**
	* @brief 行列式を取得する
	* @return 行列式を返す
	*/
	ld_float  getDeterminant() const ;

	/**
	* @brief 逆行列を取得する
	* @return 逆行列を返す
	*/
	LDMatrix43  getInverse() const ;

	/**
	* @brief 逆行列を取得する
	* @param *ret EMatrix43をセットする
	*/
	void  getInverse( LDMatrix43* ret ) const ;

	//------ Setter/Getter -------
	/**
	* @brief 行列配列を取得
	* @return 行列配列を返す
	*/
	ld_float*  getArray()
	{
		return m ;
	}

	/**
	* @brief 行列を設定
	* @param *_m 行列配列をセットする
	*/
	void  setMatrix( const ld_float* _m );

	/**
	* @brief 行列を設定
	* @param &m2 EMatrix43をセットする
	*/
	void  setMatrix( const LDMatrix43& m2 ) ;

	//------ 行列の変換 -------
	/**
	* @brief 変換
	* @param x 行列の要素xをセットする
	* @param y 行列の要素yをセットする
	* @param z 行列の要素zをセットする
	*/
	void  translate( ld_float x , ld_float y , ld_float z );

	/**
	* @brief スケール変換
	* @param scaleX Xスケール変換係数をセットする
	* @param scaleY Yスケール変換係数をセットする
	* @param scaleZ Zスケール変換係数をセットする
	*/
	void  scale( ld_float scaleX , ld_float scaleY , ld_float scaleZ );

	/**
	* @brief X軸周りの回転を行う
	* @param theta 角度をセットする
	*/
	void  rotateX( ld_float theta );

	/**
	* @brief Y軸周りの回転を行う
	* @param theta 角度をセットする
	*/
	void  rotateY( ld_float theta );

	/**
	* @brief Z軸周りの回転を行う
	* @param theta 角度をセットする
	*/
	void  rotateZ( ld_float theta );

	//------ ベクトルの変換 -------
	/**
	* @brief 変換を行う
	* @param &p EVector3をセットする
	* @return 変換行列を返す
	*/
	LDVector3	transform( const LDVector3& p ) ;

	/**
	* @brief 変換を行う
	* @param &p EVector3をセットする
	* @param *dst 変換行列を受け取るポインタをセットする
	*/
	void		transform( const LDVector3& p , LDVector3* dst ) ;

	//------ 演算 -------
	/**
	* @brief 受け取った２つの行列の掛け算を行う(指定の行列 m2 を右から掛け、dstに設定する)
	* @param &b EMatrix43をセットする
	* @param *dst 変換行列を受け取るポインタをセットする
	*/
	void mult( const LDMatrix43& b , LDMatrix43* dst ) ;

	/**
	* @brief 安全な乗算. a , b と dst が同じでも良い安全な乗算(ld_float[16]を別に用意するため負荷大)
	* @param *a 行列aをセットする
	* @param *b 行列bをセットする
	* @param *dst 変換行列を受け取るポインタをセットする
	*/
	static void mult_safe( const ld_float* a , const ld_float* b , ld_float* dst ) ;

	/**
	* @brief 高速な乗算. a , b と dst が同じ場合は不正な計算になる
	* @param *a 行列aをセットする
	* @param *b 行列bをセットする
	* @param *dst 乗算した行列を受け取るポインタをセットする
	*/
	static void mult_fast( const ld_float* a , const ld_float* b , ld_float* dst ) ;

	//------ 設定 -------
	void  fromQuaterion( const LDQuat& q ) ;

	//------ デバッグ -------
	void dump43( ) ;	//4x4でダンプ
	void dump( ) ;		//配列としてダンプ

};

//========================================================
//	クラス外の関数
//========================================================
/**
* @brief EMatrix43 * EVector3f
* @param　&m EMatrix43をセットする
* @param &p EVector3をセットする
* @return EMatrix43 * EVector3fを返す
*/
LDVector3		operator  *( const LDMatrix43& m  , const LDVector3& p ) ;

/**
* @brief EMatrix43 * EMatrix43(コピーが発生するので、速度重視の場合は使わない)
* @param　&m EMatrix43をセットする
* @param &p EMatrix43をセットする
* @return EMatrix43 * EMatrix43を返す
*/
LDMatrix43		operator  *( const LDMatrix43& a , const LDMatrix43& b ) ;

LDMatrix43		operator *=( const LDMatrix43& a , const LDMatrix43& b ) ;

/**
* @brief 行列式
* @param　&m EMatrix43をセットする
* @return 行列式を返す
*/
ld_float			det( const LDMatrix43& m ) ;

/**
* @brief 逆行列
* @param &m EMatrix43をセットする
* @return 逆行列を返す
*/
LDMatrix43		inverse( const LDMatrix43& m ) ;

#if LD_CORE_ENABLE_QT
QDebug operator<<( QDebug dbg, const LDMatrix43& m );
#endif

} // namespace live2d

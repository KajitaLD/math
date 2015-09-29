/**
 * @brief The EMathUtil class
 *
 * cf. [3D Math Primer for Graphics and Game Development] (利用許諾コード)
 */

#pragma once

#include "common.h"
#include <math.h>
#include <QDebug>
#include "private/LDMath_private.h"

namespace live2d
{


class LDMathUtil
{
public:
	// PI
	const static ld_float	PI				; //!< @brief 3.14159265f
	const static ld_float	PI2				; //!< @brief EUC_PI * 2.0f ;
	const static ld_float	PI_OVER_2		; //!< @brief EUC_PI / 2.0f ;
	const static ld_float	ONE_OVER_PI		; //!< @brief 1.0f / EUC_PI ;
	const static ld_float	ONE_OVER_PI2	; //!< @brief 1.0f / EUC_2PI ;

	const static ld_float	TOLERANCE			; //!< @brief 通常計算時の許容誤差 ;
	const static ld_float	GINBAL_TOLERANCE	; //!< @brief ジンバルロック時の許容誤差 ;

public:

	/**
	* @brief 2PIの倍数を加える事で角度を -PI .. PI にラップする
	* @param theta 位相角[rad]をセットする
	* @return -PIからPIにラップした位相角[rad]を返す
	*/
	static ld_float	wrapPi( ld_float theta )
	{
		theta += PI ;
		theta -= floor( theta * ONE_OVER_PI2 ) * PI2 ;
		theta -= PI ;
		return theta ;
	}

	/**
	* @brief Q2からQ1への、角の変化量を取得する
	* @param Q1 位相角Q1[rad]をセットする
	* @param Q2 位相角Q2[rad]をセットする
	* @return Q2からQ1への、角の変化量[rad]を返す
	*/
	static ld_float getAngleDiff( ld_float Q1 , ld_float Q2 )
	{
		ld_float ret = Q1 - Q2 ;
		while ( ret < -PI )
		{
			ret += PI2 ;    //-180より小さければ、360度足す
		}
		while ( ret >  PI )
		{
			ret -= PI2 ;    //　180より大きければ、360度引く
		}
		return ret ;
	}

	/**
	* @brief 安全な逆三角関数。acos(x)と同じ。ただし、x が範囲外のとき、最も近い有効な値にクランプ処理される
	* @param x acos()に入力する数値
	* @return 　acos()の値（Cのacosと同様に 0..PI である）
	*/
	static ld_float	safeAcos( ld_float x )
	{
		if ( x <= -1.0f )
		{
			return PI ;
		}
		if ( x >=  1.0f )
		{
			return 0.0f ;
		}
		return acos( x ) ;
	}

	/**
	* @brief Sin Cos を一回で求める
	* @param returnSin sin(theta)の計算結果を受け取るポインタをセットする
	* @param returnCos cos(theta)の計算結果を受け取るポインタをセットする
	* @param theta 位相角[rad]をセットする
	*/
	static void sinCos( ld_float* returnSin , ld_float* returnCos , ld_float theta )
	{
		*returnSin = sin( theta ) ;
		*returnCos = cos( theta ) ;
	}

	//float4つを見やすく表示するための文字列を返す
	static QString format4args( ld_float a,ld_float b,ld_float c,ld_float d );

	//float3つを見やすく表示するための文字列を返す
	static QString format3args( ld_float a,ld_float b,ld_float c );



	static double crossProductValue(LDPoint pa,LDPoint pb,LDPoint pc){
		// 有向線分 (pa,pb), (pa,pc) の外積の z 成分を求める
		double n = pb.x() * (pa.y() - pc.y()) + pa.x() * (pc.y() - pb.y()) + pc.x()
				* (pb.y() - pa.y());

		return n;
	}

	static double crossProductValue(LDPoint pa,LDPoint pb){
		// pa と pb の外積の z 成分を求める
		double n=pa.x()*pb.y() - pa.y()*pb.x();

		return n;
	}

	/**
	 * v1からv2への反時計回りの角度 (0~2pi)
	 */
	static double getAngle(QVector2D v1 , QVector2D v2){
		double q1 = atan2( v1.y() , v1.x() ) ;
		double q2 = atan2( v2.y() , v2.x() ) ;
		double ret =  q2 - q1  ;//v2の角度からv1 の角度を引く

		if( ret < 0 ) ret += 2*PI ;//0より小さければ、360度足す
		return ret ;
	}

	static LDPoint rotatePoint(const LDPoint& origin,const LDPoint& pt,ld_float rad)
	{
		LDPoint tmp=pt-origin;
		float x=tmp.x()*cosf(rad)+tmp.y()*sinf(rad);
		float y=-tmp.x()*sinf(rad)+tmp.y()*cosf(rad);
		return LDPoint(x+origin.x(),y+origin.y());
	}
	static LDPoint scalePoint(const LDPoint& origin,const LDPoint& pt,ld_float scale)
	{
		LDPoint tmp=pt-origin;
		float x=tmp.x()*scale;
		float y=tmp.y()*scale;
		return LDPoint(x+origin.x(),y+origin.y());	
	}
	static LDPoint scalePoint(const LDPoint& origin,const LDPoint& pt,ld_float scale_x,ld_float scale_y)
	{
		LDPoint tmp=pt-origin;
		float x=tmp.x()*scale_x;
		float y=tmp.y()*scale_y;
		return LDPoint(x+origin.x(),y+origin.y());	
	}
	

	/**
	 * 2つの値の間を線形補間する
	 */
	template<typename T>
	static T lerp( T from, T to,float t )
	{
		T result = ( 1-t )*from + t*to;
//		if(result > -TOLERANCE && result < 0){
//			result= 0.0;
//		}
//		if(result-1.0 < TOLERANCE && result-1 > 0){
//			result = 1.0;
//		}
		return result;
	}
//	template<>
//	static LDPoint lerp(LDPoint from, LDPoint to,float t )
//	{
//		LDPoint result = ( 1-t )*from + t*to;
//		if(result.x() > -TOLERANCE && result.x() < 0){
//			result.setX(0.0);
//		}
//		if(result.y() > -TOLERANCE && result.y() < 0){
//			result.setY(0.0);
//		}
//		if(result.x()-1.0 < TOLERANCE && result.x()-1 > 0){
//			result.setX(1.0);
//		}
//		if(result.y()-1.0 < TOLERANCE && result.y()-1 > 0){
//			result.setY(1.0);
//		}
//		return result;
//	}

	template<typename T>
	static float inverseLerp( T from, T to,T value )
	{
        Q_ASSERT(!(from == to));
		return (value-from)/(to-from);
	}

	/**
	 * 4つの値の間を二次元線形補間する
	 */
	template<typename T>
	static T lerp2D( T from1, T to1,double t1,T from2, T to2,double t2 )
	{
		T tmp1 = ( 1-t1 )*from1 + t1*to1;
		T tmp2 = ( 1-t1 )*from2 + t1*to2;
		return ( 1-t2 )*tmp1 + t2*tmp2;
	}

	template<typename T>
	static bool inverseLerp2D( T from1, T to1,T from2, T to2,T value,double& t1,double& t2)
	{
//		参考 stackoverflow "Inverse Bilinear Interpolation?"
//		http://stackoverflow.com/questions/808441/inverse-bilinear-interpolation
//		p2 --- p3
//	     |      |
//	   t |  p   |
//	     |      |
//	     p0 --- p1
//	        s
//		A = (p0-p) X (p0-p2)
//		B = ( (p0-p) X (p1-p3) + (p1-p) X (p0-p2) ) / 2
//		C = (p1-p) X (p1-p3)
//		s = ( (A-B) +- sqrt(B^2 - A*C) ) / ( A - 2*B + C )

		double a= crossProductValue( from2-value,from2-from1);
		double b= (crossProductValue(from2-value,to2-to1)+crossProductValue(to2-value,from2-from1))/2;
		double c=crossProductValue(to2-value,to2-to1);

		double d=(a-2*b+c);

		if(d==0||fabs(d)<TOLERANCE)
		{
			Q_ASSERT(!fuzzyCompare( a,c,TOLERANCE));
			t1=a/(a-c);
//			qDebug()<<"d==0"<<t1;
		}
		else
		{
			t1=((a-b)+sqrt(b*b-a*c))/d;
			if(t1-1.0 > 0 && t1-1.0 < TOLERANCE)
			{
				t1 = 1.0;
			}
			if( -t1 > -TOLERANCE && t1 < 0)
			{
				t1 = 0;
			}
			double _t1=((a-b)-sqrt(b*b-a*c))/d;
			if(t1 > 1 || t1 < 0)
			{
				if(_t1 <= 1 && _t1 >= 0)
				{
					t1 = _t1;
				}else
				{
					return false;
					Q_ASSERT(false);
				}
			}
			//TODO: 結果がNanになるときがあるので、別の計算(見た目は少しずれるかも)に切り替える。そもそもNanになるのが怪しい動作。
//			if(isnan(t1))
//			{
//				t1=((a-b)-sqrt(b*b-a*c))/d;
				if(isnan(t1))
				{
                    Q_ASSERT(false);
					t1=a/(a-c);
					Q_ASSERT( ! isnan(t1) );
				}
//			}
//			qDebug()<<"d!=0"<<t1<<"or"<<((a-b)-sqrt(b*b-a*c))/d;
		}

//		t = ( (1-s)*(x0-x) + s*(x1-x) ) / ( (1-s)*(x0-x2) + s*(x1-x3) )
//		t2=((1-t1)*(from2.y()-value.y())+t1*(to2.y()-value.y())) / ((1-t1)*(from2.y()-from1.y())+t1*(to2.y()-to1.y()));
		LDPoint tmp1=((1-t1)*(from2-value)+t1*(to2-value)) ;//(1-s)*(x0-x) + s*(x1-x) )
		LDPoint tmp2=((1-t1)*(from2-from1)+t1*(to2-to1));//(1-s)*(x0-x2) + s*(x1-x3)

		if((tmp2.x()==0&&tmp2.y()==0))
		{
			return false;
		}


//		if(fabs(tmp1.x())<TOLERANCE)
//		{
//			tmp1.setX(0);
//		}
//		if(fabs(tmp1.y())<TOLERANCE)
//		{
//			tmp1.setY(0);
//		}
//		if(fabs(tmp2.x())<TOLERANCE)
//		{
//			tmp2.setX(0);
//		}
//		if(fabs(tmp2.y())<TOLERANCE)
//		{
//			tmp2.setY(0);
//		}
		if ((tmp2.y()!=0) || fuzzyCompare( tmp1.x() , 0.0,TOLERANCE) && value.x() > value.y()) {
			t2=tmp1.y()/tmp2.y();
		}
		else //if(tmp2.y()==0&&tmp2.x()!=0)
		{
			Q_ASSERT(tmp2.x()!=0);
			t2=tmp1.x()/tmp2.x();
		}
//		else
//		{
//			LDPoint tmp(tmp1.x()/tmp2.x(),tmp1.y()/tmp2.y());
//			t2=tmp.x()+tmp.y()/2;
////			t2=sqrt(tmp.x()*tmp.x()+tmp.y()*tmp.y());
//		}

		t2=1-t2;


//		if(fabs(t1-1)<TOLERANCE)
//		{
//			t1=1;
//		}
//		if(fabs(t2-1)<TOLERANCE)
//		{
//			t2=1;
//		}
//		if(fabs(t1)<TOLERANCE)
//		{
//			t1=0;
//		}
//		if(fabs(t2)<TOLERANCE)
//		{
//			t2=0;
//		}
		t1 = clamp(t1,0.0,1.0);
		t2 = clamp(t2,0.0,1.0);
		return true;
	}

	template<typename T>
	static T clamp(T value,T min,T max)
	{
		if(value<min)return min;
		if(value>max)return max;
		return value;
	}

	template<>
	static QPointF clamp<QPointF>(QPointF value,QPointF min,QPointF max)
	{
		return QPointF(
					clamp(value.x(),min.x(),max.x()),
					clamp(value.y(),min.y(),max.y()) );
	}

	template<typename T>
	static bool fuzzyCompare(T a,T b,float fuzz)
	{
		return fabs(a - b) <= fuzz;
	}

	template<>
	static bool fuzzyCompare<LDPointList>(LDPointList a,LDPointList b,float fuzz)
	{
		if(a.length()!=b.length())
		{
			return false;
		}
		for (int i = 0; i < a.length(); ++i)
		{
			fuzzyCompare<LDPoint>(a[i],b[i],fuzz);
//			if(fabs(a[i].x()-b[i].x())>fuzz)
//			{
//				return false;
//			}
//			if(fabs(a[i].y()-b[i].y())>fuzz)
//			{
//				return false;
//			}
		}
		return true;
	}
	template<>
	static bool fuzzyCompare<LDPoint>(LDPoint a,LDPoint b,float fuzz)
	{
		if(fabs(a.x()-b.x())>fuzz)
		{
			return false;
		}
		if(fabs(a.y()-b.y())>fuzz)
		{
			return false;
		}

		return true;
	}
private:
	/**
	* @brief コンストラクタ
	*/
	LDMathUtil() {}

};


} // namespace live2d

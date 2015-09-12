using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace live2d
{
    public class CurveUtil
    {
        public CurveUtil()
        { 

        }

        //2次ベジエ曲線上の点を求める。t=0:開始点 t=1:終了点
        public static LDPoint quadraticBezierPoint(
        LDPoint start,
		LDPoint control,
		LDPoint end,float t )
	{
        float t1 = (1 - t) * (1 - t);
        float t2 = 2 * t * (1 - t);
        float t3 = t * t;

		return t1* start
			   + t2* control
			   + t3* end;
    }

    //3次ベジエ曲線上の点を求める。t=0:開始点 t=1:終了点
    public static LDPoint cubicBezierPoint(
		LDPoint start,
		LDPoint control1,
		LDPoint control2,
		LDPoint end, float t)
    {
        float t1 = (1 - t) * (1 - t) * (1 - t);
        float t2 = 3 * t * (1 - t) * (1 - t);
        float t3 = 3 * t * t * (1 - t);
        float t4 = t * t * t;

        return t1 * start
               + t2 * control1
               + t3 * control2
               + t4 * end;
    }


    //エルミート曲線上の点を求める。t=0:開始点 t=1:終了点
    static LDPoint cubicHermitePoint(
			LDPoint start,
			LDPoint startVec,
			LDPoint end,
			LDPoint endVec,
            float t)
    {
        //		P(t) = at3 + bt2 + ct + d
        //		a = 2(P0 - P1) + m0 + m1
        //		b = -3(P0 - P1) - 2m0 - m1
        //		c = m0
        //		d = P0
        float t2 = t * t;
        float t3 = t * t * t;
        LDPoint a = 2 * (start - end) + startVec + endVec;
        LDPoint b = -3 * (start - end) - 2 * startVec - endVec;
        return a * t3 + b * t2 + startVec * t + start;
    }

}
}

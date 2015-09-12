using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public class LDUvMesh
    {
        public LDUvMesh() { }
        public void copyFrom(LDUvMesh src)
        {
            m_points = src.m_points;
            m_uvMap = src.m_uvMap;
            m_lines = src.m_lines;
            m_triangles = src.m_triangles;
        }
        public LDPoint getPoint(int index)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_points, index);

            return m_points[index];
        }
        public int getVertexCount()
        {
            return m_points.length();
        }
        public bool verify()
        {
            if (getVertexCount() < 3)
            {
                //三角形を満たしてない
                common.Warning("Invalid mesh! Too few points.");
                return false;
            }
            if (getVertexCount() - 2 > getTriangleCount())
            {
                //三角分割しきれてない。飛び地があるはず
                common.Warning("Invalid mesh! Too few triangles.");
                return false;
            }
            return true;
        }
        public void reset()
        {
            m_points.Clear();
            m_uvMap.Clear();
            m_lines.Clear();
            m_triangles.Clear();
        }
        public void dump(int nest = 0)
        {
            common.Debug(
            nest.ToString() + '\t'
            + "Mesh:"
            + " Vertices " + getVertexCount()
            + " Polygons " + getTriangleCount()
            + " Points:" + m_points);
        }
        public void dumpDetail(int nest = 0)
        {
            Debug.WriteLine(
             nest.ToString() + '\t'
            + "Mesh:"
            + " Vertices " + getVertexCount()
            + " Polygons " + getTriangleCount()
            );

            Debug.WriteLine(
                    (nest + 1).ToString() + '\t'
                    + "form:" + m_points.ToString());
            Debug.WriteLine(
                    (nest + 1).ToString() + '\t'
                    + "uvmap:" + m_uvMap.ToString());
            Debug.WriteLine(
                    (nest + 1).ToString() + '\t'
                    + "lines:" + m_lines.ToString());
            Debug.WriteLine(
                    (nest + 1).ToString() + '\t'
                    + "polygons:" + m_triangles.ToString());
        }
        public int getTriangleCount()
        {
            return m_triangles.length();
        }
        public LDPoint getUv(int index)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_uvMap, index);

            return m_uvMap[index];
        }
        public LDTriangle getTriangle(int index)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_triangles, index);

            return m_triangles[index];
        }
        public LDPointList getPointList()
        {
            return m_points;
        }
        public LDTriangleList getTriangles()
        {
            return m_triangles;
        }
        public LDUvMap getUvMap() { return m_uvMap; }
        public bool isHit(LDPoint pt)
        {
            LDPolygon polygon = m_triangles.getOutlinePolygon(m_points);
            //第二引数のFillRuleはQPainterPathのリファレンスがわかりやすい
            return polygon.containsPoint(pt, FillRule.WindingFill);
        }
        public void replacePoint(int index, LDPoint pt)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_points, index);

            m_points.replace(index, pt);
        }
        /// <summary>
        /// 未実装
        /// </summary>
        /// <param name="form"></param>
        public void replaceForm(LDPointList form)
        {
            throw new NotImplementedException();
        }

        public bool existsLine(LDIndexLine line)
        {
            return m_lines.Contains(line);
        } //既にある線かチェックする
        public int getLineCount()
        {
            return m_lines.length();
        }
        public LDIndexLine getLine(int index)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_lines, index);

            return m_lines[index];
        }
        public LDIndexLineList getLines()
        {
            return m_lines;
        }
        public void replaceUv(int index, LDPoint uv)
        {
            common.LD_ASSERT_OUT_OF_INDEX(m_uvMap, index);

            m_uvMap.replace(index, uv);
        }
        //追加。UV経由での追加しかできない。Positionは自動で計算される
        public void addUv(LDPoint uv, bool clamp = true)
        {
            if (clamp)
            {
                //0-1区間の縛りに引っかかる処理が多いので、デフォルトでは自動で直す
                uv = LDMathUtil.clamp(uv, new LDPoint(0, 0), new LDPoint(1, 1));
            }
            else
            {
                common.LD_ASSERT_OUT_OF_RANGE(uv.x(), 0, 1);
                common.LD_ASSERT_OUT_OF_RANGE(uv.y(), 0, 1);
            }


            m_uvMap.Add(uv);
            //頂点の計算
            m_points.Add(getCalcAddVertex(uv));
        }
        public void addUv(float u, float v, bool clamp = true)
        {
            addUv(new LDPoint(u, v), clamp);
        }
        public void insertUv(int index, LDPoint uv)
        {
            m_uvMap.Insert(index, uv);
            m_points.Insert(index, getCalcAddVertex(uv));
            //form.insert( index,p );

            updateLinesForPointInsert(index);
        }
        public bool removeUv(LDPoint uv)
        {
            int index = m_uvMap.IndexOf(uv);

            if (index < 0)
            {
                //一致なしなら何もしない
                return false;
            }

            deleteLine(index); //まずは線を消す
            m_points.RemoveAt(index); //頂点削除
            m_uvMap.RemoveAt(index); //uv削除
            //updateLinesForPointInsert(index);
            updateLinesForPointDeleted(index);

            return true;
        }
        public void addLine(LDIndexLine line)
        {
            if (!existsLine(line))
            {
                m_lines.Add(line);
            }
            else
            {
                common.Critical("exist line came ! check line before this method called");
            }
            m_lines.sort();
        }
        public void addLine(int index1, int index2)
        {
            addLine(new LDIndexLine(index1, index2));
        }
        public bool deleteLine(LDIndexLine line)
        {
            return m_lines.Remove(line);
        }
        public bool deleteLine(int vertexIndex)
        {
            /*
            auto it = m_lines.begin();
            bool deleted = false;
            while (it != m_lines.end())
            {
                LDIndexLine line = static_cast<LDIndexLine>(*it);

                if (line.hasIndex(vertexIndex))
                {
                    deleted = true;
                    it = m_lines.erase(it);
                }
                else
                {
                    it++;
                }
            }
            */
            bool deleted = false;
            for (int i = 0; i < this.m_lines.Count; i++)
            {
                deleted = this.m_lines[i].hasIndex(vertexIndex);
                if (deleted)
                {
                    this.m_lines.RemoveAt(i);
                }
            }
            common.Debug(m_lines.ToString());
            return deleted;
        }
        public void updateLinesForPointInsert(int pointIndex)
        {
            //頂点挿入によりずれたIndexを修正//もっと効率化できるはずだがもっさりしていたらやる
            for (int i = 0; i < m_lines.size(); i++)
            {
                int first = m_lines.at(i).getIndex1();
                int second = m_lines.at(i).getIndex2();
                if (first >= pointIndex)
                {
                    first += 1;
                }
                if (second >= pointIndex)
                {
                    second += 1;
                }
                m_lines.replace(i, new LDIndexLine(first, second));
            }
        } //NOTE： もっと分かりやすい名前にする
        public void updateLinesForPointDeleted(int pointIndex)
        {
            //頂点挿入によりずれたIndexを修正//もっと効率化できるはずだがもっさりしていたらやる
            for (int i = 0; i < m_lines.size(); i++)
            {
                int first = m_lines.at(i).getIndex1();
                int second = m_lines.at(i).getIndex2();
                if (first >= pointIndex)
                {
                    first -= 1;
                }
                if (second > pointIndex)
                {
                    second -= 1;
                }
                m_lines.replace(i, new LDIndexLine(first, second));
            }
        }
        public void updateUvMap(LDSize ImageSize)
        {
            m_uvMap.Clear();
            for (int i = 0; i < m_points.size(); i++)
            {
                float u = m_points[i].x() / ImageSize.width();
                float v = m_points[i].y() / ImageSize.height();

                LDMathUtil.clamp(u, 0.0f, 1.0f);
                LDMathUtil.clamp(v, 0.0f, 1.0f);

                m_uvMap.Add(new LDPoint(u, v));
            }
        }
        public void updateLines() { m_lines.sort(); }
        public void updatePolygons()
        {
            m_triangles.update(m_lines);
            m_triangles.setClockWise(m_points, ClockWise.CCW); //反時計回りに指定

        }
        public void triangulation()
        {
            m_triangles = math.Triangulation.exec(m_points);
            m_lines = m_triangles.toIndexLineList();
        }
        public void setLines(LDIndexLineList value)
        {
            m_lines = value;
        }
        public void setUvMap(LDUvMap value) { m_uvMap = value; }
        public void setTriangles(LDTriangleList value)
        {
            m_triangles = value;
        }
        public void replacePointList(LDPointList form)
        {
            Debug.Assert(m_points.length() == form.length());

            for (int i = 0; i < form.length(); ++i)
            {
                m_points.replace(i, form[i]);
            }
        }
        public static bool operator ==(LDUvMesh a, LDUvMesh b)
        {
            if (a.m_points != b.m_points)
            {
                return false;
            }

            if (a.m_uvMap != b.m_uvMap)
            {
                return false;
            }
            if (a.m_triangles != b.m_triangles)
            {
                return false;
            }

            return true;
        }
        public static bool operator !=(LDUvMesh a, LDUvMesh b)
        {
            return !(a == b);
        }

        private LDPoint getCalcAddVertex(LDPoint uv)
        {
            LDPoint calcAddVertex = new LDPoint(-1, -1); //とりあえず  -1,-1で初期化

            if (m_points.size() == 0) //最初の頂点がなければuvと同じ座標位置にformをする
            {
                calcAddVertex = new LDPoint(0, 0);
            }
            else if (m_points.size() == 1) //頂点数が一つだけならばその座標を原点としてuvと同じ比率の座標をformにする
            {
                LDPoint p0 = m_points.at(0);
                calcAddVertex = new LDPoint(p0.x() + uv.x(), p0.y() + uv.y());
            }
            //	else if ( m_points.size()==2 )// NOTE 計算あまり検証していない
            //	{
            //		//uvと頂点の縮尺を計算
            //		float scale_x=0;
            //		if ( ( m_uvMap[1].x()-m_uvMap[0].x() )==0 )
            //		{
            //			scale_x=1;
            //		}
            //		else
            //		{
            //			scale_x=( m_points[1].x()-m_points[0].x() )/( m_uvMap[1].x()-m_uvMap[0].x() );
            //		}

            //		float scale_y=0;
            //		if ( ( m_uvMap[1].y()-m_uvMap[0].y() )==0 )
            //		{
            //			scale_y=1;
            //		}
            //		else
            //		{
            //			scale_y=( m_points[1].y()-m_points[0].y() )/( m_uvMap[1].y()-m_uvMap[0].y() );
            //		}

            //		calcAddVertex =LDPoint( uv.x()*scale_x,uv.y()*scale_y ) ;
            //	}
            else if (m_points.size() >= 2)
            {
                LDPoint s0 = m_uvMap[0];
                LDPoint s1 = m_uvMap[1];
                LDPoint s2 = m_uvMap.Last();

                LDPoint t0 = m_points[0];
                LDPoint t1 = m_points[1];
                calcAddVertex = math.TriangleUtil.getSimilarityTrianglePoint(s0, s1, s2, t0, t1);
            }

            return calcAddVertex;
        }


        private LDPointList m_points;//UV上にマッピングされた点。
        private LDUvMap m_uvMap;

        private LDIndexLineList m_lines;
        private LDTriangleList m_triangles;

        //LD_SERIALIZABLE;
    }
}

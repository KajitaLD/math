using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace live2d
{
    public class LDGridTransform
    {
        public LDGridTransform(float x = 0, float y = 0, float width = 1, float height = 1, int row = 1, int col = 1)
        {
            Debug.Assert(width > 0);
            Debug.Assert(height > 0);
            Debug.Assert(row > 0);
            Debug.Assert(col > 0);

            m_originRect.setTopLeft(new LDPoint(x, y));
            m_originRect.setBottomRight(new LDPoint(x + width, y + height));
            for (int i = 0; i < row + 1; ++i)
            {
                m_gridPoints.Add(new List<LDPoint>());
                for (int j = 0; j < col + 1; ++j)
                {
                    m_gridPoints[i].Add(new LDPoint(x + width / col * j, y + height / row * i));
                }
            }

            clearBoundsCache();
        }

        public LDGridTransform(LDPoint topLeft, LDPoint bottomRight, int row = 1, int col = 1)
            : this(topLeft.x(), topLeft.y(), bottomRight.x() - topLeft.x(), bottomRight.y() - topLeft.y(), row, col)
        {

        }

        //時計回りに4点
        public LDGridTransform(LDPoint topLeft, LDPoint topRight, LDPoint bottomRight, LDPoint bottomLeft, int row = 1, int col = 1)
        {
            m_originRect = math.PointUtil.getBoundingRect(new LDPointList { topLeft, topRight, bottomLeft, bottomRight });

            LDQuadTransform quad = new LDQuadTransform(topLeft, topRight, bottomRight, bottomLeft);

            for (int i = 0; i < row + 1; ++i)
            {
                m_gridPoints.Add(new List<LDPoint>());
                for (int j = 0; j < col + 1; ++j)
                {
                    m_gridPoints[i].Add(quad.transform((float)j / col, (float)i / row));
                }
            }

            clearBoundsCache();
        }

        public int getRow()
        {
            return m_gridPoints.Count - 1;
        }
        public int getColumn()
        {
            if (m_gridPoints.Count == 0)
            {
                return 0;
            }
            return m_gridPoints[0].Count - 1;
        }

        //配列の頂点の長さ。row+1
        public int getRowArrayLength()
        {
            return m_gridPoints.Count;
        }
        public int getColumnArrayLength()
        {
            if (m_gridPoints.Count == 0)
            {
                return 0;
            }
            return m_gridPoints[0].Count;
        }

        //平面上の点を変換した結果を返す。pは基本0..1の範囲
        /// <summary>
        /// TODO:LDPoint注意
        /// </summary>
        /// <param name="t"></param>
        /// <param name="clip"></param>
        /// <returns></returns>
        public LDPoint transform(LDPoint t, bool clip = false)
        {
            if (getColumn() == 0 && getRow() == 0)
            {
                //メッシュがない場合はそのままの値を返す
                return t;
            }

            double tx = t.x();
            double ty = t.y();

            if (clip)
            {
                //Grid内にClipする。QuadをClipして変換するのではない
                tx = LDMathUtil.clamp(tx, 0.0, 1.0);
                ty = LDMathUtil.clamp(ty, 0.0, 1.0);
            }

            //Gridから対象のQuadを見つける
            LDPoint index = getQuadIndex(new LDPoint((float)tx, (float)ty));
            int col = (int)index.x();
            int row = (int)index.y();

            LDPoint local = getLocalPoint(new LDPoint((float)tx, (float)ty));

            if (isOutside(row, col))
            {
                LDQuadTransform quad = createOutsideQuadTransform(row, col);
                return quad.transform(new LDPoint((float)tx, (float)ty));
            }
            else
            {
                LDQuadTransform quad = getQuadTransform(row, col);
                return quad.transform(local);
            }
        }
        public LDPointList transform(LDPointList points, bool clip = false)
        {
            LDPointList result=new LDPointList();
            int length = points.length();

            for (int i = 0; i < length; i++)
            {
                result.Add(transform(points[i], clip));
            }
            return result;
        }

        /// <summary>
        /// TODO: LDPoint注意
        /// </summary>
        /// <param name="pt"></param>
        /// <param name="clip"></param>
        /// <returns></returns>
        public LDPoint inverseTransform(LDPoint pt, bool clip = false)
        {
            if (getColumn() == 0 && getRow() == 0)
            {
                //メッシュがない場合はそのままの値を返す
                return pt;
            }

            double x = pt.x();
            double y = pt.y();


            //Gridからマッピング先のQuadを見つける
            LDPoint index = getMapedQuadIndex(new LDPoint((float)x, (float)y));
            int col = (int)index.x();
            int row = (int)index.y();

            if (clip)
            {
                //Grid内にClipする。QuadをClipして変換するのではない
                col = LDMathUtil.clamp(col, 0, getColumn());
                row = LDMathUtil.clamp(row, 0, getRow());
            }

            LDPoint local = new LDPoint();

            if (isOutside(row, col))
            {
                LDQuadTransform quad = createOutsideQuadTransform(row, col);
                return quad.inverseTransform(pt, clip);

                //TODO:到達しない場所あります
                local = quad.inverseTransform(pt, clip);

                LDPoint _internal;
                _internal.setX((col + 1) * (1.0f / (getColumn() + 2)) + local.x() / (getColumn() + 2));
                _internal.setY((row + 1) * (1.0f / (getRow() + 2)) + local.y() / (getRow() + 2));

                LDQuadTransform tmp = new LDQuadTransform(new LDPoint(-1, -1), new LDPoint(getColumn() + 1, getRow() + 1));
                return tmp.transform(_internal);
            }
            else
            {
                LDQuadTransform quad = getQuadTransform(row, col);
                local = quad.inverseTransform(pt, clip);

                LDPoint _internal = new LDPoint();
                _internal.setX(col * (1.0f / getColumn()) + local.x() / getColumn());
                _internal.setY(row * (1.0f / getRow()) + local.y() / getRow());

                return _internal;
            }



        }
        public LDPointList inverseTransform(LDPointList points, bool clip = false)
        {
            LDPointList result = new LDPointList();
            int length = points.length();

            for (int i = 0; i < length; i++)
            {
                result.Add(inverseTransform(points[i], clip));
            }
            return result;
        }

        //Grid自体を変換した結果を返す。基本0..1の範囲
        public LDGridTransform transform(LDGridTransform grid, bool clip = false)
        {
            LDGridTransform result = grid;

            for (int i = 0; i < grid.getRow() + 1; i++)
            {
                for (int j = 0; j < grid.getColumn() + 1; ++j)
                {
                    LDPoint newPt = transform(grid.getPoint(i, j), clip);
                    result.setPoint(i, j, newPt);
                }
            }

            return result;
        }

        //Affine変換を変換した結果を返す
        public LDAffineTransform transform(LDAffineTransform affine, bool clip = false)
        {
            LDAffineTransform result = affine;

            //Cubismと違い位置しか移動しない
            result.setToTranslate(transform(affine.getTranslate(), clip));


            return result;
        }



        //最左の列からの内分率。2分割で内分率0.6であれば、結果は0.1
        public double getRateXFromLeftCol(double rate)
        {
            Debug.Assert(rate >= 0);
            Debug.Assert(rate <= 1);

            if (rate == 0)
            {
                return 0;
            }
            if (rate == 1)
            {
                return 1;
            }

            double scaled = rate * getColumn();

            //小数部を求める
            return scaled % 1.0;
        }

        public double getRateYFromAboveRow(double rate)
        {
            Debug.Assert(rate >= 0);
            Debug.Assert(rate <= 1);

            if (rate == 0)
            {
                return 0;
            }
            if (rate == 1)
            {
                return 1;
            }

            double scaled = rate * getColumn();

            //小数部を求める
            return scaled % 1.0;
        }
        public int getIncludingColumnNo(double rate)
        {
            Debug.Assert(rate >= 0);
            Debug.Assert(rate <= 1);

            if (rate == 1)
            {
                return getColumn() - 1;
            }
            return (int)Math.Truncate(rate * getColumn());
        }
        public int getIncludingRowNo(double rate)
        {
            Debug.Assert(rate >= 0);
            Debug.Assert(rate <= 1);

            if (rate == 1)
            {
                return getRow() - 1;
            }
            return (int)Math.Truncate(rate * getColumn());
        }

        public LDPoint getQuadIndex(LDPoint t)
        {
            double tx = t.x();
            double ty = t.y();

            //	Debug.Assert( tx>=0 );
            //	Debug.Assert( tx<=1 );
            //	Debug.Assert( ty>=0 );
            //	Debug.Assert( ty<=1 );

            int row, col;
            if (tx == 1)
            {
                col = getColumn() - 1;
            }
            else
            {
                col = (int)Math.Truncate(tx * getColumn());
            }

            if (ty == 1)
            {
                row = getRow() - 1;
            }
            else
            {
                row = (int)Math.Truncate(ty * getRow());
            }


            return new LDPoint(col, row);
        }
        //Gridの内分率からQuadのローカルな内分率を取得する
        public LDPoint getLocalPoint(LDPoint t)
        {
            double tx = t.x();
            double ty = t.y();

            LDPoint localT = new LDPoint();
            if (tx == 0)
            {
                localT.setX(0);
            }
            else if (tx == 1)
            {
                localT.setX(1);
            }
            else
            {
                double scaled = tx * getColumn();
                //小数部を求める
                localT.setX((float)scaled - (int)Math.Truncate(scaled));
            }


            if (ty == 0)
            {
                localT.setY(0);
            }
            else if (ty == 1)
            {
                localT.setY(1);
            }
            else
            {
                double scaled = ty * getRow();
                //小数部を求める
                localT.setY((float)scaled - (int)Math.Truncate(scaled));
            }

            return localT;
        }

        //	LDPoint getMappingFrom( int row,int col, LDPoint map );
        public LDPoint getMapedQuadIndex(LDPoint map)
        {
            //TODO 最適化可能
            for (int row = 0; row < getRow(); ++row)
            {
                for (int col = 0; col < getColumn(); ++col)
                {
                    var quad = getQuadTransform(row, col);
                    if (quad.contains(map))
                    {
                        return new LDPoint(col, row);
                    }
                }
            }

            //範囲外を検索する。
            //TODO 保険として範囲が広すぎるときはAssert。キャンバスのサイズでどうにか最大値を求めるべき
            //TODO あまりに無駄が多い
            var extended = createExtendedGrid();
            LDPoint pt = extended.getMapedQuadIndex(map);
            return new LDPoint(pt.x() - 1, pt.y() - 1);
        }

        public bool isOutside(int row, int col)
        {
            return row < 0 || row >= getRow() || col < 0 || col >= getColumn();
        }

        public LDQuadTransform getQuadTransform(int row, int col)
        {
            if (isOutside(row, col))
            {
                Debug.WriteLine("xxx");
            }
            Debug.Assert(!isOutside(row, col));

            LDQuadTransform quad = new LDQuadTransform(
                getPoint(row, col),
                getPoint(row, col + 1),
                getPoint(row + 1, col + 1),
                getPoint(row + 1, col));

            return quad;
        }

        public LDQuadTransform createOutsideQuadTransform(int row, int col)
        {
            return getOutlineQuadTransform();
        }
        public LDQuadTransform getOutlineQuadTransform()
        {
            int rightIndex = getColumn();
            int bottomIndex = getRow();
            LDQuadTransform quad = new LDQuadTransform(
                getPoint(0, 0),
                getPoint(0, rightIndex),
                getPoint(bottomIndex, rightIndex),
                getPoint(bottomIndex, 0));
            return quad;
        }

        //格子番号から正規化された点を取得
        public LDPoint getNormalizedPoint(int row, int col)
        {
            LDPoint p=new LDPoint();
            p.setX(1.0f / getColumn() * row);
            p.setY(1.0f / getRow() * col);
            return p;
        }

        //格子番号からマッピングされた点を取得
        public LDPoint getPoint(int row, int col)
        {
            Debug.Assert(m_gridPoints.Count > row);
            Debug.Assert(m_gridPoints[0].Count > col);
            return m_gridPoints[row][col];
        }


        public LDPoint getPoint(int index)
        {
            int row = index / (getColumn() + 1);
            int col = index % (getColumn() + 1);
            return getPoint(row, col);
        }
        public int getPointIndex(int row, int col)
        {
            Debug.Assert(m_gridPoints.Count > row);
            Debug.Assert(m_gridPoints[0].Count > col);
            return row * (getColumn() + 1) + col;
        }

        public LDLine getLine(LDIndexLine line)
        {
            return new LDLine(getPoint(line.getIndex1()), getPoint(line.getIndex2()));
        }
        public LDIndexLine getIndexLine(int row1, int col1, int row2, int col2)
        {
            return new LDIndexLine(getPointIndex(row1, col1), getPointIndex(row2, col2));
        }


        public List<List<LDPoint>> getGridPoints()
        {
            return m_gridPoints;
        }
        public void setGridPoints(List<List<LDPoint>> value)
        {
            m_gridPoints = value;

            m_cacheBounds.setSize(new LDSize(0, 0));
        }

        //四角形の状態を保っているか。保っているなら自由に分割可能である。
        public bool isRectangle()
        {
            //TODO 回転の考慮なし
            for (int i = 0; i < getColumn() + 1; ++i)
            {
                if (getPoint(0, i).y() != m_originRect.y())
                {
                    return false;
                }
            }
            for (int i = 0; i < getColumn() + 1; ++i)
            {
                if (getPoint(getRow(), i).y() != m_originRect.bottom())
                {
                    return false;
                }
            }
            for (int i = 0; i < getRow() + 1; ++i)
            {
                if (getPoint(i, 0).x() != m_originRect.left())
                {
                    return false;
                }
            }
            for (int i = 0; i < getRow() + 1; ++i)
            {
                if (getPoint(i, getColumn()).x() != m_originRect.right())
                {
                    return false;
                }
            }
            return true;
        }

        public void setDivide(int row, int col)
        {
            //矩形でない場合は変形情報を失うため、変更不可。工夫次第である程度対応できるが現状未対応
            Debug.Assert(isRectangle());

            float x = m_originRect.x();
            float y = m_originRect.y();
            float width = m_originRect.width();
            float height = m_originRect.height();

            m_gridPoints.Clear();

            for (int i = 0; i < row + 1; ++i)
            {
                m_gridPoints.Add(new List<LDPoint>());
                for (int j = 0; j < col + 1; ++j)
                {
                    m_gridPoints[i].Add(new LDPoint(x + width / col * j, y + height / row * i));
                }
            }
        }
        public void setPoint(int row, int col, LDPoint pt)
        {
            Debug.Assert(m_gridPoints.Count != 0);
            common.LD_ASSERT_OUT_OF_INDEX(m_gridPoints, row);
            common.LD_ASSERT_OUT_OF_INDEX(m_gridPoints[0], col);
            m_gridPoints[row][col] = pt;

            clearBoundsCache();
        }
        public void setPointX(int row, int col, float x)
        {
            var pt = getPoint(row, col);
            pt.setX(x);
            setPoint(row, col, pt);
        }
        public void setPointY(int row, int col, float y)
        {
            var pt = getPoint(row, col);
            pt.setY(y);
            setPoint(row, col, pt);
        }

        public LDPointList toForm()
        {
            LDPointList result = new LDPointList();
            for (int i = 0; i < getRow() + 1; ++i)
            {
                for (int j = 0; j < getColumn() + 1; ++j)
                {
                    result.Add(m_gridPoints[i][j]);
                }
            }
            return result;
        }

        public void setForm(LDPointList value)
        {
            Debug.Assert(getPointCount() == value.length());
            for (int i = 0; i < getRow() + 1; ++i)
            {
                for (int j = 0; j < getColumn() + 1; ++j)
                {
                    m_gridPoints[i][j] = value[i * (getColumn() + 1) + j];
                }
            }

            clearBoundsCache();
        }

        public int getPointCount()
        {
            return (getRow() + 1) * (getColumn() + 1);
        }

        //外周の頂点インデックスを取得。(row,col)(0,0)が一番小さい点から時計周りで取得。
        public List<int> getOutlinePointIndices()
        {
            List<int> result = new List<int>();

            for (int i = 0; i < getColumn() + 1; ++i)
            {
                result.Add(getPointIndex(0, i));
            }
            for (int i = 1; i < getRow() + 1; ++i)
            {
                result.Add(getPointIndex(i, getColumn()));
            }
            for (int i = getColumn() - 1; i >= 0; --i)
            {
                result.Add(getPointIndex(getRow(), i));
            }
            for (int i = getRow() - 1; i >= 1; --i)
            {
                result.Add(getPointIndex(i, 0));
            }

            return result;
        }
        public LDIndexLineList getIndexOutline()
        {
            LDIndexLineList result = new LDIndexLineList(getOutlinePointIndices());
            return result;
        }
        public LDLineList getOutline()
        {
            return getIndexOutline().getLines(toForm());
        }
        public LDPointList getOutlinePoints()
        {
            List<int> indices = getOutlinePointIndices();

            LDPointList result = new LDPointList();

            foreach (var index in indices)
            {
                result.Add(getPoint(index));
            }
            return result;
        }
        public LDPolygon getOutlinePolygon()
        {
            List<int> indices = getOutlinePointIndices();

            LDPolygon result = new LDPolygon();

            foreach (var index in indices)
            {
                result.Add(getPoint(index));
            }
            return result;
        }

        public List<int> getInnerLinePointIndices()
        {
            List<int> result=new List<int>();

            for (int row = 0; row < getRowArrayLength(); ++row)
            {
                if (row == 0 || row + 1 == getRowArrayLength())
                {
                    continue;
                }
                for (int col = 0; col < getColumnArrayLength(); ++col)
                {
                    if (col == 0 || col + 1 == getColumnArrayLength())
                    {
                        continue;
                    }
                    result.Add(getPointIndex(row, col));
                }
            }

            return result;
        }
        public LDIndexLineList getInnerIndexLines()
        {
            LDIndexLineList result=new LDIndexLineList();

            for (int row = 0; row < getRowArrayLength(); ++row)
            {
                if (row == 0 || row + 1 == getRowArrayLength())
                {
                    continue;
                }
                for (int col = 0; col < getColumnArrayLength(); ++col)
                {
                    if (col == 0 || col + 1 == getColumnArrayLength())
                    {
                        continue;
                    }
                    //その点から左と上
                    result.Add(getIndexLine(row, col - 1, row, col));
                    result.Add(getIndexLine(row - 1, col, row, col));

                    if (row + 2 == getRowArrayLength())
                    {
                        //最後だけ下も追加
                        result.Add(new LDIndexLine(getPointIndex(row, col), getPointIndex(row + 1, col)));
                    }

                    if (col + 2 == getColumnArrayLength())
                    {
                        //最後だけ右も追加
                        result.Add(new LDIndexLine(getPointIndex(row, col), getPointIndex(row, col + 1)));
                    }
                }
            }

            return result;
        }
        public LDLineList getInnerLines()
        {
            LDIndexLineList lines = getInnerIndexLines();

            LDLineList result=new LDLineList();

            foreach (var line in lines )
	{
                result.Add(getLine(line));
            }
            return result;
        }


        //外周の周辺で判定
        public bool isHitOutline(LDPoint pt, float hitRange)
        {
            if (!isPreHit(pt, hitRange))
            {
                return false;
            }
            LDIndexLineList outline = getIndexOutline();

            return outline.isHit(toForm(), pt, hitRange);
        }


        public LDRect getBounds()
        {
            if (m_cacheBounds.size() == new LDSize(0, 0))
            {
                //TODO const関数内でのmutableの変更はスレッドセーフにしないといけない?
                m_cacheBounds = math.PointUtil.getBoundingRect(toForm());
            }

            return m_cacheBounds;
        }

        //矩形に含まれるかどうかの軽量な簡易当たり判定
        public bool isPreHit(LDPoint pt, float hitRange = 0)
        {
            LDRect rect = getBounds();

            //上下左右を拡張
            rect.adjust(-hitRange, -hitRange, hitRange, hitRange);

            return rect.contains(pt);
        }

        public LDGridTransform createExtendedGrid(int extend = 1)
        {
            LDRect bounds = getBounds();
            LDGridTransform grid = new LDGridTransform(
                getPoint(0, 0).x() - bounds.width(),
                getPoint(0, 0).y() - bounds.height(),
                bounds.width() + bounds.width() * 2,
                bounds.height() + bounds.height() * 2,
                getRow() + 1, getColumn() + 1
                );

            grid.copyFrom(this, 1, 1);
            return grid;
        }

        public void copyFrom(LDGridTransform src)
        {
            m_gridPoints = src.m_gridPoints;
            m_originRect = src.m_originRect;
        }
        //指定位置からのコピー
        public void copyFrom(LDGridTransform src, int row, int col)
        {
            for (int i = row; i < getRow() + 1; ++i)
            {
                if (src.getRow() < i)
                {
                    continue;
                }
                for (int j = col; j < getColumn() + 1; ++j)
                {
                    if (src.getColumn() < j)
                    {
                        continue;
                    }
                    setPoint(j, i, src.getPoint(j - col, i - row));
                }
            }
        }

        private void clearBoundsCache()
        {
            m_cacheBounds.setSize(new LDSize(0, 0));
        }

        private List<List<LDPoint>> m_gridPoints;
        private LDRect m_originRect;

        //当たり判定最適化のため、編集のない間は矩形を使いまわす
        private LDRect m_cacheBounds;

        public static bool operator ==(LDGridTransform a, LDGridTransform b)
        {
            return a.getGridPoints() == b.getGridPoints();
        }
        public static bool operator !=(LDGridTransform a, LDGridTransform b)
        {
            return a.getGridPoints() != b.getGridPoints();
        }

        //LD_SERIALIZABLE;
    };

    //QDebug operator <<(QDebug dbg,  LDGridTransform grid );


}

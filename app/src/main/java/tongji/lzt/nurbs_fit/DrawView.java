package tongji.lzt.nurbs_fit;


import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.RectF;
import android.graphics.Shader;
import android.util.AttributeSet;
import android.view.View;

import java.util.jar.Attributes;

public class DrawView extends View {

    static public float[] fitPoints;
    static public float[] oriPoints;
    public DrawView(Context context) {
        super(context);
    }

    public DrawView(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        /*
         * 方法 说明 drawRect 绘制矩形 drawCircle 绘制圆形 drawOval 绘制椭圆 drawPath 绘制任意多边形
         * drawLine 绘制直线 drawPoin 绘制点
         */
        // 创建画笔
        Paint mPaint = new Paint();
        mPaint.setColor(Color.BLUE);
        mPaint.setAntiAlias(true);
        mPaint.setStrokeWidth(10);

        //画点
        if(fitPoints!=null){
            canvas.drawPoints(fitPoints,mPaint);
        }
        mPaint.setColor(Color.RED);
        mPaint.setStrokeWidth(20);
        //画点
        if(oriPoints!=null){
            canvas.drawPoints(oriPoints,mPaint);
        }
    }
}

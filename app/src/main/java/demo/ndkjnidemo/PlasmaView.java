package demo.ndkjnidemo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

/**
 * Created by wuchunhui on 16-5-30.
 */
public class PlasmaView extends View implements View.OnTouchListener{
    private Bitmap mBitmap;
    long time;
    long fps;

    public PlasmaView(Context context) {
        super(context);
        Bitmap bmp = BitmapFactory.decodeResource(this.getResources(),R.drawable.bg);
        mBitmap = Bitmap.createBitmap(bmp.getWidth(), bmp.getHeight(), Bitmap.Config.RGB_565);
        JniUtils.setBitmap(bmp);
        this.setOnTouchListener(this);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        long ct = System.currentTimeMillis();
        if(ct - time > 1000){
            Log.i("wch Fps: = ", String.valueOf(fps));
            time = ct;
            fps = 0;
        }
        //fps++;
        fps += 20;

        JniUtils.render(mBitmap);
        canvas.drawBitmap(mBitmap, 0, 0, null);
        postInvalidate();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        // TODO Auto-generated method stub
        JniUtils.drop((int)event.getX(), (int)event.getY(), 1200);
        return false;
    }
}

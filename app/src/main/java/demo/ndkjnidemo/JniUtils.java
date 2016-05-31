package demo.ndkjnidemo;

import android.graphics.Bitmap;

/**
 * Created by wuchunhui on 16-5-3.
 */
public class JniUtils {
    static {
        System.loadLibrary("NdkJniDemo");//之前在build.gradle里面设置的so名字，必须一致
         }
    public static native String getStringFormC();
    public static native void setBitmap(Bitmap src);
    public static native void render(Bitmap dst);
    public static native void drop(int x, int y, int height);
    public static native int processBitmap(Bitmap bitmap);
}

package com.xgn;

import android.graphics.Bitmap;

/**
 * Created by mark on 17-12-12.
 */

public class ImageUtil {

    static {
        System.loadLibrary("imageproc");
    }

    public static native int compressBitmap(Bitmap bitmap, int w, int h, int quality, String outputFile, boolean optimize);
}

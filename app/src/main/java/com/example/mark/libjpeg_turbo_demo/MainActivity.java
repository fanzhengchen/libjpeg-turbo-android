package com.example.mark.libjpeg_turbo_demo;

import android.Manifest;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Environment;
import android.support.v4.app.ActivityCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.ImageView;
import android.widget.TextView;

import com.xgn.ImageUtil;

import java.io.File;
import java.io.FileOutputStream;

public class MainActivity extends AppCompatActivity {


    private ImageView imageView;
    private ImageView javaImageView;
    private ImageView nativeImageView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 200);

        // Example of a call to a native method
        imageView = (ImageView) findViewById(R.id.image_view_origin);
        javaImageView = (ImageView) findViewById(R.id.image_view_java);
        nativeImageView = (ImageView) findViewById(R.id.image_view_native);

        imageView.setImageResource(R.drawable.timg);

        int quality = 20;

        javaCompress(quality);
        libjpegCompress(quality);
        libjpegCompress(quality);

//        bitmap.recycle();
//        bitmap2.recycle();
    }

    private void javaCompress(int quality) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.timg);
        try {
            String outputFile = Environment.getExternalStorageDirectory().getCanonicalPath() + File.separator + "abcJava.jpg";
            long x = System.currentTimeMillis();
            FileOutputStream outputStream = new FileOutputStream(new File(outputFile));
            bitmap.compress(Bitmap.CompressFormat.JPEG, quality, outputStream);

            long y = System.currentTimeMillis();
            System.out.println("java cost: " + (y - x));

            Bitmap src = BitmapFactory.decodeFile(outputFile);
            javaImageView.setImageBitmap(src);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void libjpegCompress(int quality) {
        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.timg);
        try {
            String outputFile = Environment.getExternalStorageDirectory().getCanonicalPath() + File.separator + "abc.jpg";
//            int result = ImageUtil.compressBitmap(bitmap, quality, outputFile, optimize);
            long x = System.currentTimeMillis();
            int result = ImageUtil.compressBitmap(bitmap, quality, outputFile, true);
            long y = System.currentTimeMillis();
            System.out.println("native cost: " + (y - x));
            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inSampleSize = 4;
            Bitmap bitmap2 = BitmapFactory.decodeFile(outputFile, options);
            nativeImageView.setImageBitmap(bitmap2);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}

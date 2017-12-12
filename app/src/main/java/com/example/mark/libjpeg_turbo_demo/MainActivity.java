package com.example.mark.libjpeg_turbo_demo;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.xgn.ImageUtil;

import java.io.File;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);

        Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.testorig);

        int width = bitmap.getWidth();
        int height = bitmap.getHeight();
        int quality = 40;
        boolean optimize = true;
        String outputFile = getFilesDir().getAbsolutePath() + File.separator + "abc.jpg";
        int result = ImageUtil.compressBitmap(bitmap, width, height, quality, outputFile, optimize);
        System.out.println("fuck " + result);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}

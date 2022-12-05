package com.cookandroid.termproject;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.MediaController;
import android.widget.TextView;
import android.widget.VideoView;

public class video1Activity extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.video1);

        Intent intent=getIntent();
        String Receive1=intent.getStringExtra("nw1series");
        TextView textView=(TextView)findViewById(R.id.txtitlenw1);
        textView.setText(Receive1);

        Button btnbacknw1=(Button)findViewById(R.id.btnbacknw1);

        btnbacknw1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        VideoView video=(VideoView)findViewById(R.id.video1);
        MediaController mc=new MediaController(this);
        Uri uri= Uri.parse("android.resource://"+getPackageName()+"/"+R.raw.sss1);

        video.setMediaController(mc);
        video.setVideoURI(uri);
        video.start();
    }
}

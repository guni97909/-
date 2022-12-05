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

public class videoActivity5 extends Activity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.video5);

        Intent intent=getIntent();
        String Receive1=intent.getStringExtra("nw5series");
        TextView textView=(TextView)findViewById(R.id.txtitlenw5);
        textView.setText(Receive1);

        Button btnbacknw5=(Button)findViewById(R.id.btnbacknw5);

        btnbacknw5.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
            }
        });

        VideoView video=(VideoView)findViewById(R.id.video5);
        MediaController mc=new MediaController(this);
        Uri uri= Uri.parse("android.resource://"+getPackageName()+"/"+R.raw.ss5);

        video.setMediaController(mc);
        video.setVideoURI(uri);
        video.start();
    }
}
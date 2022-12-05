package com.cookandroid.termproject;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.View;
import android.content.Intent;
import android.widget.ImageButton;
import android.view.MenuItem;
import android.widget.LinearLayout;


public class MainActivity extends AppCompatActivity {
    LinearLayout baseLayout;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setIcon(R.drawable.netflix);
        baseLayout=(LinearLayout)findViewById(R.id.baseLayout);

        ImageButton kr1imagebutton = (ImageButton) findViewById(R.id.kr1image);

        kr1imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        kr1Activity.class);
                intent.putExtra("kr1series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton kr2imagebutton = (ImageButton) findViewById(R.id.kr2image);

        kr2imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        kr2Activity.class);
                intent.putExtra("kr2series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton kr3imagebutton = (ImageButton) findViewById(R.id.kr3image);

        kr3imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        kr3Activity.class);
                intent.putExtra("kr3series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton kr4imagebutton = (ImageButton) findViewById(R.id.kr4image);

        kr4imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        kr4Activity.class);
                intent.putExtra("kr4series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton kr5imagebutton = (ImageButton) findViewById(R.id.kr5image);

        kr5imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        kr5Activity.class);
                intent.putExtra("kr5series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton fr1imagebutton = (ImageButton) findViewById(R.id.fr1image);

        fr1imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        Fr1Activity.class);
                intent.putExtra("fr1series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton fr2imagebutton = (ImageButton) findViewById(R.id.fr2image);

        fr2imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        Fr2Activity.class);
                intent.putExtra("fr2series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton fr3imagebutton = (ImageButton) findViewById(R.id.fr3image);

        fr3imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        Fr3Activity.class);
                intent.putExtra("fr3series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton fr4imagebutton = (ImageButton) findViewById(R.id.fr4image);

        fr4imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        Fr4Activity.class);
                intent.putExtra("fr4series","장르 : 드라마");
                startActivity(intent);
            }
        });

        ImageButton fr5imagebutton = (ImageButton) findViewById(R.id.fr5image);

        fr5imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        Fr5Activity.class);
                intent.putExtra("fr5series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton nw1imagebutton = (ImageButton) findViewById(R.id.nw1image);

        nw1imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        video1Activity.class);
                intent.putExtra("nw1series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton nw2imagebutton = (ImageButton) findViewById(R.id.nw2image);

        nw2imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        video2Activity.class);
                intent.putExtra("nw2series","장르 : 예능");
                startActivity(intent);
            }
        });

        ImageButton nw3imagebutton = (ImageButton) findViewById(R.id.nw3image);

        nw3imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        video3Activity.class);
                intent.putExtra("nw3series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton nw4imagebutton = (ImageButton) findViewById(R.id.nw4image);

        nw4imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        videoActivity4.class);
                intent.putExtra("nw4series","장르 : 영화");
                startActivity(intent);
            }
        });

        ImageButton nw5imagebutton = (ImageButton) findViewById(R.id.nw5image);

        nw5imagebutton.setOnClickListener(new View.OnClickListener()
        {
            public void onClick (View v){
                Intent intent = new Intent(getApplicationContext(),
                        videoActivity5.class);
                intent.putExtra("nw5series","장르 : 영화");
                startActivity(intent);
            }
        });

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        super.onCreateOptionsMenu(menu);
        MenuInflater mInflater=getMenuInflater();
        mInflater.inflate(R.menu.menu1,menu);
        return true;
    }
    @Override public boolean onOptionsItemSelected( MenuItem item) {
        switch (item.getItemId()){
            case R.id.itemWhite:
                baseLayout.setBackgroundColor(Color.WHITE);
                return true;
            case R.id.itemBlack:
                baseLayout.setBackgroundColor(Color.BLACK);
                return  true;
        }
        return  false;
    }

}

package com.cookandroid.termproject;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Color;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;
import androidx.appcompat.app.AppCompatActivity;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

public class kr3Activity extends AppCompatActivity {
    LinearLayout kr3layout;
    int i=0;
    int j=0;
    TextView txOptionkr3;
    Button btnOptionkr3;
    EditText dlgEdtName;
    TextView toastText;
    View dialogView, toastView;

    MediaPlayer mediaPlayer;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.kr3);
        getSupportActionBar().setDisplayShowHomeEnabled(true);
        getSupportActionBar().setIcon(R.drawable.netflix);
        kr3layout=(LinearLayout)findViewById(R.id.kr3layout);

        Intent intent=getIntent();
        String Receive1=intent.getStringExtra("kr3series");
        TextView textView=(TextView)findViewById(R.id.txtitlekr3);
        textView.setText(Receive1);

        Button btnbackkr3=(Button)findViewById(R.id.btnbackkr3);

        btnbackkr3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                finish();
                // 정지버튼
                mediaPlayer.stop();
                // 초기화
                mediaPlayer.reset();
            }
        });

        final Button btnReadkr3;
        final EditText edtRawkr3;
        btnReadkr3=(Button)findViewById(R.id.btnReadkr3);
        edtRawkr3=(EditText)findViewById(R.id.edtRawkr3);

        btnReadkr3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                i+=1;
                if(i%2==1){
                    try{
                        InputStream inputS=getResources().openRawResource(R.raw.raw_kr3);
                        byte[] txt= new byte[inputS.available()];
                        inputS.read(txt);
                        edtRawkr3.setText(new String(txt));
                        btnReadkr3.setText("줄거리 접기");
                        inputS.close();
                    }catch (IOException e){}

                }else{
                    edtRawkr3.setText(null);
                    btnReadkr3.setText("줄거리 펼치기");
                }
            }
        });

        txOptionkr3 = (TextView) findViewById(R.id.txOpnionkr3);
        btnOptionkr3 = (Button) findViewById(R.id.btnOpinionkr3);

        btnOptionkr3.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {
                dialogView = (View) View.inflate(kr3Activity.this,
                        R.layout.kr1dialog, null);

                AlertDialog.Builder dlg = new AlertDialog.Builder(
                        kr3Activity.this);
                dlg.setTitle("한줄 평 남기기");
                dlg.setIcon(R.drawable.fficon);
                dlg.setView(dialogView);
                dlg.setPositiveButton("확인",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog,
                                                int which) {
                                dlgEdtName = (EditText) dialogView
                                        .findViewById(R.id.dlgEdt1);
                                txOptionkr3.setText(dlgEdtName.getText().toString());
                                // dlgLayout = null;
                            }
                        });

                dlg.setNegativeButton("취소",
                        new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog,
                                                int which) {
                                Toast toast = new Toast(kr3Activity.this);

                                toastView = (View) View.inflate(
                                        kr3Activity.this,
                                        R.layout.toast, null);
                                toastText = (TextView) toastView
                                        .findViewById(R.id.toastText1);
                                toastText.setText("취소했습니다");
                                toast.setView(toastView);
                                toast.show();
                            }
                        });
                dlg.show();

            }
        });

        final ArrayList<String> midList=new ArrayList<String>();
        ListView list=(ListView)findViewById(R.id.listview3kr);

        final ArrayAdapter<String> adapter =new ArrayAdapter<String>(this, android.R.layout.simple_list_item_1, midList);
        list.setAdapter(adapter);

        final EditText edtItem =(EditText) findViewById(R.id.edtItemkr3);
        Button btnAdd =(Button)findViewById(R.id.btnaddkr3);

        btnAdd.setOnClickListener(new View.OnClickListener(){
            public void onClick(View v){
                midList.add(edtItem.getText().toString());
                adapter.notifyDataSetChanged();
                edtItem.setText(null);
            }
        });

        list.setOnItemLongClickListener(new AdapterView.OnItemLongClickListener() {
            @Override
            public boolean onItemLongClick(AdapterView<?> parent, View view, int position, long id) {
                midList.remove(position);
                adapter.notifyDataSetChanged();
                return false;
            }
        });

        ImageButton kr2bigimagebutton = (ImageButton) findViewById(R.id.kr3bigimagebutton);

        kr2bigimagebutton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // MediaPlayer 객체 할당
                j+=1;
                if(j%2==1){
                    mediaPlayer = MediaPlayer.create(kr3Activity.this, R.raw.city);
                    mediaPlayer.start();}
                else{
                    // 정지버튼
                    mediaPlayer.stop();
                    // 초기화
                    mediaPlayer.reset();
                }
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
                kr3layout.setBackgroundColor(Color. WHITE);
                return true;
            case R.id.itemBlack:
                kr3layout.setBackgroundColor(Color.BLACK);
                return  true;
        }
        return  false;
    }

}
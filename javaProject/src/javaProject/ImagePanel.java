package javaProject;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.GridLayout;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class ImagePanel extends JPanel {
	String[] coffee= {"아메리카노","카페라떼","카푸치노","콜드부르/라떼","마끼야또","에스프레소","인절미 라떼","크림라떼","카페모카"}; //커피이름
	ImageIcon[] image= {new ImageIcon("image/아메리카노.jpg"),new ImageIcon("image/카페라떼.jpg"),
			            new ImageIcon("image/카푸치노.jpg"),new ImageIcon("image/콜드부르라떼.jpg"),
			            new ImageIcon("image/카라멜마끼야또.jpg"),new ImageIcon("image/에스프레소.jpg"),
			            new ImageIcon("image/인절미라떼.jpg"),	new ImageIcon("image/크림라떼.png"),
			            new ImageIcon("image/카페모카.jpg")}; //이미지추가
	
	
	public ImagePanel() {
		for(int i=0;i<coffee.length;i++) {
			JLabel imgLabel = new JLabel(image[i]);
			JLabel name=new JLabel(coffee[i]);
			
			this.setLayout(new GridLayout(3,3));  //이미지랑 coffee이름 gridlayout 가로세로 3 3
			this.setBackground(Color.CYAN);
			this.add(imgLabel);
			this.add(name);
			
		}
		
		
		
			
		
	}

}

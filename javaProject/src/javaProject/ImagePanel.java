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
	String[] coffee= {"�Ƹ޸�ī��","ī���","īǪġ��","�ݵ�θ�/��","�����߶�","����������","������ ��","ũ����","ī���ī"}; //Ŀ���̸�
	ImageIcon[] image= {new ImageIcon("image/�Ƹ޸�ī��.jpg"),new ImageIcon("image/ī���.jpg"),
			            new ImageIcon("image/īǪġ��.jpg"),new ImageIcon("image/�ݵ�θ���.jpg"),
			            new ImageIcon("image/ī��Ḷ���߶�.jpg"),new ImageIcon("image/����������.jpg"),
			            new ImageIcon("image/�����̶�.jpg"),	new ImageIcon("image/ũ����.png"),
			            new ImageIcon("image/ī���ī.jpg")}; //�̹����߰�
	
	
	public ImagePanel() {
		for(int i=0;i<coffee.length;i++) {
			JLabel imgLabel = new JLabel(image[i]);
			JLabel name=new JLabel(coffee[i]);
			
			this.setLayout(new GridLayout(3,3));  //�̹����� coffee�̸� gridlayout ���μ��� 3 3
			this.setBackground(Color.CYAN);
			this.add(imgLabel);
			this.add(name);
			
		}
		
		
		
			
		
	}

}

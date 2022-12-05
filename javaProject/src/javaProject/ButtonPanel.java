package javaProject;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

public class ButtonPanel extends JPanel {
	public JButton orderBt=new JButton("ÁÖ¹®");
	public JButton cancleBt = new JButton("Ãë¼Ò");
	public JButton acountBt = new JButton("ÇÒÀÎ");
	public JButton receipBt = new JButton("ÄíÆù");
	public JButton kakaoBt = new JButton("Ä«Ä«¿ÀÆäÀÌ");
	public JButton memberBt = new JButton("¸É¹ö½±Á¶È¸");
	
	
	public ButtonPanel() {
		orderBt.setFont(new Font("°íµñ",Font.ITALIC,30));
		cancleBt.setFont(new Font("°íµñ",Font.ITALIC,30));
		acountBt.setFont(new Font("°íµñ",Font.ITALIC,30));
		receipBt.setFont(new Font("°íµñ",Font.ITALIC,30));  //ÆùÆ®:°íµñ ±Û¾¾Å©±â 30pt
		kakaoBt.setFont(new Font("°íµñ",Font.ITALIC,23));
		memberBt.setFont(new Font("°íµñ",Font.ITALIC,23));  //ÆùÆ®:°íµñ ±Û¾¾Å©±â 23pt
		this.setBackground(Color.CYAN);
		this.setLayout(new GridLayout(2,3,10,10));  
		this.add(orderBt);
		this.add(cancleBt);
		this.add(acountBt);
		this.add(receipBt);
		this.add(kakaoBt);
		this.add(memberBt);
		
		
		
		
	}

}

package javaProject;

import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

public class ButtonPanel extends JPanel {
	public JButton orderBt=new JButton("�ֹ�");
	public JButton cancleBt = new JButton("���");
	public JButton acountBt = new JButton("����");
	public JButton receipBt = new JButton("����");
	public JButton kakaoBt = new JButton("īī������");
	public JButton memberBt = new JButton("�ɹ�����ȸ");
	
	
	public ButtonPanel() {
		orderBt.setFont(new Font("���",Font.ITALIC,30));
		cancleBt.setFont(new Font("���",Font.ITALIC,30));
		acountBt.setFont(new Font("���",Font.ITALIC,30));
		receipBt.setFont(new Font("���",Font.ITALIC,30));  //��Ʈ:��� �۾�ũ�� 30pt
		kakaoBt.setFont(new Font("���",Font.ITALIC,23));
		memberBt.setFont(new Font("���",Font.ITALIC,23));  //��Ʈ:��� �۾�ũ�� 23pt
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

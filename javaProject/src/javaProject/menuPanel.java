package javaProject;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

public class menuPanel extends JPanel {
	
	public JPanel basePanel[]=new JPanel[3];
	
	public JButton coffee1=new JButton("�Ƹ޸�ī��");
	public JButton coffee2=new JButton("����������");
	public JButton coffee3=new JButton("�����̶�");
	public JButton coffee4=new JButton("�����߶�");
	public JButton coffee5=new JButton("ī���");
	public JButton coffee6=new JButton("ī���ī");
	public JButton coffee7=new JButton("īǪġ��");
	public JButton coffee8=new JButton("�ݵ�θ���");
	public JButton coffee9= new JButton("ũ����");
	
	public menuPanel() {
		
		basePanel[0]=new JPanel(new FlowLayout());
		basePanel[0].setBackground(Color.WHITE);
		basePanel[0].add(coffee1);
		basePanel[0].add(coffee2);
		basePanel[0].add(coffee3);
		basePanel[0].add(coffee4);
		basePanel[0].add(coffee5);
		basePanel[0].add(coffee6);
		basePanel[0].add(coffee7);
		basePanel[0].add(coffee8);
		basePanel[0].add(coffee9);
		
        JTabbedPane tab=new JTabbedPane(JTabbedPane.TOP);   //ž�� tab�߰�
		
		JLabel lab=new JLabel("~~~~~~~~�غ����Դϴ�.~~~~~~~~"); // ������  tab �� ����
		Font font=new Font("�ü�",Font.BOLD,30);
		lab.setFont(font);
		
		JLabel lab1=new JLabel("~~~~~~~~�غ����̿�.~~~~~~~~"); // ����Ŀ�� tab �� ����
		Font font1=new Font("�޸տ�����",Font.BOLD,30);
		lab1.setFont(font1);
		basePanel[1]=new JPanel(); 
		basePanel[1].add(lab);
		basePanel[1].setBackground(Color.WHITE);
		basePanel[2]=new JPanel();
		basePanel[2].add(lab1);
		basePanel[2].setBackground(Color.WHITE);
		
		tab.add("Ŀ��",basePanel[0]);         //tab�̸�  Ŀ�� ������ ����Ŀ�� 
		tab.add("������",basePanel[1]);
		tab.add("����Ŀ��",basePanel[2]);
		this.add(tab);
				
   
	}
	       
}

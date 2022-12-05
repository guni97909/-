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
	
	public JButton coffee1=new JButton("아메리카노");
	public JButton coffee2=new JButton("에스프레소");
	public JButton coffee3=new JButton("인절미라떼");
	public JButton coffee4=new JButton("마끼야또");
	public JButton coffee5=new JButton("카페라떼");
	public JButton coffee6=new JButton("카페모카");
	public JButton coffee7=new JButton("카푸치노");
	public JButton coffee8=new JButton("콜드부르라떼");
	public JButton coffee9= new JButton("크림라떼");
	
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
		
        JTabbedPane tab=new JTabbedPane(JTabbedPane.TOP);   //탑에 tab추가
		
		JLabel lab=new JLabel("~~~~~~~~준비중입니다.~~~~~~~~"); // 스무디  tab 안 내용
		Font font=new Font("궁서",Font.BOLD,30);
		lab.setFont(font);
		
		JLabel lab1=new JLabel("~~~~~~~~준비중이요.~~~~~~~~"); // 베이커리 tab 안 내용
		Font font1=new Font("휴먼엑스포",Font.BOLD,30);
		lab1.setFont(font1);
		basePanel[1]=new JPanel(); 
		basePanel[1].add(lab);
		basePanel[1].setBackground(Color.WHITE);
		basePanel[2]=new JPanel();
		basePanel[2].add(lab1);
		basePanel[2].setBackground(Color.WHITE);
		
		tab.add("커피",basePanel[0]);         //tab이름  커피 스무디 베이커리 
		tab.add("스무디",basePanel[1]);
		tab.add("베이커리",basePanel[2]);
		this.add(tab);
				
   
	}
	       
}

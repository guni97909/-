package javaProject;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JOptionPane;

public class MyButtonListener implements ActionListener {
	int totalsum=0;
	public coffee cf;
	
	public MyButtonListener(coffee coffeeGUI) {
		// TODO Auto-generated constructor stub
		this.cf=coffeeGUI;
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
		
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).receipBt){
			String flag = JOptionPane.showInputDialog(null, "������ �Է����ּ���", "����!", JOptionPane.QUESTION_MESSAGE);  //����ǥ �޼����� ��
			 //�޼��� ����ǥ�޼������� �׸��� �Է�â��						
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).kakaoBt){
			JOptionPane.showMessageDialog(null, "���� �������� �ʽ��ϴ�.","�����޼���",JOptionPane.ERROR_MESSAGE);   // ���޼�������
			//�޼��� ���� �޼�������   
		}
		
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).memberBt){
			JOptionPane.showMessageDialog(null, "���� �������� �ʽ��ϴ�.","�����޼���",JOptionPane.ERROR_MESSAGE);  //���޼�������
			
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).acountBt){
			JOptionPane.showMessageDialog(null, "���� ������ �Ϸ�Ǿ����ϴ�.");
			((Order2Panel)cf.selectPanel[2]).resultTA.append("20%���εǾ� "+totalsum*0.8+" �� �Դϴ�.\n");   //���� 20%�����Ŵ
			
		}
		
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee1) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("�Ƹ޸�ī�밡  ���õǾ����ϴ�.\n");  //order2Panel textArea�� ���É�ٰ� ��. 
			totalsum=totalsum+3500;
			
			
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee2) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("���������Ұ�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+3500;
			
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee3) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("�����̶󶼰�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+5500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee4) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("�����߶ǰ�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+5000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee5) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("ī��󶼰�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+4000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee6) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("ī���ī��  ���õǾ����ϴ�.\n");
			totalsum=totalsum+4500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee7) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("īǪġ�밡  ���õǾ����ϴ�.\n");
			totalsum=totalsum+4500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee8) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("�ݵ�θ��󶼰�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+5000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee9) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("ũ���󶼰�  ���õǾ����ϴ�.\n");
			totalsum=totalsum+5500;
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).orderBt){			
		    JOptionPane.showMessageDialog(null, "�ֹ� �Ϸ� �Ǿ����ϴ�\n 10������ �ɸ��ϴ�.");  //�ֹ��Ϸ�â
			((Order2Panel)cf.selectPanel[2]).resultTA.setText("�ֹ��Ͻ� �ݾ���"+totalsum+"�� �Դϴ�.\n"); //order2Panel textArea��  �ֹ��� �ݾ� ǥ�� 
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).cancleBt){
			JOptionPane.showMessageDialog(null, "�ֹ��� ��� �Ǿ����ϴ�");  //��ҿϷ�â
			((Order2Panel)cf.selectPanel[2]).resultTA.setText(""); //������ �ؽ�Ʈ������ �ʱ�ȭ��
		}
		
	}

}

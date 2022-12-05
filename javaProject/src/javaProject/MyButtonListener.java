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
			String flag = JOptionPane.showInputDialog(null, "쿠폰을 입력해주세요", "쿠폰!", JOptionPane.QUESTION_MESSAGE);  //물음표 메세지가 뜸
			 //메세지 물을표메세지나옴 그리고 입력창뜸						
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).kakaoBt){
			JOptionPane.showMessageDialog(null, "아직 지원하지 않습니다.","에러메세지",JOptionPane.ERROR_MESSAGE);   // 경고메세지가뜸
			//메세지 위험 메세지나옴   
		}
		
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).memberBt){
			JOptionPane.showMessageDialog(null, "아직 지원하지 않습니다.","에러메세지",JOptionPane.ERROR_MESSAGE);  //경고메세지가뜸
			
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).acountBt){
			JOptionPane.showMessageDialog(null, "할인 적용이 완료되었습니다.");
			((Order2Panel)cf.selectPanel[2]).resultTA.append("20%할인되어 "+totalsum*0.8+" 원 입니다.\n");   //할인 20%적용시킴
			
		}
		
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee1) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("아메리카노가  선택되었습니다.\n");  //order2Panel textArea에 선택됬다고 뜸. 
			totalsum=totalsum+3500;
			
			
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee2) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("에스프레소가  선택되었습니다.\n");
			totalsum=totalsum+3500;
			
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee3) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("인절미라떼가  선택되었습니다.\n");
			totalsum=totalsum+5500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee4) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("마끼야또가  선택되었습니다.\n");
			totalsum=totalsum+5000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee5) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("카페라떼가  선택되었습니다.\n");
			totalsum=totalsum+4000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee6) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("카페모카가  선택되었습니다.\n");
			totalsum=totalsum+4500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee7) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("카푸치노가  선택되었습니다.\n");
			totalsum=totalsum+4500;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee8) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("콜드부르라떼가  선택되었습니다.\n");
			totalsum=totalsum+5000;
		}
		if(e.getSource()==((menuPanel)cf.basePanel[0]).coffee9) {
			((Order2Panel)cf.selectPanel[2]).resultTA.append("크림라떼가  선택되었습니다.\n");
			totalsum=totalsum+5500;
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).orderBt){			
		    JOptionPane.showMessageDialog(null, "주문 완료 되었습니다\n 10분정도 걸립니다.");  //주문완료창
			((Order2Panel)cf.selectPanel[2]).resultTA.setText("주문하신 금액은"+totalsum+"원 입니다.\n"); //order2Panel textArea에  주문한 금액 표시 
		}
		
		if(e.getSource()==((ButtonPanel)cf.selectPanel[3]).cancleBt){
			JOptionPane.showMessageDialog(null, "주문이 취소 되었습니다");  //취소완료창
			((Order2Panel)cf.selectPanel[2]).resultTA.setText(""); //누르면 텍스트에리아 초기화됨
		}
		
	}

}

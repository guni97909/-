package javaProject;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

public class MyDBActionListener implements ActionListener {
	

	public coffee cf;
	public Vector orRow;
	
	public MyDBActionListener(coffee coffeeDBGUI) {
		// TODO Auto-generated constructor stub
		this.cf = coffeeDBGUI;
	}
	
	

	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee1) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='아메리카노'"); //coffee테이블에서 아메리카노 정보를 reload 해옴 
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee2) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='에스프레소'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee3) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='인절미라떼'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee4) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='마끼야또'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee5) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='카페라떼'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee6) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='카페모카'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee7) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='카푸치노'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee8) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='콜드부르라떼'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() ==((menuPanel)cf.basePanel[0]).coffee9) {
			try {
				Statement stmt = cf.con.createStatement();
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='크림라떼'");
				while (reload_rs.next()) {							
					String menu = reload_rs.getString("menu");
					String number = reload_rs.getString("number");
					int price = reload_rs.getInt("price");
					cf.orderRow = new Vector<String>();
					cf.orderRow.addElement(menu);
					cf.orderRow.addElement(number);
					cf.orderRow.addElement(Integer.toString(price));
					
					((OrderPanel)cf.selectPanel[0]).model.addRow(cf.orderRow);
					
					
				}
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				System.out.println("ERR Reload");
				e1.printStackTrace();
			}
			
			
		}
		
		if (e.getSource() == ((ButtonPanel)cf.selectPanel[3]).cancleBt || 
				e.getSource() == ((ButtonPanel)cf.selectPanel[3]).orderBt) {   //취소버튼 혹은 주문버튼을 누르면 jtable내용 제거됨
			int count = ((OrderPanel)cf.selectPanel[0]).table.getRowCount();
			
			for (int i=0; i< count; i++) {
				((OrderPanel)cf.selectPanel[0]).model.removeRow(0);
			}
			((OrderPanel)cf.selectPanel[0]).table.repaint();
		}
		
		
		
		
		
	}





	 
	 
	 
	 
	 
	 
}
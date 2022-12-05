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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='�Ƹ޸�ī��'"); //coffee���̺��� �Ƹ޸�ī�� ������ reload �ؿ� 
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='����������'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='�����̶�'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='�����߶�'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='ī���'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='ī���ī'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='īǪġ��'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='�ݵ�θ���'");
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
				ResultSet reload_rs = stmt.executeQuery("select * from coffee where menu='ũ����'");
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
				e.getSource() == ((ButtonPanel)cf.selectPanel[3]).orderBt) {   //��ҹ�ư Ȥ�� �ֹ���ư�� ������ jtable���� ���ŵ�
			int count = ((OrderPanel)cf.selectPanel[0]).table.getRowCount();
			
			for (int i=0; i< count; i++) {
				((OrderPanel)cf.selectPanel[0]).model.removeRow(0);
			}
			((OrderPanel)cf.selectPanel[0]).table.repaint();
		}
		
		
		
		
		
	}





	 
	 
	 
	 
	 
	 
}
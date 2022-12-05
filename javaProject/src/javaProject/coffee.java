package javaProject;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Vector;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class coffee extends JFrame {
	Connection con = null;
	Statement stmt = null;
	ResultSet rs = null;
	PreparedStatement pstmt;
	Vector<String> orderRow = new Vector<String>();
	
	public JPanel basePanel[] = new JPanel[2];  
	public JPanel selectPanel[] = new JPanel[4];
	public MyButtonListener mb1;
	
	
	
	
	
	
		 
		   public coffee()  {
			   con = makeConnection();
			   

		      this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		      this.setTitle("Hollys coffie");
		      
		      basePanel[0] = new menuPanel();
		      basePanel[0].setBackground(Color.BLACK);
		      basePanel[1] = new JPanel(new BorderLayout());
		      
		      selectPanel[0] = new OrderPanel(this);
		      selectPanel[1] = new ImagePanel();
		      selectPanel[2] = new Order2Panel();
		      selectPanel[3] = new ButtonPanel();
		      
		      
		      
		      
		      basePanel[1].setLayout(new GridLayout(2,2)); 
		      basePanel[1].add(selectPanel[0]);
		      basePanel[1].add(selectPanel[1]);
		      basePanel[1].add(selectPanel[2]);
		      basePanel[1].add(selectPanel[3]);
		      
		      mb1= new MyButtonListener(this);
		      ((ButtonPanel)selectPanel[3]).orderBt.addActionListener(mb1);
		      ((ButtonPanel)selectPanel[3]).cancleBt.addActionListener(mb1);
		      ((ButtonPanel)selectPanel[3]).kakaoBt.addActionListener(mb1);
		      ((ButtonPanel)selectPanel[3]).memberBt.addActionListener(mb1);
		      ((ButtonPanel)selectPanel[3]).acountBt.addActionListener(mb1);
		      ((ButtonPanel)selectPanel[3]).receipBt.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee1.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee2.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee3.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee4.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee5.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee6.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee7.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee8.addActionListener(mb1);
		      ((menuPanel)basePanel[0]).coffee9.addActionListener(mb1);
		      
		      
		      
		      MyDBActionListener MDBAL = new MyDBActionListener(this);
		      ((menuPanel)basePanel[0]).coffee1.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee2.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee3.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee4.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee5.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee6.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee7.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee8.addActionListener(MDBAL);
		      ((menuPanel)basePanel[0]).coffee9.addActionListener(MDBAL);
		      ((ButtonPanel)selectPanel[3]).cancleBt.addActionListener(MDBAL);
		      ((ButtonPanel)selectPanel[3]).orderBt.addActionListener(MDBAL);
		     
		      
		      
		      
		      
		      try {
					stmt = con.createStatement();
					rs = stmt.executeQuery("select * from coffee");
					
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		      

		     		      
		      this.setLayout(new BorderLayout());
		      this.add(basePanel[0], BorderLayout.NORTH);   
		      this.add(basePanel[1], BorderLayout.CENTER);  //GridLayout 베이스페널1
		      
		      this.setSize(1000, 800);
		      this.setVisible(true);
		   }
		   

		public Connection makeConnection() {
			// DB명 : coffee_db
			// Table명 : coffee
			// Field : (1) menu varchar(10)
			// (2) number varchar(4)
			// (3) price int
			
				
				
				Connection con = null;
				String url ="jdbc:mysql://localhost:3306/coffee_db?characterEncoding=UTF-8&serverTimezone=UTC";
				String user ="root";
				String password ="1234";
				
				try {
					Class.forName("com.mysql.cj.jdbc.Driver");
					System.out.println("JDBC 적재 성공...");
					con = DriverManager.getConnection(url, user, password);
					System.out.println("DB 연결 성공...");
					
				} catch (ClassNotFoundException e) {
					// TODO Auto-generated catch block
					System.out.println("JDBC 적재 오류...");
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					System.out.println("DB 연결 실패...");
					e.printStackTrace();
				}
				
				return con;
			}

		public static void main(String[] args)  {
				// TODO Auto-generated method stub
				new coffee();
			}


		

}
